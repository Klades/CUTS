// $Id$

#include "Test_Logger_i.h"
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
}

//
// ~CUTS_Test_Logger_i
//
CUTS_Test_Logger_i::~CUTS_Test_Logger_i (void)
{
  if (!CORBA::is_nil (this->logger_.in ()))
  {
    // Destroy the logger if we have reference to the factory.
    if (!CORBA::is_nil (this->log_factory_.in ()))
      this->log_factory_->destroy (this->logger_.in ());
  }

  // Destroy the factory if we have reference to the client.
  if (!CORBA::is_nil (this->log_client_.in ()))
    this->log_client_->destroy (this->log_factory_.in ());

  // Destroy the ORB.
  if (!CORBA::is_nil (this->orb_.in ()))
    this->orb_->destroy ();
}

//
// configure
//
void CUTS_Test_Logger_i::configure (short port)
{
  std::ostringstream ostr;
  ostr << "corbaloc:iiop:localhost:" << port << "/CUTS/TestLoggerClient";

  try
  {
    // Request a reference to the CUTS::TestLoggerClient.
    CORBA::Object_var obj = this->orb_->string_to_object (ostr.str ().c_str ());
    this->log_client_ = CUTS::TestLoggerClient::_narrow (obj.in ());
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n"
                "%T - %M - failed to connect to test logger client\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception\n"));
  }
}

//
// connect
//
void CUTS_Test_Logger_i::connect (const ACE_CString & name)
{
  if (this->connect_i (name))
    this->test_name_ = name;
}

//
// connect
//
void CUTS_Test_Logger_i::connect (void)
{
  this->connect_i (this->test_name_);
}

//
// connect_i
//
bool CUTS_Test_Logger_i::connect_i (const ACE_CString & name)
{
  try
  {
    // Get a reference to the test manager.
    CORBA::Object_var obj = this->orb_->string_to_object (name.c_str ());
    this->test_manager_ = CUTS::TestManager::_narrow (obj.in ());

    // Get the test number from the test manager.
    CUTS::TestDetails_var details = this->test_manager_->details ();

    // Create the logger.
    this->log_factory_ = this->log_client_->create (details->uid);
    this->logger_ = this->log_factory_->create ();

    return true;
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
void CUTS_Test_Logger_i::
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
    }
    catch (const CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  "T - %M - %s\n",
                  ex._info ().c_str ()));

      ACE_ERROR ((LM_ERROR,
                  "T - %M - log message failed\n"));
    }
    catch (...)
    {

    }
  }
}
