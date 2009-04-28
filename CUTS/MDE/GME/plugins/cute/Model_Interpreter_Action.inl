// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_CUTE_Model_Interpreter_Action

//
//
// CUTS_CUTE_Model_Interpreter_Action
//
CUTS_INLINE
CUTS_CUTE_Model_Interpreter_Action::CUTS_CUTE_Model_Interpreter_Action (void)
{

}

//
// ~CUTS_CUTE_Model_Interpreter_Action
//
CUTS_INLINE
CUTS_CUTE_Model_Interpreter_Action::~CUTS_CUTE_Model_Interpreter_Action (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_CUTE_Replace_Model_Name_Action

//
// CUTS_CUTE_Replace_Model_Name_Action
//
CUTS_INLINE
CUTS_CUTE_Replace_Model_Name_Action::
CUTS_CUTE_Replace_Model_Name_Action (const GME::Object & object)
: object_ (object)
{

}

//
// ~CUTS_CUTE_Replace_Model_Name_Action
//
CUTS_INLINE
CUTS_CUTE_Replace_Model_Name_Action::~CUTS_CUTE_Replace_Model_Name_Action (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_CUTE_Replace_Model_Attribute_Action

//
// CUTS_CUTE_Replace_Model_Attribute_Action
//
CUTS_INLINE
CUTS_CUTE_Replace_Model_Attribute_Action::
CUTS_CUTE_Replace_Model_Attribute_Action (const GME::Attribute & attr)
: attr_ (attr)
{

}

//
// ~CUTS_CUTE_Replace_Model_Attribute_Action
//
CUTS_INLINE
CUTS_CUTE_Replace_Model_Attribute_Action::~CUTS_CUTE_Replace_Model_Attribute_Action (void)
{

}
