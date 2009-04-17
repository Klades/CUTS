#ifndef SUBAPPADAPTER_H
#define SUBAPPADAPTER_H

#include "ace/Array_Map.h"

#include "SubApp.h"

#include "DSTO_Adapter_T.h"
#include "DSTO_ContextBase.h"
#include "DSTO_EventConsumer.h"

#include "SubAppComponentS.h"

#include "SubAppAdapter_export.h"

namespace CIAO
{
  class Home_Servant_Impl_Base;
  class Container;
  typedef Container * Container_ptr;
}

namespace DSTO_AppSpace_Impl
{
  class SubAppAdapter_Export SubAppAdapter
    : public virtual ::DSTO::Adapter< ::POA_Outer::SubAppComponent>
  {
  public:
    SubAppAdapter (
      ::AppSpace::SubApp * executor,
      ::Components::CCMHome_ptr h,
      const char * ins_name,
      ::CIAO::Home_Servant_Impl_Base * hs,
      ::CIAO::Container_ptr c);
      
    virtual
    ::Components::SessionComponent_ptr get_executor (void);
    
    virtual
    ::Outer::TestData_IDLConsumer_ptr get_consumer_app_op_recv (void);

  private:
    void populate_consumer_table (void);
  
    ::Components::EventConsumerBase_ptr get_consumer_app_op_recv_i (void);

  private:
    ::AppSpace::SubApp * app_;
    ::DSTO::ContextBase * context_;
    
    ::Outer::TestData_IDLConsumer_var consumes_app_op_recv_;
  };
  
  //=============================================================

  class SubAppAdapter_Export app_op_recv_Consumer
    : public virtual POA_Outer::TestData_IDLConsumer,
      public virtual ::DSTO::EventConsumer
  {
  public:
    app_op_recv_Consumer ( ::DSTO::ExecBase * executor,
                          ::DSTO::ContextBase * ctx);
    
    virtual void push_TestData_IDL ( ::Outer::TestData_IDL * corba_ev);
    
  private:
    ::AppSpace::SubApp * executor_;
  };

  extern "C" SubAppAdapter_Export ::PortableServer::Servant
  create_SubAppAdapter_Servant (
    ::Components::EnterpriseComponent_ptr p,
    ::CIAO::Container_ptr c,
    const char *ins_name);
}

#endif // SUBAPPADAPTER_H