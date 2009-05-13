#ifndef SUBAPPDDS_H
#define SUBAPPDDS_H

#include "DSTO_ExecBase.h"

#include "AppData.h"

#include "SubAppDDS_export.h"

namespace AppSpace
{  
  class SubAppDDS_Export SubAppDDS
    : public virtual ::CUTS_DSTO::ExecBase
  {
  public:
    SubAppDDS (void);
    ~SubAppDDS (void);
    
    void app_op_recv ( ::Outer::TestData * ev);
  };
};

extern "C" SubAppDDS_Export ::Components::EnterpriseComponent_ptr
create_SubAppDDSAdapter_Impl (void);

#endif // SUBAPPDDS_H

