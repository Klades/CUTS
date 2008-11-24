// $Id$

//
// CUTS_Test_Logging_Server
//
CUTS_INLINE
CUTS_Test_Logging_Server::~CUTS_Test_Logging_Server (void)
{

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
