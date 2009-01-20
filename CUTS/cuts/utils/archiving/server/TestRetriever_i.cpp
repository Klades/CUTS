// $Id$

#include "TestRetriever_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestRetriever_i.inl"
#endif

#include "ace/FILE_Connector.h"
#include <sstream>

//
// recv_data
//
CORBA::Boolean CUTS_TestRetriever_i::recv_data (CUTS::BinaryData_out packet)
{
  // Allocate a new chunk for the data.
  ACE_NEW_THROW_EX (packet,
                    CUTS::BinaryData (this->chunk_size_),
                    CORBA::NO_MEMORY ());

  packet->length (this->chunk_size_);

  // Now, read data from the file.
  ssize_t count = this->file_.recv (packet->get_buffer (), this->chunk_size_);

  if (count == -1)
    throw CUTS::OperationFailed ();
  else if (count < this->chunk_size_)
    packet->length (count);

  return count != 0;
}

//
// open
//
int CUTS_TestRetriever_i::open (const ACE_CString & path)
{
  // Construct the location of the test file.
  std::ostringstream ostr;
  ostr << path.c_str () << "/"
       << this->uuid_.to_string ()->c_str () << ".cdb";

  this->file_addr_.set (ostr.str ().c_str ());

  ACE_FILE_Connector disk;
  return disk.connect (this->file_, this->file_addr_);
}
