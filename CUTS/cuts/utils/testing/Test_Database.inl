// $Id$

#include "ace/OS_NS_sys_time.h"


//
// CUTS_Test_Database
//
CUTS_INLINE
CUTS_Test_Database::CUTS_Test_Database (void)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::CUTS_Test_Database (void)");
  this->init ();
}

//
// ~CUTS_Test_Database
//
CUTS_INLINE
CUTS_Test_Database::~CUTS_Test_Database (void)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::~CUTS_Test_Database (void)");
}

//
// operator ->
//
CUTS_INLINE
CUTS_DB_Connection * CUTS_Test_Database::operator -> (void)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::operator -> (void)");
  return this->conn_.get ();
}

//
// close
//
CUTS_INLINE
void CUTS_Test_Database::close (void)
{
  CUTS_TEST_DATABASE_TRACE ("CUTS_Test_Database::close (void)");
  this->conn_->disconnect ();
}

//
// start_new_test
//
CUTS_INLINE
void CUTS_Test_Database::start_new_test (void)
{
  this->start_new_test (ACE_OS::gettimeofday ());
}

//
// start_new_test
//
CUTS_INLINE
void CUTS_Test_Database::stop_current_test (void)
{
  this->stop_current_test (ACE_OS::gettimeofday ());
}

//
// start_new_test
//
CUTS_INLINE
CUTS_DB_SQLite_Query * CUTS_Test_Database::create_query (void)
{
  return this->conn_->create_query ();
}
