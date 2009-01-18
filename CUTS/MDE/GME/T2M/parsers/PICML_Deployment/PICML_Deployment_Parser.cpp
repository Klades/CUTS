// $Id$

#include "PICML_Deployment_Parser.h"

#if !defined (__CUTS_INLINE__)
#include "PICML_Deployment_Parser.inl"
#endif

#include "boost/bind.hpp"
#include "boost/spirit.hpp"
#include "boost/spirit/core.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "boost/spirit/utility/lists.hpp"
#include "game/Attribute.h"
#include "game/Connection.h"
#include "game/MetaModel.h"
#include "game/Model.h"
#include "game/Project.h"
#include "game/Set.h"
#include <map>

GME_T2M_CREATE_PARSER_IMPLEMENT (PICML_Deployment_Parser);

typedef std::map <std::string, GME::Model> nodemap_type;

typedef std::pair <GME::Reference,
                   std::map <std::string, GME::Set> > collocation_map_type;

typedef std::map <std::string,
                  collocation_map_type> cache_type;

///////////////////////////////////////////////////////////////////////////////
// actors

namespace actors
{
  struct new_deployment
  {
    new_deployment (GME::Folder & folder, GME::Model & deployment)
      : folder_ (folder),
        deployment_ (deployment)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      // Make sure there are no deployments with this name.
      GME::Object obj = this->folder_.find_object_by_path (name);

      if (obj)
        obj.destroy ();

      // Create a new deployment plan.
      this->deployment_ = GME::Model::_create ("DeploymentPlan",
                                               this->folder_);

      // Set the name of the deployment plan.
      this->deployment_.name (name);
    }

  private:
    GME::Folder & folder_;

    GME::Model & deployment_;
  };

  struct refer_to_instance
  {
    refer_to_instance (GME::Model & deployment, GME::Reference & ref)
      : deployment_ (deployment),
        ref_ (ref)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string path (begin, end);

      // Locate the instance in the project.
      GME::Project project = this->deployment_.project ();
      GME::Folder root_folder = project.root_folder ();
      GME::Object obj = root_folder.find_object_by_path (path);

      if (obj)
      {
        // Get the instance's type. This will determine the type
        // of reference we need to create.
        std::string role;
        std::string type = obj.meta ().name ();

        if (type == "Component")
          role = "ComponentRef";
        else if (type == "ComponentAssembly")
          role = "ComponentAssemblyRef";

        // Create the reference to the object.
        this->ref_ = GME::Reference::_create (role, this->deployment_);
        this->ref_.name (obj.name ());

        // Refer to the located instance.
        GME::FCO fco = GME::FCO::_narrow (obj);
        this->ref_.refers_to (fco);
      }
    }

  private:
    GME::Model & deployment_;

    GME::Reference & ref_;
  };

  /**
   * @struct new_node
   */
  struct new_node
  {
    new_node (nodemap_type & nodemap,
              GME::Model & deployment,
              std::string & hostname,
              cache_type & cache)
      : nodemap_ (nodemap),
        deployment_ (deployment),
        hostname_ (hostname),
        cache_ (cache)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      // Get the name of the host.
      this->hostname_.assign (begin, end);

      // We should continue iff we cannot find the hostname.
      if (this->cache_.find (this->hostname_) != this->cache_.end ())
        return;

      // Locate the node in the node map.
      GME::Model node = this->nodemap_[this->hostname_];

      // Create a new reference in the deployment.
      GME::Reference noderef = GME::Reference::_create ("NodeReference",
                                                        this->deployment_);

      // Initialize the reference.
      noderef.name (this->hostname_);
      noderef.refers_to (node);

      // Cache the node reference for later.
      cache_type::value_type::second_type & value = this->cache_[this->hostname_];
      value.first = noderef;

      // Checkpoint the model. This will force the PICMLManager to
      // auto-generate the DefaultGroup for the node.
      GME::Project project = this->deployment_.project ();
      project.begin_transaction (true);

      // Now, let's get the auto-generated collocation group.
      GME::ConnectionPoints points;

      if (noderef.in_connection_points (points))
      {
        // Walk the connection.
        GME::ConnectionPoint point = points.begin ()->item ();
        GME::Connection conn = point.owner ();
        GME::ConnectionPoint src = conn[std::string ("src")];

        // Save the collocation group.
        GME::Set group = GME::Set::_narrow (src.target ());
        value.second.insert (std::make_pair (group.name (), group));
      }
    }

  private:
    nodemap_type & nodemap_;

    GME::Model & deployment_;

    std::string & hostname_;

    cache_type & cache_;
  };

  /**
   * @struct install
   */
  struct install
  {
    install (cache_type & cache,
             const std::string & hostname,
             const GME::Reference & ref)
      : cache_ (cache),
        hostname_ (hostname),
        ref_ (ref)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      // First, find the host in the cache.
      cache_type::iterator host_iter = this->cache_.find (this->hostname_);

      if (host_iter == this->cache_.end ())
        return;

      // Next, find the group in the host's cache.
      std::string groupname (begin, end);

      typename collocation_map_type::second_type::iterator
        group_iter = host_iter->second.second.find (groupname);

      GME::Set group;

      if (group_iter != host_iter->second.second.end ())
      {
        // Save the group.
        group = group_iter->second;
      }
      else
      {
        // We need to create a new group for this host.
        GME::Model parent = GME::Model::_narrow (this->ref_.parent ());
        group = GME::Set::_create ("CollocationGroup", parent);
        group.name (groupname);

        // Save the new group in the cache.
        host_iter->second.second.insert (std::make_pair (groupname, group));

        // We need to also add an instance mapping.
        GME::Reference noderef = host_iter->second.first;

        GME::Connection mapping =
          GME::Connection::_create ("InstanceMapping",
                                    parent,
                                    group,
                                    noderef);
      }

      // Install the instance on the group.
      group.insert (this->ref_);
    }

  private:
    cache_type & cache_;

    const std::string & hostname_;

    const GME::Reference & ref_;
  };

  /**
   * @struct new_domain
   */
  struct new_domain
  {
    new_domain (GME::Folder & target, GME::Model & domain)
      : target_ (target),
        domain_ (domain)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      // We need to get the /AutoTargets folder.
      GME::Project project = this->target_.project ();
      GME::Folder root_folder = project.root_folder ();

      GME::Folder targets;
      const std::string target_name ("AutoTargets");
      GME::Object obj = root_folder.find_object_by_path (target_name);

      if (!obj.is_nil ())
      {
        targets = GME::Folder::_narrow (obj);
      }
      else
      {
        targets = GME::Folder::_create ("Targets", root_folder);
        targets.name (target_name);
      }

      // Now, let's make sure this domain does not exist.
      obj = targets.find_object_by_path (name);

      if (!obj.is_nil ())
        obj.destroy ();

      // Create a new domain for this deployment.
      this->domain_ = GME::Model::_create ("Domain", targets);
      this->domain_.name (name);
    }

  private:
    GME::Folder & target_;

    GME::Model & domain_;
  };

  struct new_domain_node
  {
    new_domain_node (GME::Model & domain, nodemap_type & nodemap)
      : domain_ (domain),
        nodemap_ (nodemap)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      // We need to continue iff we have not seen this node.
      if (this->nodemap_.find (name) != this->nodemap_.end ())
        return;

      // Create a new node.
      GME::Model node = GME::Model::_create ("Node", this->domain_);
      node.name (name);

      // Insert in the node map.
      this->nodemap_.insert (std::make_pair (name, node));
    }

  private:
    GME::Model & domain_;

    nodemap_type & nodemap_;
  };

  /**
   * @struct checkpoint
   */
  struct checkpoint
  {
    checkpoint (GME::Object & obj)
      : obj_ (obj)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      // The exert we are checkpointing.
      std::string exert (begin, end);

      // Checkpoint the model.
      GME::Project project = this->obj_.project ();
      project.begin_transaction (true);
    }

    template <typename IteratorT>
    void operator () (IteratorT begin) const
    {
      GME::Project project = this->obj_.project ();
      project.begin_transaction (true);
    }

  private:
    GME::Object & obj_;
  };
}

///////////////////////////////////////////////////////////////////////////////
// class PICML_Domain_Parser_Grammar

class PICML_Domain_Parser_Grammar :
  public boost::spirit::grammar <PICML_Domain_Parser_Grammar>
{
public:
  PICML_Domain_Parser_Grammar (GME::Folder & target,
                               nodemap_type & nodemap)
    : target_ (target),
      nodemap_ (nodemap)
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
    definition (PICML_Domain_Parser_Grammar const & self)
    {
      using namespace boost::spirit;

      this->identifier_ =
        lexeme_d[(alpha_p | '_') >> *(alnum_p | '_')];

      this->fq_name_ =
        lexeme_d[!str_p ("::") >>
        (alpha_p | '_') >> *(alnum_p | '_') >>
        *(str_p ("::") >> (alpha_p | '_') >> *(alnum_p | '_'))];

      this->fq_path_ =
        lexeme_d[(alpha_p | '_') >> *(alnum_p | '_') >>
        *(str_p ("/") >> (alpha_p | '_') >> *(alnum_p | '_'))];

      this->deployment_ =
        str_p ("deployment") >>
        this->identifier_[actors::new_domain (self.target_, this->gme_domain_)] >>
        confix_p ('{', *(this->single_deployment_), '}') [actors::checkpoint (self.target_)];

      this->single_deployment_ =
        this->fq_path_ >> ':' >>
        this->identifier_[actors::new_domain_node (this->gme_domain_, self.nodemap_)] >>
        '[' >> this->identifier_ >> ']';
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->deployment_;
    }

  private:
    boost::spirit::rule <ScannerT> deployment_;

    boost::spirit::rule <ScannerT> single_deployment_;

    boost::spirit::rule <ScannerT> identifier_;

    boost::spirit::rule <ScannerT> fq_name_;

    boost::spirit::rule <ScannerT> fq_path_;

    GME::Model gme_domain_;

    // prevent the following operations
    definition (const definition &);
    const definition & operator = (const definition &);
  };

private:
  GME::Folder & target_;

  nodemap_type & nodemap_;
};

///////////////////////////////////////////////////////////////////////////////
// class PICML_Deployment_Parser_Grammar

class PICML_Deployment_Parser_Grammar :
  public boost::spirit::grammar <PICML_Deployment_Parser_Grammar>
{
public:
  PICML_Deployment_Parser_Grammar (GME::Folder & target,
                                   nodemap_type & nodemap)
    : target_ (target),
      nodemap_ (nodemap)
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
    definition (PICML_Deployment_Parser_Grammar const & self)
    {
      using namespace boost::spirit;

      this->identifier_ =
        lexeme_d[(alpha_p | '_') >> *(alnum_p | '_')];

      this->fq_name_ =
        lexeme_d[!str_p ("::") >>
        (alpha_p | '_') >> *(alnum_p | '_') >>
        *(str_p ("::") >> (alpha_p | '_') >> *(alnum_p | '_'))];

      this->fq_path_ =
        lexeme_d[(alpha_p | '_') >> *(alnum_p | '_') >>
        *(str_p ("/") >> (alpha_p | '_') >> *(alnum_p | '_'))];

      this->deployment_ =
        str_p ("deployment") >>
        this->identifier_[actors::new_deployment (self.target_, this->gme_deployment_)] >>
        confix_p ('{', *(this->single_deployment_), '}') [actors::checkpoint (self.target_)];

      this->single_deployment_ =
        this->fq_path_[actors::refer_to_instance (this->gme_deployment_, this->gme_instance_ref_)] >> ':' >>
        this->identifier_[actors::new_node (self.nodemap_, this->gme_deployment_, this->hostname_, this->gme_cache_)] >> '[' >>
        this->identifier_[actors::install (this->gme_cache_, this->hostname_, this->gme_instance_ref_)] >> ']';
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->deployment_;
    }

  private:
    boost::spirit::rule <ScannerT> deployment_;

    boost::spirit::rule <ScannerT> single_deployment_;

    boost::spirit::rule <ScannerT> identifier_;

    boost::spirit::rule <ScannerT> fq_name_;

    boost::spirit::rule <ScannerT> fq_path_;

    GME::Model gme_deployment_;

    GME::Reference gme_instance_ref_;

    cache_type gme_cache_;

    std::string hostname_;

    // prevent the following operations
    definition (const definition &);
    const definition & operator = (const definition &);
  };

private:
  GME::Folder & target_;

  nodemap_type & nodemap_;
};

///////////////////////////////////////////////////////////////////////////////
// class PICML_Deployment_Parser

//
// parse
//
bool PICML_Deployment_Parser::
parse (const std::string & filename, GME::Object & parent)
{
  using namespace boost::spirit;

  typedef file_iterator < > iterator_t;

  // Get an iterator to the beginning of the file.
  iterator_t first (filename);

  if (!first)
    return false;

  // Get an iterator to the end of the file.
  iterator_t last = first.make_end ();

  // The parent should be a container, which is a model in PICML.
  GME::Folder folder = GME::Folder::_narrow (parent);

  // First, we need to create a default domain for the deployment. Make
  // sure to cache node infomration.
  nodemap_type nodemap;
  PICML_Domain_Parser_Grammar domain_grammar (folder, nodemap);

  parse_info <iterator_t> result =
    boost::spirit::parse (first,
                          last,
                          domain_grammar >> !end_p,
                          space_p);

  if (result.full)
  {
    // New, we can create the deployment plan using the nodes from
    // the auto-generated domain.
    PICML_Deployment_Parser_Grammar grammar (folder, nodemap);

    result = boost::spirit::parse (first,
                                   last,
                                   grammar >> !end_p,
                                   space_p);
  }

  return result.full;
}
