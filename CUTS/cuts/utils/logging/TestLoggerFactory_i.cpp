// $Id$

#include "TestLoggerFactory_i.h"
#include "TestLogger_i.h"
#include "Logging_Client_Options.h"
#include "ace/INET_Addr.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Guard_T.h"

//
// CUTS_TestLoggerFactory_i
//
CUTS_TestLoggerFactory_i::
CUTS_TestLoggerFactory_i (long test_number, PortableServer::POA_ptr test_poa)
: test_number_ (test_number),
  test_poa_ (test_poa)
{
  // Get the hostname of the logging client.
  char hostname[1024];
  ACE_OS::hostname (hostname, sizeof (hostname));
  ACE_INET_Addr inet ((u_short)0, hostname, AF_ANY);

  this->hostname_.reset (ACE_OS::strdup (inet.get_host_name ()));

  // Create a new TestLogger object and instantiate it under the
  // child POA provided in the constructor.
  ACE_NEW_THROW_EX (this->logger_,
                    CUTS_TestLogger_i (*this),
                    CORBA::NO_MEMORY ());

  PortableServer::ObjectId_var oid =
    this->test_poa_->activate_object (this->logger_);

  this->servant_ = this->logger_;
}

//
// ~CUTS_TestLoggerFactory_i
//
CUTS_TestLoggerFactory_i::~CUTS_TestLoggerFactory_i (void)
{

}

//
// create
//
CUTS::TestLogger_ptr CUTS_TestLoggerFactory_i::create (void)
{
  ACE_DEBUG ((LM_DEBUG,
              "%M (%t) - %T - create a new test logger for test %d\n",
              this->test_number_));

  CORBA::Object_var obj =
    this->test_poa_->servant_to_reference (this->logger_);

  {
    ACE_GUARD_RETURN (ACE_Thread_Mutex,
                      guard,
                      this->lock_,
                      CUTS::TestLogger::_nil ());

    if (this->logger_->increment () == 1)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%M (%t) - %T - starting the logger for test %d\n",
                  this->test_number_));

      // Start the logger.
      ACE_Time_Value timeout (CUTS_LOGGING_OPTIONS->timeout_);
      this->logger_->start (timeout);
    }
  }

  ACE_DEBUG ((LM_DEBUG,
              "%M (%t) - %T - returning logger for test %d to client\n",
              this->test_number_));

  CUTS::TestLogger_var logger = CUTS::TestLogger::_narrow (obj.in ());
  return logger._retn ();
}

//
// database
//
void CUTS_TestLoggerFactory_i::database (const ACE_CString & server)
{
  try
  {
    // Establish a connection with the database.
    this->conn_.connect (CUTS_USERNAME,
                         CUTS_PASSWORD,
                         server.c_str ());
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - caught unknown exception; failed to connect to "
                "database on %s\n",
                server.c_str ()));
  }
}

//
// destroy
//
void CUTS_TestLoggerFactory_i::destroy (CUTS_TestLogger_i * logger)
{
  ACE_GUARD (ACE_Thread_Mutex,
             guard,
             this->lock_);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) -  %M - decrementing logger for test %d reference count\n",
              this->test_number_));

  if (this->logger_->decrement () == 0)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - stopping test %d logger event loop\n",
                this->test_number_));

    this->logger_->stop ();
  }
}

//
// poa
//
PortableServer::POA_ptr CUTS_TestLoggerFactory_i::poa (void)
{
  PortableServer::POA_var poa =
    PortableServer::POA::_duplicate (this->test_poa_.in ());

  return poa._retn ();
}

//
// connection
//
CUTS_DB_Connection & CUTS_TestLoggerFactory_i::connection (void)
{
  return this->conn_;
}
