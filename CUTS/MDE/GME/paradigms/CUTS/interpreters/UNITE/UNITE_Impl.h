// - *- C++ -*-

//=============================================================================
/**
 * @file      RawComponent.h
 *
 * $Id$
 *
 * @author    Pooja Varshneya
 */
//=============================================================================

#ifndef _CUTS_GME_UNITE_IMPL_H_
#define _CUTS_GME_UNITE_IMPL_H_

#include "game/mga/component/Interpreter_Impl_Base.h"

/**
 * @class UNITE_Interpreter_Impl
 *
 * Actual implementation of the interpreter.
 */
class UNITE_Interpreter_Impl :
  public GAME::Interpreter_Impl_Base
{
public:
  UNITE_Interpreter_Impl (void);

  virtual ~UNITE_Interpreter_Impl (void);

  int invoke_ex (GAME::Project project,
                 GAME::FCO_in fco,
                 std::vector <GAME::FCO> & selected,
                 long flags);

private:
  void preprocess (GAME::Project project);

  void postprocess (GAME::Project project);

  /// Output directory for the generated files.
  std::string output_;
};

#endif  // !defined _CUTS_COMPONENT_H_
