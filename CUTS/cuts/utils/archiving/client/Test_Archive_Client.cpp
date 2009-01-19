// $Id$

#include "Test_Archive_Client.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Archive_Client.inl"
#endif

#include "cuts/UUID.h"
#include "cuts/utils/testing/Test_Database.h"
#include "ace/FILE_Connector.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"

#define DEFAULT_BUFSIZE 512

static const char * __HELP__ =
"Client for uploading test results to the CUTS archive\n"
"\n"
"  Usage: cutsarc [OPTIONS]\n"
"\n"
"Main options:\n"
"  -f, --file=TEST            upload TEST to archive\n"
"\n"
"Informative output:\n"
"  -v, --verbose              display verbose information\n"
"  -h, --help                 display this help screen\n";

//
// run_main
//
int CUTS_Test_Archive_Client::run_main (int argc, char * argv [])
{
  try
  {
    if (this->parse_args (argc, argv) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to parse command-line arguments\n"),
                         -1);
    }

    // Get the UUID from the test database.
    ACE_Utils::UUID uuid;

    if (this->get_test_uuid (uuid) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - invalid file; failed to "
                         "read test uuid\n"),
                         -1);
    }

    // Open the file for reading in binary format.
    ACE_FILE_Addr addr (this->opts_.input_file_.c_str ());

    ACE_FILE_IO file;
    int flags = O_BINARY | O_RDONLY;
    ACE_FILE_Connector connector (file, addr, 0, ACE_Addr::sap_any, 0, flags);

    if (file.get_handle () == ACE_INVALID_HANDLE)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to open file %s\n",
                         this->opts_.input_file_.c_str ()),
                         -1);
    }

    // Resolve the test archive for the client.
    CORBA::Object_var obj =
      this->orb_->resolve_initial_references ("TestArchive");

    if (CORBA::is_nil (obj.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - please define -ORBInitRef TestArchive\n"),
                         -1);
    }

    this->archive_ = CUTS::TestArchive::_narrow (obj.in ());

    if (CORBA::is_nil (this->archive_.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - initial reference is not a TestArchive\n"),
                         -1);
    }

    // Begin uploading the test to the archive server.
    CUTS::TestProfile result;
    result.uid <<= uuid;

    CUTS::TestUploader_var uploader = this->archive_->begin_upload (result);

    // Send the test's data to the server.
    CUTS::ResultData data (DEFAULT_BUFSIZE);

    this->is_busy_ = true;
    ssize_t count;

    do
    {
      // Read a chunk of the data file.
      data.length (DEFAULT_BUFSIZE);
      count = file.recv (data.get_buffer (), DEFAULT_BUFSIZE);

      if (count > 0)
      {
        // Update the length of the buffer.
        if (count < DEFAULT_BUFSIZE)
          data.length (count);

        // Send the data to the server.
        uploader->send_data (data);
      }
    } while (this->is_busy_ && count != 0);

    // Close the file.
    file.close ();

    if (count == 0)
    {
      // The upload is complete.
      this->archive_->upload_complete (uploader.in ());
    }
    else
    {
      // Cancel the current upload.
      // this->archive_->cancel_upload (uploader.in ());
    }

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// parse_args
//
int CUTS_Test_Archive_Client::parse_args (int argc, char * argv [])
{
  this->orb_ = CORBA::ORB_init (argc, argv);

  const char * optargs = "f:vh";
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);

  char opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (ACE_OS::strcmp ("file", get_opt.long_option ()) == 0)
      {
        this->opts_.input_file_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("help", get_opt.long_option ()) == 0)
      {
        this->print_help ();
      }
      break;

    case 'f':
      this->opts_.input_file_ = get_opt.opt_arg ();
      break;

    case 'h':
      this->print_help ();
      break;

    case 'v':
      break;
    }
  }

  return 0;
}

//
// print_help
//
void CUTS_Test_Archive_Client::print_help (void)
{
  std::cout << __HELP__ << std::endl;
  ACE_OS::exit (0);
}

//
// destroy
//
void CUTS_Test_Archive_Client::destroy (void)
{
  try
  {
    // Destroy the ORB.
    this->orb_->destroy ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// shutdown
//
void CUTS_Test_Archive_Client::shutdown (void)
{
  try
  {
    this->is_busy_ = false;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// get_test_uuid
//
int CUTS_Test_Archive_Client::
get_test_uuid (ACE_Utils::UUID & uuid)
{
  try
  {
    // Open the database for reading.
    CUTS_Test_Database test_db;

    if (!test_db.open (this->opts_.input_file_))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to open %s for reading\n",
                         this->opts_.input_file_.c_str ()),
                         -1);
    }

    // Extract the UUID from the test database.
    CUTS_Test_Profile profile;
    int retval = test_db.get_test_profile (profile);

    if (retval == 0)
      uuid = profile.uuid_;

    return retval;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex.message ().c_str ()));
  }

  return -1;
}
