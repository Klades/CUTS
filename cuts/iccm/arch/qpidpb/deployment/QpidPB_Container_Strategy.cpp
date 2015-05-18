// -*- C++ -*-
// $Id$

#include "QpidPB_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Container_Strategy.inl"
#endif

#include "QpidPB_Container.h"
#include "../servant/QpidPB_Servant.h"

namespace iCCM
{

//
// configure_servant
//
void QpidPB_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & values)
{
  // NOTE: The servant can be casted to an QpidPB_Servant
  // by using 'dynamic_cast <QpidPB_Servant *> (servant)'.
  // Also, the ConfigValues passed into this method are the same
  // configuration values attached to a component instance.
}

}
