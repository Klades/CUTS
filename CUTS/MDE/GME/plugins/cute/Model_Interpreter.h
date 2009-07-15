// -*- C++ -*-

//=============================================================================
/**
 * @file        Model_Interpreter.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CUTE_MODEL_INTERPRETER_H_
#define _CUTS_CUTE_MODEL_INTERPRETER_H_

#include "game/GME_fwd.h"
#include "game/Collection_T.h"
#include "Model_Interpreter_Action_List.h"

class CUTS_Property_Map;

/**
 * @class CUTS_CUTE_Model_Interpreter
 */
class CUTS_CUTE_Model_Interpreter
{
public:
  /**
   * Initializing constructor.
   */
  CUTS_CUTE_Model_Interpreter (CUTS_CUTE_Model_Interpreter_Action_List & actlist,
                               CUTS_Property_Map & params,
                               GME::Project & project,
                               GME::FCO & target,
                               GME::Collection_T <GME::FCO> & selected,
                               long flags);

  /// Destructor.
  ~CUTS_CUTE_Model_Interpreter (void);

  void interpreter (const ACE_CString & interpreter);

  void handle_config (const CUTS_Property_Map & config);

  void base_config (CUTS_Property_Map & config, const std::string & basename);

private:
  CUTS_CUTE_Model_Interpreter_Action_List & actlist_;

  CUTS_Property_Map & params_;

  /// Target GME project to interpret.
  GME::Project & project_;

  GME::FCO & target_;

  GME::Collection_T <GME::FCO> & selected_;

  long flags_;

  ACE_CString interpreter_;
};

#if defined (__CUTS_INLINE__)
#include "Model_Interpreter.inl"
#endif

#endif  // !defined _CUTS_CUTE_MODEL_INTERPRETER_H_
