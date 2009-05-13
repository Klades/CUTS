#ifndef SUBAPPDDSADAPTER_H
#define SUBAPPDDSADAPTER_H

#include "SubAppDDS.h"

#include "DSTO_Adapter_T.h"
//#include "DSTO_ContextBase.h"
//#include "DSTO_EventConsumer.h"

#include "DDS_Utility.h"

#include "ModelDDSDataDcps_impl.h"

#include "SubAppDDSComponentS.h"
#include "SubAppDDSAdapter_export.h"

namespace CIAO
{
  class Home_Servant_Impl_Base;
  class Container;
  typedef Container * Container_ptr;
}

namespace DSTO_AppSpace_Impl
{
  class SubAppDDSAdapter_Export SubAppDDSAdapter
    : public virtual ::DSTO::Adapter< ::POA_Outer::SubAppDDSComponent>
  {
  public:
    SubAppDDSAdapter (
      ::AppSpace::SubAppDDS * executor,
      ::Components::CCMHome_ptr h,
      const char * ins_name,
      ::CIAO::Home_Servant_Impl_Base * hs,
      ::CIAO::Container_ptr c);
      
    virtual
    ::Components::SessionComponent_ptr get_executor (void);
    
    virtual
    ::Components::EventConsumerBase_ptr get_consumer (
      const char *sink_name);

    virtual
    ::CUTS_DDS::DummyConsumer_ptr get_consumer_app_op_recv (void);

  private:
    void populate_consumer_table (void);
  
    ::Components::EventConsumerBase_ptr get_consumer_app_op_recv_i (void);

  private:
    DDS_Utility dds_utility_;
    ::AppSpace::SubAppDDS * app_;
//    ::DSTO::ContextBase * context_;
    
    ::CUTS_DDS::DummyConsumer_var consumes_app_op_recv_;

    // Generate this for each consumes port.
    ::Outer::TestData_DDSDataReader_var app_op_recv_reader_;
    DataReaderListener_var app_op_recv_listener_;
  };
  
  extern "C" SubAppDDSAdapter_Export ::PortableServer::Servant
  create_SubAppDDSAdapter_Servant (
    ::Components::EnterpriseComponent_ptr p,
    ::CIAO::Container_ptr c,
    const char *ins_name);
}

#endif // SUBAPPDDSADAPTER_H

