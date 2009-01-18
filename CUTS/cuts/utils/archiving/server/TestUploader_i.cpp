// $Id$

#include "TestUploader_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestUploader_i.inl"
#endif

#include "cuts/utils/db/DB_Connection.h"
#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/testing/Test_Database.h"
#include "cuts/Auto_Functor_T.h"
#include "ace/FILE_Connector.h"
#include "ace/OS_NS_unistd.h"
#include <sstream>

//
// CUTS_TestUploader_i
//
CUTS_TestUploader_i::~CUTS_TestUploader_i (void)
{
  if (this->file_.get_handle () != ACE_INVALID_HANDLE)
    this->file_.remove ();
}

//
// init
//
int CUTS_TestUploader_i::init (void)
{
  // Open the temporary file for writing.
  ACE_FILE_Connector conn (this->file_, this->file_addr_);
  return this->file_.get_handle () != ACE_INVALID_HANDLE ? 0 : -1;
}

//
// close
//
int CUTS_TestUploader_i::close (CUTS_DB_Connection & conn)
{
  // Close the temporary file.
  int retval = this->file_.close ();

  if (retval != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to close temporary file [%m]\n"),
                       -1);

  // Construct the pathname of the real file.
  std::ostringstream ostr;

  ostr << this->output_dir_.c_str () << "/"
        << this->uuid_.to_string ()->c_str ()
        << ".cdb";

  // Copy the temporary file to its real location.
  retval = ACE_OS::rename (this->file_addr_.get_path_name (),
                           ostr.str ().c_str ());

  if (retval != 0)
  {
    // Delete the temporary file.
    this->file_.unlink ();

    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to save temporary file [%m]\n"),
                       -1);
  }

  try
  {
    CUTS_Test_Database test_db;

    if (test_db.open (ostr.str ().c_str ()))
    {
      // Extract important information from test database.
      CUTS_Test_Profile profile;
      retval = test_db.get_test_profile (profile);

      if (retval == 0)
      {
        // Write the test information to the database.
        CUTS_DB_Query * query = conn.create_query ();

        CUTS_Auto_Functor_T <CUTS_DB_Query>
          auto_clean (query, &CUTS_DB_Query::destroy);

        char uuid[37];
        char name[256];


        // Prepare the SQL statement.
        const char * __STMT__ = "call cuts.insert_test (?, ?)";
        query->prepare (__STMT__);
        query->parameters ()[0].bind (uuid, 0);
        query->parameters ()[1].bind (name, 0);

        // Initialize the parameters.
        ACE_OS::strcpy (uuid, profile.uuid_.to_string ()->c_str ());
        ACE_OS::strcpy (name, profile.name_.c_str ());

        // Execute the SQL statement.
        query->execute_no_record ();

        ACE_DEBUG ((LM_DEBUG,
                    "%T (%t) - %M - successfully uploaded test %s [%s]\n",
                    this->uuid_.to_string ()->c_str (),
                    ostr.str ().c_str ()));
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T - %M - failed to read test profile\n"));
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to open test database [%s]\n",
                  ostr.str ().c_str ()));

      retval = -1;
    }
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }

  if (retval != 0)
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T - %M - deleting test database [%s]\n",
                ostr.str ().c_str ()));

    ACE_OS::unlink (ostr.str ().c_str ());
  }

  return retval;
}

