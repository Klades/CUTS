// -*- C++ -*-
// $Id$

//
// ~CUTS_TestArchiveBrowser_i
//
CUTS_INLINE
CUTS_TestArchiveBrowser_i::~CUTS_TestArchiveBrowser_i (void)
{

}

//
// done
//
CUTS_INLINE
CORBA::Boolean CUTS_TestArchiveBrowser_i::done (void)
{
  return this->is_done_;
}
