// $Id$

//
// unit_test
//
CUTS_INLINE
const CUTS_Unite_Test * CUTS_Dataset_Result::unit_test (void) const
{
  return this->unit_test_;
}

//
// vtable_name
//
CUTS_INLINE
const ACE_CString * CUTS_Dataset_Result::vtable_name (void) const
{
  return this->vtable_name_;
}