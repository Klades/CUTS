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
#include "TCPIP_HelloWorldEC.h"
#include "HelloWorld_svnt_export.h"

namespace CUTS_TCPIP
{
  /**
   * @class HelloWorld_svnt
   */
  class HELLOWORLD_SVNT_Export HelloWorld_svnt :
    public CUTS_TCPIP_Servant_T <HelloWorld_svnt>
  {
  public:
    /// Type definition of the servant type.
    typedef CUTS_TCPIP_Servant_T <HelloWorld_svnt> servant_type;

    /// Default constructor.
    HelloWorld_svnt (TCPIP::HelloWorld_Exec * impl);

    /// Destructor.
    virtual ~HelloWorld_svnt (void);

    /**
     * Method responsible for unmarshalling an ACE_Message_Block object
     * to a Message object.
     *
     * @param[in]         ev          Message block to unmarshall.
     */
    int tcpip_handle_message (ACE_InputCDR & input);

  private:
    /// Pointer to the implementation.
    TCPIP::HelloWorld_Exec_var impl_;
  };
}

#if defined (__CUTS_INLINE__)
#include "HelloWorld_svnt.inl"
#endif

#endif  // !defined _HELLOWORLD_SVNT_H_
