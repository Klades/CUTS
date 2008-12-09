// $Id$

#include "TestUploader_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestUploader_i.inl"
#endif

#include "ace/FILE_Connector.h"

//
// CUTS_TestUploader_i
//
CUTS_TestUploader_i::~CUTS_TestUploader_i (void)
{
  if (this->file_.get_handle () != ACE_INVALID_HANDLE)
    this->file_.remove ();
}

//
// open
//
int CUTS_TestUploader_i::open (const ACE_CString & filename)
{
  // Set the address of the file.
  ACE_FILE_Addr addr (filename.c_str ());

  // Open the file for reading.
  ACE_FILE_Connector conn;
  return conn.connect (this->file_, addr);
}
