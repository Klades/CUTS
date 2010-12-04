// -*- C++ -*-

#ifndef _HELLOWORLD_SVNT_H_
#define _HELLOWORLD_SVNT_H_

#include "HelloWorldEC.h"
#include "HelloWorldS.h"
#include "OpenSplice_HelloWorldC.h"

#include "cuts/arch/ccm/CCM_Context_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_EventConsumer_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_Subscriber_T.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_Subscriber_Table_T.h"

#include "HelloWorld_svnt_export.h"

// Forward decl.
class HelloWorld_Servant;

typedef CUTS_CCM_Context_T <
::CCM_HelloWorld_Context,
HelloWorld_Servant > HelloWorld_Servant_Context_Base;

class HelloWorld_Servant_Context : public HelloWorld_Servant_Context_Base
{
  public:
  // Initializing constructor
  HelloWorld_Servant_Context (HelloWorld_Servant & parent);

  // Destructor
  virtual ~HelloWorld_Servant_Context (void);

  public:
  // push method for output ev port: output_message
  virtual void push_output_message (::Message * ev);

  CUTS_OpenSplice_CCM_Subscriber & writer_output_message (void);

  private:
  CUTS_OpenSplice_CCM_Subscriber_T < ::CUTS_OSPL::Message > output_message_;

  public:
  // push method for output ev port: handle_message_ex
  virtual void push_handle_message_ex (::Message * ev);

  CUTS_CCM_Subscriber_Table & writers_handle_message_ex (void);

  private:
  CUTS_OpenSplice_CCM_Subscriber_Table_T < ::CUTS_OSPL::Message > handle_message_ex_;
};

/// Type definition for the HelloWorld_Servant base class.
typedef CUTS_OpenSplice_CCM_Servant_T <
  HelloWorld_Servant,
  HelloWorld_Servant_Context,
  ::CIAO_HelloWorld_Impl::HelloWorld_Exec,
  ::POA_HelloWorld > HelloWorld_Servant_Base;

/**
 * @class HelloWorld_Servant
 *
 * Default servant implementation for HelloWorld
 * component implementations.
 */
class HelloWorld_Servant : public HelloWorld_Servant_Base
{
  public:
  // Initializing constructor
  HelloWorld_Servant (const char * name,
                      ::PortableServer::POA_ptr port_POA,
                      ::CIAO_HelloWorld_Impl::HelloWorld_Exec_ptr executor);

  // Destructor
  virtual ~HelloWorld_Servant (void);

  // attribute setter: message
  virtual void message (const char * message);

  // attribute getter: message
  virtual char * message (void);

  // attribute getter: readonly_message
  virtual char * readonly_message (void);

  // Set the component's attributes
  virtual void set_attributes (const ::Components::ConfigValues & config);
  void connect_output_message (::MessageConsumer_ptr);

  ::MessageConsumer_ptr disconnect_output_message (void);

  ::Components::Cookie * subscribe_handle_message_ex (::MessageConsumer_ptr);

  ::MessageConsumer_ptr unsubscribe_handle_message_ex(::Components::Cookie *);

  public:
  ::MessageConsumer_ptr get_consumer_input_message (void);

  private:
  static void deserialize_input_message (HelloWorld_Servant *,
                                         const ::CUTS_OSPL::Message& dds_event);

  CUTS_OpenSplice_CCM_EventConsumer_T <
    HelloWorld_Servant,
    ::CUTS_OSPL::Message > input_message_consumer_;
};


extern "C" HELLOWORLD_SVNT_Export
::PortableServer::Servant
create_HelloWorld_Servant (const char * name,
                           ::PortableServer::POA_ptr port_POA,
                           ::Components::EnterpriseComponent_ptr p);

#endif  // !defined _HELLOWORLD_SVNT_H_
