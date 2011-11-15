// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_Env_Variable_Parser_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_ENV_VARIABLE_PARSER_T_H_
#define _CUTS_BE_ENV_VARIABLE_PARSER_T_H_

#include "boost/spirit/core.hpp"

/**
 * @class CUTS_BE_Env_Variable_Parser_T
 *
 * Environment variable parser. This is a Boost Spririt grammar for
 * converting environment variables in a CUTS model to a backend specific
 * environment variables. This parsar does not expand any of the
 * environment variables and leaves that up to the backend generator,
 * if it wishes to do so.
 *
 * Environment variables are defined in the model using the following 
 * syntax: $(VAR_NAME)
 */
template <typename T>
class CUTS_BE_Env_Variable_Parser_T :
  public boost::spirit::grammar <CUTS_BE_Env_Variable_Parser_T <T> >
{
public:
  CUTS_BE_Env_Variable_Parser_T (std::string & out);

  template <typename ScannerT>
  class definition
  {
  public:
    /**
     * Initializing constructor.
     *
     * @param[in]     self        The input grammar.
     */
    definition (CUTS_BE_Env_Variable_Parser_T const & self);

    /**
     * Start of the input grammar.
     *
     * @return        Starting expression for the grammar.
     */
    const boost::spirit::rule <ScannerT> & start (void) const;

  private:
    /// rule: var_name_;
    boost::spirit::rule <ScannerT> var_name_;

    /// rule: env_var_
    boost::spirit::rule <ScannerT> env_var_;

    /// rule: text_;
    boost::spirit::rule <ScannerT> text_;

    /// Content of the string.
    boost::spirit::rule <ScannerT> content_;
  };

private:
  /// Location to store the converted string.
  std::string & out_;
};

#include "BE_Env_Variable_Parser_T.cpp"

#endif  // !defined _CUTS_BE_ENV_VARIABLE_PARSER_T_H_
