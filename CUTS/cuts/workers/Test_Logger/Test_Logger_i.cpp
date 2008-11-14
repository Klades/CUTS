// $Id$

#include "Test_Logger_i.h"
#include "cuts/UUID.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Date_Time.h"
#include <sstream>

//
// CUTS_Test_Logger_i
//
CUTS_Test_Logger_i::CUTS_Test_Logger_i (void)
: test_name_ ("(default)")
{
  char * args_str = "";
  int argc = 0;
  char ** argv;

  ACE_OS::string_to_argv (args_str, argc, argv);
  this->orb_ = CORBA::ORB_init (argc, argv);

  // Initialize the contents of the UUID.
  this->uuid_ <<= ACE_Utils::UUID::NIL_UUID;
}

//
// ~CUTS_Test_Logger_i
//
CUTS_Test_Logger_i::~CUTS_Test_Logger_i (void)
{
  if (!::CORBA::is_nil (this->logger_.in ()))
  {
    // Destroy the logger if we have reference to the factory.
    if (!::CORBA::is_nil (this->log_factory_.in ()))
      this->log_factory_->destroy (this->logger_.in ());
  }

  if (!::CORBA::is_nil (this->log_client_.in ()))
  {
    // Destroy the factory if we have reference to the client.
    if (!::CORBA::is_nil (this->log_factory_.in ()))
      this->log_client_->destroy (this->log_factory_.in ());
  }

  // Destroy the ORB.
  if (!CORBA::is_nil (this->orb_.in ()))
    this->orb_->destroy ();
}

//
// configure
//
bool CUTS_Test_Logger_i::configure (short port)
{
  std::ostringstream ostr;
  ostr << "corbaloc:iiop:localhost:" << port << "/CUTS/TestLoggerClient";

  try
  {
    // Request a reference to the CUTS::TestLoggerClient.
    ::CORBA::Object_var obj = this->orb_->string_to_object (ostr.str ().c_str ());
    this->log_client_ = CUTS::TestLoggerClient::_narrow (obj.in ());

    return !::CORBA::is_nil (this->log_client_.in ());
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n"
                "%T - %M - failed to connect to test logger client\n",
                ex._info ().c_str ()));
  }

  return false;
}

//
// connect
//
bool CUTS_Test_Logger_i::connect (const ACE_CString & name)
{
  try
  {
    // Get a reference to the test manager.
    ::CORBA::Object_var obj = this->orb_->string_to_object (name.c_str ());
    this->test_manager_ = CUTS::TestManager::_narrow (obj.in ());

    if (!::CORBA::is_nil (this->test_manager_.in ()))
    {
      // Save the UUID from the test manager.
      CUTS::TestDetails_var details = this->test_manager_->details ();
      this->uuid_ = details->uid;

      // Finish connecting to the logging client.
      return this->connect ();
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to connect to test manager [%s]\n",
                  name.c_str ()));
    }
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return false;
}

//
// connect
//
bool CUTS_Test_Logger_i::connect (void)
{
  try
  {
    if (!CORBA::is_nil (this->log_client_.in ()))
    {
      // Convert the UUID to display it in string format.
      ACE_Utils::UUID uuid;
      this->uuid_ >>= uuid;

      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %T - creating logger factory for test %s\n",
                  uuid.to_string ()->c_str ()));

      // Create a new logging factory for the test logger.
      this->log_factory_ = this->log_client_->create (this->uuid_);

      if (!CORBA::is_nil (this->log_factory_.in ()))
      {
        ACE_DEBUG ((LM_DEBUG,
                    "%T (%t) - %M - creating a new logger\n"));

        // Create a logger from the logging factory.
        this->logger_ = this->log_factory_->create ();
        return !::CORBA::is_nil (this->logger_.in ());
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - test logger factory is NIL\n"));
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - logger client is NIL; please invoke "
                  "configure () first\n"));
    }
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n"
                "%T - %M - failed to create logger client\n",
                ex._info ().c_str ()));
  }

  return false;
}

//
// log
//
bool CUTS_Test_Logger_i::
log (const ACE_Time_Value & tv, long severity, const char * msg, size_t msg_length)
{
  if (!CORBA::is_nil (this->logger_.in ()))
  {
    try
    {
      // Copy over the time value.
      CUTS::TimeValue ts;
      ts.sec = tv.sec ();
      ts.usec = tv.usec ();

      // Copy the message into the buffer.
      CUTS::MessageText msg_txt (msg_length);
      msg_txt.length (msg_length);

      ACE_OS::memcpy (msg_txt.get_buffer (), msg, msg_length);

      // Send the message to the client.
      this->logger_->log (ts, severity, msg_txt);
      return true;
    }
    catch (const CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  "T - %M - %s\n",
                  ex._info ().c_str ()));

      ACE_ERROR ((LM_ERROR,
                  "T - %M - log message failed\n"));
    }
  }

  return false;
}
