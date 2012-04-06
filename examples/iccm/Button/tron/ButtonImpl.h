// $Id:

#ifndef _BUTTONIMPL_H_
#define _BUTTONIMPL_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/pre.h"
#include "Button_iCCMC.h"

#include "cuts/arch/ccm/CCM_Component_T.h"
#include "cuts/Periodic_Event_T.h"

namespace ButtonImpl
{
// Type definition of the implementation base type
typedef CUTS_CCM_Component_T < CIAO_Button_Impl::Button_Exec, ::iCCM_Button_Context > Button_Base;

/**
 * @class Button
 *
 * Implementation of the CIAO_Button_Impl::Button_Exec component executor
 */
class Button :
  public Button_Base
{
public:
  // Type definition of the base component type
  typedef Button_Base base_type;

  // Default constructor
  Button (void);

  // Destructor
  virtual ~Button (void);

  // push Click events from Button.idl
  virtual void push_Click (::Notify * ev);

  // PeriodicEvent: EventCreator
  void periodic_EventCreator (void);

private:
  // periodic: EventCreator
  CUTS_Periodic_Event_T < Button > periodic_EventCreator_;
};

}

#include "Button_impl_export.h"

//
// create_HelloReceiver_Impl
//
extern "C" BUTTON_IMPL_Export
::Components::EnterpriseComponent_ptr create_Button_Impl (void);

#include "ace/post.h"

#endif  // !defined _BUTTONIMPL_H_
