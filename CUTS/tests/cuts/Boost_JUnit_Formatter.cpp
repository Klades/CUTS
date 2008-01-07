// $Id$

#include "Boost_JUnit_Formatter.h"
#include "boost/test/unit_test_suite.hpp"
#include "boost/test/test_tools.hpp"

//
// CUTS_Boost_JUnit_Formatter
//
CUTS_Boost_JUnit_Formatter::
CUTS_Boost_JUnit_Formatter (void)
{

}

//
// CUTS_Boost_JUnit_Formatter
//
CUTS_Boost_JUnit_Formatter::
CUTS_Boost_JUnit_Formatter (const std::string & package)
: package_ (package)
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
log_start (std::ostream & output, boost::unit_test::counter_t test_cases_amount)
{
  output
    << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"
    << std::endl;
}

//
// log_build_info
//
void CUTS_Boost_JUnit_Formatter::
log_build_info (std::ostream & output)
{

}

//
// finish_log
//
void CUTS_Boost_JUnit_Formatter::log_finish (std::ostream & output)
{

}

//
// test_unit_start
//
void CUTS_Boost_JUnit_Formatter::
test_unit_start (std::ostream & output,
                 const boost::unit_test::test_unit & tu)
{
  switch (tu.p_type)
  {
  case boost::unit_test::tut_any:
  case boost::unit_test::tut_case:
    output << "<testcase";
    break;

  case boost::unit_test::tut_suite:
    output << "<testsuite package=\"" << this->package_ << "\"";
    break;
  }

  output << " name=\"" << tu.p_name << "\">" << std::endl;
}

//
// test_unit_finish
//
void CUTS_Boost_JUnit_Formatter::
test_unit_finish (std::ostream & output,
                  const boost::unit_test::test_unit & tu,
                  unsigned long elapsed)
{
  output << "</test" << tu.p_type_name << ">" << std::endl;
}

//
// test_unit_skipped
//
void CUTS_Boost_JUnit_Formatter::
test_unit_skipped (std::ostream & output,
                   const::boost::unit_test::test_unit & tu)
{

}

//
// log_exception
//
void CUTS_Boost_JUnit_Formatter::
log_exception (std::ostream & output,
               const boost::unit_test::log_checkpoint_data & lcd,
               boost::unit_test::const_string explanation)
{
  output << "<error>" << explanation << "</error>" << std::endl;
}

//
// log_entry_begin
//
void CUTS_Boost_JUnit_Formatter::
log_entry_start (std::ostream & output,
                 const boost::unit_test::log_entry_data & led,
                 boost::unit_test::unit_test_log_formatter::log_entry_types let)
{
  switch (let)
  {
  case BOOST_UTL_ET_INFO:
  case BOOST_UTL_ET_MESSAGE:
    this->closing_tag_.clear ();
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
// log_entry_end
//
void CUTS_Boost_JUnit_Formatter::
log_entry_finish (std::ostream & output)
{
  if (!this->closing_tag_.empty ())
  {
    output << this->closing_tag_ << std::endl;
    this->closing_tag_.clear ();
  }
}
