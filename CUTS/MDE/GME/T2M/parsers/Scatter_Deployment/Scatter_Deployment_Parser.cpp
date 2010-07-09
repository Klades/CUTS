// $Id$

#include "stdafx.h"
#include "Scatter_Deployment_Parser.h"

#include "boost/bind.hpp"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "boost/spirit/error_handling/exceptions.hpp"
#include "boost/spirit/actor.hpp"
#include <iostream>

namespace actor
{
  void normalize (std::string & name)
  {
    std::remove_if (name.begin (),
                    name.end (),
                    boost::bind (std::equal_to <int> (),
                                 0,
                                 boost::bind (&isalnum, _1)));
  }

/**
 * @struct find_instance
 */
struct find_instance
{
  find_instance (const GAME::Model & assembly, GAME::FCO & instance)
    : assembly_ (assembly),
      instance_ (instance)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT first, IteratorT last) const
  {
    // Get the name of the instance.
    std::string name (first, last);

    GAME::Object obj = this->assembly_.find_object_by_path (name);

    if (obj)
      this->instance_ = GAME::FCO::_narrow (obj);
    else
      this->instance_.release ();
  }

private:
  const GAME::Model & assembly_;

  GAME::FCO & instance_;
};

/**
 * @struct deploy_instance
 *
 * Deploys an instance onto a host in the PICML model. This requires
 * creating a reference to the instance, then adding it to the specified
 * collocation group.
 */
struct deploy_instance
{
  deploy_instance (GAME::Model & deployment,
                   const std::map <std::string, GAME::Set> & groups,
                   const GAME::FCO & instance)
    : deployment_ (deployment),
      groups_ (groups),
      instance_ (instance)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    if (!this->instance_.is_nil ())
    {
      GAME::Reference ref;
      std::string metaname = this->instance_.meta ().name ();

      if (metaname == "Component")
      {
        ref = GAME::Reference::_create (this->deployment_, "ComponentRef");
      }
      else if (metaname == "ComponentAssembly")
      {
        ref = GAME::Reference::_create (this->deployment_, "ComponentAssemblyReference");
      }

      if (ref)
      {
        // Initialize the component reference.
        ref.name (this->instance_.name ());
        ref.refers_to (this->instance_);

        // Get the target collocation group.
        std::string name (begin, end);
        normalize (name);

        groups_type::const_iterator iter = this->groups_.find (name);

        // Insert the component into the collocation group.
        if (iter != this->groups_.end ())
        {
          GAME::Set group = iter->second;
          group.insert (ref);
        }
      }
    }
  }

private:
  GAME::Model & deployment_;

  typedef std::map <std::string, GAME::Set> groups_type;

  const groups_type & groups_;

  const GAME::FCO & instance_;
};

/**
 * @class new_node
 */
class new_node
{
public:
  new_node (GAME::Model & domain, std::map <std::string, GAME::Model> & nodes)
    : domain_ (domain),
      nodes_ (nodes)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    // Get the name of the node and normalize it.
    std::string name (begin, end);
    normalize (name);

    GAME::Object obj;

    if (this->domain_)
    {
      obj = this->domain_.find_object_by_path (name);

      if (!obj)
      {
        obj = GAME::Model::_create (this->domain_, "Node");
        obj.name (name);
      }
    }
    else
    {
      GAME::Project project = this->domain_.project ();
      obj = project.object_by_path (name);
    }

    if (obj)
    {
      GAME::Model node = GAME::Model::_narrow (obj);
      this->nodes_.insert (std::make_pair (name, node));
    }
  }

private:
  GAME::Model & domain_;

  std::map <std::string, GAME::Model> & nodes_;
};

} // namespace actor

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Scatter_Domain_Parser

struct CUTS_Scatter_Domain_Parser :
  public boost::spirit::grammar <CUTS_Scatter_Domain_Parser>
{
  /**
   * Initializing constructor.
   *
   * @param[in]       project               Target project.
   * @param[in]       deployment_folder     Target deployment folder.
   * @param[in]       options               Application options.
   */
  CUTS_Scatter_Domain_Parser (GAME::Model & domain,
                              std::map <std::string, GAME::Model> & nodes)
    : domain_ (domain),
      nodes_ (nodes)
  {
    if (domain)
    {
      // Get all the elements in the domain.
      std::vector <GAME::Model> temp;
      domain.children ("Node", temp);

      // Let's make our life easy right now and delete all nodes in
      // the domain. This way, we are starting from scratch each time.
      std::for_each (temp.begin (),
                     temp.end (),
                     boost::bind (&GAME::Object::destroy, _1));
    }
  }

  template <typename ScannerT>
  struct definition
  {
    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */
    definition (CUTS_Scatter_Domain_Parser const & self)
    {
      // Type definition of the iterator type.
      typedef typename ScannerT::iterator_t iterator_t;

      this->component_ =
        boost::spirit::lexeme_d [
          *(boost::spirit::graph_p - boost::spirit::ch_p (':'))];

      this->host_ =
        boost::spirit::lexeme_d [*(boost::spirit::graph_p)];

      this->deployment_member_ =
        this->component_ >> ':' >>
        this->host_[actor::new_node (self.domain_, self.nodes_)] >>
        *(boost::spirit::space_p);

      this->deployment_list_ = *(this->deployment_member_);
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->deployment_list_;
    }

  private:
    /// @{
    /// rule: component_
    boost::spirit::rule <ScannerT> component_;

    /// rule: host_
    boost::spirit::rule <ScannerT> host_;

    /// rule: deployment_member_
    boost::spirit::rule <ScannerT> deployment_member_;


    /// rule: deployment_list_
    boost::spirit::rule <ScannerT> deployment_list_;

    /// @}

  private:
    definition (const definition &);
    const definition & operator = (const definition &);
  };

  /// The target GAME project.
  GAME::Model & domain_;

  /// Collection of nodes in the domain.
  std::map <std::string, GAME::Model> & nodes_;
};

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Scatter_To_Picml_Parser

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
  CUTS_Scatter_To_Picml_Parser (GAME::Model & deployment,
                                const GAME::Model & assembly,
                                const std::map <std::string, GAME::Set> & groups)
    : deployment_ (deployment),
      assembly_ (assembly),
      groups_ (groups)
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

      this->component_ =
        boost::spirit::lexeme_d [
          *(boost::spirit::graph_p - boost::spirit::ch_p (':'))];

      this->host_ =
        boost::spirit::lexeme_d [*(boost::spirit::graph_p)];

      this->deployment_member_ =
        this->component_[actor::find_instance (self.assembly_, this->instance_)]
        >> ':' >>
          this->host_[actor::deploy_instance (self.deployment_, self.groups_, this->instance_)] >>
        *(boost::spirit::space_p);

      this->deployment_list_ = *(this->deployment_member_);
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->deployment_list_;
    }

  private:
    /// @{
    GAME::FCO instance_;
    /// @}

    /// @{
    /// rule: component_
    boost::spirit::rule <ScannerT> component_;

    /// rule: host_
    boost::spirit::rule <ScannerT> host_;

    /// rule: deployment_member_
    boost::spirit::rule <ScannerT> deployment_member_;

    /// rule: deployment_list_
    boost::spirit::rule <ScannerT> deployment_list_;
    /// @}

  private:
    definition (const definition &);
    const definition & operator = (const definition &);
  };

private:
  GAME::Model & deployment_;

  const GAME::Model & assembly_;

  const std::map <std::string, GAME::Set> & groups_;
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
// parse
//
bool Scatter_Deployment_Parser::
parse (const std::string & filename, GAME::Object & parent)
{
  return this->parse (filename, parent, GAME::Model (), GAME::Model ());
}

//
// parse
//
bool Scatter_Deployment_Parser::parse (const std::string & filename,
                                       GAME::Object & parent,
                                       const GAME::Model & assembly,
                                       GAME::Model & domain)
{
  typedef char char_t;
  typedef boost::spirit::file_iterator <char_t> iterator_t;

  // Get an iterator to the beginning of the file.
  iterator_t first (filename);

  if (!first)
    return false;

  // Get an iterator to the end of the file.
  iterator_t last = first.make_end ();

  boost::spirit::parse_info <iterator_t> result;

  // Preprocess the deployment. This will ensure we have the correct
  // node in our domain for the deployment.
  std::map <std::string, GAME::Model> nodes;
  CUTS_Scatter_Domain_Parser domain_parser (domain, nodes);

  result = boost::spirit::parse (first,
                                 last,
                                 domain_parser >> boost::spirit::end_p,
                                 boost::spirit::space_p);

  // Extract the the deployment model.
  GAME::Model deployment = GAME::Model::_narrow (parent);

  // Clear the deployment model.
  this->clear_deployment (deployment);

  // Install the node in the deployment.
  std::map <std::string, GAME::Set> groups;
  this->insert_nodes_in_deployment (deployment, nodes, groups);

  // Process the deployment. This will install the components in
  // the correct nodes.
  CUTS_Scatter_To_Picml_Parser parser (deployment, assembly, groups);

  result = boost::spirit::parse (first,
                                 last,
                                 parser >> boost::spirit::end_p,
                                 boost::spirit::space_p);

  return result.full;
}

//
// clear_deployment
//
void Scatter_Deployment_Parser::
clear_deployment (GAME::Model & deployment)
{
  // Delete all the component references.
  std::vector <GAME::Reference> refs;
  deployment.children ("ComponentRef", refs);

  std::for_each (refs.begin (),
                 refs.end (),
                 boost::bind (&GAME::Reference::destroy, _1));

  deployment.children ("ComponentAssemblyReference", refs);

  std::for_each (refs.begin (),
                 refs.end (),
                 boost::bind (&GAME::Reference::destroy, _1));

  // Delete all the collocation groups.
  std::vector <GAME::Set> groups;
  deployment.children ("CollocationGroup", groups);

  std::for_each (groups.begin (),
                 groups.end (),
                 boost::bind (&GAME::Set::destroy, _1));

  // Delete all the node references.
  deployment.children ("NodeReference", refs);

  std::for_each (refs.begin (),
                 refs.end (),
                 boost::bind (&GAME::Reference::destroy, _1));
}

//
// insert_nodes_in_deployment
//
void Scatter_Deployment_Parser::
insert_nodes_in_deployment (GAME::Model & deployment,
                            const std::map <std::string, GAME::Model> & nodes,
                            std::map <std::string, GAME::Set> & groups)
{
  typedef std::map <std::string, GAME::Model> nodemap_type;
  nodemap_type::const_iterator iter = nodes.begin ();
  nodemap_type::const_iterator iter_end = nodes.end ();

  for ( ; iter != iter_end; ++ iter)
  {
    // Create a new node reference.
    GAME::Reference noderef =
      GAME::Reference::_create (deployment, "NodeReference");

    // Initialize the node reference.
    noderef.name (iter->first);
    noderef.refers_to (iter->second);

    // Force a new transaction. This should cause the loaded add-on(s)
    // to execute their event handlers.
    GAME::ConnectionPoints points;

    if (noderef.in_connection_points (points))
    {
      // Get the destination point for this connection.
      GAME::Connection conn = points.begin ()->item ().owner ();
      GAME::ConnectionPoint dst = conn[std::string ("src")];

      // Save the collocation group.
      GAME::Set group = GAME::Set::_narrow (dst.target ());
      groups.insert (std::make_pair (iter->first, group));
    }
  }
}

GME_T2M_CREATE_PARSER_IMPLEMENT (Scatter_Deployment_Parser);
