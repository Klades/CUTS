// $Id:

#include "Setaf_Parser.h"
#include "ace/CORBA_macros.h"
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"
#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi_char_class.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <string>


namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

/**
 * @struct CUTS_Setaf_Parser_Grammar
 *
 * Underlying grammer for the .uas parser object.
 */
template <typename IteratorT>
struct CUTS_Setaf_Parser_Grammar :
    public qi::grammar <IteratorT,
                        void (CUTS_Setaf_Interpreter *),
                        ascii::space_type>
{
  CUTS_Setaf_Parser_Grammar (void) :
      CUTS_Setaf_Parser_Grammar::base_type (this->spec_)
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;
    namespace ascii = boost::spirit::ascii;

    // Definition of an interpreter variable type
    this->var_type_ =
      ascii::string ("int")[qi::_val = phoenix::new_ <CUTS_Setaf_Integer_Variable> ()] |
      ascii::string ("string")[qi::_val = phoenix::new_ <CUTS_Setaf_String_Variable> ()];

    // Definition of a variable identifier
    this->ident_ %=
      qi::lexeme[qi::alpha >>
      *(qi::alnum | ascii::char_ ('_'))];

    // Definition of a variable decleration
    this->variable_decl_ =
      this->var_type_[qi::_a = qi::_1] >>
      this->ident_[qi::_b = qi::_1] >>
      ascii::char_ (';')[phoenix::bind (&CUTS_Setaf_Interpreter::add_state_variable, qi::_r1, qi::_b, qi::_a)];

    // Definition of variables
    this->variables_ =
      ascii::string ("Variables:") >>
      *(this->variable_decl_ (qi::_r1));

    // Definition of a variable value
    this->var_val_ %= +(qi::digit) | this->ident_;

    // Definition of initialization
    this->init_assign_ =
      this->ident_[qi::_a = qi::_1] >>
      ascii::char_ ('=') >>
      this->var_val_[qi::_b = qi::_1] >>
      ascii::char_ (';')[phoenix::bind (&CUTS_Setaf_Interpreter::set_init_value, qi::_r1, qi::_a, qi::_b)];

    // Defintion of resetting
    this->reset_assign_ =
        this->ident_[qi::_a = qi::_1] >>
        ascii::char_ ('=') >>
        this->var_val_[qi::_b = qi::_1] >>
        ascii::char_ (';')[phoenix::bind (&CUTS_Setaf_Interpreter::set_reset_value,
                                          qi::_r1, qi::_a, qi::_b)];

    // Definition of Init
    this->inits_ =
        ascii::string ("Init:") >>
        *(this->init_assign_ (qi::_r1));

    // Definition of Reset
    this->resets_ =
        ascii::string ("Reset:") >>
        *(this->reset_assign_ (qi::_r1));

    // Definition of log format adaptation
    this->data_point_type_ =
        ascii::string("int")[qi::_val = phoenix::new_ <CUTS_Setaf_Log_Format> (qi::_1)] |
        ascii::string("long")[qi::_val = phoenix::new_ <CUTS_Setaf_Log_Format> (qi::_1)] |
        ascii::string("string")[qi::_val = phoenix::new_ <CUTS_Setaf_Log_Format> (qi::_1)];

    /// Definition of data_point identifiers
    this->data_point_ident_ %=
        this->ident_ >> ascii::char_ ('.') >>
        qi::alpha >> *(qi::alnum);

    /// Definition of data_point declerations
    this->data_point_decl_ =
        this->data_point_type_[qi::_a = qi::_1] >>
        this->data_point_ident_[qi::_b = qi::_1] >>
        ascii::char_(";")[phoenix::bind (&CUTS_Setaf_Log_Format::process_format_string, qi::_a, qi::_b)]
        [phoenix::bind (&CUTS_Setaf_Interpreter::add_setaf_datapoint , qi::_r1, qi::_a)];

    /// Definition of data_points
    this->datapoints_ =
        ascii::string("DataPoints:") >>
        *(this->data_point_decl_ (qi::_r1));

    /// Definition of relation declerations
    this->relation_decl_ =
        this->data_point_ident_[qi::_a = qi::_1] >>
        ascii::char_ ('-') >> ascii::char_ ('>') >>
        this->data_point_ident_[qi::_b = qi::_1]>>
        ascii::char_ (';')[qi::_val = phoenix::new_ <CUTS_Setaf_Log_Format_Relation > ()]
        [phoenix::bind (&CUTS_Setaf_Log_Format_Relation::process_relation_strings, qi::_val, qi::_a, qi::_b)]
        [phoenix::bind (&CUTS_Setaf_Interpreter::add_setaf_relation, qi::_r1, qi::_val)];

    /// Definition of relations
    this->relations_ =
        ascii::string("Relations:") >>
        *(this->relation_decl_ (qi::_r1));

    /// Defintion of a variable
    this->variable_ %=
        (ascii::char_('[') >> this->ident_ >>
        ascii::char_(']')) | this->ident_;

    /// Definition of an Add command
    this->add_command_ =
        this->variable_[qi::_a = qi::_1] >>
        ascii::char_("=") >>
        this->variable_[qi::_b = qi::_1] >>
        ascii::char_("+") >>
        qi::int_[qi::_c = qi::_1] >>
        ascii::char_(";")[phoenix::bind (&CUTS_Setaf_Interpreter::create_add_command, qi::_r1, qi::_a, qi::_b, qi::_c, qi::_r2)];

    /// Definition of an Assignment command
    this->assignment_command_ =
        this->variable_[qi::_a = qi::_1] >>
        ascii::char_("=") >>
        this->variable_[qi::_b = qi::_1] >>
        ascii::char_(";")[phoenix::bind (&CUTS_Setaf_Interpreter::create_assignment_command, qi::_r1, qi::_a, qi::_b, qi::_r2)];

    /// Definition of an Adaptation code
    this->adaptation_code_ =
        +(this->assignment_command_(qi::_r1, qi::_r2) |
        this->add_command_(qi::_r1, qi::_r2));

    /// Definition of log format adapts
    this->log_format_adapts_ =
        ascii::string("On") >> this->ident_[qi::_a = qi::_1] >>
        ascii::char_(':') >> this->adaptation_code_(qi::_r1, qi::_a);

    /// The main rule, for the entire speciifcation.
    this->spec_ =
      this->variables_ (qi::_r1) >>
      this->inits_ (qi::_r1) >>
      this->resets_ (qi::_r1) >>
      this->datapoints_ (qi::_r1) >>
      this->relations_ (qi::_r1) >>
      +(this->log_format_adapts_ (qi::_r1));

}

private:

  /// Rule for the Unite Adaptation Specification
  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            ascii::space_type> spec_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            ascii::space_type> variables_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            qi::locals <CUTS_Setaf_Variable *, std::string>,
            ascii::space_type> variable_decl_;

  qi::rule <IteratorT,
            CUTS_Setaf_Variable * (),
            ascii::space_type> var_type_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> ident_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            ascii::space_type> inits_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            ascii::space_type> resets_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            qi::locals <std::string, std::string>,
            ascii::space_type> init_assign_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            qi::locals <std::string, std::string>,
            ascii::space_type> reset_assign_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> var_val_;

  qi::rule <IteratorT,
            CUTS_Setaf_Log_Format * (),
            ascii::space_type> data_point_type_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> data_point_ident_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            qi::locals <CUTS_Setaf_Log_Format *, std::string>,
            ascii::space_type> data_point_decl_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            ascii::space_type> datapoints_;

  qi::rule <IteratorT,
            CUTS_Setaf_Log_Format_Relation * (CUTS_Setaf_Interpreter *),
            qi::locals <std::string, std::string>,
            ascii::space_type> relation_decl_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            ascii::space_type> relations_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *),
            qi::locals <std::string>,
            ascii::space_type> log_format_adapts_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *, std::string),
            ascii::space_type> adaptation_code_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *, std::string),
            qi::locals <std::string, std::string, int>,
            ascii::space_type> add_command_;

  qi::rule <IteratorT,
            void (CUTS_Setaf_Interpreter *, std::string),
            qi::locals <std::string, std::string>,
            ascii::space_type> assignment_command_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> variable_;

};


//
// CUTS_Setaf_Parser
//
CUTS_Setaf_Parser::CUTS_Setaf_Parser (void)
{

}

//
// ~CUTS_Setaf_Parser
//
CUTS_Setaf_Parser::~CUTS_Setaf_Parser (void)
{

}

//
// parse_spec
//
bool CUTS_Setaf_Parser::
parse_spec (std::istream & input,
            CUTS_Setaf_Interpreter * interpreter)
{
  namespace spirit = boost::spirit;
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  // Adapt the iterator to support Boost backtracking.
  long flags = input.flags ();

  if ((flags & std::ios::skipws) != 0)
    input.unsetf (std::ios::skipws);

  spirit::istream_iterator begin (input);
  spirit::istream_iterator end;

  CUTS_Setaf_Parser_Grammar <spirit::istream_iterator> grammar;

  bool ret_val =  qi::phrase_parse (begin,
                                    end,
                                    grammar (interpreter),
                                    ascii::space);

  if ((flags & std::ios::skipws) != 0)
    input.setf (std::ios::skipws);

   return ret_val;
}