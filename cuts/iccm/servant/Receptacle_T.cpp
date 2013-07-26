// $Id$

#if !defined (__CUTS_INLINE__)
#include "Receptacle_T.inl"
#endif  // !defined __CUTS_INLINE__

namespace iCCM
{

template <typename T>
::Components::Cookie *
Receptacle_T <T>::connect (::CORBA::Object_ptr obj)
{
  this->connection_ = typename T::_narrow (obj);
  if (CORBA::is_nil (this->connection_))
    throw ::CORBA::INTERNAL ();

  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (this->uuid_);
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - facet cookie value is <%s>\n",
              this->uuid_.to_string ()->c_str ()));

  // Allocate a new cookie for the subscriber.
  OBV_Components::Cookie * cookie = 0;

  ACE_NEW_THROW_EX (cookie,
                    Cookie (this->uuid_),
                    ::CORBA::NO_MEMORY ());

  return cookie;
}

template <typename T>
::CORBA::Object_ptr
Receptacle_T <T>::disconnect (::Components::Cookie * c)
{
  Cookie * cookie = dynamic_cast <Cookie *> (c);

  if (0 == cookie)
    throw ::CORBA::INTERNAL ();

  ACE_Utils::UUID uuid;
  cookie->extract (uuid);

  // Check that the cookie is valid
  if (uuid != this->uuid_)
    throw ::CORBA::INTERNAL ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - disconnecting %s\n"),
              uuid.to_string ()->c_str ()));

  return this->connection_._retn ();
}


template <typename T>
typename T::_ptr_type
Receptacle_T <T>::get_connection (void)
{
  return this->connection_;
}

} // namespace iCCM
