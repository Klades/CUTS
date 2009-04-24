// -*- C++ -*-
// $Id$

//
// ~CUTS_CUTE_Property_Locator
//
CUTS_INLINE
CUTS_CUTE_Property_Locator::~CUTS_CUTE_Property_Locator (void)
{

}

//
// clear
//
CUTS_INLINE
void CUTS_CUTE_Property_Locator::clear (void)
{
  this->map_.unbind_all ();
  this->total_size_ = 0;
}

//
// clear
//
CUTS_INLINE
const CUTS_CUTE_Property_Locator::map_type &
CUTS_CUTE_Property_Locator::items (void) const
{
  return this->map_;
}
