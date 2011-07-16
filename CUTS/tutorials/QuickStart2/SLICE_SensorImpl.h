// -*- C++ -*-

#ifndef _SLICE_SENSORIMPL_H_
#define _SLICE_SENSORIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "ComponentTypesEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"

#include "Client_Logger.h"
#include "cuts/Periodic_Event_T.h"

namespace SLICE_SensorImpl
{
  // Type definition of the implentation base type
  typedef CUTS_CCM_Component_T < CIAO_SLICE_Sensor_Impl::Sensor_Exec, ::SLICE::CCM_Sensor_Context > Sensor_Base;

  /**
   * @class Sensor
   *
   * Implementation of the CIAO_SLICE_Sensor_Impl::Sensor_Exec component executor
   */
  class Sensor :
    public Sensor_Base
  {
    public:
    // Type definition of the base component type
    typedef Sensor_Base base_type;

    // Default constructor
    Sensor (void);

    // Destructor
    virtual ~Sensor (void);

    // PeriodicEvent: periodicData
    void periodic_periodicData (void);

    virtual void ccm_activate (void);

    virtual void ccm_passivate (void);

    private:
    // variable: eventCount
    ::CORBA::ULong eventCount_;

    // worker variable: logger
    CUTS_Client_Logger logger_;

    // periodic: periodicData
    CUTS_Periodic_Event_T < Sensor > periodic_periodicData_;
  };
}

#include "SLICE_Sensor_impl_export.h"

//
// create_SLICE_Sensor_Impl
//
extern "C" SLICE_SENSOR_IMPL_Export
::Components::EnterpriseComponent_ptr create_SLICE_Sensor_Impl (void);

#include "ace/post.h"

#endif  // !defined _SLICE_SENSORIMPL_H_

// end of auto-generated file

