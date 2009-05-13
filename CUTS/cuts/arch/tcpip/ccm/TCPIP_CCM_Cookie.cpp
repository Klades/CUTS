// $Id$

#include "TCPIP_CCM_Cookie.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_CCM_Cookie.inl"
#endif

//
// CUTS_TCPIP_CCM_Cookie
//
CUTS_TCPIP_CCM_Cookie::CUTS_TCPIP_CCM_Cookie (const ACE_Utils::UUID & uuid)
{
  this->cookieValue ().length (16);
  ACE_OS::memcpy (this->cookieValue ().get_buffer (),
                  &uuid,
                  16);
}

//
// extract
//
void CUTS_TCPIP_CCM_Cookie::extract (ACE_Utils::UUID & uuid)
{
  ACE_Utils::UUID temp;

  ACE_OS::memcpy (&temp,
                  this->cookieValue ().get_buffer (),
                  16);

  uuid = temp;
}

//
// create_for_unmarshal
//
::CORBA::ValueBase *
CUTS_TCPIP_CCM_Cookie_Factory::create_for_unmarshal (void)
{
  ::CORBA::ValueBase * value = 0;

  ACE_NEW_THROW_EX (value,
                    CUTS_TCPIP_CCM_Cookie (),
                    ::CORBA::NO_MEMORY ());

  return value;
}
