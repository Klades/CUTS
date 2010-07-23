// -*- C++ -*-

//=============================================================================
/**
 * @file        Quotas_Integrator_Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _QUOTAS_INTEGRATOR_IMPL_H_
#define _QUOTAS_INTEGRATOR_IMPL_H_

#include "game/be/Interpreter_Impl_Base.h"
#include "addons/PICMLManager/Configurator.h"

/**
 * @class Quotas_Integrator_Impl
 *
 * Implemenation of the Quotas specification interpreter.
 */
class Quotas_Integrator_Impl : public GAME::Interpreter_Impl_Base
{
public:
  /// Default constructor.
  Quotas_Integrator_Impl (void);

  /// Destructor.
  virtual ~Quotas_Integrator_Impl (void);

  // Initialize the interpreter.
  int initialize (GAME::Project & project);

  // Handle the InvokeEx callback.
  int invoke_ex (GAME::Project & project,
                 GAME::FCO & fco,
                 std::vector <GAME::FCO> & selected,
                 long flags);

private:
  bool get_default_qoutas_impl (const GAME::Model & c,
                                GAME::Atom & impl);

  bool create_assembly (const GAME::Atom & driver_impl,
                        GAME::Model & driver_inst,
                        const GAME::Atom & comp_impl,
                        GAME::Model & comp_inst);

  bool generate_driver_component (const GAME::Model & component,
                                  GAME::Folder & idl_folder,
                                  GAME::Model & driver);

  bool get_receptacle_and_method (const GAME::Model & driver,
                                  GAME::Reference & receptacle,
                                  GAME::Model & method);


  bool get_target_component (GAME::Project & p, GAME::Model & c);

  int integrate (const GAME::Model & component,
                 const GAME::Reference & receptacle,
                 const GAME::Model & method,
                 const GAME::Model & behavior,
                 GAME::Model & driver);


  CComPtr <IConfigurator> configurator_;
};

#endif  // !defined _QUOTAS_SPECIFICATION_IMPL_H_
