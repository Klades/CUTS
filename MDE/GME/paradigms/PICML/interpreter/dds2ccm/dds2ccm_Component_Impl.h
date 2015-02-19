// -*- C++ -*-

//=============================================================================
/**
 * @file       dds2ccm_Component_Impl.h
 *
 * $Id$
 *
 * @author     Tanumoy Pati
 */
//=============================================================================

#ifndef _DDS2CCM_COMPONENT_IMPL_H_
#define _DDS2CCM_COMPONENT_IMPL_H_

#include "game/mga/component/Interpreter_Impl_Base.h"



class dds2ccm_Component_Impl :
 public GAME::Mga::Interpreter_Impl_Base
{
public:
  /// Default constructor.
  dds2ccm_Component_Impl (void);

  /// Destructor.
  virtual ~dds2ccm_Component_Impl (void);

  /// Handle the InvokeEx callback.
  int invoke_ex (GAME::Mga::Project project,
                 GAME::Mga::FCO_in focus,
                 GAME::Mga::Collection_T <GAME::Mga::FCO> & selected,
                 long flags);
};

#endif