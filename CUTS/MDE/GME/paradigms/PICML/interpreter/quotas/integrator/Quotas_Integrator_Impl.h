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
#include <map>

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
  int initialize (GAME::Project project);

  // Handle the InvokeEx callback.
  int invoke_ex (GAME::Project project,
                 GAME::FCO_in fco,
                 std::vector <GAME::FCO> & selected,
                 long flags);

private:
  bool get_default_qoutas_impl (const GAME::Model_in c,
                                GAME::Atom & impl);

  bool create_assembly (const GAME::Atom_in driver_impl,
                        const GAME::Atom_in comp_impl,
                        GAME::Model & assembly);

  bool generate_driver_component (const GAME::Model_in component,
                                  GAME::Folder_in idl_folder,
                                  GAME::Model & driver);

  bool get_receptacle_and_method (const GAME::Model_in driver,
                                  GAME::Reference & receptacle,
                                  GAME::Model & method);

  bool get_driver_receptacle (const GAME::Model_in model,
                              GAME::Reference & receptacle);

  bool get_testobject_facet (const GAME::Model_in model,
                             GAME::Reference & receptacle);

  bool get_testdriver_receptacle (const GAME::Model_in model,
                                  GAME::Reference & receptacle);

  bool get_target_component (GAME::Project p, GAME::Model & c);

  bool integrate (const GAME::Model_in component,
                  const GAME::Reference_in receptacle,
                  const GAME::Model_in method,
                  const GAME::Model_in behavior,
                  GAME::Model_in driver,
                  GAME::Model & assembly);

  bool generate_domain (GAME::Project proj,
                        GAME::Model & domain);

  bool generate_deployment (GAME::Project proj,
                            const GAME::Model_in domain,
                            const GAME::Model_in assembly,
                            GAME::Model & deployment);

  bool create_action_parameter (GAME::Model_in action,
                                const GAME::Reference_in param,
                                std::map <GAME::FCO, GAME::FCO> & mapping);

  CComPtr <IConfigurator> configurator_;
};

#endif  // !defined _QUOTAS_SPECIFICATION_IMPL_H_
