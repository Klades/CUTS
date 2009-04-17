#ifndef DSTO_EXECBASE_H
#define DSTO_EXECBASE_H

#include "tao/LocalObject.h"

#include "ccm/CCM_SessionComponentC.h"

#include "DSTO_Utilities_export.h"

namespace DSTO
{
  class DSTO_Utilities_Export ExecBase
    : public virtual ::Components::SessionComponent,
      public virtual ::CORBA::LocalObject
  {
  public:
    ExecBase (void);
    virtual ~ExecBase (void);
    
    virtual void set_session_context ( ::Components::SessionContext_ptr);
    virtual void configuration_complete (void);
    virtual void ccm_activate (void);
    virtual void ccm_passivate (void);
    virtual void ccm_remove (void);
    
    static ExecBase * _narrow ( ::CORBA::Object_ptr);
  };
}

#endif // DSTO_EXECBASE_H