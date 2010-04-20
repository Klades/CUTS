// -*- C++ -*-
// $Id$

//
// ~CUTS_DatabaseWorker
//
CUTS_INLINE
CUTS_Database_Worker::~CUTS_Database_Worker (void)
{
  this->destroy_connection ();
}
