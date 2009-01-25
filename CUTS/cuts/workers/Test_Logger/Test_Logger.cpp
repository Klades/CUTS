// $Id$

#include "Test_Logger.h"
#include "Test_Logger_i.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_sys_time.h"
#include <sstream>

//
// CUTS_Test_Logger
//
CUTS_Test_Logger::CUTS_Test_Logger (void)
{
  CUTS_Test_Logger_i * impl = 0;
  ACE_NEW_THROW_EX (impl, CUTS_Test_Logger_i (), ACE_bad_alloc ());
  this->impl_.reset (impl);
}

//
// ~CUTS_Test_Logger
//
CUTS_Test_Logger::~CUTS_Test_Logger (void)
{

}

//
// configure
//
bool CUTS_Test_Logger::configure (short port)
{
  try
  {
    return this->impl_->configure (port);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception (%N:%l)\n"));
  }

  return false;
}

//
// connect
//
bool CUTS_Test_Logger::
connect_using_location (const ACE_CString & location)
{
  try
  {
    return this->impl_->connect_using_location (location);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception (%N:%l)\n"));
  }

  return false;
}

//
// connect
//
bool CUTS_Test_Logger::
connect_using_name (const ACE_CString & name)
{
  try
  {
    return this->impl_->connect_using_name (name);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception (%N:%l)\n"));
  }

  return false;
}

//
// connect
//
bool CUTS_Test_Logger::connect (void)
{
  try
  {
    return this->impl_->connect ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception (%N:%l)\n"));
  }

  return false;
}

//
// log
//
bool CUTS_Test_Logger::log (long severity, const char * format, ...)
{
  try
  {
    ACE_Time_Value tv = ACE_OS::gettimeofday ();

    // Initialize the variable arguments list.
    va_list args;
    va_start (args, format);

    // Parse the format string.
    std::ostringstream ostr;
    this->parser_.parse (format, args, ostr);

    // End the variable arguments.
    va_end (args);

    // Pass control to the implementation.
    return this->impl_->log (tv,
                             severity,
                             ostr.str ().c_str (),
                             ostr.str ().length ());
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception (%N:%l)\n"));
  }

  return false;
}

//
// disconnect
//
void CUTS_Test_Logger::disconnect (void)
{
  try
  {
    this->impl_->disconnect ();
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception (%N:%l)\n"));
  }
}
