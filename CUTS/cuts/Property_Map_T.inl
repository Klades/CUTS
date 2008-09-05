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
CUTS_Property_Map_T <MUTEX>::~CUTS_Property_Map_T (void)
{

}

//
// get
//
template <typename MUTEX>
CUTS_INLINE
int CUTS_Property_Map_T <MUTEX>::
get (const ACE_CString & key, ACE_CString & value) const
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
ACE_CString & CUTS_Property_Map_T <MUTEX>::operator [] (const ACE_CString & key)
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

template <typename MUTEX>
CUTS_INLINE
size_t CUTS_Property_Map_T <MUTEX>::size (void) const
{
  return this->map_.current_size ();
}

//
// contains
//
template <typename MUTEX>
CUTS_INLINE
bool CUTS_Property_Map_T <MUTEX>::contains (const ACE_CString & name) const
{
  return this->map_.find (name) == 0;
}

//
// begin
//
template <typename MUTEX>
CUTS_INLINE
typename CUTS_Property_Map_T <MUTEX>::iterator
CUTS_Property_Map_T <MUTEX>::begin (void)
{
  return this->map_.begin ();
}

//
// begin
//
template <typename MUTEX>
CUTS_INLINE
typename CUTS_Property_Map_T <MUTEX>::const_iterator
CUTS_Property_Map_T <MUTEX>::begin (void) const
{
  return this->map_.begin ();
}

//
// end
//
template <typename MUTEX>
CUTS_INLINE
typename CUTS_Property_Map_T <MUTEX>::iterator
CUTS_Property_Map_T <MUTEX>::end (void)
{
  return this->map_.end ();
}

//
// end
//
template <typename MUTEX>
CUTS_INLINE
typename CUTS_Property_Map_T <MUTEX>::const_iterator
CUTS_Property_Map_T <MUTEX>::end (void) const
{
  return this->map_.end ();
}
