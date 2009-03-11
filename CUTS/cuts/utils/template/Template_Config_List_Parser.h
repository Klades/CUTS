// -*- C++ -*-

//=============================================================================
/**
 * @file        Template_Config_List_Parser.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEMPLATE_CONFIG_LIST_PARSER_H_
#define _CUTS_TEMPLATE_CONFIG_LIST_PARSER_H_

#include "cuts/utils/Property_Parser.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include "Template_Config_Handler.h"
#include <string>

/**
 * @class CUTS_Template_Config_List_Parser_Grammar
 *
 * Definition of the grammar for the configuration list parser.
 */
class CUTS_Template_Config_List_Parser_Grammar :
  public boost::spirit::grammar <CUTS_Template_Config_List_Parser_Grammar>
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_Template_Config_List_Parser_Grammar (CUTS_Template_Config_Handler * handler,
                                            const CUTS_Property_Map & overrides);

  /// Destructor
  ~CUTS_Template_Config_List_Parser_Grammar (void);

  template <typename ScannerT>
  class definition
  {
  public:
    /**
      * Initializing constructor.
      *
      * @param[in]     self        The input grammar.
      */
    definition (CUTS_Template_Config_List_Parser_Grammar const & self)
    {
      using namespace boost::spirit;

      this->config_ =
        str_p ("config") [begin_config (this->prop_map_)] >>
        confix_p ('(', (*anychar_p)[set_name (this->prop_map_)] , ')') >>
        confix_p ('{', (*anychar_p)[parse_config (this->prop_map_)], '}');

      this->config_list_ =
        *(this->config_[handle_config (this->prop_map_,
                                       self.overrides_,
                                       self.handler_)]);
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->config_list_;
    }

  private:
    struct begin_config
    {
      begin_config (CUTS_Property_Map & prop_map)
        : prop_map_ (prop_map)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        if (!this->prop_map_.empty ())
          this->prop_map_.clear ();
      }

    private:
      CUTS_Property_Map & prop_map_;
    };

    /**
     * @struct parse_config
     *
     * Functor for parsing a single configuration in the listing.
     */
    struct parse_config
    {
      parse_config (CUTS_Property_Map & prop_map)
        : prop_map_ (prop_map)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        // Parse the configuration.
        CUTS_Property_Parser parser (this->prop_map_);

        if (!parser.parse (begin, end))
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - failed to parse configuration "
                      "properties [%s]\n",
                      std::string (begin, end).c_str ()));
      }

    private:
      CUTS_Property_Map & prop_map_;
    };

    /**
     * @struct set_name
     *
     * Functor for setting the name of the configuration.
     */
    struct set_name
    {
      set_name (CUTS_Property_Map & map)
        : map_ (map)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        std::string name (begin, end);
        this->map_.set ("name", name.c_str());
      }

    private:
      CUTS_Property_Map & map_;
    };

    struct handle_config
    {
      handle_config (CUTS_Property_Map & prop_map,
                     const CUTS_Property_Map & overrides,
                     CUTS_Template_Config_Handler * handler)
        : prop_map_ (prop_map),
          overrides_ (overrides),
          handler_ (handler)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT, IteratorT) const
      {
        ACE_CString temp;
        this->prop_map_.get ("name", temp);

        this->prop_map_.join (this->overrides_, true);
        this->handler_->handle_config (this->prop_map_);
      }

    private:
      CUTS_Property_Map & prop_map_;

      const CUTS_Property_Map & overrides_;

      CUTS_Template_Config_Handler * handler_;
    };

    /// Property map for the current configuration
    CUTS_Property_Map prop_map_;

    /// rule: config_
    boost::spirit::rule <ScannerT> config_;

    /// rule: config_list_
    boost::spirit::rule <ScannerT> config_list_;
  };

private:
  /// Tempalte configuration handler for the parser.
  CUTS_Template_Config_Handler * handler_;

  /// Properties to override the values in the configuration file.
  const CUTS_Property_Map & overrides_;
};

/**
 * @class CUTS_Template_Config_List_Parser
 *
 * Parser for configuration files. This object is parameterizable
 * by a functor that processes each configuration in the file.
 */
class CUTS_TEMPLATE_COMMON_Export CUTS_Template_Config_List_Parser
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       overrides       Property overrides.
   */
  CUTS_Template_Config_List_Parser (CUTS_Template_Config_Handler * handler,
                                    const CUTS_Property_Map & overrides);

  /// Destructor.
  ~CUTS_Template_Config_List_Parser (void);

  /**
   * Parse the specified configuration file.
   *
   * @param[in]       filename        Location of configuration file.
   * @retval          -1              Failed to open \a filename
   * @retval          0               Parsing succeeded
   * @retval          >0              Number of errors
   */
  int parse (const char * filename);

private:
  /// Underlying grammar for the parser.
  CUTS_Template_Config_List_Parser_Grammar grammar_;
};

#if defined (__CUTS_INLINE__)
#include "Template_Config_List_Parser.inl"
#endif

#endif  // !defined _CUTS_TEMPLATE_CONFIG_LIST_PARSER_H_
