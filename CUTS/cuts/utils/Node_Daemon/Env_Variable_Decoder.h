// -*- C++ -*-

//=============================================================================
/**
 * @file        Env_Variable_Decoder.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ENV_VARIABLE_DECODER_H_
#define _CUTS_ENV_VARIABLE_DECODER_H_

#include "ace/SStringfwd.h"

/**
 * @class CUTS_Env_Variable_Decorder
 *
 * Substitutes variables defined in a string with their expanded value.
 * Variables are defined by enclosing a set of non-whitespace characters
 * with the following: ${ }. Right now, the value of a variable is located
 * in the system's environment variables.
 */
class CUTS_Env_Variable_Decorder
{
public:
  /// Defualt constructor.
  CUTS_Env_Variable_Decorder (void);

  /// Destructor
  ~CUTS_Env_Variable_Decorder (void);

  /**
   * Decode the environment variables by expanding them. The environment
   * variables used during the expansion are defined by the operating
   * system.
   *
   * @param[in]         str           String with environment variables
   * @param[out]        value         Expanded version of \a str
   */
  bool expand (const char * str, ACE_CString & value);
};

#endif  // !defined _CUTS_ENV_VARIABLE_DECODER_H_
