// $Id$

//
// CUTS_Testing_Service_Manager
//
CUTS_INLINE
CUTS_Testing_Service_Manager::
CUTS_Testing_Service_Manager (CUTS_Testing_App & app)
: test_app_ (app)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_Manager::CUTS_Testing_Service_Manager (CUTS_Testing_App &)");
}

//
// ~CUTS_Testing_Service_Manager
//
CUTS_INLINE
CUTS_Testing_Service_Manager::~CUTS_Testing_Service_Manager (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_Manager::~CUTS_Testing_Service_Manager (void)");
  this->close ();
}
