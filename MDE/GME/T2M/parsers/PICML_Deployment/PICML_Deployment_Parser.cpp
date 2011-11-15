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
#include "game/GAME.h"
#include <map>

GME_T2M_CREATE_PARSER_IMPLEMENT (PICML_Deployment_Parser);

typedef std::map <std::string, GAME::Model> nodemap_type;

typedef std::pair <GAME::Reference,
                   std::map <std::string, GAME::Set> > collocation_map_type;

typedef std::map <std::string,
                  collocation_map_type> cache_type;

///////////////////////////////////////////////////////////////////////////////
// actors

namespace actors
{
  struct new_deployment
  {
    new_deployment (GAME::Folder & folder, GAME::Model & deployment)
      : folder_ (folder),
        deployment_ (deployment)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      // Make sure there are no deployments with this name.
      GAME::Object obj = this->folder_.find_object_by_path (name);

      if (obj)
        obj.destroy ();

      // Create a new deployment plan.
      this->deployment_ = GAME::Model::_create (this->folder_, "DeploymentPlan");

      // Set the name of the deployment plan.
      this->deployment_.name (name);
    }

  private:
    GAME::Folder & folder_;

    GAME::Model & deployment_;
  };

  struct refer_to_instance
  {
    refer_to_instance (GAME::Model & deployment, GAME::Reference & ref)
      : deployment_ (deployment),
        ref_ (ref)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string path (begin, end);

      // Locate the instance in the project.
      GAME::Project project = this->deployment_.project ();
      GAME::Folder root_folder = project.root_folder ();
      GAME::Object obj = root_folder.find_object_by_path (path);

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
        this->ref_ = GAME::Reference::_create (this->deployment_, role);
        this->ref_.name (obj.name ());

        // Refer to the located instance.
        GAME::FCO fco = GAME::FCO::_narrow (obj);
        this->ref_.refers_to (fco);
      }
    }

  private:
    GAME::Model & deployment_;

    GAME::Reference & ref_;
  };

  /**
   * @struct new_node
   */
  struct new_node
  {
    new_node (nodemap_type & nodemap,
              GAME::Model & deployment,
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
      GAME::Model node = this->nodemap_[this->hostname_];

      // Create a new reference in the deployment.
      GAME::Reference noderef =
        GAME::Reference::_create (this->deployment_, "NodeReference");

      // Initialize the reference.
      noderef.name (this->hostname_);
      noderef.refers_to (node);

      // Cache the node reference for later.
      cache_type::value_type::second_type & value = this->cache_[this->hostname_];
      value.first = noderef;

      // Checkpoint the model. This will force the PICMLManager to
      // auto-generate the DefaultGroup for the node.
      GAME::Project project = this->deployment_.project ();

      // Now, let's get the auto-generated collocation group.
      GAME::ConnectionPoints points;

      if (noderef.in_connection_points (points))
      {
        // Walk the connection.
        GAME::ConnectionPoint point = points.begin ()->item ();
        GAME::Connection conn = point.owner ();
        GAME::ConnectionPoint src = conn[std::string ("src")];

        // Save the collocation group.
        GAME::Set group = GAME::Set::_narrow (src.target ());
        value.second.insert (std::make_pair (group.name (), group));
      }
    }

  private:
    nodemap_type & nodemap_;

    GAME::Model & deployment_;

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
             const GAME::Reference & ref)
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

      GAME::Set group;

      if (group_iter != host_iter->second.second.end ())
      {
        // Save the group.
        group = group_iter->second;
      }
      else
      {
        // We need to create a new group for this host.
        GAME::Model parent = GAME::Model::_narrow (this->ref_.parent ());
        group = GAME::Set::_create (parent, "CollocationGroup");
        group.name (groupname);

        // Save the new group in the cache.
        host_iter->second.second.insert (std::make_pair (groupname, group));

        // We need to also add an instance mapping.
        GAME::Reference noderef = host_iter->second.first;

        GAME::Connection mapping =
          GAME::Connection::_create (parent,
                                    "InstanceMapping",
                                    group,
                                    noderef);
      }

      // Install the instance on the group.
      group.insert (this->ref_);
    }

  private:
    cache_type & cache_;

    const std::string & hostname_;

    const GAME::Reference & ref_;
  };

  /**
   * @struct new_domain
   */
  struct new_domain
  {
    new_domain (GAME::Folder & target, GAME::Model & domain)
      : target_ (target),
        domain_ (domain)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      // We need to get the /AutoTargets folder.
      GAME::Project project = this->target_.project ();
      GAME::Folder root_folder = project.root_folder ();

      GAME::Folder targets;
      const std::string target_name ("AutoTargets");
      GAME::Object obj = root_folder.find_object_by_path (target_name);

      if (!obj.is_nil ())
      {
        targets = GAME::Folder::_narrow (obj);
      }
      else
      {
        targets = GAME::Folder::_create (root_folder, "Targets");
        targets.name (target_name);
      }

      // Now, let's make sure this domain does not exist.
      obj = targets.find_object_by_path (name);

      if (!obj.is_nil ())
        obj.destroy ();

      // Create a new domain for this deployment.
      this->domain_ = GAME::Model::_create (targets, "Domain");
      this->domain_.name (name);
    }

  private:
    GAME::Folder & target_;

    GAME::Model & domain_;
  };

  struct new_domain_node
  {
    new_domain_node (GAME::Model & domain, nodemap_type & nodemap)
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
      GAME::Model node = GAME::Model::_create (this->domain_, "Node");
      node.name (name);

      // Insert in the node map.
      this->nodemap_.insert (std::make_pair (name, node));
    }

  private:
    GAME::Model & domain_;

    nodemap_type & nodemap_;
  };

  /**
   * @struct checkpoint
   */
  struct checkpoint
  {
    checkpoint (GAME::Object & obj)
      : obj_ (obj)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      // The exert we are checkpointing.
      std::string exert (begin, end);

      // Checkpoint the model.
      GAME::Project project = this->obj_.project ();
    }

    template <typename IteratorT>
    void operator () (IteratorT begin) const
    {
      GAME::Project project = this->obj_.project ();
    }

  private:
    GAME::Object & obj_;
  };
}

///////////////////////////////////////////////////////////////////////////////
// class PICML_Domain_Parser_Grammar

class PICML_Domain_Parser_Grammar :
  public boost::spirit::grammar <PICML_Domain_Parser_Grammar>
{
public:
  PICML_Domain_Parser_Grammar (GAME::Folder & target,
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

      this->placeholder_ =
        lexeme_d[str_p ("${") >> *(print_p - '}') >> '}'];

      this->nodename_ =
        this->identifier_ | this->placeholder_;

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
        this->nodename_[actors::new_domain_node (this->gme_domain_, self.nodemap_)] >>
        '[' >> this->identifier_ >> ']';

      BOOST_SPIRIT_DEBUG_NODE (this->nodename_);
      BOOST_SPIRIT_DEBUG_NODE (this->identifier_);
      BOOST_SPIRIT_DEBUG_NODE (this->placeholder_);
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

    boost::spirit::rule <ScannerT> placeholder_;

    boost::spirit::rule <ScannerT> nodename_;

    boost::spirit::rule <ScannerT> fq_name_;

    boost::spirit::rule <ScannerT> fq_path_;

    GAME::Model gme_domain_;

    // prevent the following operations
    definition (const definition &);
    const definition & operator = (const definition &);
  };

private:
  GAME::Folder & target_;

  nodemap_type & nodemap_;
};

///////////////////////////////////////////////////////////////////////////////
// class PICML_Deployment_Parser_Grammar

class PICML_Deployment_Parser_Grammar :
  public boost::spirit::grammar <PICML_Deployment_Parser_Grammar>
{
public:
  PICML_Deployment_Parser_Grammar (GAME::Folder & target,
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

      this->placeholder_ =
        lexeme_d[str_p ("${") >> *(print_p - '}') >> '}'];

      this->nodename_ =
        this->identifier_ | this->placeholder_;

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
        this->nodename_[actors::new_node (self.nodemap_, this->gme_deployment_, this->hostname_, this->gme_cache_)] >> '[' >>
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

    boost::spirit::rule <ScannerT> placeholder_;

    boost::spirit::rule <ScannerT> nodename_;

    boost::spirit::rule <ScannerT> fq_name_;

    boost::spirit::rule <ScannerT> fq_path_;

    GAME::Model gme_deployment_;

    GAME::Reference gme_instance_ref_;

    cache_type gme_cache_;

    std::string hostname_;

    // prevent the following operations
    definition (const definition &);
    const definition & operator = (const definition &);
  };

private:
  GAME::Folder & target_;

  nodemap_type & nodemap_;
};

///////////////////////////////////////////////////////////////////////////////
// class PICML_Deployment_Parser

//
// parse
//
bool PICML_Deployment_Parser::
parse (const std::string & filename, GAME::Object & parent)
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
  GAME::Folder folder = GAME::Folder::_narrow (parent);

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
