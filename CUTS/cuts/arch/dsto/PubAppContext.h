#ifndef PUBAPPCONTEXT_H
#define PUBAPPCONTEXT_H

#include "ace/Array_Map.h"

#include "DSTO_ContextBase.h"
#include "ModelDataC.h"

#include "AppData.h"
#include "PubApp_export.h"

namespace DSTO_AppSpace_Impl
{
  class PubApp_Export PubAppContext
    : public virtual ::DSTO::ContextBase
  {
  public:
    PubAppContext (void);
    virtual ~PubAppContext (void);
    
    virtual void
    push_app_op_send ( ::Outer::TestData * ev);
    
    virtual ::Components::Cookie *
    subscribe_app_op_send ( ::Outer::TestData_IDLConsumer_ptr c);
    
    virtual ::Outer::TestData_IDLConsumer_ptr
    unsubscribe_app_op_send ( ::Components::Cookie * ck);
    
    static PubAppContext *
    _narrow ( ::Components::SessionContext_ptr p);
    
  protected:
    typedef ACE_Array_Map<ptrdiff_t,
                          ::Outer::TestData_IDLConsumer_var>
      APP_OP_SEND_TABLE;
    APP_OP_SEND_TABLE app_op_send_table_;
    TAO_SYNCH_MUTEX app_op_send_lock_;
  };
}

#endif // PUBAPPCONTEXT_H