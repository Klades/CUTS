// -*- C++ -*-

#ifndef _TCPIP_HELLOWORLDC_H_
#define _TCPIP_HELLOWORLDC_H_

#include "cuts/arch/tcpip/TCPIP_Object_T.h"
#include "cuts/arch/tcpip/TCPIP_Var_T.h"
#include "ace/CDR_Stream.h"
#include "ace/SString.h"
#include "HelloWorld_stub_export.h"

namespace TCPIP
{
  /**
   * @struct TimeValue
   */
  struct HELLOWORLD_STUB_Export TimeValue
  {
    // member: sec
    ACE_UINT32 sec;

    // member: usec
    ACE_UINT32 usec;
  };

  // Stream operations
  ACE_CDR::Boolean HELLOWORLD_STUB_Export operator << (ACE_OutputCDR & stream, TimeValue & rhs);
  ACE_CDR::Boolean HELLOWORLD_STUB_Export operator >> (ACE_InputCDR & stream, TimeValue & rhs);

  // Forward decl.
  class Message;

  /// Type definition fo the Message_var type.
  typedef CUTS_TCPIP_Var_T <Message> Message_var;

  /**
   * @class Message
   */
  class HELLOWORLD_STUB_Export Message :
    public CUTS_TCPIP_MT_Object
  {
  public:
    // Friend decl.
    friend ACE_CDR::Boolean HELLOWORLD_STUB_Export operator << (ACE_OutputCDR & stream, Message & rhs);
    friend ACE_CDR::Boolean HELLOWORLD_STUB_Export operator >> (ACE_InputCDR & stream, Message & rhs);

    /// Type definition of the _var type.
    typedef Message_var var_type;

    /// Default constructor.
    Message (void);

    /// Destructor.
    virtual ~Message (void);

    ::TCPIP::TimeValue & time (void);
    const ::TCPIP::TimeValue & time (void) const;
    void time (const ::TCPIP::TimeValue & time);

    ACE_CString & message (void);
    const ACE_CString & message (void) const;
    void message (const char * message);

  private:
    ::TCPIP::TimeValue time_;

    ACE_CString message_;
  };

  // Stream operations
  ACE_CDR::Boolean HELLOWORLD_STUB_Export operator << (ACE_OutputCDR & stream, Message & rhs);
  ACE_CDR::Boolean HELLOWORLD_STUB_Export operator >> (ACE_InputCDR & stream, Message & rhs);
}

#endif  // !defined _TCPIP_HELLOWORLDC_H_
