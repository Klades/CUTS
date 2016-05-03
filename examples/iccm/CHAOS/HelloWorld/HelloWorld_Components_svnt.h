// -*- C++ -*-

#ifndef _HELLOWORLD_COMPONENTS_SVNT_H_
#define _HELLOWORLD_COMPONENTS_SVNT_H_

#include "HelloWorld_Components_iCCMC.h"
#include "HelloWorld_ComponentsS.h"


#include "cuts/iccm/servant/Context_T.h"
#include "cuts/iccm/arch/chaos/servant/CHAOS_Servant_T.h"

#include "cuts/iccm/servant/Receptacle_T.h"
#include "HelloWorld_Components_svnt_export.h"

namespace CHAOS
{
  // Forward decl.
  class HelloReceiver_Servant;

  // Type definition of the servant type.
  typedef iCCM::Context_T < iCCM_HelloReceiver_Context, HelloReceiver_Servant > HelloReceiver_Context_Base;

  /**
   * @class HelloReceiver_Context
   *
   * Implementation of the iCCM_HelloReceiver_Context interface.
   */
  class HELLOWORLD_COMPONENTS_SVNT_Export HelloReceiver_Context :
    public HelloReceiver_Context_Base
  {
    public:
    // Default constructor
    HelloReceiver_Context (HelloReceiver_Servant & parent);

    // Destructor
    virtual ~HelloReceiver_Context (void);

    private:
  };

  // Type definition of the servant base type.
  typedef iCCM::CHAOS_Servant_T < 
    HelloReceiver_Servant,
    HelloReceiver_Context,
    ::CIAO_HelloReceiver_Impl::HelloReceiver_Exec,
    ::POA_HelloReceiver > HelloReceiver_Servant_Base;

  class HELLOWORLD_COMPONENTS_SVNT_Export HelloReceiver_Servant
    : public HelloReceiver_Servant_Base
  {
    /// typedef for generated implementation code
    typedef HelloReceiver_Servant self_type;

    /// Default constructor
    public:
    HelloReceiver_Servant (const char * name,
                           ::PortableServer::POA_ptr poa,
                           ::CIAO_HelloReceiver_Impl::HelloReceiver_Exec_ptr executor);

    /// Destructor
    virtual ~HelloReceiver_Servant (void);

    virtual void set_attributes (const ::Components::ConfigValues &);

    virtual void push_greeting_ospl (::MessageEvent *ev);

    virtual void push_greeting_ndds (::MessageEvent *ev);

    virtual void push_greeting_tcpip (::MessageEvent *ev);

    virtual ::MessageEventConsumer_ptr get_greeting_ospl_consumer (void);

    virtual ::MessageEventConsumer_ptr get_greeting_ndds_consumer (void);

    virtual ::MessageEventConsumer_ptr get_greeting_tcpip_consumer (void);

    iCCM::CHAOS_EventConsumer_T < HelloReceiver_Servant, ::MessageEvent > greeting_ospl_consumer_;
    iCCM::CHAOS_EventConsumer_T < HelloReceiver_Servant, ::MessageEvent > greeting_ndds_consumer_;
    iCCM::CHAOS_EventConsumer_T < HelloReceiver_Servant, ::MessageEvent > greeting_tcpip_consumer_;
  };

  extern "C" HELLOWORLD_COMPONENTS_SVNT_Export ::PortableServer::Servant
  create_HelloReceiver_Servant (const char * name,
                                ::PortableServer::POA_ptr poa,
                                ::Components::EnterpriseComponent_ptr p);
}

namespace CHAOS
{
  // Forward decl.
  class HelloSender_Servant;

  // Type definition of the servant type.
  typedef iCCM::Context_T < iCCM_HelloSender_Context, HelloSender_Servant > HelloSender_Context_Base;

  /**
   * @class HelloSender_Context
   *
   * Implementation of the iCCM_HelloSender_Context interface.
   */
  class HELLOWORLD_COMPONENTS_SVNT_Export HelloSender_Context :
    public HelloSender_Context_Base
  {
    public:
    // Default constructor
    HelloSender_Context (HelloSender_Servant & parent);

    // Destructor
    virtual ~HelloSender_Context (void);

    virtual void push_greeting_ospl (::MessageEvent *ev);

    virtual void push_greeting_ndds (::MessageEvent *ev);

    virtual void push_greeting_tcpip (::MessageEvent *ev);

    virtual ::MessageEvent * new_greeting_ospl_event (void);

    virtual ::MessageEvent * new_greeting_ndds_event (void);

    virtual ::MessageEvent * new_greeting_tcpip_event (void);

    iCCM::CHAOS_Publisher & get_greeting_ospl_publisher (void);

    iCCM::CHAOS_Publisher & get_greeting_ndds_publisher (void);

    iCCM::CHAOS_Publisher & get_greeting_tcpip_publisher (void);

    private:
    iCCM::CHAOS_Publisher_T < MessageEvent > greeting_ospl_;

    iCCM::CHAOS_Publisher_T < MessageEvent > greeting_ndds_;

    iCCM::CHAOS_Publisher_T < MessageEvent > greeting_tcpip_;
  };

  // Type definition of the servant base type.
  typedef iCCM::CHAOS_Servant_T < 
    HelloSender_Servant,
    HelloSender_Context,
    ::CIAO_HelloSender_Impl::HelloSender_Exec,
    ::POA_HelloSender > HelloSender_Servant_Base;

  class HELLOWORLD_COMPONENTS_SVNT_Export HelloSender_Servant
    : public HelloSender_Servant_Base
  {
    /// typedef for generated implementation code
    typedef HelloSender_Servant self_type;

    /// Default constructor
    public:
    HelloSender_Servant (const char * name,
                         ::PortableServer::POA_ptr poa,
                         ::CIAO_HelloSender_Impl::HelloSender_Exec_ptr executor);

    /// Destructor
    virtual ~HelloSender_Servant (void);

    virtual void set_attributes (const ::Components::ConfigValues &);

    virtual void connect_greeting_ospl (::MessageEventConsumer_ptr);
    virtual ::MessageEventConsumer_ptr disconnect_greeting_ospl (void);

    virtual void connect_greeting_ndds (::MessageEventConsumer_ptr);
    virtual ::MessageEventConsumer_ptr disconnect_greeting_ndds (void);

    virtual void connect_greeting_tcpip (::MessageEventConsumer_ptr);
    virtual ::MessageEventConsumer_ptr disconnect_greeting_tcpip (void);

    virtual char * message (void);
    virtual void message (const char * val);
  };

  extern "C" HELLOWORLD_COMPONENTS_SVNT_Export ::PortableServer::Servant
  create_HelloSender_Servant (const char * name,
                              ::PortableServer::POA_ptr poa,
                              ::Components::EnterpriseComponent_ptr p);
}

#endif  // !defined _HELLOWORLD_COMPONENTS_SVNT_H_
