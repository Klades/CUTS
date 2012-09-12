// $Id$

#include "TCPIP_Servant_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Servant_Manager.inl"
#endif

#include "../servant/TCPIP_Servant.h"

//
// activate_object
//
int
CUTS_TCPIP_Servant_Manager::activate_object (iCCM::TCPIP_Servant * obj)
{
  // Generate a new UUID.
  ACE_Utils::UUID uuid;
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (uuid);

  // Insert the object into the map.
  if (0 != this->active_objects_.bind (uuid, obj))
    return -1;

  // Set the UUID of the object.
  obj->uuid_ = uuid;
  obj->orb_ = this->orb_;
  return 0;
}

//
// deactivate_object
//
int
CUTS_TCPIP_Servant_Manager::deactivate_object (const ACE_Utils::UUID & uuid)
{
  // Remove the object from the list.
  iCCM::TCPIP_Servant * obj = 0;
  if (0 != this->active_objects_.unbind (uuid, obj))
    return -1;

  // Reset the UUID of the object.
  obj->uuid_ = ACE_Utils::UUID::NIL_UUID;
  obj->orb_ = 0;
  return 0;
}

//
// get_uuid
//
int CUTS_TCPIP_Servant_Manager::
get_uuid (iCCM::TCPIP_Servant * obj, ACE_Utils::UUID & uuid) const
{
  map_type::CONST_ITERATOR iter (this->active_objects_);

  for (; !iter.done (); ++ iter)
  {
    if (iter->item () == obj)
    {
      uuid = iter->key ();
      return 0;
    }
  }

  return -1;
}
