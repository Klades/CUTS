// -*- C++ -*-
// $Id$

//
// CUTS_TestArchive_i
//
CUTS_INLINE
CUTS_TestRetriever_i::
CUTS_TestRetriever_i (const ACE_Utils::UUID & uuid, size_t chunk_size)
: uuid_ (uuid),
  chunk_size_ (chunk_size)
{

}

//
// ~CUTS_TestArchive_i
//
CUTS_INLINE
CUTS_TestRetriever_i::~CUTS_TestRetriever_i (void)
{

}

//
// uuid
//
CUTS_INLINE
const ACE_Utils::UUID & CUTS_TestRetriever_i::uuid (void) const
{
  return this->uuid_;
}

//
// close
//
CUTS_INLINE
int CUTS_TestRetriever_i::close (void)
{
  return this->file_.close ();
}
