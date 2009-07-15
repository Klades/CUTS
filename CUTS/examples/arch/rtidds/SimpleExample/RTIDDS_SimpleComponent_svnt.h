// -*- C++ -*-

#ifndef _RTIDDS_SIMPLECOMPONENT_SVNT_H_
#define _RTIDDS_SIMPLECOMPONENT_SVNT_H_

#include "SimpleComponentEC.h"

#include "cuts/arch/ccm/CCM_Context_T.h"
#include "cuts/arch/rtidds/ccm/RTIDDS_CCM_Servant_T.h"
#include "cuts/arch/rtidds/ccm/RTIDDS_EventConsumer_T.h"
#include "cuts/arch/rtidds/ccm/RTIDDS_Subscriber_T.h"
#include "cuts/arch/rtidds/ccm/RTIDDS_Subscriber_Table_T.h"

#include "SimpleComponentS.h"
#include "RTIDDS_SimpleComponentC.h"

namespace RTIDDS_SimpleComponent_Basic_Impl
{
  // Forward decl.
  class SimpleComponent_Servant;

  typedef CUTS_CCM_Context_T < 
  ::Example::CCM_SimpleComponent_Context, 
  SimpleComponent_Servant > SimpleComponent_Servant_Context_Base;

  class SimpleComponent_Servant_Context : public SimpleComponent_Servant_Context_Base
  {
    public:
    // Initializing constructor
    SimpleComponent_Servant_Context (SimpleComponent_Servant & parent);

    // Destructor
    virtual ~SimpleComponent_Servant_Context (void);

    public:
    // push method for output event port: publishEvent
    virtual void push_publishEvent (::Outer::TestData_DDS * ev);

    CUTS_CCM_Subscriber_Table & writers_publishEvent (void);

    private:
    CUTS_RTIDDS_CCM_Subscriber_Table_T < ::CUTS_DDS::Outer::TestData_DDS > publishEvent_;

    public:
    // push method for output event port: emitEvent
    virtual void push_emitEvent (::Outer::TestData_DDS * ev);

    CUTS_RTIDDS_CCM_Subscriber & writer_emitEvent (void);

    private:
    CUTS_RTIDDS_CCM_Subscriber_T < ::CUTS_DDS::Outer::TestData_DDS > emitEvent_;
  };

  typedef CUTS_RTIDDS_CCM_Servant_T < 
    SimpleComponent_Servant,
    SimpleComponent_Servant_Context,
    ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec,
    ::POA_Example::SimpleComponent > SimpleComponent_Servant_Base;

  class SimpleComponent_Servant : public SimpleComponent_Servant_Base
  {
    public:
    // Initializing constructor
    SimpleComponent_Servant (const char * name,
                             ::CIDL_SimpleComponent_Basic_Impl::SimpleComponent_Exec_ptr executor);

    virtual ~SimpleComponent_Servant (void);

    ::Components::Cookie * subscribe_publishEvent (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr unsubscribe_publishEvent(::Components::Cookie *);

    void connect_emitEvent (::Outer::TestData_DDSConsumer_ptr);

    ::Outer::TestData_DDSConsumer_ptr disconnect_emitEvent (void);

    public:
    ::Outer::TestData_DDSConsumer_ptr get_consumer_processEvent (void);

    private:
    static void deserialize_processEvent (SimpleComponent_Servant *,
                                          const ::CUTS_DDS::Outer::TestData_DDS& dds_event);

    CUTS_RTIDDS_CCM_EventConsumer_T < 
      SimpleComponent_Servant,
      ::CUTS_DDS::Outer::TestData_DDS > processEvent_consumer_;
  };
}

#include "RTIDDS_SimpleComponent_svnt_export.h"

extern "C" RTIDDS_SIMPLECOMPONENT_SVNT_Export
::PortableServer::Servant
create_SimpleComponent_Servant (const char * name,
                                ::Components::EnterpriseComponent_ptr p);

#endif  // !defined _RTIDDS_SIMPLECOMPONENT_SVNT_H_
