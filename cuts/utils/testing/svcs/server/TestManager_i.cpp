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
  // Get the test profile from the database.
  CUTS_Test_Database & archive = this->server_.test_app ()->test_db ();
  CUTS_Test_Profile profile;

  if (archive.get_test_profile (profile) != 0)
    ACE_ERROR ((LM_WARNING,
                "%T (%t) - %M - failed to get test profile from archive\n"));

  // Create a new object to hold the test details.
  CUTS::TestDetails_var details;

  ACE_NEW_THROW_EX (details,
                    ::CUTS::TestDetails (),
                    ::CORBA::NO_MEMORY ());

  // Initialize the content of the object.
  details->uid <<= profile.uuid_;
  details->name = CORBA::string_dup (profile.name_.c_str ());

  // Return the details to the client.
  return details._retn ();
}

//
// shutdown
//
void CUTS_TestManager_i::shutdown (void)
{
  this->server_.test_app ()->shutdown ();
}
