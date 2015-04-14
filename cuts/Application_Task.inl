// -*- C++ -*-
// $Id$


CUTS_INLINE
CUTS_Application_Task::~CUTS_Application_Task (void)
{
  this->deactivate ();
}

CUTS_INLINE
bool CUTS_Application_Task::is_active (void) const
{
  return this->active_;
}

CUTS_INLINE
void CUTS_Application_Task::nthreads (int n)
{
  this->nthreads_ = n;
}

CUTS_INLINE
int CUTS_Application_Task::nthreads (void) const
{
  return this->nthreads_;
}