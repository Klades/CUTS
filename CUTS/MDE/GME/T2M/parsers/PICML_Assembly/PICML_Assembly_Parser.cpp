// $Id$

#include "PICML_Assembly_Parser.h"

#if !defined (__CUTS_INLINE__)
#include "PICML_Assembly_Parser.inl"
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
#include <map>

GME_T2M_CREATE_PARSER_IMPLEMENT (PICML_Assembly_Parser);

///////////////////////////////////////////////////////////////////////////////
// actors

namespace actors
{
  /**
   * @struct new_assembly
   */
  struct new_assembly
  {
    new_assembly (GME::Model & container, GME::Model & assembly)
      : container_ (container),
        assembly_ (assembly)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      // First, delete an existing component assemblies in the
      // container. We don't want to have duplicate assemblies.
      GME::Object obj = this->container_.find_object_by_path (name);

      if (obj)
        obj.destroy ();

      // Create the assembly.
      const std::string type ("ComponentAssembly");
      this->assembly_ = ::GME::Model::_create (type, this->container_);

      // Set the name of the assembly.
      this->assembly_.name (name);
    }

    GME::Model & container_;

    GME::Model & assembly_;
  };

  /**
   * @struct new_instance
   */
  struct new_instance
  {
    new_instance (GME::Model & assembly,
                  GME::Model & type,
                  GME::Model & instance,
                  std::map <std::string, GME::Model> & map)
      : assembly_ (assembly),
        type_ (type),
        instance_ (instance),
        instance_map_ (map)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      // Create a new instance in the assembly.
      GME::FCO fco = this->type_.create_instance (this->assembly_);
      this->instance_ = GME::Model::_narrow (fco);
      this->instance_.name (name);

      // Cache the instance for later.
      this->instance_map_[name] = this->instance_;
    }

    GME::Model & assembly_;

    GME::Model & type_;

    GME::Model & instance_;

    std::map <std::string, GME::Model> & instance_map_;
  };

  /**
   * @struct find_instance
   */
  struct find_instance
  {
    find_instance (std::map <std::string, GME::Model> & instance_map,
                   GME::Model & instance)
      : instance_map_ (instance_map),
        instance_ (instance)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);
      this->instance_ = this->instance_map_[name];
    }

    std::map <std::string, GME::Model> & instance_map_;

    GME::Model & instance_;
  };

  /**
   * @struct find_component_type
   */
  struct find_component_type
  {
    static GME::Collection_T <GME::Model> files_;

    find_component_type (GME::Project const & project, GME::Model & type)
      : project_ (project),
        type_ (type)
    {
      if (this->files_.empty ())
      {
        // Get the root folder of the project.
        GME::Folder root_folder = this->project_.root_folder ();

        // Get all the interface definition folders.
        GME::Collection_T <GME::Folder> folders;

        // Cache all the files in the project.
        if (root_folder.folders ("InterfaceDefinitions", folders))
          std::for_each (folders.begin (),
                         folders.end (),
                         boost::bind (&find_component_type::save_files,
                                      _1,
                                      boost::ref (this->files_)));
      }
    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string fq_name (begin, end);

      // Convert the scope to a GME path.
      size_t pos = 0;

      while ((pos = fq_name.find_first_of ("::", pos)) != std::string::npos)
        fq_name.replace (pos, 2, "/");

      // Remove the leading slash, if necessary.
      if (fq_name[0] == '/')
        fq_name.erase (0, 1);

      // Locate the type in the cached files.
      GME::Collection_T <GME::Model>::const_iterator iter =
        std::find_if (this->files_.begin (),
                      this->files_.end (),
                      has_component_type (fq_name, this->type_));

      if (iter == this->files_.end ())
        this->type_.release ();
    }

  private:
    /**
     * @struct has_component_type
     */
    struct has_component_type
    {
      has_component_type (const std::string & fq_name,
                          GME::Model & component_type)
        : fq_name_ (fq_name),
          component_type_ (component_type)
      {

      }

      bool operator () (GME::Model & file) const
      {
        GME::Object obj = file.find_object_by_path (this->fq_name_);

        if (obj)
        {
          this->component_type_ = GME::Model::_narrow (obj);
          return true;
        }
        else
          return false;
      }

    private:
      const std::string & fq_name_;

      GME::Model & component_type_;
    };

    static void save_files (const GME::Folder & folder,
                            GME::Collection_T <GME::Model> & files)
    {
      GME::Collection_T <GME::Model> temp;

      if (folder.models ("File", temp))
        std::for_each (temp.begin (),
                       temp.end (),
                       boost::bind (&find_component_type::insert,
                                    boost::ref (files),
                                    _1));
    }

    static void insert (GME::Collection_T <GME::Model> & files,
                        GME::Model & model)
    {
      files.items ().push_back (model);
    }

    GME::Project const & project_;

    GME::Model & type_;
  };

  GME::Collection_T <GME::Model> find_component_type::files_;

  /**
   * @struct find_attribute
   *
   * Functor that will locate an attribute in a component. If the
   * attribute does not exist, then \attribute will be set to NIL.
   */
  struct find_attribute
  {
    find_attribute (const GME::Model & instance, GME::Model & attribute)
      : instance_ (instance),
        attribute_ (attribute)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      // Find the attribute by its name.
      GME::Object obj = this->instance_.find_object_by_path (name);

      if (obj)
        this->attribute_ = GME::Model::_narrow (obj);
      else
        this->attribute_.release ();
    }

  private:
    const GME::Model & instance_;

    GME::Model & attribute_;
  };

  /**
   * @struct new_attribute
   */
  struct new_property
  {
    new_property (GME::Model & assembly, const GME::Model & attribute)
      : assembly_ (assembly),
        attribute_ (attribute)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string value (begin, end);

      // Create a new property for the attribute.
      GME::Model property = GME::Model::_create ("Property", this->assembly_);

      // Set the value of the property.
      GME::Attribute attr = property.attribute ("DataValue");
      attr.string_value (value);

      // Finally, connect the property to the attribute.
      GME::Connection attr_value =
        GME::Connection::_create ("AttributeValue",
                                  this->assembly_,
                                  this->attribute_,
                                  property);
    }

  private:
    GME::Model & assembly_;

    const GME::Model & attribute_;
  };

  /**
   * @struct checkpoint
   */
  struct checkpoint
  {
    checkpoint (GME::Model & assembly)
      : assembly_ (assembly)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      // The exert we are checkpointing.
      std::string exert (begin, end);

      // Checkpoint the model.
      GME::Project project = this->assembly_.project ();
      project.begin_transaction (true);
    }

    template <typename IteratorT>
    void operator () (IteratorT begin) const
    {
      GME::Project project = this->assembly_.project ();
      project.begin_transaction (true);
    }

  private:
    GME::Model & assembly_;
  };

  /**
   * @struct find_src_port
   */
  struct find_src_port
  {
    find_src_port (const GME::Model & instance, GME::Reference & port)
      : instance_ (instance),
        port_ (port)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      GME::Collection_T <GME::Reference> ports;

      if (this->instance_.references ("OutEventPort", ports))
      {
        GME::Collection_T <GME::Reference>::const_iterator iter =
          std::find_if (ports.begin (),
                        ports.end (),
                        boost::bind (std::equal_to <std::string> (),
                                     name,
                                     boost::bind (&GME::Reference::name,
                                                  _1)));

        if (iter != ports.items ().end ())
          this->port_ = *iter;
        else
          this->port_.release ();
      }
      else
        this->port_.release ();
    }

  private:
    const GME::Model & instance_;

    GME::Reference & port_;
  };

  /**
   * @struct find_dst_port
   */
  struct find_dst_port
  {
    find_dst_port (const GME::Model & instance, GME::Reference & port)
      : instance_ (instance),
        port_ (port)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string name (begin, end);

      GME::Collection_T <GME::Reference> ports;

      if (this->instance_.references ("InEventPort", ports))
      {
        GME::Collection_T <GME::Reference>::const_iterator iter =
          std::find_if (ports.begin (),
                        ports.end (),
                        boost::bind (std::equal_to <std::string> (),
                                     name,
                                     boost::bind (&GME::Reference::name,
                                                  _1)));

        if (iter != ports.items ().end ())
          this->port_ = *iter;
        else
          this->port_.release ();
      }
      else
        this->port_.release ();
    }

  private:
    const GME::Model & instance_;

    GME::Reference & port_;
  };

  struct new_connection
  {
    new_connection (GME::Model & assembly,
                    const std::string & symbol,
                    const GME::Reference & src,
                    const GME::Reference & dst)
      : assembly_ (assembly),
        symbol_ (symbol),
        src_ (src),
        dst_ (dst)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      if (this->symbol_ == ">")
      {
        // We can directly create an 'emit' connection.
        GME::Connection emit =
          GME::Connection::_create ("emit",
                                    this->assembly_,
                                    this->src_,
                                    this->dst_);
      }
      else if (this->symbol_ == ">>")
      {
        // Determine of the port already has a connector.
        GME::Atom connector;
        GME::ConnectionPoints points;

        if (this->src_.in_connection_points (points))
        {
          // There should be only one connection point.
          GME::ConnectionPoint point = points.begin ()->item ();

          // Walk the connection to find the connector.
          GME::Connection publish = point.owner ();

          const std::string dst_role ("dst");
          GME::ConnectionPoint dst = publish[dst_role];

          // Save the connector.
          connector = GME::Atom::_narrow (dst.target ());
        }

        if (connector.is_nil ())
        {
          // Create a new publish connector.
          connector = GME::Atom::_create ("PublishConnector",
                                          this->assembly_);

          // Connect the source port to the publish connector.
          GME::Connection publish =
            GME::Connection::_create ("publish",
                                      this->assembly_,
                                      this->src_,
                                      connector);
        }

        // Now, we can create the deliverTo connection.
        GME::Connection deliver =
          GME::Connection::_create ("deliverTo",
                                    this->assembly_,
                                    connector,
                                    this->dst_);
      }
    }

  private:
    GME::Model & assembly_;

    const std::string & symbol_;

    const GME::Reference & src_;

    const GME::Reference & dst_;
  };
}

///////////////////////////////////////////////////////////////////////////////
// class PICML_Assembly_Parser_Grammar

class PICML_Assembly_Parser_Grammar :
  public boost::spirit::grammar <PICML_Assembly_Parser_Grammar>
{
public:
  PICML_Assembly_Parser_Grammar (GME::Model & container)
    : container_ (container),
      project_ (container_.project ())
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
    definition (PICML_Assembly_Parser_Grammar const & self)
    {
      using namespace boost::spirit;

      this->identifier_ =
        lexeme_d[(alpha_p | '_') >> *(alnum_p | '_')];

      this->fq_name_ =
        lexeme_d[!str_p ("::") >>
        (alpha_p | '_') >> *(alnum_p | '_') >>
        *(str_p ("::") >> (alpha_p | '_') >> *(alnum_p | '_'))];

      this->assembly_ =
        str_p ("assembly") >>
        this->identifier_[actors::new_assembly (self.container_, this->gme_assembly_)] >>
        confix_p ('{', !this->assembly_content_, '}');

      this->instances_ =
        str_p ("instances") >>
        confix_p ('{', *this->instance_decl_, '}');

      this->instance_decl_ =
        this->fq_name_[actors::find_component_type (self.project_, this->gme_component_type_)] >>
        this->identifier_[actors::new_instance (this->gme_assembly_, this->gme_component_type_, this->gme_instance_, this->gme_instance_map_)] >>
        confix_p ('{', *this->property_, '}');

      this->connections_ =
        str_p ("connections") >>
        confix_p ('{', *(this->connection_[actors::new_connection (this->gme_assembly_, this->conn_type_, this->gme_src_port_, this->gme_dst_port_)]), '}');

      this->property_ =
        this->identifier_[actors::find_attribute (this->gme_instance_, this->gme_attribute_)] >>
        '=' >>
        lexeme_d [*(anychar_p - eol_p)][actors::new_property (this->gme_assembly_, this->gme_attribute_)];

      this->connection_ =
        this->identifier_[actors::find_instance (this->gme_instance_map_, this->gme_instance_)] >>
        '.' >>
        this->identifier_[actors::find_src_port (this->gme_instance_, this->gme_src_port_)] >>
        this->connection_type_[assign_a (this->conn_type_)] >>
        this->identifier_[actors::find_instance (this->gme_instance_map_, this->gme_instance_)] >>
        '.' >>
        this->identifier_[actors::find_dst_port (this->gme_instance_, this->gme_dst_port_)];

      this->connection_type_ =
        str_p (">>") | ">";

      this->assembly_content_ =
        this->instances_ [actors::checkpoint (this->gme_assembly_)] >>
        !(this->connections_[actors::checkpoint (this->gme_assembly_)]);


      BOOST_SPIRIT_DEBUG_NODE (this->assembly_content_);
      BOOST_SPIRIT_DEBUG_NODE (this->instances_);
      BOOST_SPIRIT_DEBUG_NODE (this->identifier_);
      BOOST_SPIRIT_DEBUG_NODE (this->connections_);
      BOOST_SPIRIT_DEBUG_NODE (this->connection_);
      BOOST_SPIRIT_DEBUG_NODE (this->connection_type_);
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->assembly_;
    }

  private:
    /// rule: deployment_member_
    boost::spirit::rule <ScannerT> assembly_;

    boost::spirit::rule <ScannerT> assembly_content_;

    boost::spirit::rule <ScannerT> identifier_;

    boost::spirit::rule <ScannerT> fq_name_;

    boost::spirit::rule <ScannerT> instances_;

    boost::spirit::rule <ScannerT> instance_decl_;

    boost::spirit::rule <ScannerT> property_;

    boost::spirit::rule <ScannerT> connections_;

    boost::spirit::rule <ScannerT> connection_;

    boost::spirit::rule <ScannerT> connection_type_;

    boost::spirit::rule <ScannerT> emits_;

    boost::spirit::rule <ScannerT> publishes_;

    GME::Model gme_assembly_;

    GME::Model gme_component_type_;

    GME::Model gme_instance_;

    GME::Model gme_attribute_;

    GME::Reference gme_src_port_;

    GME::Reference gme_dst_port_;

    std::map <std::string, GME::Model> gme_instance_map_;

    std::string conn_type_;

  private:
    definition (const definition &);
    const definition & operator = (const definition &);
  };

private:
  GME::Model & container_;

  GME::Project project_;
};

///////////////////////////////////////////////////////////////////////////////
// class PICML_Assembly_Parser

//
// parse
//
bool PICML_Assembly_Parser::
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
  GME::Model container = GME::Model::_narrow (parent);
  PICML_Assembly_Parser_Grammar grammar (container);

  parse_info <iterator_t> result =
    boost::spirit::parse (first,
                          last,
                          grammar >> !end_p,
                          space_p);

  return result.full;
}
