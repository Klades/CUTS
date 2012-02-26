// $Id:

#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "ace/streams.h"
#include "ace/CORBA_macros.h"
#include "Setaf_Lang_Compiler.h"
#include "Setaf_Code_Generator.h"


namespace spirit = boost::spirit;

/**
 * @struct create_setaf_log_format
 */
struct create_setaf_log_format
{
   create_setaf_log_format (CUTS_SETAF_UTILS::Setaf_Entries & entries,
                            std::string & var_type,
                            std::string & log_format_string)
    : entries_ (entries),
      var_type_ (var_type),
      log_format_string_ (log_format_string)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    // Create a Setaf log format

    CUTS_Setaf_Log_Format * log_format = 0;

    this->log_format_string_.assign (begin, end);

    ACE_NEW_THROW_EX (log_format,
      CUTS_Setaf_Log_Format (this->var_type_),
                        ACE_bad_alloc ());

    // process the string return from the parser and populate the object
    // and store it in the vector

    log_format->process_format_string (this->log_format_string_);
    this->entries_.push_back (log_format);
  }

private:

  CUTS_SETAF_UTILS::Setaf_Entries & entries_;

  std::string & var_type_;

  std::string & log_format_string_;

};

/**
 * @struct create_setaf_log_format_relation
 */
struct create_setaf_log_format_relation
{
   create_setaf_log_format_relation (CUTS_SETAF_UTILS::Setaf_Relations & relations,
                                        std::string & cause_str,
                                        std::string & effect_str)
    : relations_ (relations),
      cause_str_ (cause_str),
      effect_str_ (effect_str)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    CUTS_Setaf_Log_Format_Relation * rel = 0;

    this->effect_str_.assign (begin, end);

    ACE_NEW_THROW_EX (rel,
      CUTS_Setaf_Log_Format_Relation (),
      ACE_bad_alloc ());

    // process the string return from the parser and populate the object
    // and store it in the vector

    rel->process_relation_strings (this->cause_str_,
      this->effect_str_);

    this->relations_.push_back (rel);
  }

private:
  CUTS_SETAF_UTILS::Setaf_Relations & relations_;

  std::string & cause_str_;

  std::string & effect_str_;

};

/**
 * @struct create_setaf_log_format
 */
struct create_setaf_log_format_code
{
  create_setaf_log_format_code (CUTS_SETAF_UTILS::Setaf_Code & codes,
                                std::string & code_id,
                                std::string & code)
    : codes_ (codes),
      code_id_ (code_id),
      code_ (code)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    CUTS_Setaf_Log_Format_Code * log_format_code = 0;

    this->code_.assign (begin, end);

    ACE_NEW_THROW_EX (log_format_code,
      CUTS_Setaf_Log_Format_Code (this->code_id_, this->code_),
                        ACE_bad_alloc ());

    // process the string return from the parser and populate the object
    // and store it in the vector
    this->codes_.push_back (log_format_code);
  }

private:

  CUTS_SETAF_UTILS::Setaf_Code & codes_;

  std::string & code_id_;

  std::string & code_;

};


/**
 * @struct CUTS_Setaf_Lang_Compiler_Grammar
 */
struct CUTS_Setaf_Lang_Compiler_Grammar :
  boost::spirit::grammar <CUTS_Setaf_Lang_Compiler_Grammar>
{
  /**
   * Initializing constructor
   */
  CUTS_Setaf_Lang_Compiler_Grammar (CUTS_SETAF_UTILS::Setaf_Entries & entries,
                                    CUTS_SETAF_UTILS::Setaf_Relations & relations,
                                    CUTS_SETAF_UTILS::string_vector & var_decls,
                                    CUTS_SETAF_UTILS::Setaf_Code & codes,
                                    std::string & init_str,
                                    std::string & reset_str)
    : entries_ (entries),
      relations_ (relations),
      var_decls_ (var_decls),
      codes_ (codes),
      init_str_ (init_str),
      reset_str_ (reset_str)
  {

  }

  /**
   * @struct definition
   */
  template <typename ScannerT>
  struct definition
  {
    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */

     // Rules to parse the adaptation specification

    definition (CUTS_Setaf_Lang_Compiler_Grammar const & self)
    {
      this->type_ =
        spirit::str_p("int") |
        spirit::str_p("long") |
        spirit::str_p("string") |
        spirit::str_p("std::string");

      this->ident_ =
        spirit::lexeme_d[spirit::alpha_p >>
        *(spirit::alnum_p | spirit::ch_p ('_'))];

      this->variable_decl_ =
        this->type_ >>
        this->ident_ >>
        spirit::ch_p (';');

      this->variables_ =
        spirit::str_p("Variables:") >>
        *(this->variable_decl_[spirit::push_back_a (self.var_decls_)]);

      this->init_code_ =
        spirit::lexeme_d[*(spirit::anychar_p - spirit::str_p ("Reset:"))];

      this->init_ =
        spirit::str_p("Init:") >>
        this->init_code_[spirit::assign (self.init_str_)];

      this->reset_code_ =
        spirit::lexeme_d[*(spirit::anychar_p - spirit::str_p ("DataPoints:"))];

      this->reset_ =
        spirit::str_p("Reset:") >>
        this->reset_code_[spirit::assign (self.reset_str_)];

      this->log_format_ident_ =
        this->ident_ >> spirit::ch_p ('.') >>
        spirit::alpha_p >> *(spirit::alnum_p);

      this->column_decl_ =
        this->type_[spirit::assign (this->var_type_)] >>
        this->log_format_ident_ [create_setaf_log_format (
        self.entries_, this->var_type_, this->log_format_string_)] >>
        spirit::ch_p (';');

      this->columns_ =
        spirit::str_p ("DataPoints:") >> *(this->column_decl_);

      this->relation_decl_ =
        this->log_format_ident_[spirit::assign (this->cause_str_)] >>
        spirit::ch_p ('-') >> spirit::ch_p ('>') >>
        this->log_format_ident_[create_setaf_log_format_relation (
        self.relations_, this->cause_str_, this->effect_str_)] >>
        spirit::ch_p (';');

      this->relations_ =
        spirit::str_p ("Relations:") >> *(this->relation_decl_);

      this->adaption_code_ =
        spirit::lexeme_d[*(spirit::anychar_p - spirit::str_p ("On"))];

      this->log_format_adapts_ =
        spirit::str_p ("On") >> this->ident_[spirit::assign (this->code_id_)] >>
        spirit::ch_p (':') >> this->adaption_code_[create_setaf_log_format_code (
        self.codes_, this->code_id_, this->code_)];

      this->spec_ =
        !(this->variables_) >> !(this->init_) >>
        !(this->reset_) >> this->columns_ >>
        this->relations_ >> +(this->log_format_adapts_);

    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->spec_;
    }

  private:

    // Grammar rules

    boost::spirit::rule <ScannerT> spec_;
    boost::spirit::rule <ScannerT> variables_;
    boost::spirit::rule <ScannerT> init_;
    boost::spirit::rule <ScannerT> reset_;
    boost::spirit::rule <ScannerT> type_;
    boost::spirit::rule <ScannerT> ident_;
    boost::spirit::rule <ScannerT> variable_decl_;
    boost::spirit::rule <ScannerT> columns_;
    boost::spirit::rule <ScannerT> column_decl_;
    boost::spirit::rule <ScannerT> log_format_ident_;
    boost::spirit::rule <ScannerT> relation_decl_;
    boost::spirit::rule <ScannerT> relations_;
    boost::spirit::rule <ScannerT> log_format_adapts_;
    boost::spirit::rule <ScannerT> adaption_code_;
    boost::spirit::rule <ScannerT> init_code_;
    boost::spirit::rule <ScannerT> reset_code_;

    std::string var_type_;
    std::string log_format_string_;
    std::string cause_str_;
    std::string effect_str_;
    std::string code_id_;
    std::string code_;

};

private:

  // container objects to keep the parsed data

  CUTS_SETAF_UTILS::Setaf_Entries & entries_;

  CUTS_SETAF_UTILS::Setaf_Relations & relations_;

  CUTS_SETAF_UTILS::string_vector & var_decls_;

  CUTS_SETAF_UTILS::Setaf_Code & codes_;

  std::string & init_str_;

  std::string & reset_str_;

};

//
// CUTS_Setaf_Lang_Compiler
//
CUTS_Setaf_Lang_Compiler::CUTS_Setaf_Lang_Compiler()
{

}

//
// ~CUTS_Setaf_Lang_Compiler
//
CUTS_Setaf_Lang_Compiler::~CUTS_Setaf_Lang_Compiler (void)
{

}

//
// compile
//
bool CUTS_Setaf_Lang_Compiler::compile (const char * file_content,
                                        CUTS_SETAF_UTILS::Setaf_Entries & entries,
                                        CUTS_SETAF_UTILS::Setaf_Relations & relations,
                                        CUTS_SETAF_UTILS::string_vector & var_decls,
                                        CUTS_SETAF_UTILS::Setaf_Code & codes,
                                        std::string & init_code,
                                        std::string & reset_code)
{
  // Initiate the grammar
  CUTS_Setaf_Lang_Compiler_Grammar grammar (
    entries, relations, var_decls, codes, init_code, reset_code);

  // Parse the adaptation spec using the grammaar.
  boost::spirit::parse_info < > result =
    boost::spirit::parse (file_content, grammar, boost::spirit::space_p);

  return result.full;
}