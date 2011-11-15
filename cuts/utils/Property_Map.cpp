// $Id$

#include "Property_Map.h"

#if !defined (__CUTS_INLINE__)
#include "Property_Map.inl"
#endif

//
// CUTS_Property_Map
//
CUTS_Property_Map::CUTS_Property_Map (const CUTS_Property_Map & copy)
: map_ (copy.size ())
{
  for (map_type::CONST_ITERATOR iter (copy.map ()); !iter.done (); ++ iter)
    this->map_.bind (iter->key (), iter->item ());
}

//
// join
//
size_t CUTS_Property_Map::
join (const CUTS_Property_Map & map, bool overwrite)
{
  int retval;
  size_t count = 0;

  CUTS_Property_Map::const_iterator iter (map.map ());

  for ( ; !iter.done (); ++ iter)
  {
    // Insert the item into the map.
    if (overwrite)
      retval = this->map_.rebind (iter->key (), iter->item ());
    else
      retval = this->map_.bind (iter->key (), iter->item ());

    if (retval == 0 || (overwrite && retval != -1))
      ++ count;
  }

  return count;
}
