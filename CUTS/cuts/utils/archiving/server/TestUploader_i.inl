// -*- C++ -*-
// $Id$

//
// CUTS_TestUploader_i
//
CUTS_INLINE
CUTS_TestUploader_i::
CUTS_TestUploader_i (const ACE_Utils::UUID & uuid,
                     const ACE_CString & output_dir)
: uuid_ (uuid),
  output_dir_ (output_dir),
  file_addr_ (reinterpret_cast <const ACE_FILE_Addr &> (ACE_Addr::sap_any))
{
  this->init ();
}

//
// send_data
//
CUTS_INLINE
void CUTS_TestUploader_i::
send_data (const CUTS::ResultData & packet)
{
  this->file_.send (packet.get_buffer (), packet.length ());
}

//
// uuid
//
CUTS_INLINE
const ACE_Utils::UUID & CUTS_TestUploader_i::uuid (void) const
{
  return this->uuid_;
}

//
// uuid
//
CUTS_INLINE
bool CUTS_TestUploader_i::is_open (void) const
{
  return this->file_.get_handle () != ACE_INVALID_HANDLE;
}
