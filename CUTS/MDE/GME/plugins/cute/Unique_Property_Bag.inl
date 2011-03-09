// -*- C++ -*-
// $Id$

//
// CUTS_CUTE_Unique_Property_Bag
//
CUTS_INLINE
CUTS_CUTE_Unique_Property_Bag::CUTS_CUTE_Unique_Property_Bag (void)
{

}

//
// ~CUTS_CUTE_Unique_Property_Bag
//
CUTS_INLINE
CUTS_CUTE_Unique_Property_Bag::~CUTS_CUTE_Unique_Property_Bag (void)
{

}

//
// items
//
CUTS_INLINE
const CUTS_CUTE_Unique_Property_Bag::items_type &
CUTS_CUTE_Unique_Property_Bag::items (void) const
{
  return this->items_;
}

//
// handle_attribute
//
CUTS_INLINE
int CUTS_CUTE_Unique_Property_Bag::
handle_attribute (GAME::Mga::Attribute_in,
                  const ACE_Unbounded_Set <ACE_CString> & params)
{
  this->insert_parameters (params);
  return 0;
}

//
// handle_name
//
CUTS_INLINE
int CUTS_CUTE_Unique_Property_Bag::
handle_name (GAME::Mga::Object_in,
             const ACE_Unbounded_Set <ACE_CString> & params)
{
  this->insert_parameters (params);
  return 0;
}
