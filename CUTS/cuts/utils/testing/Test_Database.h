// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Database.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEST_DATABASE_H_
#define _CUTS_TEST_DATABASE_H_

#include "Test_Database_export.h"
#include "cuts/utils/db/SQLite/Connection.h"
#include "ace/Auto_Ptr.h"
#include "ace/SString.h"

// Forward decl.
class CUTS_DB_Connection;

// Forward decl.
class ACE_Time_Value;

namespace ACE_Utils
{
  // Forward decl.
  class UUID;
}

/**
 * @class CUTS_Test_Database
 */
class CUTS_TEST_DATABASE_Export CUTS_Test_Database
{
public:
  /// Default constructor.
  CUTS_Test_Database (void);

  /// Destructor
  ~CUTS_Test_Database (void);

  /**
   * Get a reference to the test database.
   *
   * @return        Reference to database connection.
   */
  CUTS_DB_Connection * operator -> (void);

  /**
   * Create the test database.
   */
  bool create (const ACE_CString & location,
               const ACE_Utils::UUID & uuid);

  /**
   * Open the test database.
   *
   *@param[in]      location        Location of the database.
   */
  bool open (const ACE_CString & location);

  /// Close the connection to the database.
  void close (void);

  void start_new_test (void);
  void start_new_test (const ACE_Time_Value & tv);

  void stop_current_test (void);
  void stop_current_test (const ACE_Time_Value & tv);

  CUTS_DB_SQLite_Query * create_query (void);

  /**
   * Get the UUID stored in the test database.
   *
   * @param[out]        uuid        UUID in the database
   * @retval            0           Successfully read test UUID
   * @retval            -1          Failed to read test UUID
   */
  int get_test_uuid (ACE_Utils::UUID & uuid);

  /**
   * Set the UUID for the test.
   */
  int set_test_uuid (const ACE_Utils::UUID & uuid);

private:
  void init (void);

  bool open_i (const ACE_CString & location, long flags);

  /// Output directory of the database.
  ACE_CString outdir_;

  /// Connection to the SQLite database.
  ACE_Auto_Ptr <CUTS_DB_SQLite_Connection> conn_;

  /// Id of the active test in the database.
  ACE_INT32 active_id_;
};

#if defined (__CUTS_INLINE__)
#include "Test_Database.inl"
#endif

#endif  // !defined _CUTS_TEST_DATABASE_H_
