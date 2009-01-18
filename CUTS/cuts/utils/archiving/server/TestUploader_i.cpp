// $Id$

#include "TestUploader_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestUploader_i.inl"
#endif

#include "ace/FILE_Connector.h"
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
int CUTS_TestUploader_i::close (void)
{
  // Close the temporary file.
  int retval = this->file_.close ();

  if (retval == 0)
  {
    // Construct the pathname of the real file.
    std::ostringstream ostr;

    ostr << this->output_dir_.c_str () << "/"
         << this->uuid_.to_string ()->c_str ()
         << ".cdb";

    // Copy the temporary file to its real location.
    retval = ACE_OS::rename (this->file_addr_.get_path_name (),
                             ostr.str ().c_str ());

    if (retval == 0)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - successfully uploaded test %s [%s]\n",
                  this->uuid_.to_string ()->c_str (),
                  ostr.str ().c_str ()));
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to save temporary file [%m]\n"));
    }
  }
  else
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to close temporary file [%m]\n"));


  return retval;
}

