#ifndef PUBAPPDDSADAPTER_H
#define PUBAPPDDSADAPTER_H

#include "ace/Auto_Ptr.h"

#include "PubAppDDS.h"
#include "PubAppDDSContext.h"

#include "DSTO_Adapter_T.h"
#include "DSTO_EventConsumer.h"

#include "DDS_Utility.h"

#include "PubAppDDSComponentS.h"
#include "PubAppDDSAdapter_export.h"

namespace CIAO
{
  class Home_Servant_Impl_Base;
  class Container;
  typedef Container * Container_ptr;
}

namespace DSTO_AppSpace_Impl
{
  class PubAppDDSAdapter_Export PubAppDDSAdapter
    : public virtual ::DSTO::Adapter< ::POA_Outer::PubAppDDSComponent>
  {
  public:
    PubAppDDSAdapter (
      ::AppSpace::PubAppDDS * exe,
      ::Components::CCMHome_ptr h,
      const char * ins_name,
      ::CIAO::Home_Servant_Impl_Base * hs,
      ::CIAO::Container_ptr c);
      
    virtual ~PubAppDDSAdapter (void);
      
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
      ::CUTS_DDS::DummyConsumer_ptr c);
      
    virtual
    ::CUTS_DDS::DummyConsumer_ptr unsubscribe_app_op_send (
      ::Components::Cookie * ck);
      
    virtual void configuration_complete (void);
    
  private:
    ::AppSpace::PubAppDDS * app_;
    PubAppDDSContext * context_;
    DDS_Utility dds_utility_;
  };

  extern "C" PubAppDDSAdapter_Export ::PortableServer::Servant
  create_PubAppDDSAdapter_Servant (
    ::Components::EnterpriseComponent_ptr p,
    ::CIAO::Container_ptr c,
    const char *ins_name);
}
  
#endif // PUBAPPDDSADAPTER_H

