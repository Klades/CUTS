// $Id$

#include "Log_Format_Compiler.h"
#include "Variable.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "ace/CORBA_macros.h"

/**
 * @struct append
 */
struct append
{
  append (std::ostringstream & ostr)
    : ostr_ (ostr)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    std::string text (begin, end);

    // Escape any special characters before append;
    static const char * special = ".()+*?\\";
    std::string::size_type found = text.find_first_of (special);

    while (found != std::string::npos)
    {
      text.insert (found, 1, '\\');
      found = text.find_first_of (special, found + 2);
    }

    this->ostr_ << text;
  }

private:
  std::ostringstream & ostr_;
};

/**
 * @struct capture
 */
struct capture
{
  capture (std::ostringstream & ostr, std::string & type, std::string & name)
    : ostr_ (ostr),
      type_ (type),
      name_ (name)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT, IteratorT) const
  {
    std::string pcre_type;

    if (this->type_ == "INT")
      pcre_type = "-?\\d+";
    else if (this->type_ == "UINT")
      pcre_type = "\\d+";
    else if (this->type_ == "STRING")
      pcre_type = "\\S+";
    else if (this->type_ == "FLOAT")
      pcre_type = "\\d*\\.\\d+";

    this->ostr_ << "(?<" << this->name_ << ">" << pcre_type << ")";
  }

private:
  std::ostringstream & ostr_;

  std::string & type_;

  std::string & name_;
};

/**
 * @struct insert
 */
struct insert
{
  insert (CUTS_Log_Format_Variable_Table & vars, std::string & type, std::string & name)
    : vars_ (vars),
      type_ (type),
      name_ (name)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    CUTS_Log_Format_Variable * variable = 0;
    size_t index = this->vars_.current_size ();

    if (this->type_ == "STRING")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_String_Log_Format_Variable (index),
                        ACE_bad_alloc ());
    }
    else if (this->type_ == "INT")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Integer_Log_Format_Variable (index),
                        ACE_bad_alloc ());
    }
    else if (this->type_ == "FLOAT")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Integer_Log_Format_Variable (index),
                        ACE_bad_alloc ());
    }
    else if (this->type_ == "UINT")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Integer_Log_Format_Variable (index),
                        ACE_bad_alloc ());
    }

    this->name_.assign (begin, end);
    this->vars_.bind (this->name_.c_str (), variable);
  }

private:
  CUTS_Log_Format_Variable_Table & vars_;

  std::string & type_;

  std::string & name_;
};

/**
 * @struct CUTS_Log_Format_Compiler_Grammar
 */
struct CUTS_Log_Format_Compiler_Grammar :
  boost::spirit::grammar <CUTS_Log_Format_Compiler_Grammar>
{
  /**
   * Initializing constructor
   */
  CUTS_Log_Format_Compiler_Grammar (std::ostringstream & expr,
                                    CUTS_Log_Format_Variable_Table & vars)
    : expr_ (expr),
      vars_ (vars)
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
    definition (CUTS_Log_Format_Compiler_Grammar const & self)
    {
      this->text_ =
        *(boost::spirit::anychar_p - (boost::spirit::ch_p ('{') | '}'));

      this->ident_ =
        *boost::spirit::alpha_p;

      this->variable_tag_ =
        boost::spirit::confix_p ('{', this->variable_[capture (self.expr_, this->vartype_, this->varname_)], '}');

      this->variable_ =
        this->ident_[boost::spirit::assign (this->vartype_)] >>
        *boost::spirit::space_p >>
        this->ident_[insert (self.vars_, this->vartype_, this->varname_)];

      this->format_ =
        this->text_ [append (self.expr_)] >>
        *(this->variable_tag_ >> this->text_[append (self.expr_)]);
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->format_;
    }

  private:
    boost::spirit::rule <ScannerT> text_;

    boost::spirit::rule <ScannerT> ident_;

    boost::spirit::rule <ScannerT> variable_;

    boost::spirit::rule <ScannerT> variable_tag_;

    boost::spirit::rule <ScannerT> format_;

    std::string varname_;

    std::string vartype_;
  };

private:
  std::ostringstream & expr_;

  CUTS_Log_Format_Variable_Table & vars_;
};

//
// CUTS_Log_Format_Compiler
//
CUTS_Log_Format_Compiler::CUTS_Log_Format_Compiler (void)
{

}

//
// ~CUTS_Log_Format_Compiler
//
CUTS_Log_Format_Compiler::~CUTS_Log_Format_Compiler (void)
{

}

//
// compile
//
bool CUTS_Log_Format_Compiler::compile (const char * format,
                                        std::ostringstream & expr,
                                        CUTS_Log_Format_Variable_Table & vars)
{
  CUTS_Log_Format_Compiler_Grammar grammar (expr, vars);

  boost::spirit::parse_info < > result =
    boost::spirit::parse (format, grammar);

  return result.full;
}

