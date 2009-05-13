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
: is_connected_ (false),
  test_name_ ("(default)")
{
  char * args_str = "";
  int argc = 0;
  char ** argv;

  ACE_OS::string_to_argv (args_str, argc, argv);
  this->orb_ = ::CORBA::ORB_init (argc, argv, "CUTS_Test_Logger_i");
}

//
// ~CUTS_Test_Logger_i
//
CUTS_Test_Logger_i::~CUTS_Test_Logger_i (void)
{
  if (this->is_connected_)
    this->disconnect ();

  try
  {
    // Destroy the ORB.
    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->destroy ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception (%N:%l)\n"));
  }
}

//
// configure
//
bool CUTS_Test_Logger_i::configure (short port)
{
  std::ostringstream ostr;
  ostr << "corbaloc:iiop:localhost:" << port << "/CUTS/LocalTestLoggerClient";

  try
  {
    // Request a reference to the CUTS::LocalTestLoggerClient
    ::CORBA::Object_var obj = this->orb_->string_to_object (ostr.str ().c_str ());

    if (::CORBA::is_nil (obj.in ()))
      return false;

    // Extract the local logging client.
    this->log_client_ = CUTS::LocalTestLoggerClient::_narrow (obj.in ());
    return !::CORBA::is_nil (this->log_client_.in ());
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n"
                "%T (%t) - %M - failed to connect to local test logger client [%s]\n",
                ex._info ().c_str (),
                ostr.str ().c_str ()));
  }

  return false;
}

//
// connect_using_location
//
bool CUTS_Test_Logger_i::
connect_using_location (const ACE_CString & location)
{
  // Construct the corbaloc for the CUTS/TestManager
  std::ostringstream ostr;
  ostr << "corbaloc:iiop:" << location.c_str () << "/CUTS/TestManager";

  if (this->connect_i (ostr.str ().c_str ()) == 0)
    return this->connect ();

  ACE_ERROR ((LM_ERROR,
              "%T (%t) - %M - failed to get test manager\n"));
  return false;
}

//
// connect_using_name
//
bool CUTS_Test_Logger_i::
connect_using_name (const ACE_CString & name)
{
  // Construct the corbaloc for the CUTS/TestManager
  std::ostringstream ostr;
  ostr << "corbaname:rir:#CUTS/TestManager/" << name.c_str ();

  if (this->connect_i (ostr.str ().c_str ()) == 0)
    return this->connect ();

  ACE_ERROR ((LM_ERROR,
              "%T (%t) - %M - failed to get test manager\n"));
  return false;
}

//
// connect
//
bool CUTS_Test_Logger_i::connect (void)
{
  try
  {
    if (::CORBA::is_nil (this->log_client_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - logger client is NIL; please invoke "
                         "configure () first\n"),
                         false);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - locating factory for test %s\n",
                this->uuid_.to_string ()->c_str ()));

    // Locate the logger factory for this test.
    CUTS::UUID uuid;

    uuid <<= this->uuid_;
    this->log_factory_ = this->log_client_->find (uuid);

    if (::CORBA::is_nil (this->log_factory_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - test logger factory is NIL\n"),
                         false);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - creating a new logger\n"));

    // Create a logger from the logging factory.
    this->logger_ = this->log_factory_->create ();

    if (::CORBA::is_nil (this->logger_.in ()))
      return false;

    this->logger_->start (30);
    return true;
  }
  catch (const CUTS::RegistrationNotFound &)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to find factory for test %s\n",
                this->uuid_.to_string ()->c_str ()));
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n"
                "%T (%t) - %M - failed to create logger client\n",
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
  try
  {
    if (::CORBA::is_nil (this->logger_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - logger is NIL; please connect with client\n"),
                         false);

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
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));

    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - log message failed\n"));
  }

  return false;
}

//
// connect_i
//
int CUTS_Test_Logger_i::connect_i (const char * refstr)
{
  try
  {
    // Resolve the test manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - converting string into object [%s]\n",
                refstr));

    CORBA::Object_var obj = this->orb_->string_to_object (refstr);

    if (::CORBA::is_nil (obj.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to locate object\n"),
                         -1);
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - converting object into test manager\n"));

    this->test_manager_ = ::CUTS::TestManager::_narrow (obj.in ());

    if (::CORBA::is_nil (this->test_manager_.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - reference is not a "
                         "CUTS::TestManger object\n"),
                         -1);
    }

    // Get the test details and store the UUID
    CUTS::TestDetails_var details = this->test_manager_->details ();
    details->uid >>= this->uuid_;

    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - logging data under test %s\n",
                this->uuid_.to_string ()->c_str ()));
    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// disconnect
//
void CUTS_Test_Logger_i::disconnect (void)
{
  try
  {
    if (!::CORBA::is_nil (this->logger_.in ()))
    {
      // Stop the logger.
      this->logger_->stop ();

      // Destroy the logger if we have reference to the factory.
      if (!::CORBA::is_nil (this->log_factory_.in ()))
        this->log_factory_->destroy (this->logger_.in ());

      this->is_connected_ = false;
    }
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}
