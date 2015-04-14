// -*- C++ -*-
// $Id$

//
// CUTS_Lock_Worker
//
CUTS_INLINE
CUTS_Lock_Worker::CUTS_Lock_Worker (void)
: cond_ (mutex_)
{

}

//
// ~CUTS_Lock_Worker
//
CUTS_INLINE
CUTS_Lock_Worker::~CUTS_Lock_Worker (void)
{

}

CUTS_INLINE
void CUTS_Lock_Worker::noop (void)
{

}