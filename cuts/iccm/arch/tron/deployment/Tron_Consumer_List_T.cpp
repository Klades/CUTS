//  $Id$

#include "Tron_Consumer_List_T.h"
#include "../servant/Tron_EventConsumer.h"
#include "boost/bind.hpp"

//
// Tron_Consumer_List_T
//
template <typename T>
CUTS_INLINE
Tron_Consumer_List_T <T>::
Tron_Consumer_List_T (void)
{

}


//
// ~Tron_Consumer_List_T
//
template <typename T>
CUTS_INLINE
Tron_Consumer_List_T <T>::
~Tron_Consumer_List_T (void)
{

}

//
// add
//
template <typename T>
CUTS_INLINE
void Tron_Consumer_List_T <T>::
add (::iCCM::Tron_EventConsumer * consumer)
{
  this->consumers_.push_back (consumer);
}


//
// push_event
//
template <typename T>
void Tron_Consumer_List_T <T>::
push_event (uint16_t size, const int32_t data[])
{
  // Figure out the Tron_Event event type to create
  typedef typename ::iCCM::Tron_Event_Traits <T>::tron_event_type tron_event_type;

  // Narrow the push_event to the correct overload
  typedef void (::iCCM::Tron_EventConsumer::* PUSH_METHOD) (tron_event_type *);

  // Create and intialize the event
  tron_event_type ev (size, data);

  // Send the event to the consumers
  std::for_each (this->consumers_.begin (),
                 this->consumers_.end (),
                 boost::bind (reinterpret_cast <PUSH_METHOD> (&::iCCM::Tron_EventConsumer::push_event),
                              _1,
                              &ev));
}
