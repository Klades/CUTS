// -*- C++ -*-

#ifndef _HELLOWORLD_SVNT_H_
#define _HELLOWORLD_SVNT_H_

#include "HelloWorld_iCCMC.h"
#include "HelloWorldS.h"

#include "portico/HelloWorld_ObjectClass.h"

#include "cuts/arch/ccm/CCM_Context_T.h"
#include "cuts/arch/portico/ccm/Portico_CCM_EventConsumer_T.h"
#include "cuts/arch/portico/ccm/Portico_CCM_Publisher_Table_T.h"
#include "cuts/arch/portico/ccm/Portico_CCM_Servant_T.h"

#include "HelloWorld_svnt_export.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Forward decl.
class HelloSender_Servant;

/// Type definition of the base context.
typedef
  CUTS_CCM_Context_T < iCCM_HelloSender_Context,
                       HelloSender_Servant >
                       HelloSender_Servant_Context_Base;

/**
 * @class HelloReceiver_Servant_Context
 *
 * Implementation of the HelloSender iCCM servant context.
 */
class HelloSender_Servant_Context :
  public HelloSender_Servant_Context_Base
{
public:
  // Initializing constructor
  HelloSender_Servant_Context (HelloSender_Servant & parent);

  // Destructor
  virtual ~HelloSender_Servant_Context (void);

  // push method for output ev port: output_message
  virtual ::Message * push_greeting_event (void);
  virtual void push_greeting (::Message * ev);
  Portico_CCM_Publisher_Table & publisher_greeting (void);

  virtual void tick (void);
  virtual void advance_time (::CORBA::Double amount);

private:
  Portico_CCM_Publisher_Table_T < ::Message > greeting_;
};

/// Type definition of the servant base.
typedef
  Portico_CCM_Servant_T < HelloSender_Servant,
                          HelloSender_Servant_Context,
                          CIAO_HelloSender_Impl::HelloSender_Exec,
                          ::POA_HelloSender>
                          HelloSender_Servant_Base;

/**
 * @class HelloSender_Servant
 *
 * Implementation of the HelloSender component servant. This servant
 * can host and implementation of a HelloSender component.
 */
class HelloSender_Servant : public HelloSender_Servant_Base
{
  public:
  // Initializing constructor
  HelloSender_Servant (const char * name,
                      ::PortableServer::POA_ptr poa,
                      ::CIAO_HelloSender_Impl::HelloSender_Exec_ptr executor);

  // Destructor
  virtual ~HelloSender_Servant (void);

  // attribute setter: message
  virtual void message (const char * message);

  // attribute getter: message
  virtual char * message (void);

  // Set the component's attributes
  virtual void set_attributes (const ::Components::ConfigValues & config);

  void connect_greeting (::MessageConsumer_ptr);
  ::MessageConsumer_ptr disconnect_greeting (void);

  ::Components::Cookie * subscribe_greeting (::MessageConsumer_ptr);
  ::MessageConsumer_ptr unsubscribe_greeting (::Components::Cookie *);

  //::MessageConsumer_ptr get_consumer_input_message (void);

  //virtual void push_input_message (::Message * ev);

private:
  //Portico_CCM_EventConsumer_T < HelloSender_Servant, ::Message > input_message_consumer_;
};


extern "C" HELLOWORLD_SVNT_Export
::PortableServer::Servant
create_HelloSender_Servant (const char * name,
                            ::PortableServer::POA_ptr poa,
                            ::Components::EnterpriseComponent_ptr p);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Forward decl.
class HelloReceiver_Servant;

/// Type definition of the base context.
typedef
  CUTS_CCM_Context_T < iCCM_HelloReceiver_Context,
                       HelloReceiver_Servant >
                       HelloReceiver_Servant_Context_Base;

/**
 * @class HelloReceiver_Servant_Context
 *
 * Implementation of the HelloReceiver iCCM servant context.
 */
class HelloReceiver_Servant_Context :
  public HelloReceiver_Servant_Context_Base
{
public:
  // Initializing constructor
  HelloReceiver_Servant_Context (HelloReceiver_Servant & parent);

  // Destructor
  virtual ~HelloReceiver_Servant_Context (void);

  virtual void tick (void);
};

/// Type definition of the servant base.
typedef
  Portico_CCM_Servant_T < HelloReceiver_Servant,
                          HelloReceiver_Servant_Context,
                          CIAO_HelloReceiver_Impl::HelloReceiver_Exec,
                          ::POA_HelloReceiver>
                          HelloReceiver_Servant_Base;

/**
 * @class HelloReceiver_Servant
 *
 * Implementation of the HelloSender component servant. This servant
 * can host and implementation of a HelloSender component.
 */
class HelloReceiver_Servant : public HelloReceiver_Servant_Base
{
  public:
  // Initializing constructor
  HelloReceiver_Servant (const char * name,
                         ::PortableServer::POA_ptr poa,
                         ::CIAO_HelloReceiver_Impl::HelloReceiver_Exec_ptr executor);

  // Destructor
  virtual ~HelloReceiver_Servant (void);

  ::MessageConsumer_ptr get_consumer_greeting (void);
  virtual void push_greeting (::Message * ev);

private:
  Portico_CCM_EventConsumer_T < HelloReceiver_Servant, ::Message > greeting_consumer_;
};


extern "C" HELLOWORLD_SVNT_Export
::PortableServer::Servant
create_HelloReceiver_Servant (const char * name,
                            ::PortableServer::POA_ptr poa,
                            ::Components::EnterpriseComponent_ptr p);

#endif  // !defined _HELLOWORLD_SVNT_H_
