// $Id$

#include "TestManager_i.h"
#include "Testing_App.h"

//
// CUTS_TestManager_i
//
CUTS_TestManager_i::CUTS_TestManager_i (CUTS_Testing_App & parent)
: parent_ (parent)
{

}

//
// ~CUTS_TestManager_i
//
CUTS_TestManager_i::~CUTS_TestManager_i (void)
{

}

//
// test_number
//
CORBA::Long CUTS_TestManager_i::test_number (void)
{
  return this->parent_.current_test_number ();
}
