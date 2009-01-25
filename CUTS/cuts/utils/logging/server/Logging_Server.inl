// $Id$

//
// CUTS_Test_Logging_Server
//
CUTS_INLINE
CUTS_Test_Logging_Server::CUTS_Test_Logging_Server (void)
: is_owner_ (false),
  archive_ (0)
{

}

//
// CUTS_Test_Logging_Server
//
CUTS_INLINE
CUTS_Test_Logging_Server::CUTS_Test_Logging_Server (CORBA::ORB_ptr orb)
: orb_ (::CORBA::ORB::_duplicate (orb))
{

}

//
// CUTS_Test_Logging_Server
//
CUTS_INLINE
CUTS_Test_Logging_Server::~CUTS_Test_Logging_Server (void)
{
  if (this->is_owner_ && this->archive_ != 0)
    delete this->archive_;
}

//
// install_callback
//
CUTS_INLINE
int CUTS_Test_Logging_Server::
install_callback (CUTS::TestLoggerServerCallback_ptr callback)
{
  return this->server_.install_callback (callback);
}
