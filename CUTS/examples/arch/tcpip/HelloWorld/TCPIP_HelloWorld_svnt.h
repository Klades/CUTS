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

#include "HelloWorldS.h"
#include "HelloWorldEC.h"
#include "TCPIP_HelloWorldC.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_Context_T.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_Remote_Endpoint_T.h"
#include "cuts/arch/tcpip/ccm/TCPIP_CCM_Servant_T.h"
#include "HelloWorld_svnt_export.h"

// Forward decl.
class CUTS_TCPIP_Servant_Manager;

namespace TCPIP
{
  // Forwar dec.
  class HelloWorld_Servant;

  typedef CUTS_TCPIP_CCM_Context_T <::CCM_HelloWorld_Context,
                                    ::TCPIP::HelloWorld_Servant>
                                    HelloWorld_Servant_Context_Base;

  /**
   * @class HelloWorld_Servant_Context
   */
  class HELLOWORLD_SVNT_Export HelloWorld_Servant_Context :
    public HelloWorld_Servant_Context_Base
  {
  public:
    HelloWorld_Servant_Context (::TCPIP::HelloWorld_Servant & parent);

    virtual ~HelloWorld_Servant_Context (void);

    virtual void push_handle_message (::Message * ev);

    CUTS_TCPIP_CCM_Remote_Endpoint & endpoint_handle_message (void);

  private:
    CUTS_TCPIP_CCM_Remote_Endpoint_T <::Message> handle_message_;
  };

  // Forward decl.
  class HelloWorld_Servant;

  typedef CUTS_TCPIP_CCM_Servant_T <::TCPIP::HelloWorld_Servant,
                                    ::TCPIP::HelloWorld_Servant_Context,
                                    ::CIDL_HelloWorld_Impl::HelloWorld_Exec,
                                    ::POA_HelloWorld> HelloWorld_Servant_Base;

  /**
   * @class HelloWorld_svnt
   */
  class HELLOWORLD_SVNT_Export HelloWorld_Servant :
    public HelloWorld_Servant_Base
  {
  public:
    /// Default constructor.
    HelloWorld_Servant (CUTS_TCPIP_Servant_Manager & svnt_mgr,
                        ::CIDL_HelloWorld_Impl::HelloWorld_Exec_ptr executor);

    /// Destructor.
    virtual ~HelloWorld_Servant (void);

    // MessageConsumer methods
    void connect_handle_message (::MessageConsumer_ptr);

    ::MessageConsumer_ptr disconnect_handle_message (void);

    ::MessageConsumer_ptr get_consumer_handle_message (void);

    /**
     * Method responsible for unmarshalling an ACE_Message_Block object
     * to a Message object.
     *
     * @param[in]         ev          Message block to unmarshall.
     */
    static int tcpip_handle_message (HelloWorld_Servant * svnt,
                                     CUTS_TCPIP_InputCDR & input);

  private:
    CUTS_TCPIP_CCM_EventConsumer handle_message_consumer_;
  };

  extern "C" HELLOWORLD_SVNT_Export
  ::PortableServer::Servant
  create_HelloWorld_Servant (CUTS_TCPIP_Servant_Manager * svnt_mgr,
                             ::Components::EnterpriseComponent_ptr executor);
}

#endif  // !defined _HELLOWORLD_SVNT_H_
