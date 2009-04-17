#ifndef SUB_APPLICATION_H
#define SUB_APPLICATION_H

#include "DSTO_ExecBase.h"

#include "AppData.h"

#include "SubApp_export.h"

namespace AppSpace
{  
  class SubApp_Export SubApp
    : public virtual ::DSTO::ExecBase
  {
  public:
    SubApp (void);
    ~SubApp (void);
    
    void app_op_recv ( ::Outer::TestData * ev);
  };
};

extern "C" SubApp_Export ::Components::EnterpriseComponent_ptr
create_SubAppAdapter_Impl (void);

#endif // SUB_APPLICATION_H