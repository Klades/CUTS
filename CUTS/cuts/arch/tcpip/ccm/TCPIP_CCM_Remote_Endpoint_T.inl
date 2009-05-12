// -*- C++ -*-
// $Id$

//
// CUTS_TCPIP_CCM_Remote_Endpoint_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_CCM_Remote_Endpoint_T <T>::CUTS_TCPIP_CCM_Remote_Endpoint_T (void)
{

}

//
// ~CUTS_TCPIP_CCM_Remote_Endpoint_T
//
template <typename T>
CUTS_INLINE
CUTS_TCPIP_CCM_Remote_Endpoint_T <T>::~CUTS_TCPIP_CCM_Remote_Endpoint_T (void)
{

}

//
// disconnect
//
template <typename T>
CUTS_INLINE ::Components::EventConsumerBase_ptr
CUTS_TCPIP_CCM_Remote_Endpoint_T <T>::disconnect (void)
{
  return this->consumer_._retn ();
}
