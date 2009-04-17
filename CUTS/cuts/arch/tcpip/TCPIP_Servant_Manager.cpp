// $Id$

#include "TCPIP_Servant_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Servant_Manager.inl"
#endif

#include "TCPIP_Servant.h"

//
// activate_object
//
int
CUTS_TCPIP_Servant_Manager::activate_object (CUTS_TCPIP_Servant * obj)
{
  // Generate a new UUID.
  ACE_Utils::UUID uuid;
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (uuid);

  // Insert the object into the map.
  int retval = this->active_objects_.bind (uuid, obj);

  if (0 == retval)
  {
    // Set the UUID of the object.
    obj->uuid_ = uuid;

    // Increment the reference count.
    obj->incr_refcount ();
  }

  return retval;
}

//
// deactivate_object
//
int
CUTS_TCPIP_Servant_Manager::deactivate_object (const ACE_Utils::UUID & uuid)
{
  // Remove the object from the list.
  CUTS_TCPIP_Servant * obj = 0;
  int retval = this->active_objects_.unbind (uuid, obj);

  if (0 == retval)
  {
    // Reset the UUID of the object.
    obj->uuid_ = ACE_Utils::UUID::NIL_UUID;

    // Decrement the reference count.
    obj->decr_refcount ();
  }

  return retval;
}
