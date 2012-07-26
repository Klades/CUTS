// $Id$

#include "Format_Parser.h"

#include "ace/OS_NS_stdio.h"
#include "ace/Log_Msg.h"

#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_stl.hpp"
#include "boost/spirit/include/phoenix_object.hpp"

#include <cstdarg>

namespace actors
{
  namespace qi = boost::spirit::qi;

  /**
   * @struct simple_arg
   */
  template <typename T>
  struct simple_arg
  {
    template <typename Context>
    void operator () (qi::unused_type, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      std::ostream & ostr = fusion::at_c <2> (ctx.attributes);
      va_list & args = fusion::at_c <1> (ctx.attributes);

      // Get the next value from the argument list, and write it to
      // the output stream.
      T val = va_arg (args, T);
      ostr << val;
    }
  };


  /**
   * @struct append
   */
  struct append
  {
    template <typename Context>
    void operator () (char const & val, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      std::ostream & ostr = fusion::at_c <2> (ctx.attributes);
      ostr << val;
    }

    template <typename Context>
    void operator () (std::string const & val, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      std::ostream & ostr = fusion::at_c <2> (ctx.attributes);
      ostr << val;
    }
  };
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Format_Parser_i

template <typename IteratorT, typename SpaceT>
class CUTS_Format_Parser_i :
  public boost::spirit::qi::grammar <IteratorT, void (va_list & args, std::ostream &)>
{
public:
  CUTS_Format_Parser_i (void)
    : CUTS_Format_Parser_i::base_type (content_),
      token_value_ (std::string ("token_value")),
      token_ (std::string ("token")),
      text_ (std::string ("text")),
      content_ (std::string ("content"))
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;

    this->content_ =
      qi::no_skip[
        this->text_[actors::append ()] >>
          *(this->token_ (qi::_r1, qi::_r2) >> this->text_[actors::append ()])];

    this->token_ =
      qi::lit ('%') >> this->token_value_ (qi::_r1, qi::_r2);

    this->token_value_ =
      qi::lit ('i')[actors::simple_arg <int> ()] |
      qi::lit ('d')[actors::simple_arg <int> ()] |
      qi::lit ('c')[actors::simple_arg <char> ()] |
      qi::lit ('s')[actors::simple_arg <char *> ()] |
      qi::lit ('f')[actors::simple_arg <double> ()] |
      qi::lit ('B')[actors::simple_arg <size_t> ()] |
      qi::lit ('b')[actors::simple_arg <ssize_t> ()] |
      qi::lit ('u')[actors::simple_arg <unsigned int> ()] |
      qi::lit ('q')[actors::simple_arg <long long> ()] |
      qi::lit ('Q')[actors::simple_arg <unsigned long long> ()] |
      qi::lit (':')[actors::simple_arg <time_t> ()] |
      qi::char_ ('%')[actors::append ()];

    this->text_ %= *(qi::char_ - '%');

    qi::on_error <qi::fail>
      (content_,
       std::cerr
                << phoenix::val ("Error! Expecting ")
                << qi::_4                               // what failed?
                << phoenix::val (" here: \"")
                << phoenix::construct <std::string> (qi::_3, qi::_2)   // iterators to error-pos, end
                << phoenix::val ("\"")
                << std::endl
        );
  }

private:
  /// Content of the string.
  boost::spirit::qi::rule <IteratorT, void (va_list &, std::ostream &)> content_;

  /// rule: token_;
  boost::spirit::qi::rule <IteratorT, void (va_list &, std::ostream &)> token_;

  /// rule: token_;
  boost::spirit::qi::rule <IteratorT, void (va_list &, std::ostream &)> token_value_;

  /// rule: text_;
  boost::spirit::qi::rule <IteratorT, std::string ()> text_;
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
parse (const std::string & format, va_list & args, std::ostream & ostr)
{
  namespace spirit = boost::spirit;
  namespace qi = boost::spirit::qi;
  namespace phoenix = boost::phoenix;

  // Parse the contents for the file.
  CUTS_Format_Parser_i <
    std::string::const_iterator,
    spirit::ascii::space_type>
    grammar;

  bool retval =
    qi::phrase_parse (format.begin (),
                      format.end (),
                      grammar (phoenix::ref (args), phoenix::ref (ostr)),
                      spirit::ascii::space);

  return retval;
}
