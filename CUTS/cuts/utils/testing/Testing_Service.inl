// -*- C++ -*-
// $Id$

//
// CUTS_Testing_Service
//
CUTS_INLINE
CUTS_Testing_Service::CUTS_Testing_Service (void)
: app_ (0)
{

}

//
// ~CUTS_Testing_Service
//
CUTS_INLINE
CUTS_Testing_Service::~CUTS_Testing_Service (void)
{

}

//
// init
//
CUTS_INLINE
int CUTS_Testing_Service::init (int argc, char * argv [])
{
  return 0;
}

//
// fini
//
CUTS_INLINE
int CUTS_Testing_Service::fini (void)
{
  return 0;
}

//
// handle_startup
//
CUTS_INLINE
int CUTS_Testing_Service::handle_startup (const ACE_Time_Value &)
{
  return 0;
}

//
// handle_shutdown
//
CUTS_INLINE
int CUTS_Testing_Service::handle_shutdown (const ACE_Time_Value &)
{
  return 0;
}

//
// test_app
//
CUTS_INLINE
CUTS_Testing_App_Base * const CUTS_Testing_Service::test_app (void)
{
  return this->app_;
}
