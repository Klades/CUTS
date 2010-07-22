// -*- C++ -*-

//=============================================================================
/**
 * @file        Pojo_Codegen_Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_SPRING_DEPLOYMENT_IMPL_H_
#define _QUOTAS_SPRING_DEPLOYMENT_IMPL_H_

#include "game/be/Interpreter_Impl_Base.h"

/**
 * @class Quotas_Pojo_Codegen_Impl
 *
 * Implemenation of the Quotas specification interpreter.
 */
class Quotas_Pojo_Codegen_Impl :
  public GAME::Interpreter_Impl_Base
{
public:
  /// Default constructor.
  Quotas_Pojo_Codegen_Impl (void);

  /// Destructor.
  virtual ~Quotas_Pojo_Codegen_Impl (void);

  // Handle the InvokeEx callback.
  int invoke_ex (GAME::Project & project,
                 GAME::FCO & fco,
                 std::vector <GAME::FCO> & selected,
                 long flags);
};

#endif  // !defined _QUOTAS_SPECIFICATION_IMPL_H_
