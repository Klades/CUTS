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
void CUTS_Test_Logger::configure (short port)
{
  this->impl_->configure (port);
}

//
// connect
//
void CUTS_Test_Logger::connect (const ACE_CString & name)
{
  this->impl_->connect (name);
}

//
// connect
//
void CUTS_Test_Logger::connect (void)
{
  this->impl_->connect ();
}

//
// log
//
void CUTS_Test_Logger::log (long severity, const char * msg)
{
  ACE_Time_Value tv = ACE_OS::gettimeofday ();
  size_t length = ACE_OS::strlen (msg);

  this->impl_->log (tv, severity, msg, length);
}

//
// log
//
void CUTS_Test_Logger::log (long severity, const char * format, ...)
{
  ACE_Time_Value tv = ACE_OS::gettimeofday ();

  // Initialize the variable arguments list.
  va_list args;
  va_start (args, format);

  // Parse the format string.
  std::ostringstream ostr;
  this->parser_.parse (format, args, ostr);

  // Pass control to the implementation.
  this->impl_->log (tv,
                    severity,
                    ostr.str ().c_str (),
                    ostr.str ().length ());

  // End the variable arguments.
  va_end (args);
}
