// $Id$

#include "Boost_JUnit_Formatter.h"
#include "boost/test/unit_test_suite.hpp"

//
// CUTS_Boost_JUnit_Formatter
//
CUTS_Boost_JUnit_Formatter::
CUTS_Boost_JUnit_Formatter (const boost::unit_test::unit_test_log & log)
: boost::unit_test::unit_test_log_formatter (log)
{

}

//
// ~CUTS_Boost_JUnit_Formatter
//
CUTS_Boost_JUnit_Formatter::~CUTS_Boost_JUnit_Formatter (void)
{

}

//
// start_log
//
void CUTS_Boost_JUnit_Formatter::
start_log (std::ostream & output, bool log_build_info)
{
  output
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"
    << std::endl;
}

//
// finish_log
//
void CUTS_Boost_JUnit_Formatter::
finish_log (std::ostream & output)
{

}

//
// log_header
//
void CUTS_Boost_JUnit_Formatter::
log_header (std::ostream & output,
            boost::unit_test::unit_test_counter counter)
{

}

//
// track_test_case_scope
//
void CUTS_Boost_JUnit_Formatter::
track_test_case_scope (std::ostream & output,
                       const boost::unit_test::test_case & tc,
                       bool is_open)
{
  if (tc.p_type)
  {
    if (is_open)
      output << "<testcase name=\"" << tc.p_name << "\">";
    else
      output << "</testcase>";
  }
  else
  {
    if (is_open)
      output << "<testsuite name=\"" << tc.p_name << "\">";
    else
      output << "</testsuite>";
  }
}

//
// log_exception
//
void CUTS_Boost_JUnit_Formatter::
log_exception (std::ostream & output,
               boost::unit_test::const_string test_name,
               boost::unit_test::const_string explanation)
{
  output << "<error>" << explanation << "</error>";
}

//
// begin_log_entry
//
void CUTS_Boost_JUnit_Formatter::
begin_log_entry (std::ostream & output, log_entry_types let)
{
  switch (let)
  {
  case BOOST_UTL_ET_INFO:
  case BOOST_UTL_ET_MESSAGE:
    break;

  case BOOST_UTL_ET_WARNING:
    output << "<failure>";
    this->closing_tag_ = "</failure>";
    break;

  case BOOST_UTL_ET_ERROR:
  case BOOST_UTL_ET_FATAL_ERROR:
    output << "<error>";
    this->closing_tag_ = "</error>";
    break;

  default:
    this->closing_tag_.clear ();
  }
}

//
// log_entry_value
//
void CUTS_Boost_JUnit_Formatter::
log_entry_value (std::ostream & output, boost::unit_test::const_string value)
{
  if (!this->closing_tag_.empty ())
    output << value;
}

//
// end_log_entry
//
void CUTS_Boost_JUnit_Formatter::end_log_entry (std::ostream & output)
{
  if (!this->closing_tag_.empty ())
  {
    output << this->closing_tag_;
    this->closing_tag_.clear ();
  }
}
