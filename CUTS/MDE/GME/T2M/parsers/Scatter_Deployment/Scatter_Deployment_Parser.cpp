// $Id$

#include "stdafx.h"
#include "Scatter_Deployment_Parser.h"
#include "Model_Cache_T.h"
#include "Model_Cache_Manager.h"

#include "game/Project.h"
#include "game/Connection.h"
#include "game/MetaFCO.h"

#include "boost/bind.hpp"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "boost/spirit/error_handling/exceptions.hpp"
#include "boost/spirit/actor.hpp"

#include "ace/Log_Msg.h"

#include <iostream>

namespace actor
{
//=============================================================================
/**
 * @struct find_instance
 */
//=============================================================================

template <typename iterator_t>
struct find_instance
{
  find_instance (GME::Project & project, GME::Model & instance)
    : project_ (project),
      instance_ (instance)
  {

  }

  void operator () (iterator_t const & first, iterator_t const & last) const
  {
    // Get the name of the instance.
    std::string name (first, last);

    ACE_DEBUG ((LM_DEBUG,
                "%M - %T - searching for component instance named %s\n",
                name.c_str ()));

    if (!this->instance_.is_nil ())
      this->instance_.release ();

    // Get the cache of the component instance elements.
    ACE_DEBUG ((LM_DEBUG,
                "%M - %T - looking in model cache\n"));

    typedef std::map <std::string, GME::Model> Model_Cache;
    Model_Cache & inst_cache = MODEL_CACHE (GME::Model, "Component");

    Model_Cache::iterator inst_iter = inst_cache.find (name);

    if (inst_iter != inst_cache.end ())
    {
      // Save the located component instance.
      ACE_DEBUG ((LM_DEBUG,
                  "%M - %T - found component instance in model cache\n"));
      this->instance_ = inst_iter->second;
    }
    else
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%M - %T - component instance not found in model cache; "
                  "searching entire model for %s\n",
                  name.c_str ()));

      // We need to search the model for the the component instance.
      // First, convert the string name to a path, if applicable.
      std::string path = name;
      std::replace (path.begin (), path.end (), '.', '/');

      // Get the root folder to the project.
      GME::Folder root_folder = this->project_.root_folder ();

      // Get all the implementation folders from the project.
      typedef GME::Collection_T <GME::Folder> Folder_Set;
      Folder_Set impls_folders;

      root_folder.folders ("ComponentImplementations", impls_folders);

      Folder_Set::const_iterator
        impl_folder = impls_folders.begin (),
        impl_folder_end = impls_folders.end ();

      GME::Object object;

      for ( ; impl_folder != impl_folder_end; impl_folder ++)
      {
        ACE_DEBUG ((LM_DEBUG,
                    "%T - %M - looking for component instance [%s] in %s\n",
                    path.c_str (),
                    impl_folder->path ("/").c_str ()));

        // Look for the instance in this folder.
        object = impl_folder->find_object_by_path (path);

        // Exit the loop if we have found the object.
        if (!object.is_nil ())
        {
          this->instance_ = GME::Model::_narrow (object);
          inst_cache.insert (std::make_pair (name, this->instance_));
          break;
        }
      }

      // Release the resources if we could not find the instance.
      if (impl_folder == impl_folder_end)
        this->instance_.release ();
    }
  }

private:
  GME::Project & project_;

  GME::Model & instance_;
};

//=============================================================================
/**
 * @struct find_deployment
 *
 * Locates the deployment with the specified name in the project.
 */
//=============================================================================

template <typename iterator_t>
struct find_deployment
{
  find_deployment (GME::Folder & folder,
                   GME::Model & deployment)
    : folder_ (folder),
      deployment_ (deployment)
  {
    // Initialize the cache w/ the known deployments from the
    // target folder.

    typedef GME::Collection_T <GME::Model> Model_Set;
    Model_Set deployments;

    if (this->folder_.models ("DeploymentPlan", deployments))
    {
      // Get the <DeploymentPlan> cache.
      typedef std::map <std::string, GME::Model> Model_Cache;
      Model_Cache & dp_cache = MODEL_CACHE (GME::Model, "DeploymentPlan");

      Model_Set::iterator
        iter = deployments.begin (), iter_end = deployments.end ();

      // Insert the deployment plans into the cache.
      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - saving %d deployment plan(s) in %s to cache\n",
                  deployments.size (),
                  this->folder_.path ("/", true).c_str ()));

      for ( ; iter != iter_end; iter ++)
        dp_cache.insert (std::make_pair (iter->name (), *iter));
    }
  }

  void operator () (iterator_t const & start, iterator_t const & end) const
  {
    // Save the name of the deployment of interest.
    std::string name (start, end);

    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - looking for deployment plan named %s\n",
                name.c_str ()));

    // Reset the deployment plan.
    if (!this->deployment_.is_nil ())
      this->deployment_.release ();

    // Clear the cache for the collocation groups for the
    // new deployment.
    MODEL_CACHE (GME::Set, "CollocationGroup").clear ();

    // Search for the deployment plan in the cache.
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - searching the deployment plan model cache\n"));

    typedef std::map <std::string, GME::Model> Model_Cache;
    Model_Cache & dp_cache = MODEL_CACHE (GME::Model, "DeploymentPlan");
    Model_Cache::iterator result = dp_cache.find (name);

    if (result != dp_cache.end ())
      this->deployment_ = result->second;

    if (this->deployment_.is_nil ())
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - %s deployment plan not found; create a new one\n",
                  name.c_str ()));

      // We need to create a new deployment since the one of
      // interest does not exist.
      this->deployment_ = GME::Model::_create ("DeploymentPlan", this->folder_);
      this->deployment_.name (name);

      // Save the plan into the cache.
      dp_cache.insert (std::make_pair (name, this->deployment_));
    }
    else
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - found deployment plan in model cache\n",
                  name.c_str ()));

    }
  }

private:
  /// The parent folder of the deployment.
  GME::Folder & folder_;

  /// The output for the target deployment.
  GME::Model & deployment_;
};

//=============================================================================
/**
 * @struct find_host
 *
 * Locate the specified host in the PICML model. Right now, we assume
 * there is only one collocation group per host. If we cannot find
 * the host in the current deployment, we add it and assign it a default
 * collocation group.
 */
//=============================================================================

template <typename iterator_t>
struct find_host
{
  find_host (GME::Project & project,
             GME::Model & deployment,
             GME::Set & group)
    : project_ (project),
      deployment_ (deployment),
      group_ (group)
  {

  }

  void operator () (iterator_t const & start, iterator_t const & end) const
  {
    // Save the name of the host.
    std::string name (start, end);

    if (!this->group_.is_nil ())
      this->group_.release ();

    // Get the element cache for the collocation group elements.
    typedef std::map <std::string, GME::Set> Set_Cache;
    Set_Cache & group_cache = MODEL_CACHE (GME::Set, "CollocationGroup");

    // Search for the collocation group in the cache.
    Set_Cache::iterator group_result = group_cache.find (name);

    if (group_result != group_cache.end ())
    {
      this->group_ = group_result->second;
      return;
    }

    // 1. Since we did not find the collocation group. Look in
    // the current deployment for the node with the specified name.
    typedef GME::Collection_T <GME::Reference> Reference_Set;

    Reference_Set nodes;
    Reference_Set::value_type target_node;

    if (this->deployment_.references ("NodeReference", nodes))
    {
      Reference_Set::iterator result;

      // Look for reference to host with specified name.
      result =
        std::find_if (nodes.begin (),
                      nodes.end (),
                      boost::bind (std::equal_to <std::string> (),
                        name,
                        boost::bind (&GME::FCO::name,
                                     boost::bind (&GME::Reference::refers_to,
                                                  _1))));

      // Save the reference to the target host that we found.
      if (result != nodes.end ())
        target_node = *result;
    }

    // 2. Since we did not find the node in the current deployment,
    // we need to add it. So, locate the node in the project.
    if (target_node.is_nil ())
    {
      // Get the element cache for the Node elements.
      typedef std::map <std::string, GME::Model> Model_Cache;
      Model_Cache & node_cache = MODEL_CACHE (GME::Model, "Node");

      // Look for the target node in the cache.
      Model_Cache::iterator node_iter = node_cache.find (name);
      Model_Cache::mapped_type node;

      if (node_iter != node_cache.end ())
      {
        // We found it, so we can save it and quit.
        node = node_iter->second;
      }
      else
      {
        // We have to search the entire project for the node. Start
        // by getting the root folder. We should be using GME::Filter
        // to simplify the search.
        GME::Folder root_folder = this->project_.root_folder ();

        // Get all the implementation folders from the project.
        typedef GME::Collection_T <GME::Folder> Folder_Set;
        Folder_Set target_folders;

        root_folder.folders ("Targets", target_folders);

        Folder_Set::const_iterator
          target_folder = target_folders.begin (),
          target_folder_end = target_folders.end ();

        typedef GME::Collection_T <GME::Model> Model_Set;
        Model_Set domains;

        for ( ; target_folder != target_folder_end; target_folder ++)
        {
          // Get all the nodes in this domain.
          if (target_folder->models ("Domain", domains))
          {
            Model_Set::iterator
              domain_iter = domains.begin (), domain_iter_end = domains.end ();

            for ( ; domain_iter != domain_iter_end; domain_iter ++)
            {
              Model_Set nodes;
              domain_iter->models ("Node", nodes);

              // Look for the node in this domain.
              Model_Set::iterator result =
                std::find_if (nodes.begin (),
                              nodes.end (),
                              boost::bind (std::equal_to <std::string> (),
                                name,
                                boost::bind (&Model_Set::value_type::name,
                                            _1)));

              if (result != nodes.end ())
              {
                // We can stop if we have found the node.
                node = *result;

                // Save the node in the cache.
                node_cache.insert (std::make_pair (name, node));
                break;
              }
            }
          }

          // Exit the loop if we have found the node.
          if (!node.is_nil ())
            break;
        }
      }

      if (!node.is_nil ())
      {
        // Create a reference to this node in the deployment. Set the
        // name of the node reference and is reference.
        target_node = GME::Reference::_create ("NodeReference",
                                               this->deployment_);

        target_node.name (name);
        target_node.refers_to (node);
      }
    }

    // 3. Get the collocation group for this host. Right now, we
    // take the first collocation group that we find.
    if (!target_node.is_nil ())
    {
      // Get the default collocation group for this node.
      GME::ConnectionPoints points;

      if (target_node.in_connection_points (points) == 0)
      {
        // Create the default collocation group.
        this->group_ =
          GME::Set::_create ("CollocationGroup", this->deployment_);

        this->group_.name (name + "_DefaultGroup");

        // Create a connection between the group and its host.
        GME::Connection::_create ("InstanceMapping",
                                  this->deployment_,
                                  this->group_,
                                  target_node);
      }
      else
      {
        // Get the first collocation group for this connection.
        GME::Connection connection;
        GME::ConnectionPoints::iterator
          iter = points.begin (), iter_end = points.end ();

        for ( ; iter != iter_end; iter ++)
        {
          if (iter->item ().role () == "dst" &&
              iter->item ().owner ().meta ().name () == "InstanceMapping")
          {
            connection = iter->item ().owner ();
            break;
          }
        }

        // Save the target group for the deployment.
        if (!connection.is_nil ())
        {
          connection.connection_points (points);
          this->group_ = GME::Set::_narrow (points["src"].target ());
        }
        else
          this->group_.release ();
      }
    }
    else
    {
      this->group_.release ();
    }

    // Save the group into the cache.
    if (!this-group_.is_nil ())
      group_cache.insert (std::make_pair (name, this->group_));
  }

private:
  GME::Project & project_;

  GME::Model & deployment_;

  GME::Set & group_;
};

//=============================================================================
/**
 * @struct deploy_instance
 *
 * Deploys an instance onto a host in the PICML model. This requires
 * creating a reference to the instance, then adding it to the specified
 * collocation group.
 */
//=============================================================================

struct deploy_instance
{
  deploy_instance (GME::Set & collocation_group,
                   const GME::Model & instance)
    : group_ (collocation_group),
      instance_ (instance)
  {

  }

  void operator () (char) const
  {
    // Get the parent of the deployment.
    GME::Model deployment = GME::Model::_narrow (this->group_.parent ());

    // Get all the component references in this deployment.
    typedef GME::Collection_T <GME::Reference> Reference_Set;
    Reference_Set component_refs;

    deployment.references ("ComponentRef", component_refs);

    // Search the current component references and validate if
    // the instance has already been deployed.
    Reference_Set::value_type component_ref;
    Reference_Set::iterator
      iter = component_refs.begin (), iter_end = component_refs.end ();

    for ( ; iter != iter_end; iter ++)
    {
      if (iter->refers_to () == this->instance_)
        component_ref = *iter;
    }

    if (component_ref.is_nil ())
    {
      // Create a new deployment reference in the deployment model.
      component_ref = GME::Reference::_create ("ComponentRef", deployment);

      // Reference the target instance.
      component_ref.name (this->instance_.name ());
      component_ref.refers_to (this->instance_);
    }

    // Validate the group does not contain the component referece.
    if (!this->group_.contains (component_ref))
      this->group_.insert (component_ref);
  }

private:
  GME::Set & group_;

  const GME::Model & instance_;
};

} // namespace actor

//=============================================================================
/**
 * @class CUTS_Scatter_To_Picml_Parser
 */
//=============================================================================

struct CUTS_Scatter_To_Picml_Parser :
  public boost::spirit::grammar <CUTS_Scatter_To_Picml_Parser>
{
  /**
   * Initializing constructor.
   *
   * @param[in]       project               Target project.
   * @param[in]       deployment_folder     Target deployment folder.
   * @param[in]       options               Application options.
   */
  CUTS_Scatter_To_Picml_Parser (GME::Project & project,
                                GME::Folder & deployment_folder)
    : project_ (project),
      deployment_folder_ (deployment_folder)
  {

  }

  template <typename ScannerT>
  struct definition
  {
    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */
    definition (CUTS_Scatter_To_Picml_Parser const & self)
    {
      // Type definition of the iterator type.
      typedef typename ScannerT::iterator_t iterator_t;

      this->special_chars_ =
        boost::spirit::ch_p (':') |
        boost::spirit::ch_p (';') |
        boost::spirit::ch_p ('{') |
        boost::spirit::ch_p ('}');

      this->identifier_ =
        boost::spirit::lexeme_d [*(boost::spirit::alnum_p | '_')];

      this->component_ =
        boost::spirit::lexeme_d [*(boost::spirit::graph_p - (boost::spirit::ch_p (':') | ';' | '{' | '}'))];

      this->host_ =
        boost::spirit::lexeme_d [*(boost::spirit::graph_p - (boost::spirit::ch_p (':') | ';' | '{' | '}'))];

      this->deployment_member_ =
        this->component_[
          actor::find_instance <iterator_t>  (self.project_,
                                              this->instance_)] >>
        ':' >>
        this->host_[
          actor::find_host <iterator_t> (self.project_,
                                         this->picml_deployment_,
                                         this->picml_host_group_)] >>
        boost::spirit::ch_p (';')[
          actor::deploy_instance (this->picml_host_group_, this->instance_)] >>
        *(boost::spirit::space_p);

      this->deployment_list_ = *(this->deployment_member_);

      this->deployment_ =
        this->identifier_[
          actor::find_deployment <iterator_t> (self.deployment_folder_,
                                               this->picml_deployment_)] >>
        boost::spirit::confix_p ('{', this->deployment_list_, '}');

      this->start_ = this->deployment_list_;
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->start_;
    }

  private:
    /// @{
    /// Temporary placeholder for the component's name.
    GME::Model instance_;

    /// Temporary placeholder for the host's name
    GME::Set picml_host_group_;

    /// The target PICML deployment model.
    GME::Model picml_deployment_;
    /// @}

    /// @{
    boost::spirit::rule <ScannerT> special_chars_;

    boost::spirit::rule <ScannerT> identifier_;

    /// rule: component_
    boost::spirit::rule <ScannerT> component_;

    /// rule: host_
    boost::spirit::rule <ScannerT> host_;

    /// rule: deployment_member_
    boost::spirit::rule <ScannerT> deployment_member_;

    /// rule: deployment_
    boost::spirit::rule <ScannerT> deployment_;

    /// rule: deployment_list_
    boost::spirit::rule <ScannerT> deployment_list_;

    /// rule: start_
    boost::spirit::rule <ScannerT> start_;
    /// @}

  private:
    definition (const definition &);
    const definition & operator = (const definition &);
  };

  /// The target GME project.
  GME::Project & project_;

  /// The target (defualt) deployment folder.
  GME::Folder & deployment_folder_;
};

///////////////////////////////////////////////////////////////////////////////
// class Scatter_Deployment_Parser

//
// Scatter_Deployment_Parser
//
Scatter_Deployment_Parser::Scatter_Deployment_Parser (void)
{

}

//
// ~Scatter_Deployment_Parser
//
Scatter_Deployment_Parser::~Scatter_Deployment_Parser (void)
{

}

//
// get_target_deployment_folder
//
void get_target_deployment_folder (GME::Project & project,
                                   GME::Folder & folder,
                                   const std::string & name)
{
  GME::Folder root = project.root_folder ();

  typedef GME::Collection_T <GME::Folder> Folder_Set;
  Folder_Set folders;

  if (root.folders ("DeploymentPlans", folders))
  {
    // Perform a search of the current folders by name.
    Folder_Set::iterator result =
      std::find_if (folders.begin (),
                    folders.end (),
                    boost::bind (std::equal_to <std::string> (),
                                 name,
                                 boost::bind (&Folder_Set::value_type::name,
                                              _1)));

    if (result != folders.end ())
    {
      // Since we found the folder, we can leave.
      folder = *result;
      return;
    }
  }

  // Create a new folder with the specified name.
  folder = GME::Folder::_create ("DeploymentPlans", root);
  folder.name (name);
}

//
// parse
//
bool Scatter_Deployment_Parser::
parse (const std::string & filename, GME::Object & parent)
{
  typedef char char_t;
  typedef boost::spirit::file_iterator <char_t> iterator_t;

  // Get an iterator to the beginning of the file.
  iterator_t first (filename);

  if (!first)
    return false;

  // Get an iterator to the end of the file.
  iterator_t last = first.make_end ();

  // Locate the target (default) deployment folder.
  GME::Folder target_folder = GME::Folder::_narrow (parent);
  GME::Project project = parent.project ();

  // Parse the select file.
  CUTS_Scatter_To_Picml_Parser parser (project, target_folder);

  boost::spirit::parse_info <iterator_t> result =
    boost::spirit::parse (first,
                          last,
                          parser >> boost::spirit::end_p,
                          boost::spirit::space_p);

  // We need to clear the cache.
  MODEL_CACHE_MANAGER ()->clear_all ();

  return result.full;
}

GME_T2M_CREATE_PARSER_IMPLEMENT (Scatter_Deployment_Parser);
