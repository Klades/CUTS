// -*- C++ -*-

#include "HelloWorldEC.h"
#include "cuts/arch/ccm/CCM_Component_T.h"
#include "HelloWorld_Basic_Impl_export.h"

typedef CUTS_CCM_Component_T <
  ::CIDL_HelloWorld_Basic_Impl::HelloWorld_Exec,
  ::CCM_HelloWorld_Context > 
  HelloWorld_Basic_Impl_Base;

class HelloWorld_Basic_Impl : public HelloWorld_Basic_Impl_Base
{
  // Consturctor
  HelloWorld_Basic_Impl (void);

  // Destructor
  virtual ~HelloWorld_Basic_Impl (void);

  // push_handle_message
  virtual void push_handle_message (::Message * ev);

  // Setter method for message
  virtual void message (const char * message);

  // Getter method for message
  virtual char * message (void);

  // Getter method for readonly_message
  virtual char * readonly_message (void);

  // environment: activate
  virtual void ccm_activate (void);
};

