// $Id$

//
// CUTS_ORB_Server_Task
//
CUTS_INLINE
CUTS_ORB_Server_Task::CUTS_ORB_Server_Task (::CORBA::ORB_ptr orb)
: orb_ (::CORBA::ORB::_duplicate (orb))
{
  CUTS_TRACE ("CUTS_ORB_Server_Task::CUTS_ORB_Server_Task (::CORBA::ORB_ptr)");
}

//
// CUTS_ORB_Server_Task
//
CUTS_INLINE
CUTS_ORB_Server_Task::~CUTS_ORB_Server_Task (void)
{
  CUTS_TRACE ("CUTS_ORB_Server_Task::~CUTS_ORB_Server_Task (void)");
}

//
// CUTS_ORB_Server_Task
//
CUTS_INLINE
int CUTS_ORB_Server_Task::reset (CORBA::ORB_ptr orb)
{
  CUTS_TRACE ("CUTS_ORB_Server_Task::init (CORBA::ORB_ptr)");

  this->orb_ = ::CORBA::ORB::_duplicate (orb);
  return 0;
}
