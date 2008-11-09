// $Id$

#include "Test_Summary_Service.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Summary_Service.inl"
#endif

#include "Basic_Test_Summary_Impl.h"
#include "XML_Test_Summary_Impl.h"

CUTS_TESTING_SERVICE_IMPL (CUTS_Test_Summary_Service, _make_CUTS_Test_Summary_Service);

//
// init
//
int CUTS_Test_Summary_Service::init (int argc, char * argv [])
{
  CUTS_TESTING_SUMMARY_TRACE ("CUTS_Test_Summary_Service::init (int, char * [])");

  CUTS_Test_Summary_Impl * impl = 0;
  ACE_NEW_RETURN (impl, CUTS_Basic_Test_Summary_Impl (), -1);
  this->impl_.reset (impl);

  return 0;
}

//
// handle_shutdown
//
int CUTS_Test_Summary_Service::
handle_shutdown (const ACE_Time_Value & tv)
{
  CUTS_TESTING_SUMMARY_TRACE ("CUTS_Test_Summary_Service::handle_shutdown (const ACE_Time_Value &)");

  if (this->impl_.get () != 0)
    return this->impl_->generate (std::cout, *this->test_app ());

  return 0;
}
