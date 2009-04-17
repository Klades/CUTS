#ifndef PUBAPPADAPTER_H
#define PUBAPPADAPTER_H

#include "ace/Auto_Ptr.h"

#include "PubApp.h"
#include "PubAppContext.h"

#include "DSTO_Adapter_T.h"
#include "DSTO_EventConsumer.h"

#include "PubAppComponentS.h"

#include "PubAppAdapter_export.h"

namespace CIAO
{
  class Home_Servant_Impl_Base;
  class Container;
  typedef Container * Container_ptr;
}

namespace DSTO_AppSpace_Impl
{
  class PubAppAdapter_Export PubAppAdapter
    : public virtual ::DSTO::Adapter< ::POA_Outer::PubAppComponent>
  {
  public:
    PubAppAdapter (
      ::AppSpace::PubApp * exe,
      ::Components::CCMHome_ptr h,
      const char * ins_name,
      ::CIAO::Home_Servant_Impl_Base * hs,
      ::CIAO::Container_ptr c);
      
    virtual
    ::Components::SessionComponent_ptr get_executor (void);
    
    virtual
    ::Components::Cookie * subscribe (
      const char * publisher_name,
      ::Components::EventConsumerBase_ptr subscriber);
    
    virtual
    ::Components::EventConsumerBase_ptr unsubscribe (
      const char * publisher_name,
      ::Components::Cookie * ck);
      
    virtual
    ::Components::Cookie * subscribe_app_op_send (
      ::Outer::TestData_IDLConsumer_ptr c);
      
    virtual
    ::Outer::TestData_IDLConsumer_ptr unsubscribe_app_op_send (
      ::Components::Cookie * ck);
      
    virtual void configuration_complete (void);
    
  private:
    ::AppSpace::PubApp * app_;
//    ACE_Auto_Ptr<PubAppContext> context_;
    PubAppContext * context_;
  };

  extern "C" PubAppAdapter_Export ::PortableServer::Servant
  create_PubAppAdapter_Servant (
    ::Components::EnterpriseComponent_ptr p,
    ::CIAO::Container_ptr c,
    const char *ins_name);
}
  
#endif // PUBAPPADAPTER_H