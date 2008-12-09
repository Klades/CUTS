// -*- C++ -*-
// $Id$

//
// CUTS_TestUploader_i
//
CUTS_INLINE
CUTS_TestUploader_i::
CUTS_TestUploader_i (const ACE_Utils::UUID & uuid)
: uuid_ (uuid)
{

}

//
// close
//
CUTS_INLINE
int CUTS_TestUploader_i::close (void)
{
  return this->file_.close ();
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
