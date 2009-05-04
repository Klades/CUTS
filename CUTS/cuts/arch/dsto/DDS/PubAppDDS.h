#ifndef PUBAPPDDS_H
#define PUBAPPDDS_H

#include "DSTO_ExecBase.h"

#include "PubAppDDSContext.h"

namespace AppSpace
{  
  class PubAppDDS_Export PubAppDDS
    : public virtual ::DSTO::ExecBase
  {
  public:
    PubAppDDS (void);
    virtual ~PubAppDDS (void);
    
    void app_op_send ( ::Outer::TestData * ev);
    
    virtual void set_session_context (
      ::Components::SessionContext_ptr ctx);
     
  protected:
    ::DSTO_AppSpace_Impl::PubAppDDSContext * context_;
  };

  extern "C" PubAppDDS_Export ::Components::EnterpriseComponent_ptr
  create_PubAppDDSAdapter_Impl (void);
}

#endif // PUBAPPDDS_H