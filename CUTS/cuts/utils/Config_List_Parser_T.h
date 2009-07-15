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

#ifndef _CUTS_CONFIG_LIST_PARSER_T_H_
#define _CUTS_CONFIG_LIST_PARSER_T_H_

#include "cuts/utils/Property_Parser.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"
#include <string>

/**
 * @class CUTS_Config_List_Parser_Grammar_T
 *
 * Definition of the grammar for the configuration list parser. This
 * class is parameterized by the actor for handling configurations.
 */
template <typename ACTOR>
class CUTS_Config_List_Parser_Grammar_T :
  public boost::spirit::grammar <CUTS_Config_List_Parser_Grammar_T <ACTOR> >
{
public:
  /// Type definition of the actor.
  typedef ACTOR actor_type;

  /**
   * Initializing constructor.
   *
   * @param[in]         actor         Actor for handling events.
   */
  CUTS_Config_List_Parser_Grammar_T (ACTOR & actor);

  /// Destructor
  ~CUTS_Config_List_Parser_Grammar_T (void);

  template <typename ScannerT>
  class definition
  {
  public:
    /**
      * Initializing constructor.
      *
      * @param[in]     self        The input grammar.
      */
    definition (CUTS_Config_List_Parser_Grammar_T const & self)
    {
      using namespace boost::spirit;

      this->identifer_ =
        lexeme_d[(alpha_p | '_') >> *(alnum_p | '_')];

      this->config_ =
        str_p ("config") [begin_config (this->prop_map_)] >>
        confix_p ('(', (this->identifer_)[assign_a (this->name_)] , ')') >>
        !(":" >> list_p (this->identifer_[base_config (this->prop_map_, self.actor_)], ",", "{")) >>
        confix_p ('{', (*anychar_p)[parse_config (this->prop_map_)], '}');

      this->config_list_ =
        *(this->config_[handle_config (this->name_, this->prop_map_, self.actor_)]);
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->config_list_;
    }

  private:
    /**
     * @struct begin_config
     *
     * Functor for starting a new configuration.
     */
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
     * @struct base_config
     *
     * Functor for deriving a configuration.
     */
    struct base_config
    {
      base_config (CUTS_Property_Map & prop_map, ACTOR & actor)
        : prop_map_ (prop_map),
          actor_ (actor)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        std::string base_name (begin, end);
        this->actor_.base_config (this->prop_map_, base_name);
      }

    private:
      CUTS_Property_Map & prop_map_;

      ACTOR & actor_;
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
     * @struct handle_config
     *
     * Functor for handling a parse configuration.
     */
    struct handle_config
    {
      handle_config (const std::string & name,
                     CUTS_Property_Map & prop_map,
                     ACTOR & actor)
        : name_ (name),
          prop_map_ (prop_map),
          actor_ (actor)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT, IteratorT) const
      {
        this->prop_map_["config.name"] = this->name_.c_str ();
        this->actor_.handle_config (this->prop_map_);
      }

    private:
      const std::string & name_;

      CUTS_Property_Map & prop_map_;

      ACTOR & actor_;
    };

    /// Property map for the current configuration
    CUTS_Property_Map prop_map_;

    /// Current name of the configuration.
    std::string name_;

    /// rule: config_
    boost::spirit::rule <ScannerT> config_;

    /// rule: config_
    boost::spirit::rule <ScannerT> identifer_;

    /// rule: config_list_
    boost::spirit::rule <ScannerT> config_list_;
  };

private:
  ACTOR & actor_;
};

/**
 * @class CUTS_Config_List_Parser_T
 *
 * Parser for configuration files. This object is parameterizable
 * by a functor that processes each configuration in the file.
 */
 template <typename ACTOR>
class CUTS_Config_List_Parser_T
{
public:
  /**
   * Initializing constructor
   */
  CUTS_Config_List_Parser_T (ACTOR & actor);

  /// Destructor.
  ~CUTS_Config_List_Parser_T (void);

  /**
   * Parse the specified configuration file.
   */
  bool parse (const char * filename);

private:
  /// Underlying grammar for the parser.
  CUTS_Config_List_Parser_Grammar_T <ACTOR> grammar_;
};

#if defined (__CUTS_INLINE__)
#include "Config_List_Parser_T.inl"
#endif

#include "Config_List_Parser_T.cpp"

#endif  // !defined _CUTS_TEMPLATE_CONFIG_LIST_PARSER_H_
