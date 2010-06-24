// $Id$

#include "Javap_Output_Parser.h"

#include "boost/spirit/include/qi.hpp"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_stl.hpp"
#include "boost/spirit/include/phoenix_object.hpp"
#include "boost/spirit/include/support_istream_iterator.hpp" 
#include "boost/fusion/include/adapt_struct.hpp"

#include <string>
#include <vector>

#include "game/xme/Model.h"
#include "game/xme/Folder.h"
#include "game/xme/Attribute.h"
#include "game/utils/modelgen.h"

#include "boost/bind.hpp"

namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace types
{
  typedef std::vector <std::string> scope_t;

  typedef std::vector <scope_t> param_list_t;
}

namespace action
{
  
  std::string flatten_scope (types::scope_t::const_iterator begin, 
                             types::scope_t::const_iterator end,
                             const std::string & separator)
  {
    std::string scope (*begin ++);

    for (begin; begin != end; ++ begin)
      scope += separator + *begin;

    return scope;
  }

  /**
   * @struct create_class
   *
   * Functor for creating a Java class in the specified folder.
   */
  struct create_class
  {
  public:
    create_class (GAME::XME::Folder & idl_folder)
      : idl_folder_ (idl_folder)
    {

    }

    template <typename ContextT>
    void operator () (const types::scope_t & classname, ContextT ctx, qi::unused_type) const
    {
      static const ::Utils::XStr meta_File ("File");
      const ::Utils::XStr filename = classname.back ();

      using GAME::XME::Model;

      // Create in the interface definitions the specified file it 
      // already does not exist.
      Model javafile;

      if (GAME::create_if_not (this->idl_folder_, meta_File, javafile,
          GAME::contains (boost::bind (std::equal_to < ::Utils::XStr > (),
                                       filename,
                                       boost::bind (&Model::name, _1)))))
      {
        javafile.name (filename);
      }

      // Set the path of the specified file.
      std::string path;

      if (classname.size () > 1)
      {
        types::scope_t::const_iterator 
          iter = classname.begin (), iter_end = -- classname.end ();

        path = flatten_scope (iter, iter_end, "/");
        javafile.attribute ("Path", true).value (path);

        // Now, lets create the Java class within its package. Each iteration
        // will create a new package and replace the old <javafile> container
        // element. In the end, <javafile> will contain the location of the
        // target Java file.
        for (iter; iter != iter_end; ++ iter)
        {
          static const ::Utils::XStr meta_Package ("Package");

          if (GAME::create_if_not (javafile, meta_Package, javafile,
              GAME::contains (boost::bind (std::equal_to < ::Utils::XStr > (),
                                           *iter,
                                           boost::bind (&Model::name, _1)))))
          {
            javafile.name (*iter);
          }
        }
      }

      // Create the Java class in the current <javafile> container.
      GAME::XME::Model object;

      static const std::string meta_Object ("Object");
      if (GAME::create_if_not (javafile, meta_Object, object,
          GAME::contains (boost::bind (std::equal_to < ::Utils::XStr > (),
                                       filename,
                                       boost::bind (&Model::name, _1)))))
      {
        object.name (filename);
      }

      // Store the new object as the return value (i.e., qi::_val).
      fusion::at_c <0> (ctx.attributes) = object;
    }

  private:
    GAME::XME::Folder & idl_folder_;
  };

  /**
   * @struct create_method
   *
   * Functor for creating a Java class in the specified folder.
   */
  struct create_method
  {
  public:
    template <typename ContextT>
    void operator () (const std::string & name, ContextT ctx, qi::unused_type) const
    {
      using GAME::XME::Model;
  
      Model object;
      Model & parent = fusion::at_c <1> (ctx.attributes);
      static const ::Utils::XStr meta_TwowayOperation ("TwowayOperation");

      if (GAME::create_if_not (parent, meta_TwowayOperation, object,
          GAME::contains (boost::bind (std::equal_to < ::Utils::XStr > (),
                                       name,
                                       boost::bind (&Model::name, _1)))))
      {
        object.name (name);
      }

      fusion::at_c <0> (ctx.attributes) = object;
    }
  };

  /**
   * @struct create_parameter
   *
   * Functor for creating a Java class in the specified folder.
   */
  struct create_parameter
  {
  public:
    create_parameter (size_t & pcount)
      : pcount_ (pcount)
    {

    }

    template <typename ContextT>
    void operator () (const types::scope_t & param, ContextT ctx, qi::unused_type) const
    {
      using GAME::XME::Model;
      using GAME::XME::Reference;

      Reference parameter;
      Model & parent = fusion::at_c <1> (ctx.attributes);
      static const ::Utils::XStr meta_InParameter ("InParameter");
  
      std::ostringstream pname;
      pname << "p" << this->pcount_ ++;

      const ::Utils::XStr name (pname.str ());

      if (GAME::create_if_not (parent, meta_InParameter, parameter,
          GAME::contains (boost::bind (std::equal_to < ::Utils::XStr > (),
                                       name,
                                       boost::bind (&Reference::name, _1)))))
      {
        parameter.name (name);
      }
    }

  private:
    size_t & pcount_;
  };

  /**
   * @struct reset_counter
   *
   * Functor for reseting a counter variable.
   */
  struct reset_counter 
  {
    reset_counter (size_t & counter)
      : counter_ (counter)
    {

    }

    void operator () (qi::unused_type, qi::unused_type, qi::unused_type) const
    {
      this->counter_ = 0;
    }

  private:
    size_t & counter_;
  };
}

/**
 * @class Quotas_Javap_Output_Grammar
 *
 * Grammer for converting Javap output to a PICML model for Quotas.
 */
template <typename IteratorT, typename SpaceT>
class Quotas_Javap_Output_Grammar : 
  public qi::grammar <IteratorT, void (), SpaceT>
{
public:
  typedef IteratorT iterator_type;

  typedef SpaceT space_type;

  Quotas_Javap_Output_Grammar (GAME::XME::Folder & idl_folder, bool debug = false)
    : Quotas_Javap_Output_Grammar::base_type (this->grammar_),
      idl_folder_ (idl_folder),
      grammar_ (std::string ("grammar")),
      header_ (std::string ("header")),
      class_specification_ (std::string ("class_specification")),
      scoped_name_ (std::string ("scoped_name")),
      ident_ (std::string ("ident"))
  {
    using qi::raw;
    using ascii::char_;
    using ascii::string;

    using phoenix::push_back;

    this->grammar_ =
      this->header_ >> this->class_specification_;

    this->header_ = 
      qi::lit ("Compiled") >> qi::lit ("from") >>
      qi::lit ("\"") >> this->scoped_name_ >> qi::lit ("\"");

    this->class_specification_ =
      this->visibility_ >> qi::lit ("class") > 
      this->scoped_name_[action::create_class (this->idl_folder_)] >>
      -(qi::lit ("extends") > this->scoped_name_) >>
      -(qi::lit ("implements") > this->scoped_name_ >> 
      *(qi::lit (",") >> this->scoped_name_)) >>
      qi::lit ("{") >> * this->class_definition_ (qi::labels::_val) >> qi::lit ("}");

    this->class_definition_ =
      this->constr_decl_ |
      this->method_decl_ (qi::labels::_r1) |
      this->ignorable_method_decl_ |
      this->variable_decl_;

    this->constr_decl_ =
      this->visibility_ >> this->scoped_name_ >>
      qi::lit ("(") >> - this->ignorable_param_list_ >> qi::lit (")") >> qi::lit (";");

    this->ignorable_method_decl_ = 
      (qi::lit ("protected") | qi::lit ("private")) >> 
      this->scoped_name_ >>
      this->ident_ >> 
      qi::lit ("(") >> - this->ignorable_param_list_ >> qi::lit (")") >> 
      qi::lit (";");

    this->method_decl_ = 
      qi::lit ("public") >> 
      qi::eps[action::reset_counter (this->pcount_)] >>
      this->scoped_name_/*[create_return_type ()]*/ >>
      this->ident_[action::create_method ()] >> 
      qi::lit ("(") >> - this->param_list_ (qi::labels::_val) >> qi::lit (")") >> 
      qi::lit (";");

    this->variable_decl_ =
      this->scoped_name_ >> this->ident_ >> qi::lit (";");

    this->param_list_ =
      this->scoped_name_[action::create_parameter (this->pcount_)] >> 
      * (qi::lit (",") >> this->scoped_name_[action::create_parameter (this->pcount_)]);

    this->ignorable_param_list_ =
      this->scoped_name_ >> - (qi::lit (",") >> this->scoped_name_);

    this->scoped_name_ = 
      this->ident_[push_back (qi::labels::_val, qi::labels::_1)]  >> 
      * (qi::lit ('.') >> this->ident_[push_back (qi::labels::_val, qi::labels::_1)]);

    // The different visibility attributes allowed in Java.
    this->visibility_ = 
      qi::lit ("public") | qi::lit ("protected") | qi::lit ("private");

    // Rule definition for parsing identifiers.
    this->ident_ %= qi::lexeme [(qi::alpha >> *(qi::alnum | '_'))];
  }

private:
  GAME::XME::Folder & idl_folder_;

  size_t pcount_;

  qi::rule <IteratorT, void (), SpaceT> grammar_;

  qi::rule <IteratorT, void (), SpaceT> header_;
  
  qi::rule <IteratorT, void (), SpaceT> visibility_;

  qi::rule <IteratorT, 
            GAME::XME::Model (), 
            SpaceT> class_specification_;

  qi::rule <IteratorT, 
            void (GAME::XME::Model), 
            SpaceT> class_definition_;

  qi::rule <IteratorT, 
            GAME::XME::Model (GAME::XME::Model),
            SpaceT> method_decl_;

  qi::rule <IteratorT, void (), SpaceT> ignorable_method_decl_;

  qi::rule <IteratorT, void (), SpaceT> constr_decl_;

  qi::rule <IteratorT, void (), SpaceT> variable_decl_;

  qi::rule <IteratorT, void (GAME::XME::Model), SpaceT> param_list_;

  qi::rule <IteratorT, void (), SpaceT> ignorable_param_list_;

  qi::rule <IteratorT, types::scope_t (), SpaceT> scoped_name_;

  qi::rule <IteratorT, std::string (), SpaceT> ident_;
};

///////////////////////////////////////////////////////////////////////////////
//

//
// Quotas_Javap_Output_Parser
//
Quotas_Javap_Output_Parser::Quotas_Javap_Output_Parser (void)
{

}

//
// ~Quotas_Javap_Output_Parser
//
Quotas_Javap_Output_Parser::~Quotas_Javap_Output_Parser (void)
{

}

//
// parse
//
bool Quotas_Javap_Output_Parser::
parse (std::istream & stream, GAME::XME::Folder & idl_folder)
{
  namespace spirit = boost::spirit;

  // Adapt the iterator to support Boost backtracking.
  long flags = stream.flags ();

  if ((flags & std::ios::skipws) != 0)
    stream.unsetf (std::ios::skipws);

  spirit::istream_iterator begin_iter (stream);
  spirit::istream_iterator end_iter;

  // Parse the open file using the iterators above.
  Quotas_Javap_Output_Grammar <spirit::istream_iterator, 
                               ascii::space_type> 
                               grammar (idl_folder);

  bool retval = qi::phrase_parse (begin_iter, 
                                  end_iter, 
                                  grammar, 
                                  ascii::space);

  if ((flags & std::ios::skipws) != 0)  
    stream.setf (std::ios::skipws);

  return retval;
}