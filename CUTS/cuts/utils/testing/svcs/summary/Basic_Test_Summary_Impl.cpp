// $Id$

#include "Basic_Test_Summary_Impl.h"

#if !defined (__CUTS_INLINE__)
#include "Basic_Test_Summary_Impl.inl"
#endif

#include "streams.h"
#include "cuts/utils/testing/Testing_App.h"
#include <sstream>

//
// generate
//
int CUTS_Basic_Test_Summary_Impl::
generate (std::ostream & out, const CUTS_Testing_App & app) const
{
  std::ostringstream ostr;

  // Calculate the duration of the test.
  ACE_Time_Value duration = app.options ().stop_ - app.options ().start_;

  // Buffer the test summary before output it.
  ostr
    << "CUTS Test Summary" << std::endl
    << "=============================================================" << std::endl
    << "  Name       : " << app.options ().name_.c_str () << std::endl
    << "  Start Time : " << app.options ().start_ << std::endl
    << "  Stop Time  : " << app.options ().stop_ << std::endl
    << "  Duration   : " << duration.sec () << " second(s)" << std::endl
    << std::endl;

  // Write the string to the output stream.
  out << ostr.str () << std::endl;

  return 0;
}
