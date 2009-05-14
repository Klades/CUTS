// -*- C++ -*-

//=============================================================================
/**
 * @file        Property_Evaluator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROPERTY_EVALUATOR_H_
#define _CUTS_PROPERTY_EVALUATOR_H_

#include "Property_Map.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/streams.h"
#include "ace/Log_Msg.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"

// Forward decl.
template <typename T>
class CUTS_Property_Evaluator_Grammar;

/**
 * @class CUTS_Property_Evaluator_Config
 *
 * Configuration for the CUTS_Property_Evaluator object.
 */
class CUTS_UTILS_Export CUTS_Property_Evaluator_Config
{
public:
  /// Defualt constructor.
  CUTS_Property_Evaluator_Config (void);

  /// Use environment variables.
  bool use_env_;

  /// The open tag for the property.
  ACE_CString open_tag_;

  /// The close tag for the property.
  ACE_CString close_tag_;
};

/**
 * @class CUTS_Property_Evaluator
 *
 * Substitutes variables defined in a string with their expanded value.
 * Variables are defined by enclosing a set of non-whitespace characters
 * with the following: ${ }. Right now, the value of a variable is located
 * in the system's environment variables.
 */
template <typename ACTOR>
class CUTS_Property_Evaluator_T
{
public:
  /// Type definition of the actor type.
  typedef ACTOR actor_type;

  /// Type definition of the grammar.
  typedef CUTS_Property_Evaluator_Grammar <ACTOR> grammar_type;

  /**
   * Initializing constructor
   *
   * @param[in]       map           Map containing properties
   * @param[in]       actor         Actor object for evaluator
   */
  CUTS_Property_Evaluator_T (const CUTS_Property_Map & map, ACTOR & actor);

  /// Destructor
  ~CUTS_Property_Evaluator_T (void);

  /**
   * Expand the properties in the \a str. The result will be placed
   * in \a out.
   *
   * @param[in]         str       String with environment variables
   * @param[out]        out       Output stream for expansion of \a str.
   */
  bool evaluate (const char * str);

  /**
   * @overload
   */
  template <typename IteratorT>
  bool evaluate (IteratorT begin, IteratorT end);

  /**
   * Get the configuration for the evaluator.
   *
   * @return            Reference to configuration.
   */
  CUTS_Property_Evaluator_Config & config (void);

  /**
   * @overload
   *
   * @return            Read-only refernce to configuration
   */
  const CUTS_Property_Evaluator_Config & config (void) const;

  /**
   * Get the map currently used by the evaluator.
   */
  const CUTS_Property_Map & property_map (void) const;

private:
  /// Configuration for the property expander.
  CUTS_Property_Evaluator_Config config_;

  /// Grammar for the evaluator.
  grammar_type grammar_;
};

/**
 * @class CUTS_Property_Evaluator_Grammar
 *
 * Grammar for the CUTS_Property_Evaluator object.
 */
template <typename T>
class CUTS_Property_Evaluator_Grammar :
  public boost::spirit::grammar <CUTS_Property_Evaluator_Grammar <T> >
{
public:
  /**
    * Initializing constructor
    *
    * @param[in]       map           Source property map
    * @param[in]       use_env       Use environment variables
    * @param[out]      ostr          Target stream for output
    */
  CUTS_Property_Evaluator_Grammar (const CUTS_Property_Map & map,
                                   const CUTS_Property_Evaluator_Config & config,
                                   T & actor)
    : prop_map_ (map),
      config_ (config),
      actor_ (actor)
  {

  }

  const CUTS_Property_Map & property_map (void) const
  {
    return this->prop_map_;
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
    definition (CUTS_Property_Evaluator_Grammar const & self)
    {
      using namespace boost::spirit;

      this->special_chars_ = ch_p ('.') | '_';

      this->open_tag_ = str_p (self.config_.open_tag_.c_str ());

      this->close_tag_ = str_p (self.config_.close_tag_.c_str ());

      this->property_name_ =
        lexeme_d[(alpha_p >> *(alnum_p | this->special_chars_))];

      this->text_ =
        *(boost::spirit::anychar_p - this->open_tag_);

      this->property_ =
        boost::spirit::confix_p (
          this->open_tag_,
          this->property_name_[expand (self.prop_map_, self.config_, self.actor_)],
          this->close_tag_);

      this->content_ =
        this->text_[append (self.actor_)] >>
        *(this->property_ >> this->text_[append (self.actor_)]);
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->content_;
    }

  private:
    struct append
    {
      append (T & actor)
        : actor_ (actor)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        this->actor_.append (begin, end);
      }

    private:
      T & actor_;
    };

    struct expand
    {
      expand (const CUTS_Property_Map & map,
              const CUTS_Property_Evaluator_Config & config,
              T & actor)
        : prop_map_ (map),
          config_ (config),
          actor_ (actor)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        this->actor_.expand (begin, end, this->prop_map_, this->config_);
      }

    private:
      const CUTS_Property_Map & prop_map_;

      const CUTS_Property_Evaluator_Config & config_;

      T & actor_;
    };

    /// rule: var_name_;
    boost::spirit::rule <ScannerT> property_name_;

    /// rule: env_var_
    boost::spirit::rule <ScannerT> property_;

    /// rule: text_;
    boost::spirit::rule <ScannerT> text_;

    /// rule: content_;
    boost::spirit::rule <ScannerT> content_;

    boost::spirit::rule <ScannerT> special_chars_;

    boost::spirit::rule <ScannerT> open_tag_;

    boost::spirit::rule <ScannerT> close_tag_;
  };

private:
  /// Property map used by expander.
  const CUTS_Property_Map & prop_map_;

  /// Configuration for the property expander.
  const CUTS_Property_Evaluator_Config & config_;

  /// Target actors for the evalation.
  T & actor_;
};

#if defined (__CUTS_INLINE__)
#include "Property_Evaluator_T.inl"
#endif

#include "Property_Evaluator_T.cpp"

#endif  // !defined _CUTS_PROPERTY_EVALUATOR_H_
