// $Id$

//=============================================================================
/**
 * @file          HelloWorld_svnt.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _HELLOWORLD_SVNT_H_
#define _HELLOWORLD_SVNT_H_

#include "cuts/arch/tcpip/TCPIP_Servant_T.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_Events_Impl.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_EventConsumer.h"
#include "TCPIP_HelloWorldEC.h"
#include "HelloWorld_svnt_export.h"
#include "ace/SOCK_Stream.h"

namespace TCPIP
{
  class HelloWorld_Servant_Context;

  typedef CUTS_TCPIP_Var_T <HelloWorld_Servant_Context> HelloWorld_Servant_Context_var;

  class HELLOWORLD_SVNT_Export HelloWorld_Servant_Context :
    public HelloWorld_Context
  {
  public:
    typedef HelloWorld_Servant_Context_var var_type;

    HelloWorld_Servant_Context (void);

    virtual ~HelloWorld_Servant_Context (void);

    virtual void tcpip_handle_message (TCPIP::Message * ev);

    void connect_handle_message (Components::EventConsumerBase_ptr consumer);

  private:
    ACE_SOCK_Stream handle_message_;

    long event_;

    ACE_Utils::UUID uuid_;
  };

  class HelloWorld_Servant;

  typedef CUTS_TCPIP_Servant_T <::TCPIP::HelloWorld_Servant,
                                ::TCPIP::HelloWorld_Servant_Context,
                                ::TCPIP::HelloWorld_Exec> HelloWorld_Servant_Base;
  /**
   * @class HelloWorld_svnt
   */
  class HELLOWORLD_SVNT_Export HelloWorld_Servant :
    public HelloWorld_Servant_Base,
    public CUTS_TCPIP_CCM_Events_Impl
  {
  public:
    /// Default constructor.
    HelloWorld_Servant (CUTS_TCPIP_Component * impl);

    /// Destructor.
    virtual ~HelloWorld_Servant (void);

    virtual Components::EventConsumerBase_ptr get_consumer (const char * name);

    virtual void connect_consumer (const char * name, Components::EventConsumerBase_ptr consumer);

    /**
     * Method responsible for unmarshalling an ACE_Message_Block object
     * to a Message object.
     *
     * @param[in]         ev          Message block to unmarshall.
     */
    int tcpip_handle_message (ACE_InputCDR & input);

  private:
    ACE_Auto_Ptr <CUTS_TCPIP_CCM_EventConsumer> handle_message_;
  };
}

#if defined (__CUTS_INLINE__)
#include "HelloWorld_svnt.inl"
#endif

#endif  // !defined _HELLOWORLD_SVNT_H_
