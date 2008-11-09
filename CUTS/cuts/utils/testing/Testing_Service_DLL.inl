// $Id$

//
// CUTS_Testing_Service_DLL
//
CUTS_INLINE
CUTS_Testing_Service_DLL::CUTS_Testing_Service_DLL (void)
: factory_ (0),
  svc_ (0)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::CUTS_Testing_Service_DLL (void)");
}

//
// CUTS_Testing_Service_DLL
//
CUTS_INLINE
CUTS_Testing_Service_DLL::
CUTS_Testing_Service_DLL (const char * module, const char * symbol)
: factory_ (0),
  svc_ (0)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::CUTS_Testing_Service_DLL (const char *, const char *)");
  this->open (module, symbol);
}

//
// ~CUTS_Testing_Service_DLL
//
CUTS_INLINE
CUTS_Testing_Service_DLL::~CUTS_Testing_Service_DLL (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::~CUTS_Testing_Service_DLL (void)");
  this->close ();
}

