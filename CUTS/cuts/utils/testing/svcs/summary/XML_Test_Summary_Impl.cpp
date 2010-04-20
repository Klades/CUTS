// $Id$

#include "XML_Test_Summary_Impl.h"

#if !defined (__CUTS_INLINE__)
#include "XML_Test_Summary_Impl.inl"
#endif

#include "cuts/utils/testing/Testing_App.h"
#include "ace/UUID.h"
#include "ace/SString.h"
#include <sstream>

//
// generate
//
int CUTS_XML_Test_Summary_Impl::
generate (std::ostream & out, const CUTS_Testing_App_Base & app) const
{
  std::ostringstream ostr;

  ostr << "<summary>" << std::endl
       << "  <name>" << app.options ().name_.c_str () << "</name>" << std::endl
       << "  <uuid>" << app.options ().uuid_.to_string ()->c_str () << "</uuid>" << std::endl;

  if (app.options ().start_ != ACE_Time_Value::zero)
    ostr << "  <starttime>" << app.options ().start_ << "</starttime>" << std::endl;

  if (app.options ().stop_ != ACE_Time_Value::zero)
    ostr << "  <stoptime>" << app.options ().stop_ << "</stoptime>" << std::endl;

  ostr << "</summary>" << std::endl;

  // Write the XML document to the output stream.
  out << ostr.str ();

  return 0;
}
