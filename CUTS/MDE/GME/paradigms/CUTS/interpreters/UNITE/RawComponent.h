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

#ifndef _CUTS_COMPONENT_H_
#define _CUTS_COMPONENT_H_

#include "ComponentLib.h"
#include "game/be/Interpreter_T.h"
#include "game/be/Interpreter_Impl_Base.h"

/**
 * @class CUTS_Interpreter_Impl
 *
 * Actual implementation of the interpreter.
 */
class CUTS_Interpreter_Impl :
  public GME::Interpreter_Impl_Base
{
public:
  CUTS_Interpreter_Impl (void);

  virtual ~CUTS_Interpreter_Impl (void);

  int invoke_ex (GME::Project & project,
                 GME::FCO & fco,
                 std::vector <GME::FCO> & selected,
                 long flags);

private:
  void preprocess (GME::Project & project);

  void postprocess (GME::Project & project);

  /// Output directory for the generated files.
  std::string output_;
};

GME_RAWCOMPONENT_DECL (GME::Interpreter_T, CUTS_Interpreter_Impl);

#endif  // !defined _CUTS_COMPONENT_H_
