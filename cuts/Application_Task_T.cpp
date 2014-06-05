// $Id$

#if !defined (__CUTS_INLINE__)
# include "Application_Task_T.inl"
#endif

#include "ace/OS_NS_stdlib.h"
#include "ace/OS_NS_time.h"
#include "ace/Time_Value.h"

//
// CUTS_Application_Task_T
//
template <typename COMPONENT>
CUTS_Application_Task_T <COMPONENT>::CUTS_Application_Task_T (void)
: component_ (0),
  method_ (0)
{

}

//
// ~CUTS_Application_Task_T
//
template <typename COMPONENT>
CUTS_Application_Task_T <COMPONENT>::~CUTS_Application_Task_T (void)
{

}

//
// svc
//
template <typename COMPONENT>
int CUTS_Application_Task_T <COMPONENT>::svc (void)
{
  try
  {
    (this->component_->*this->method_) ();
    return 0;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%P) - %M - application task caught unknown exception\n")));

    return -1;
  }
}
