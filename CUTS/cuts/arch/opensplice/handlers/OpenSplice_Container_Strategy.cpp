// $Id$

#include "OpenSplice_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Container_Strategy.inl"
#endif

#include "OpenSplice_Container.h"
#include "cuts/arch/opensplice/ccm/OpenSplice_CCM_Servant.h"

//
//CUTS_OpenSplice_CCM_Container_Strategy
//
CUTS_OpenSplice_CCM_Container_Strategy::
CUTS_OpenSplice_CCM_Container_Strategy (CUTS_OpenSplice_CCM_Container & container)
  : base_type (container)
{

}

//
// configure_servant
//
void
CUTS_OpenSplice_CCM_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & config)
{
  // Convert the servant into an OpenSplice servant.
  CUTS_OpenSplice_CCM_Servant * ospl_servant =
    dynamic_cast <CUTS_OpenSplice_CCM_Servant *> (servant);

  if (0 == ospl_servant)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - object is not an OpenSplice servant\n")));
    return;
  }

  if (0 != this->configurator_.configure (ospl_servant, config))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to configure OpenSplice servant\n")));
}

