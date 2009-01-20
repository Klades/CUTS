// -*- C++ -*-

//=============================================================================
/**
 * @file          Property_Parser.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROPERTY_PARSER_H_
#define _CUTS_PROPERTY_PARSER_H_

#include "Property_Map.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/lists.hpp"
#include "ace/Log_Msg.h"

/**
 * @class CUTS_Property_Parser_Grammar
 */
class CUTS_Property_Parser_Grammar :
  public boost::spirit::grammar <CUTS_Property_Parser_Grammar>
{
public:
  CUTS_Property_Parser_Grammar (CUTS_Property_Map & prop_map)
    : prop_map_ (prop_map)
  {

  }

  struct insert_property
  {
    insert_property (CUTS_Property_Map & map,
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
                  "%T (%t) - %M - storing property [%s] => %s\n",
                  this->name_.c_str (),
                  this->value_.c_str ()));

      this->prop_map_[this->name_.c_str ()] = this->value_.c_str ();
    }

  private:
    mutable CUTS_Property_Map & prop_map_;

    const std::string & name_;

    const std::string & value_;
  };

  template <typename ScannerT>
  class definition
  {
  public:
    definition (CUTS_Property_Parser_Grammar const & self)
    {
      using namespace boost::spirit;

      this->property_name_ =
        lexeme_d[(alpha_p | '_') >> *(alnum_p | '_')];

      this->property_value_ =
        lexeme_d[*(anychar_p - eol_p)];

      this->property_ =
        this->property_name_[assign_a (this->name_)] >> '=' >>
        this->property_value_[assign_a (this->value_)];

      this->property_list_ =
        *(this->property_[insert_property (self.prop_map_, this->name_, this->value_)]);
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->property_list_;
    }

  private:
    boost::spirit::rule <ScannerT> property_;

    boost::spirit::rule <ScannerT> property_name_;

    boost::spirit::rule <ScannerT> property_value_;

    boost::spirit::rule <ScannerT> property_list_;

    std::string name_;

    std::string value_;
  };

private:
  CUTS_Property_Map & prop_map_;
};

/**
 * @class CUTS_Property_Parser
 */
class CUTS_UTILS_Export CUTS_Property_Parser
{
public:
  /**
   * Initializing constructor. This will set the target property
   * map the parser will use to store new properties, and retrieve
   * existing ones.
   *
   * @param[in]       map       Target property map
   */
  CUTS_Property_Parser (CUTS_Property_Map & map);

  /// Destructor
  ~CUTS_Property_Parser (void);

  /**
   * Parse the specified string for properties.
   *
   * @param[in]       str       String to parse.
   */
  bool parse (const char * str);

  bool parse_str (const ACE_CString & str);

  template <typename IteratorT>
  bool parse (IteratorT begin, IteratorT end)
  {
    CUTS_Property_Parser_Grammar grammar (this->prop_map_);

    boost::spirit::parse_info <IteratorT> result =
      boost::spirit::parse (begin,
                            end,
                            grammar >> !boost::spirit::end_p,
                            boost::spirit::space_p);

    return result.full;
  }

private:
  /// Reference to property map used during substitution
  CUTS_Property_Map & prop_map_;
};

#endif  // !defined _CUTS_PROPERTY_PARSER_H_
