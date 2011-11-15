// -*- C++ -*-
// $Id$

//
// CUTS_CUTE_Property_Locator_Handler
//
CUTS_INLINE
CUTS_CUTE_Property_Locator_Handler::CUTS_CUTE_Property_Locator_Handler (void)
{

}

//
// ~CUTS_CUTE_Property_Locator_Handler
//
CUTS_INLINE
CUTS_CUTE_Property_Locator_Handler::~CUTS_CUTE_Property_Locator_Handler (void)
{

}

//
// handle_attribute
//
CUTS_INLINE
int CUTS_CUTE_Property_Locator_Handler::
handle_attribute (GAME::Mga::Attribute_in, const ACE_Unbounded_Set <ACE_CString> &)
{
  return 0;
}

//
// handle_name
//
CUTS_INLINE
int CUTS_CUTE_Property_Locator_Handler::
handle_name (GAME::Mga::Object_in, const ACE_Unbounded_Set <ACE_CString> &)
{
  return 0;
}
