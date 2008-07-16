// $Id$

//
// CUTS_Threadpool_Server_Strategy
//
CUTS_INLINE
CUTS_Threadpool_Server_Strategy::
CUTS_Threadpool_Server_Strategy (CORBA::ORB_ptr orb)
: CUTS_Logging_Server_Thread_Strategy (orb),
  thr_count_ (7)
{

}

//
// ~CUTS_Threadpool_Server_Strategy
//
CUTS_INLINE
CUTS_Threadpool_Server_Strategy::~CUTS_Threadpool_Server_Strategy (void)
{

}

//
// thr_count
//
CUTS_INLINE
size_t CUTS_Threadpool_Server_Strategy::thr_count (void) const
{
  return this->thr_count_;
}

//
// thr_count
//
CUTS_INLINE
void CUTS_Threadpool_Server_Strategy::thr_count (size_t count)
{
  this->thr_count_ = count;
}
