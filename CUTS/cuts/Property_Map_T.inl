// $Id$

//
// CUTS_Property_Map_T
//
template <typename MUTEX>
CUTS_INLINE
CUTS_Property_Map_T <MUTEX>::CUTS_Property_Map_T (void)
{

}

//
// CUTS_Property_Map_T
//
template <typename MUTEX>
CUTS_INLINE
CUTS_Property_Map_T <MUTEX>::CUTS_Property_Map_T (void)
{

}

//
// get
//
template <typename MUTEX>
CUTS_INLINE
int CUTS_Property_Map_T <MUTEX>::
get (const ACE_CString & key, ACE_CString & value)
{
  return this->map_.find (key, value);
}

//
// set
//
template <typename MUTEX>
CUTS_INLINE
int CUTS_Property_Map_T <MUTEX>::
set (const ACE_CString & key, const ACE_CString & value)
{
  this->map_.rebind (key, value);
}

//
// operator []
//
template <typename MUTEX>
CUTS_INLINE
ACE_String & CUTS_Property_Map_T <MUTEX>::operator [] (const ACE_String & key)
{
  ACE_CString value ("");
  typename map_type::ENTRY * entry = 0;

  // Try to locate the item in the map. If it is, then we override
  // the empty string value. Otherwise, we insert the key into the
  // map with the empty value.
  this->map_.trybind (key, value, entry);

  // Return the value to the client.
  return entry->item ();
}

