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

#include "ace/SString.h"

/**
 * @class CUTS_Env_Variable_Decorder
 *
 * Decodes strings with environment variables by expanding them.
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
