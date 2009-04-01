// $Id$

//
// unit_test
//
CUTS_INLINE
const CUTS_Unit_Test * CUTS_Unit_Test_Result::unit_test (void) const
{
  return this->unit_test_;
}

//
// vtable_name
//
CUTS_INLINE
const ACE_CString * CUTS_Unit_Test_Result::vtable_name (void) const
{
  return this->vtable_name_;
}
