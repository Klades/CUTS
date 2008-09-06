// -*- C++ -*-

//=============================================================================
/**
 * @file          Preprocessor.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEXT_PREPROCESSOR_H_
#define _CUTS_TEXT_PREPROCESSOR_H_

#include "Env_Variable_Decoder.h"
#include "Command_Substitution.h"

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_Text_Preprocessor
 *
 * Preprocess for string values. The preprocessor will expand all environment
 * variables, and substitute all commands with the generated text.
 */
class CUTS_Text_Preprocessor
{
public:
  /// Default constructor.
  CUTS_Text_Preprocessor (const CUTS_Property_Map & map);

  /// Destructor.
  ~CUTS_Text_Preprocessor (void);

  /**
   * Run the preprocess on a string.
   *
   * @param[in]         str           String to preprocess.
   * @param[out]        output        Resultant string.
   * @return            Number of errors
   */
  int evaluate (const char * str, ACE_CString & output);

private:
  /// Environment variable substitution engine.
  CUTS_Env_Variable_Decorder variable_sub_;

  /// Command substitution engine.
  CUTS_Command_Substitution command_sub_;
};

#endif  // !defined _CUTS_NODE_PREPROCESSOR_H_
