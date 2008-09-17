// $Id$

#include "TestManager_i.h"
#include "Testing_App.h"
#include "cuts/UUID.h"

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
// details
//
CUTS::TestDetails * CUTS_TestManager_i::details (void)
{
  // Create a new object to hold the test details.
  CUTS::TestDetails * details = 0;

  ACE_NEW_THROW_EX (details,
                    CUTS::TestDetails (),
                    CORBA::NO_MEMORY ());

  CUTS::TestDetails_var auto_clean = details;

  // Initialize the content of the object.
  details->uid <<= this->parent_.test_uuid ();
  details->name = CORBA::string_dup (this->parent_.test_name ().c_str ());

  // Return the details to the client.
  return auto_clean._retn ();
}
