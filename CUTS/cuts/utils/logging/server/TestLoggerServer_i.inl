// $Id$

//
// CUTS_TestLoggerServer_i
//
CUTS_INLINE
CUTS_TestLoggerServer_i::CUTS_TestLoggerServer_i (void)
{

}

//
// install_callback
//
CUTS_INLINE
int CUTS_TestLoggerServer_i::
install_callback (CUTS::TestLoggerServerCallback_ptr callback)
{
  return this->callbacks_.insert (callback);
}
