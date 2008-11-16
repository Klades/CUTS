// $Id$

//
// CUTS_Test_Logging_Server
//
CUTS_INLINE
CUTS_Test_Logging_Server::CUTS_Test_Logging_Server (void)
: task_ (*this)
{

}

//
// CUTS_Test_Logging_Server
//
CUTS_INLINE
CUTS_Test_Logging_Server::CUTS_Test_Logging_Server (CORBA::ORB_ptr orb)
: task_ (*this),
  orb_ (CORBA::ORB::_duplicate (orb))
{

}

//
// CUTS_Test_Logging_Server
//
CUTS_INLINE
CUTS_Test_Logging_Server::~CUTS_Test_Logging_Server (void)
{

}

