// $Id$

//
// CUTS_Property_Map
//
CUTS_INLINE
CUTS_Property_Map::CUTS_Property_Map (void)
{

}

//
// ~CUTS_Property_Map
//
CUTS_INLINE
CUTS_Property_Map::~CUTS_Property_Map (void)
{

}

//
// get
//
CUTS_INLINE
int CUTS_Property_Map::
get (const ACE_CString & key, ACE_CString & value) const
{
  return this->map_.find (key, value);
}

//
// set
//
CUTS_INLINE
int CUTS_Property_Map::
set (const ACE_CString & key, const ACE_CString & value)
{
  return this->map_.rebind (key, value);
}

//
// operator []
//
CUTS_INLINE
ACE_CString & CUTS_Property_Map::operator [] (const ACE_CString & key)
{
  ACE_CString value ("");
  map_type::ENTRY * entry = 0;

  // Try to locate the item in the map. If it is, then we override
  // the empty string value. Otherwise, we insert the key into the
  // map with the empty value.
  this->map_.trybind (key, value, entry);

  // Return the value to the client.
  return entry->item ();
}

//
// size
//
CUTS_INLINE
size_t CUTS_Property_Map::size (void) const
{
  return this->map_.current_size ();
}

//
// contains
//
CUTS_INLINE
bool CUTS_Property_Map::contains (const ACE_CString & name) const
{
  return this->map_.find (name) == 0;
}

//
// begin
//
CUTS_INLINE
CUTS_Property_Map::iterator CUTS_Property_Map::begin (void)
{
  return this->map_.begin ();
}

//
// begin
//
CUTS_INLINE
CUTS_Property_Map::const_iterator CUTS_Property_Map::begin (void) const
{
  return this->map_.begin ();
}

//
// end
//
CUTS_INLINE
CUTS_Property_Map::iterator CUTS_Property_Map::end (void)
{
  return this->map_.end ();
}

//
// end
//
CUTS_INLINE
CUTS_Property_Map::const_iterator CUTS_Property_Map::end (void) const
{
  return this->map_.end ();
}

//
// map
//
CUTS_INLINE
const CUTS_Property_Map::map_type & CUTS_Property_Map::map (void) const
{
  return this->map_;
}

//
// map
//
CUTS_INLINE
void CUTS_Property_Map::clear (void)
{
  this->map_.unbind_all ();
}

//
// map
//
CUTS_INLINE
bool CUTS_Property_Map::empty (void) const
{
  return this->map_.current_size () == 0;
}
