// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// DDS_Container
//
template <typename T>
CUTS_INLINE
DDS_Container <T>::
DDS_Container (typename T::component_instance_handler_type * handler, ::PortableServer::POA_ptr the_POA)
: Container_T (handler, the_POA)
{

}

//
// ~DDS_Container
//
template <typename T>
CUTS_INLINE
DDS_Container <T>::~DDS_Container (void)
{

}

}
