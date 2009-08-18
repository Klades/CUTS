// $Id$

#include "Client_Logger.h"
#include "Client_Logger_Impl.h"
#include "Format_Parser.h"
#include <sstream>

//
// CUTS_Client_Logger
//
CUTS_Client_Logger::CUTS_Client_Logger (const char * name)
{
  // Allocate a new client logger implementation.
  CUTS_Client_Logger_Impl * impl = 0;
  ACE_NEW_THROW_EX (impl,
                    CUTS_Client_Logger_Impl (name),
                    ACE_bad_alloc ());
  this->impl_.reset (impl);

  // Allocate a new format parser for the logger.
  CUTS_Format_Parser * parser = 0;
  ACE_NEW_THROW_EX (parser,
                    CUTS_Format_Parser (),
                    ACE_bad_alloc ());
  this->parser_.reset (parser);
}

//
// CUTS_Client_Logger
//
CUTS_Client_Logger::~CUTS_Client_Logger (void)
{

}

//
// connect
//
int CUTS_Client_Logger::connect (const char * client)
{
  return this->impl_->connect (client);
}

//
// disconnect
//
int CUTS_Client_Logger::disconnect (void)
{
  return this->impl_->disconnect ();
}

//
// set_uuid
//
int CUTS_Client_Logger::set_uuid (const ACE_Utils::UUID & uuid)
{
  return this->impl_->set_uuid (uuid);
}

//
// log
//
int CUTS_Client_Logger::log (int severity, const char * format, ...)
{
  // Initialize the variable arguments list.
  va_list args;
  va_start (args, format);

  // Parse the format string.
  std::ostringstream ostr;
  this->parser_->parse (format, args, ostr);

  // End the variable arguments.
  va_end (args);

  return this->impl_->log (severity,
                           ostr.str ().c_str (),
                           ostr.str ().length ());
}
