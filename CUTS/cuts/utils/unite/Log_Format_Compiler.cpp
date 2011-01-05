// $Id$

#include "Log_Format_Compiler.h"
#include "Variable.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "ace/CORBA_macros.h"
#include "ace/streams.h"



// Given a letter in the DateTime format string, this
// function will return the occurrence of that letter

//
// letter_count
//
int letter_count (std::string & format, char ch)
{
  // For a given character in the Date_Time format find the
  // number of occurrences to determine the pcre expression
  int count = 0;
  int index = -1;
  while (1)
  {
    index = format.find_first_of (ch, index + 1);
    if (index == format.npos)
      break;
    else
      count++;
  }
  return count;
}

//
// get_datetime_pcre_type
//
std::string get_datetime_pcre_type (std::string & format)
{
  // Converts the user specifies DateTime format to a pcre type

  int Y_count = letter_count (format, 'Y');
  int M_count = letter_count (format, 'M');
  int D_count = letter_count (format, 'D');
  int h_count = letter_count (format, 'h');
  int m_count = letter_count (format, 'm');
  int s_count = letter_count (format, 's');
  int S_count = letter_count (format, 'S');

  // writing the letter counts to the pcre stream

  std::ostringstream ostr;

  if(Y_count != 0)
  {
    ostr<<"\\d{"<<Y_count<<"}:\\d{"<<M_count<<"}:\\d{"<<D_count<<"}:";
  }
  ostr<<"\\d{"<<h_count<<"}:\\d{"<<m_count<<"}:\\d{"<<s_count<<"}\\.\\d{"<<S_count<<"}";

  std::string pcre = ostr.str ();
  return pcre;
}

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
    static const char * special = "{}|[]^.()+*?\\-";
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
  capture (std::ostringstream & ostr,
           std::string & type,
           std::string & name,
           std::string & dt_format)
    : ostr_ (ostr),
      type_ (type),
      name_ (name),
      dt_format_ (dt_format)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT, IteratorT) const
  {
    std::string pcre_type;

    if (this->type_ == "INT" ||
        this->type_ == "LONG" ||
        this->type_ == "LONGLONG" ||
        this->type_ == "SHORT")
      pcre_type = "-?\\d+";
    else if (this->type_ == "UINT" ||
             this->type_ == "ULONG" ||
             this->type_ == "ULONGLONG" ||
             this->type_ == "USHORT")
      pcre_type = "\\d+";
    else if (this->type_ == "STRING")
      pcre_type = "\\S+";
    else if (this->type_ == "FLOAT")
      pcre_type = "\\d*\\.\\d+";

    // For DATETIME and REGEX we can't exactly match the type string.
    // So we do a find

    else if(((this->type_).find ("DATETIME") !=
      std::string::npos)||
      ((this->type_).find ("REGEX") !=
      std::string::npos))
    {
      // The user specified format is in between the parenthesis

      size_t pos1;
      size_t pos2;

      pos1 = (this->type_).find ("(");
      pos2 = (this->type_).find (")");

      size_t n = pos2 - pos1 - 1;
      std::string format = (this->type_).substr (pos1 + 1, n);
      if((this->type_).find ("DATETIME") != std::string::npos)
      {
        pcre_type = get_datetime_pcre_type (format);
      }
      else
      {
        pcre_type = format;
      }
    }

    this->ostr_ << "(?<" << this->name_ << ">" << pcre_type << ")";

  }


private:
  std::ostringstream & ostr_;

  std::string & type_;

  std::string & name_;

  std::string & dt_format_;

};

/**
 * @struct insert
 */
struct insert
{
  insert (CUTS_Log_Format_Variable_Table & vars,
          std::string & type,
          std::string & name,
          std::string & dt_format)
    : vars_ (vars),
      type_ (type),
      name_ (name),
      dt_format_ (dt_format)
  {

  }

  template <typename IteratorT>
  void operator () (IteratorT begin, IteratorT end) const
  {
    // Create the variable based on the type

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
                        CUTS_Basic_Log_Format_Variable_T <ACE_INT32> (index),
                        ACE_bad_alloc ());
    }
    else if (this->type_ == "LONG")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <ACE_INT32> (index),
                        ACE_bad_alloc ());
    }
    else if (this->type_ == "LONGLONG")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <ACE_INT64> (index),
                        ACE_bad_alloc ());
    }
    else if (this->type_ == "SHORT")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <ACE_INT16> (index),
                        ACE_bad_alloc ());
    }
    else if (this->type_ == "FLOAT")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <double> (index),
                        ACE_bad_alloc ());
    }
    else if (this->type_ == "UINT")
    {
      ACE_NEW_THROW_EX (variable,
                        CUTS_Basic_Log_Format_Variable_T <unsigned int> (index),
                        ACE_bad_alloc ());
    }

    else if (((this->type_).find ("DATETIME") != std::string::npos) ||
              ((this->type_).find ("REGEX") != std::string::npos))
    {

      // Create either a Date_Time or a Regex variable

      size_t pos1;
      size_t pos2;

      pos1 = (this->type_).find ("(");
      pos2 = (this->type_).find (")");

      size_t n = pos2 - pos1 - 1;
      std::string format = (this->type_).substr (pos1 + 1, n);

      if((this->type_).find ("DATETIME") !=
          std::string::npos)
      {
        ACE_NEW_THROW_EX (variable,
                      CUTS_Datetime_Log_Format_Variable (index, format),
                      ACE_bad_alloc ());
      }
      else
      {
        ACE_NEW_THROW_EX (variable,
                      CUTS_Regex_Log_Format_Variable (index, format),
                      ACE_bad_alloc ());
      }

    }

    this->name_.assign (begin, end);
    this->vars_.bind (this->name_.c_str (), variable);
  }

private:

  // The variable table
  CUTS_Log_Format_Variable_Table & vars_;

  // Type string returned from the parser
  std::string & type_;

  // Name of the variable returned from the parser
  std::string & name_;

  // User specified DateTime format in case of DateTime
  std::string & dt_format_;
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

      this->dt_chars_ = (boost::spirit::ch_p ('(') | boost::spirit::ch_p (')') |
        boost::spirit::ch_p (':') | boost::spirit::ch_p ('-') | boost::spirit::ch_p ('%') |
        boost::spirit::ch_p ('.'));

      this->ident_ =
        boost::spirit::lexeme_d[boost::spirit::alpha_p >> *(boost::spirit::alnum_p | this->dt_chars_)];

      this->variable_tag_ =
        boost::spirit::confix_p ('{',
        this->variable_[capture (self.expr_, this->vartype_, this->varname_, this->date_time_format_)], '}');

      this->variable_ =
        this->ident_[boost::spirit::assign (this->vartype_)] >>
        *boost::spirit::space_p >>
        this->ident_[insert (self.vars_, this->vartype_, this->varname_, this->date_time_format_)];

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

    boost::spirit::rule <ScannerT> dt_chars_;

    std::string varname_;

    std::string vartype_;

    std::string date_time_format_;
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
  // Parsing the string containg the log formats

  CUTS_Log_Format_Compiler_Grammar grammar (expr, vars);

  boost::spirit::parse_info < > result =
    boost::spirit::parse (format, grammar);

  return result.full;
}

