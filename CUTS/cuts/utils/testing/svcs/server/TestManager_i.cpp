// $Id$

#include "TestManager_i.h"
#include "Testing_Server.h"
#include "cuts/utils/testing/Testing_App.h"
#include "cuts/UUID.h"

//
// CUTS_TestManager_i
//
CUTS_TestManager_i::CUTS_TestManager_i (CUTS_Testing_Server & server)
: server_ (server)
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
  details->uid <<= this->server_.test_app ()->options ().uuid_;
  details->name = CORBA::string_dup (this->server_.test_app ()->options ().name_.c_str ());

  // Return the details to the client.
  return auto_clean._retn ();
}
