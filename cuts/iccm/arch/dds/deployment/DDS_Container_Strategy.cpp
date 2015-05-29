// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Container_Strategy.inl"
#endif

namespace iCCM
{

//
// DDS_Container_Strategy
//
template <typename T>
DDS_Container_Strategy <T>::
DDS_Container_Strategy (typename T::container_type & container)
: Container_Strategy_T <typename T::container_type> (container)
{

}

//
// configure_servant
//
template <typename T>
void DDS_Container_Strategy <T>::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & config)
{
  typedef typename T::servant_type servant_type;
  servant_type * dds_servant = dynamic_cast <servant_type *> (servant);

  if (0 == dds_servant)
    throw CORBA::INTERNAL ();

  dds_servant->handle_config (config);
}

}
