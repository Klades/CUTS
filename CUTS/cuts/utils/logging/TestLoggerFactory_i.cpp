// $Id$

#include "TestLoggerFactory_i.h"
#include "TestLoggerClient_i.h"
#include "TestLogger_i.h"
#include "Logging_Client_Options.h"
#include "ace/INET_Addr.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Guard_T.h"

//
// CUTS_TestLoggerFactory_i
//
CUTS_TestLoggerFactory_i::
CUTS_TestLoggerFactory_i (CUTS_TestLoggerClient_i & parent,
                          long test_number, 
                          PortableServer::POA_ptr test_poa)
: parent_ (parent),
  test_number_ (test_number),
  test_poa_ (PortableServer::POA::_duplicate (test_poa))
{

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
  CUTS_TestLogger_i * servant = 0;

  // Create a new TestLogger object and instantiate it under the
  // child POA provided in the constructor.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - create new logger for test %d\n",
              this->test_number_));

  ACE_NEW_THROW_EX (servant,
                    CUTS_TestLogger_i (*this),
                    CORBA::NO_MEMORY ());

  ACE_Auto_Ptr <CUTS_TestLogger_i> auto_clean (servant);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - activating newly created logger for test %d\n",
              this->test_number_));

  PortableServer::ObjectId_var oid =
    this->test_poa_->activate_object (servant);

  CORBA::Object_var obj = this->test_poa_->servant_to_reference (servant);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - starting the logger for test %d\n",
              this->test_number_));

  // Start the logger.
  ACE_Time_Value timeout (CUTS_LOGGING_OPTIONS->timeout_);
  servant->start (timeout);

  ACE_GUARD_RETURN (ACE_Thread_Mutex,
                    guard,
                    this->lock_,
                    CUTS::TestLogger::_nil ());

  // Save the logger to the list of servants.
  if (this->servants_.insert (servant) == 0)
    auto_clean.release ();

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - returning logger for test %d to client\n",
              this->test_number_));

  CUTS::TestLogger_var logger = CUTS::TestLogger::_narrow (obj.in ());
  return logger._retn ();
}

//
// destroy
//
void CUTS_TestLoggerFactory_i::destroy (void)
{
  // First, we need to remove all the logger objects.

  // Tell the parent to remove this factory.
  this->parent_.destroy (this);
}

//
// test_number
//
long CUTS_TestLoggerFactory_i::test_number (void) const
{
  return this->test_number_;
}

//
// database
//
void CUTS_TestLoggerFactory_i::database (const ACE_CString & server)
{
  try
  {
    // Establish a connection with the database.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - connecting to database on '%s'\n",
                server.c_str ()));

    this->conn_.connect (CUTS_USERNAME,
                         CUTS_PASSWORD,
                         server.c_str ());
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception; failed to connect to "
                "database on %s\n",
                server.c_str ()));
  }
}

//
// destroy
//
void CUTS_TestLoggerFactory_i::destroy (CUTS_TestLogger_i * logger)
{
  // First, deactivate the object
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - deactivating logger servant for test %d\n",
              this->test_number_));

  PortableServer::ObjectId_var oid = this->test_poa_->servant_to_id (logger);
  this->test_poa_->deactivate_object (oid);

  // Then, stop the object from handling events. This will cause the
  // logger to dump its queue to the database.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - stopping logger for test %d\n",
              this->test_number_));

  logger->stop ();

  // Remove the logger from our servant listing.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - removing logger for test %d from memory\n",
              this->test_number_));

  this->servants_.remove (logger);
}

//
// poa
//
PortableServer::POA_ptr CUTS_TestLoggerFactory_i::_default_POA (void)
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
