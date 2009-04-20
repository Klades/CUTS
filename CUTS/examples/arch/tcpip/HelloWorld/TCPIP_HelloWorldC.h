// -*- C++ -*-

#ifndef _TCPIP_HELLOWORLDC_H_
#define _TCPIP_HELLOWORLDC_H_

#include "cuts/arch/tcpip/TCPIP_Object_T.h"
#include "cuts/arch/tcpip/TCPIP_Var_T.h"
#include "HelloWorld_stub_export.h"

namespace TCPIP
{
  struct HELLOWORLD_STUB_Export TimeValue
  {
    ACE_UINT32 sec;
    ACE_UINT32 usec;
  };

  // Forward decl.
  class Message;

  /// Type definition fo the Message_var type.
  typedef CUTS_TCPIP_Var_T <Message> Message_var;

  class HELLOWORLD_STUB_Export Message :
    public CUTS_TCPIP_MT_Object
  {
  public:
    /// Type definition of the _var type.
    typedef Message_var var_type;

    /// Default constructor.
    Message (void);

    /// Destructor.
    virtual ~Message (void);

    TimeValue & time (void);
    const TimeValue & time (void) const;
    void time (const TimeValue & time);

    ACE_CString & message (void);
    const ACE_CString & message (void) const;
    void message (const char * message);

  private:
    TimeValue time_;

    ACE_CString message_;
  };
}

#endif  // !defined _TCPIP_HELLOWORLDC_H_
