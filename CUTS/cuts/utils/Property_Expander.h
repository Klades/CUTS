// -*- C++ -*-

//=============================================================================
/**
 * @file        Property_Expander.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROPERTY_EXPANDER_H_
#define _CUTS_PROPERTY_EXPANDER_H_

#include "Property_Map.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/streams.h"
#include "ace/Log_Msg.h"
#include "boost/spirit/core.hpp"
#include "boost/spirit/utility/confix.hpp"

// Forward decl.
class CUTS_Property_Expander_Grammar;

/**
 * @class CUTS_Property_Expander
 *
 * Substitutes variables defined in a string with their expanded value.
 * Variables are defined by enclosing a set of non-whitespace characters
 * with the following: ${ }. Right now, the value of a variable is located
 * in the system's environment variables.
 */
class CUTS_UTILS_Export CUTS_Property_Expander
{
public:
  /// Defualt constructor.
  CUTS_Property_Expander (const CUTS_Property_Map & map);

  /// Destructor
  ~CUTS_Property_Expander (void);

  /**
   * Expand the properties in the \a str. The result will be placed
   * in \a out.
   *
   * @param[in]         str       String with environment variables
   * @param[out]        out       Output stream for expansion of \a str.
   */
  int expand (const char * str, bool use_env, std::ostream & out);

  template <typename IteratorT>
  int expand (IteratorT begin, IteratorT end, bool use_env, std::ostream & out)
  {
    CUTS_Property_Expander_Grammar grammar (this->prop_map_, use_env, out);

    boost::spirit::parse_info <IteratorT> info =
      boost::spirit::parse (begin, end, grammar);

    return info.full ? 0 : -1;
  }

private:
  /// Reference to property map used during substitution
  const CUTS_Property_Map & prop_map_;
};

/**
  * @class CUTS_Property_Expander_Grammar
  *
  * Implementation
  */
class CUTS_Property_Expander_Grammar :
  public boost::spirit::grammar <CUTS_Property_Expander_Grammar>
{
public:
  /**
    * Initializing constructor
    *
    * @param[in]       map           Source property map
    * @param[in]       use_env       Use environment variables
    * @param[out]      ostr          Target stream for output
    */
  CUTS_Property_Expander_Grammar (const CUTS_Property_Map & map,
                                  bool use_env,
                                  std::ostream & ostr)
    : ostr_ (ostr),
      use_env_ (use_env),
      prop_map_ (map)
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
    definition (CUTS_Property_Expander_Grammar const & self)
    {
      this->property_name_ =
        boost::spirit::lexeme_d[
          *(boost::spirit::print_p - '}')];

      this->text_ =
        *(boost::spirit::anychar_p - '$');

      this->property_ =
        boost::spirit::confix_p ("${",
          this->property_name_[expand (self.prop_map_, self.use_env_, self.ostr_)],
          "}");

      this->content_ =
        this->text_[append (self.ostr_)] >>
        *(this->property_ >> this->text_[append (self.ostr_)]);
    }

    const boost::spirit::rule <ScannerT> & start (void) const
    {
      return this->content_;
    }

  private:
    struct append
    {
      append (std::ostream & out)
        : out_ (out)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        std::string str (begin, end);
        this->out_ << str;
      }

    private:
      std::ostream & out_;
    };

    struct expand
    {
      expand (const CUTS_Property_Map & map, bool use_env, std::ostream & out)
        : prop_map_ (map),
          use_env_ (use_env),
          out_ (out)
      {

      }

      template <typename IteratorT>
      void operator () (IteratorT begin, IteratorT end) const
      {
        // Store the name of the property.
        std::string name (begin, end);

        // Locate the value of the property.
        ACE_CString value;

        if (this->prop_map_.get (name.c_str (), value) == 0)
        {
          // Write the value of the property.
          this->out_ << value.c_str ();
        }
        else
        {
          if (this->use_env_)
          {
            // Try and locate the name in the environment variables.
            char * val = ACE_OS::getenv (name.c_str ());

            if (val != 0)
              this->out_ << val;
            else
              this->out_ << "${" << name << "}";
          }
          else
          {
            this->out_ << "${" << name << "}";
          }
        }
      }

    private:
      const CUTS_Property_Map & prop_map_;

      bool use_env_;

      std::ostream & out_;
    };

    /// rule: var_name_;
    boost::spirit::rule <ScannerT> property_name_;

    /// rule: env_var_
    boost::spirit::rule <ScannerT> property_;

    /// rule: text_;
    boost::spirit::rule <ScannerT> text_;

    /// Content of the string.
    boost::spirit::rule <ScannerT> content_;
  };

private:
  /// Target output stream.
  std::ostream & ostr_;

  bool use_env_;

  /// Property map used by expander.
  const CUTS_Property_Map & prop_map_;
};

#endif  // !defined _CUTS_ENV_VARIABLE_DECODER_H_
