// $Id$

#if !defined (__CUTS_INLINE__)
# include "Periodic_Event_T.inl"
#endif

#include "ace/OS_NS_stdlib.h"
#include "ace/OS_NS_time.h"
#include "ace/Time_Value.h"

//
// CUTS_Periodic_Event_T
//
template <typename COMPONENT>
CUTS_Periodic_Event_T <COMPONENT>::CUTS_Periodic_Event_T (void)
: component_ (0),
  method_ (0)
{

}

//
// ~CUTS_Periodic_Event_T
//
template <typename COMPONENT>
CUTS_Periodic_Event_T <COMPONENT>::~CUTS_Periodic_Event_T (void)
{

}

//
// handle_timeout
//
template <typename COMPONENT>
int CUTS_Periodic_Event_T <COMPONENT>::handle_timeout_i (void)
{
  if (this->component_ != 0 && this->method_ != 0)
  {
    // Make upcall to the component.
    (this->component_->*this->method_) ();
  }
  else
  {
    if (this->component_ == 0)
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - target component not set in peridoic event"));
    else
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - target method not set in peridoic event"));
  }

  return 0;
}
