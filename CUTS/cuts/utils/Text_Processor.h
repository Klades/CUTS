// -*- C++ -*-

//=============================================================================
/**
 * @file          Text_Processor.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEXT_PROCESSOR_H_
#define _CUTS_TEXT_PROCESSOR_H_

#include "Property_Expander.h"
#include "Command_Substitution.h"

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_Text_Processor
 *
 * Preprocess for string values. The preprocessor will expand all environment
 * variables, and substitute all commands with the generated text.
 */
class CUTS_UTILS_Export CUTS_Text_Processor
{
public:
  /// Default constructor.
  CUTS_Text_Processor (const CUTS_Property_Map & map);

  /// Destructor.
  ~CUTS_Text_Processor (void);

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
  CUTS_Property_Expander prop_expander_;

  /// Command substitution engine.
  CUTS_Command_Substitution command_sub_;
};

#if defined (__CUTS_INLINE__)
#include "Text_Processor.inl"
#endif

#endif  // !defined _CUTS_NODE_PREPROCESSOR_H_
