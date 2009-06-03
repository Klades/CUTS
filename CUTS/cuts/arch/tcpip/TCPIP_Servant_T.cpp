// $Id$

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Servant_T.inl"
#endif

#include "ace/CORBA_macros.h"

//
// vtable_
//
template <typename T>
CUTS_TCPIP_Servant_VTable_T <T> CUTS_TCPIP_Servant_T <T>::vtable_;

//
// CUTS_TCPIP_Servant_T
//
template <typename T>
CUTS_TCPIP_Servant_T <T>::
CUTS_TCPIP_Servant_T (T * servant)
: servant_ (servant)
{

}
