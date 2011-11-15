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

#include "Property_Evaluator_T.h"
#include "Property_Evaluator_Stream_Actor.h"
#include "Command_Substitution.h"
#include <sstream>

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
  /// Type definition of the property evaluator.
  typedef
    CUTS_Property_Evaluator_T <CUTS_Property_Evaluator_Stream_Actor>
    property_evaluator_type;

  /// Default constructor.
  CUTS_Text_Processor (const CUTS_Property_Map & map);

  /// Destructor.
  ~CUTS_Text_Processor (void);

  /**
   * Run the preprocess on a string.
   *
   * @param[in]         str           String to preprocess.
   * @param[out]        output        Resultant string.
   */
  bool evaluate (const char * str,
                 ACE_CString & output,
                 bool use_env = false,
                 bool ignore_variables = false,
                 bool ignore_commands = false);

  template <typename IteratorT>
  bool evaluate (IteratorT begin,
                 IteratorT end,
                 std::ostream & out,
                 bool use_env = false,
                 bool ignore_variables = false,
                 bool ignore_commands = false);

private:
  std::ostringstream buffer_;

  CUTS_Property_Evaluator_Stream_Actor stream_actor_;

  /// Environment variable substitution engine.
  property_evaluator_type property_eval_;

  /// Command substitution engine.
  CUTS_Command_Substitution command_sub_;
};

#if defined (__CUTS_INLINE__)
#include "Text_Processor.inl"
#endif

#include "Text_Processor_T.cpp"

#endif  // !defined _CUTS_NODE_PREPROCESSOR_H_
