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

#include "game/mga/Project.h"
#include "game/mga/FCO.h"
#include "game/mga/Collection_T.h"
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
  CUTS_CUTE_Model_Interpreter (const CUTS_CUTE_Model_Interpreter_Action_List & actlist,
                               const CUTS_Property_Map & params,
                               GAME::Mga::Project project,
                               GAME::Mga::FCO target,
                               const std::vector <GAME::Mga::FCO> & selected,
                               long flags);

  /// Destructor.
  ~CUTS_CUTE_Model_Interpreter (void);

  void interpreter (const ACE_CString & interpreter);

  void handle_config (const CUTS_Property_Map & config);

  void base_config (CUTS_Property_Map & config, const std::string & basename);

private:
  const CUTS_CUTE_Model_Interpreter_Action_List & actlist_;

  const CUTS_Property_Map & params_;

  /// Target GAME project to interpret.
  GAME::Mga::Project project_;

  GAME::Mga::FCO target_;

  const std::vector <GAME::Mga::FCO> & selected_;

  long flags_;

  ACE_CString interpreter_;
};

#if defined (__CUTS_INLINE__)
#include "Model_Interpreter.inl"
#endif

#endif  // !defined _CUTS_CUTE_MODEL_INTERPRETER_H_
