// $Id$

#include "Client_Logger.h"
#include "Format_Parser.h"
#include "cuts/UUID.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_sys_time.h"
#include "ace/OS_NS_unistd.h"
#include <sstream>

//
// CUTS_Client_Logger
//
CUTS_Client_Logger::CUTS_Client_Logger (const char * name)
{
  char * args_str = "";
  int argc = 0;
  char ** argv;

  ACE_OS::string_to_argv (args_str, argc, argv);
  this->orb_ = ::CORBA::ORB_init (argc, argv, name);
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
  try
  {
    // Convert the string to an object.
    ::CORBA::Object_var obj = this->orb_->string_to_object (client);

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to convert string to object\n")),
                         -1);

    // Extract the logger for the
    this->client_ = ::CUTS::LoggingClient::_narrow (obj.in ());

    if (::CORBA::is_nil (this->client_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a CUTS::LoggingClient\n")),
                         -1);

    this->set_uuid_i (this->uuid_);
    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}

//
// disconnect
//
int CUTS_Client_Logger::disconnect (void)
{
  try
  {
    if (!::CORBA::is_nil (this->client_.in ()))
    {
      this->client_->release (this->logger_.in ());
      this->logger_ = ::CUTS::Logger::_nil ();
    }

    this->client_ = ::CUTS::LoggingClient::_nil ();
    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}

//
// set_uuid
//
int CUTS_Client_Logger::set_uuid (const ACE_Utils::UUID & uuid)
{
  try
  {
    if (0 == this->set_uuid_i (uuid))
      this->uuid_ = uuid;

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}

//
// set_uuid_i
//
int CUTS_Client_Logger::set_uuid_i (const ACE_Utils::UUID & uuid)
{
  if (::CORBA::is_nil (this->client_.in ()))
    return -1;

  // Conver the UUID to its binary format.
  ::CUTS::UUID test_uuid;
  test_uuid <<= uuid;

  // Get the logger for the specified UUID.
  this->logger_ = this->client_->get_logger (test_uuid);
  return 0;
}

//
// log
//
int CUTS_Client_Logger::log (int severity, const char * format, ...)
{
  try
  {
    if (::CORBA::is_nil (this->logger_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - logger does not exist\n")),
                         -1);

    ACE_Time_Value tv = ACE_OS::gettimeofday ();

    // Initialize the variable arguments list.
    va_list args;
    va_start (args, format);

    // Parse the format string.
    std::ostringstream ostr;
    this->parser_.parse (format, args, ostr);

    // End the variable arguments.
    va_end (args);

    // Copy the contents to a ::CUTS::LogMessage object.
    CUTS::LogMessage logmsg;
    logmsg.severity = severity;
    logmsg.timestamp.sec = tv.sec ();
    logmsg.timestamp.usec = tv.usec ();

    ::CORBA::ULong length = ostr.str ().length () + 1;
    logmsg.message.length (length);

    ACE_OS::memcpy (logmsg.message.get_buffer (),
                    ostr.str ().c_str (),
                    length);

    this->logger_->log (logmsg);
    return 0;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception (%N:%l)\n")));
  }

  return -1;
}
