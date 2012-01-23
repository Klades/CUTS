// $Id$

#include "Cookie.h"

#if !defined (__CUTS_INLINE__)
#include "Cookie.inl"
#endif

namespace iCCM
{

//
// Cookie
//
Cookie::Cookie (const ACE_Utils::UUID & uuid)
{
  this->cookieValue ().length (16);

  ACE_OS::memcpy (this->cookieValue ().get_buffer (),
                  &uuid,
                  16);
}

//
// extract
//
void Cookie::extract (ACE_Utils::UUID & uuid)
{
  ACE_OS::memcpy (&uuid,
                  this->cookieValue ().get_buffer (),
                  16);
}

//
// create_for_unmarshal
//
::CORBA::ValueBase * Cookie_Factory::create_for_unmarshal (void)
{
  ::CORBA::ValueBase * value = 0;

  ACE_NEW_THROW_EX (value,
                    Cookie (),
                    ::CORBA::NO_MEMORY ());

  return value;
}

}
