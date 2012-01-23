// $Id$

#include "OpenSplice_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Container_Strategy.inl"
#endif

#include "cuts/iccm/arch/opensplice/servant/OpenSplice_Servant.h"

namespace iCCM
{

//
//OpenSplice_Container_Strategy
//
OpenSplice_Container_Strategy::
OpenSplice_Container_Strategy (OpenSplice_Container & container)
  : base_type (container)
{

}

//
// configure_servant
//
void
OpenSplice_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & config)
{
  OpenSplice_Servant * ospl_servant = dynamic_cast <OpenSplice_Servant *> (servant);

  if (0 != ospl_servant)
    ospl_servant->configure ();
}

}
