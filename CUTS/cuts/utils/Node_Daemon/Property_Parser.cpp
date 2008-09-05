// $Id$

#include "Property_Parser.h"
#include "cuts/Property_Map_T.h"
#include "ace/SString.h"
#include "ace/Log_Msg.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "boost/spirit/actor/assign_actor.hpp"

namespace actors
{
  struct insert_property
  {
    insert_property (CUTS_Property_Map_T <ACE_RW_Thread_Mutex> & map,
                     const std::string & name,
                     const std::string & value)
      : prop_map_ (map),
        name_ (name),
        value_ (value)
    {

    }

    template <typename IteratorT>
    void operator () (IteratorT, IteratorT) const
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - storing property [%s] => %s\n",
                  this->name_.c_str (),
                  this->value_.c_str ()));

      this->prop_map_[this->name_.c_str ()] = this->value_.c_str ();
    }

  private:
    mutable CUTS_Property_Map_T <ACE_RW_Thread_Mutex> & prop_map_;

    const std::string & name_;

    const std::string & value_;
  };
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Property_Parser_i

class CUTS_Property_Parser_i :
  public boost::spirit::grammar <CUTS_Property_Parser_i>
{
public:
  /// Default constructor.
  CUTS_Property_Parser_i (CUTS_Property_Map_T <ACE_RW_Thread_Mutex> & map)
    : prop_map_ (map)
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
    definition (CUTS_Property_Parser_i const & self)
    {
      this->property_name_ =
        boost::spirit::lexeme_d [*(boost::spirit::print_p - '=')];

      this->property_value_ =
        *(boost::spirit::anychar_p - '\n');

      this->property_ =
        (this->property_name_[boost::spirit::assign_a (this->name_)] >>
        '=' >>
        this->property_value_[boost::spirit::assign_a (this->value_)])
        [actors::insert_property (self.prop_map_, this->name_, this->value_)];
    }

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->property_;
    }

  private:
    /// rule: var_name_;
    boost::spirit::rule <ScannerT> property_;

    /// rule: env_var_
    boost::spirit::rule <ScannerT> property_name_;

    /// rule: text_;
    boost::spirit::rule <ScannerT> property_value_;

    std::string name_;

    std::string value_;
  };

private:
  /// Property map used by the decoder.
  CUTS_Property_Map_T <ACE_RW_Thread_Mutex> & prop_map_;
};

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Property_Parser

//
// CUTS_Property_Parser
//
CUTS_Property_Parser::
CUTS_Property_Parser (CUTS_Property_Map_T <ACE_RW_Thread_Mutex> & map)
: prop_map_ (map)
{

}

//
// ~CUTS_Property_Parser
//
CUTS_Property_Parser::~CUTS_Property_Parser (void)
{

}

//
// parse
//
bool CUTS_Property_Parser::parse (const char * begin, const char * end)
{
  CUTS_Property_Parser_i parser (this->prop_map_);

  boost::spirit::parse_info < > info =
    boost::spirit::parse (begin, end, parser);

  return info.full;
}

//
// parse
//
bool CUTS_Property_Parser::parse (const char * str)
{
  CUTS_Property_Parser_i parser (this->prop_map_);

  boost::spirit::parse_info < > info =
    boost::spirit::parse (str, parser);

  return info.full;
}
