// $Id$

#include "RTIDDS_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "RTIDDS_Container_Strategy.inl"
#endif

#include "RTIDDS_Container.h"
#include "cuts/arch/rtidds/ccm/RTIDDS_CCM_Servant.h"

//
//CUTS_RTIDDS_CCM_Container_Strategy
//
CUTS_RTIDDS_CCM_Container_Strategy::
CUTS_RTIDDS_CCM_Container_Strategy (CUTS_RTIDDS_CCM_Container & container)
  : base_type (container)
{

}

//
// configure_servant
//
void
CUTS_RTIDDS_CCM_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & config)
{
  // Convert the servant into an RTIDDS servant.
  CUTS_RTIDDS_CCM_Servant * rtidds_servant =
    dynamic_cast <CUTS_RTIDDS_CCM_Servant *> (servant);

  if (0 == rtidds_servant)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - object is not an RTIDDS servant\n")));
    return;
  }

  if (0 != this->configurator_.configure (rtidds_servant, config))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to configure RTIDDS servant\n")));
}

