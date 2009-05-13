#ifndef PUB_APPLICATION_H
#define PUB_APPLICATION_H

#include "DSTO_ExecBase.h"

#include "PubAppContext.h"

namespace AppSpace
{  
  class PubApp_Export PubApp
    : public virtual ::CUTS_DSTO::ExecBase
  {
  public:
    PubApp (void);
    virtual ~PubApp (void);
    
    void app_op_send ( ::Outer::TestData * ev);
    
    virtual void set_session_context (
      ::Components::SessionContext_ptr ctx);
     
  protected:
    ::DSTO_AppSpace_Impl::PubAppContext * context_;
  };

  extern "C" PubApp_Export ::Components::EnterpriseComponent_ptr
  create_PubAppAdapter_Impl (void);
}

#endif // PUB_APPLICATION_H

