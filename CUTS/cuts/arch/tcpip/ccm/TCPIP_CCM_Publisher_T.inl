// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_CCM_Publisher_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_CCM_Publisher_T <T>::CUTS_TCPIP_CCM_Publisher_T (void)
{

}

//
// ~CUTS_TCPIP_CCM_Publisher_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_CCM_Publisher_T <T>::~CUTS_TCPIP_CCM_Publisher_T (void)
{
  this->disconnect ();
}

//
// send_event
//
template <typename T>
CUTS_INLINE
void CUTS_TCPIP_CCM_Publisher_T <T>::send_event (T * ev)
{
  this->endpoint_.send_event (ev);
}
