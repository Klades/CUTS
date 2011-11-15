// $Id$

//
// CUTS_Testing_Service_DLL
//
CUTS_INLINE
CUTS_Testing_Service_DLL::
CUTS_Testing_Service_DLL (const char * module, const char * symbol)
: svc_ (0)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::CUTS_Testing_Service_DLL (const char *, const char *)");
  this->init ();
  this->open (module, symbol);
}

//
// CUTS_Testing_Service_DLL
//
CUTS_INLINE
CUTS_Testing_Service_DLL::CUTS_Testing_Service_DLL (void)
: svc_ (0)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::CUTS_Testing_Service_DLL (void)");
  this->init ();
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

//
// operator ->
//
CUTS_INLINE
CUTS_Testing_Service * CUTS_Testing_Service_DLL::operator -> (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::operator -> (void)");
  return this->svc_;
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Testing_Service_DLL_Guard

//
// CUTS_Testing_Service_DLL_Guard
//
CUTS_INLINE
CUTS_Testing_Service_DLL_Guard::
CUTS_Testing_Service_DLL_Guard (CUTS_Testing_Service_DLL & dll)
: guard_ (dll.svc_config_.get ())
{

}

//
// ~CUTS_Testing_Service_DLL_Guard
//
CUTS_INLINE
CUTS_Testing_Service_DLL_Guard::~CUTS_Testing_Service_DLL_Guard (void)
{

}
