// $Id$

#include "Format_Parser.h"
#include "ace/OS_NS_stdio.h"
#include "boost/spirit/core.hpp"

namespace actors
{
  /**
   * @class append
   *
   * Functor for inserting a string to a stream.
   */
  class append
  {
  public:
    append (std::ostream & ostr)
      : ostr_ (ostr)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT begin, IteratorT end) const
    {
      std::string str (begin, end);
      this->ostr_ << str;
    }

    template <typename CharT>
    void operator () (CharT ch) const
    {
      this->ostr_ << ch;
    }

  private:
    // Target stream for appending.
    std::ostream & ostr_;
  };

  /**
   * @class simple_arg
   */
  template <typename ARG_TYPE>
  class simple_arg
  {
  public:
    simple_arg (va_list & args, std::ostream & ostr)
      : args_ (args),
        ostr_ (ostr)
    {

    }

    template <typename CharT>
    void operator () (CharT) const
    {
      ARG_TYPE arg = va_arg (this->args_, ARG_TYPE);
      this->ostr_ << arg;
    }

  private:
    va_list & args_;

    std::ostream & ostr_;
  };

  /**
   * @class simple_arg
   */
  template < >
  class simple_arg <char>
  {
  public:
    simple_arg (va_list & args, std::ostream & ostr)
      : args_ (args),
        ostr_ (ostr)
    {

    }

    template <typename CharT>
    void operator () (CharT) const
    {
      char arg = static_cast <char> (va_arg (this->args_, int));
      this->ostr_ << arg;
    }

  private:
    va_list & args_;

    std::ostream & ostr_;
  };
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Format_Parser_i

class CUTS_Format_Parser_i :
  public boost::spirit::grammar <CUTS_Format_Parser_i>
{
public:
  CUTS_Format_Parser_i (va_list & args, std::ostream & ostr)
    : args_ (args),
      ostr_ (ostr)
  {

  }

  /**
   * @class definition
   *
   * Definition of the grammar.
   */
  template <typename ScannerT>
  class definition
  {
  public:
    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */
    definition (CUTS_Format_Parser_i const & self)
    {
      this->token_value_ =
        boost::spirit::ch_p ('i')[actors::simple_arg <int> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('d')[actors::simple_arg <int> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('c')[actors::simple_arg <char> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('s')[actors::simple_arg <char *> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('f')[actors::simple_arg <double> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('B')[actors::simple_arg <size_t> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('b')[actors::simple_arg <ssize_t> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('u')[actors::simple_arg <unsigned int> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('q')[actors::simple_arg <long long> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('Q')[actors::simple_arg <unsigned long long> (self.args_, self.ostr_)] |
        boost::spirit::ch_p (':')[actors::simple_arg <time_t> (self.args_, self.ostr_)] |
        boost::spirit::ch_p ('%')[actors::append (self.ostr_)];

      this->token_ =
        boost::spirit::lexeme_d [
          boost::spirit::ch_p ('%') >> this->token_value_];

      this->text_ =
        *(boost::spirit::anychar_p - '%');

      this->content_ =
        this->text_ [actors::append (self.ostr_)] >>
        *(this->token_ >> this->text_ [actors::append (self.ostr_)]);
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->content_;
    }

  private:
    /// rule: token_;
    boost::spirit::rule <ScannerT> token_value_;

    /// rule: token_;
    boost::spirit::rule <ScannerT> token_;

    /// rule: text_;
    boost::spirit::rule <ScannerT> text_;

    /// Content of the string.
    boost::spirit::rule <ScannerT> content_;
  };

private:
  /// Reference to the variable argument list.
  va_list & args_;

  /// Reference to the output string.
  std::ostream & ostr_;
};


///////////////////////////////////////////////////////////////////////////////
// class CUTS_Format_Parser

//
// CUTS_Format_Parser
//
CUTS_Format_Parser::CUTS_Format_Parser (void)
{

}

//
// ~CUTS_Format_Parser
//
CUTS_Format_Parser::~CUTS_Format_Parser (void)
{

}

//
// parse
//
bool CUTS_Format_Parser::
parse (const char * format, va_list args, std::ostream & out)
{
  CUTS_Format_Parser_i parser (args, out);

  boost::spirit::parse_info < > info =
    boost::spirit::parse (format, parser);

  return info.full;
}
