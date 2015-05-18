// -*- C++ -*-
// $Id$

#include "QpidPB_Container_Strategy.h"

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Container_Strategy.inl"
#endif

#include "QpidPB_Container.h"
#include "../servant/QpidPB_Servant.h"
#include <sstream>

namespace iCCM
{

//
// configure_servant
//
void QpidPB_Container_Strategy::
configure_servant (::PortableServer::Servant servant,
                   const ::Components::ConfigValues & values)
{
  QpidPB_Servant * svnt = dynamic_cast <QpidPB_Servant *> (servant);

  if (svnt == 0)
    throw CORBA::INTERNAL ();

  size_t length = values.length ();
  const char * broker = 0;

  for (size_t i = 0; i < length; ++i)
  {
    if (0 == ACE_OS::strcmp (values[i]->name (), "QPIDBroker"))
      values[i]->value () >>= broker;
  }

  if (broker == 0)
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Using default configuration for ")
                ACE_TEXT ("Qpid Broker [localhost:5672]\n")));
  }
  else
  {
    // Format is [host]:[port]
    std::string host;
    int port;
    int size (ACE_OS::strlen (broker));

    std::istringstream ss (broker);
    std::istream & stream = std::getline (ss, host, ':');
    stream >> port;

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Configuring component for ")
                ACE_TEXT ("Qpid Broker [%s:%d]\n"),
                host.c_str (),
                port));

    svnt->configure_broker (host, port);
  }
}

}
