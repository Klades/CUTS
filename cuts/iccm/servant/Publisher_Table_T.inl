// -*- C++ -*
// $Id$

namespace iCCM
{

//
// Publisher_Table_T
//
template <typename BASE, typename PUBLISHER, bool AUTO_CONNECT>
CUTS_INLINE
Publisher_Table_T <BASE, PUBLISHER, AUTO_CONNECT>::Publisher_Table_T (void)
{

}

//
// ~Publisher_Table_T
//
template <typename BASE, typename PUBLISHER, bool AUTO_CONNECT>
CUTS_INLINE
Publisher_Table_T <BASE, PUBLISHER, AUTO_CONNECT>::~Publisher_Table_T (void)
{

}

//
// send_event
//
template <typename BASE, typename PUBLISHER, bool AUTO_CONNECT>
CUTS_INLINE
void Publisher_Table_T <BASE, PUBLISHER, AUTO_CONNECT>::
send_event (::Components::EventBase * base)
{
  event_type * ev = dynamic_cast < event_type * > (base);

  if (0 == ev)
    throw ::Components::BadEventType ();

  this->send_event (ev);
}

}
