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

// Forward decl.
class CUTS_Property_Map;

namespace actors
{
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
                  "%T - %M - storing property [%s] => %s\n",
                  this->name_.c_str (),
                  this->value_.c_str ()));

      this->prop_map_[this->name_.c_str ()] = this->value_.c_str ();
    }

  private:
    mutable CUTS_Property_Map & prop_map_;

    const std::string & name_;

    const std::string & value_;
  };
}

/**
 * @class CUTS_Property_Parser
 */
class CUTS_COMMON_UTILS_Export CUTS_Property_Parser
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
   * Parse the data between the iterators.
   *
   * @param[in]       begin     Beginning of data
   * @param[in]       end       End of data
   */
  template <typename IteratorT>
  bool parse (IteratorT begin, IteratorT end);

  /**
   * Parse the specified string for properties.
   *
   * @param[in]       str       String to parse.
   */
  bool parse (const char * str);

private:
  /**
   * @class CUTS_Property_Parser_i
   */
  class CUTS_COMMON_UTILS_Export CUTS_Property_Parser_i :
    public boost::spirit::grammar <CUTS_Property_Parser_i>
  {
  public:
    /**
     * Initializing constructor
     *
     * @param[inout]        map         Target property map.
     */
    CUTS_Property_Parser_i (CUTS_Property_Map & map);

    /**
     * @class definition
     *
     * Definition of the grammar for the hosting parser.
     */
    template <typename ScannerT>
    class definition
    {
    public:
      definition (CUTS_Property_Parser_i const & self);

      const boost::spirit::rule <ScannerT> & start (void) const;

    private:
      boost::spirit::rule <ScannerT> property_;

      boost::spirit::rule <ScannerT> property_name_;

      boost::spirit::rule <ScannerT> property_value_;

      boost::spirit::rule <ScannerT> property_list_;

      std::string name_;

      std::string value_;
    };

  private:
    /// Property map used by the decoder.
    CUTS_Property_Map & prop_map_;
  };

  /// Reference to property map used during substitution
  CUTS_Property_Map & prop_map_;
};

#include "Property_Parser_T.cpp"

#endif  // !defined _CUTS_PROPERTY_PARSER_H_
