// -*- C++ -*-
// $Id$

//
// CUTS_ACE_Msg_Backend_Interceptor
//
CUTS_INLINE
CUTS_ACE_Msg_Backend::CUTS_ACE_Msg_Backend (void)
: logger_ ("CUTS_ACE_Msg_Backend")
{

}

//
// ~CUTS_ACE_Msg_Backend_Interceptor
//
CUTS_INLINE
CUTS_ACE_Msg_Backend::~CUTS_ACE_Msg_Backend (void)
{
}

//
// open
//
CUTS_INLINE
int CUTS_ACE_Msg_Backend::open (const ACE_TCHAR *logger_key)
{
  return this->logger_.connect (logger_key);
}

//
// reset
//
CUTS_INLINE
int CUTS_ACE_Msg_Backend::reset (void)
{
  return 0;
}

//
// close
//
CUTS_INLINE
int CUTS_ACE_Msg_Backend::close (void)
{
  return this->logger_.disconnect ();
}

//
// old_msg_backend
//
CUTS_INLINE
ACE_Log_Msg_Backend * CUTS_ACE_Msg_Backend::old_msg_backend (void)
{
  return this->old_msg_backend_;
}

//
// old_msg_backend
//
CUTS_INLINE
void CUTS_ACE_Msg_Backend::
old_msg_backend (ACE_Log_Msg_Backend * old)
{
  this->old_msg_backend_ = old;
}

//
// logger
//
CUTS_INLINE
CUTS_Client_Logger & CUTS_ACE_Msg_Backend::logger (void)
{
  return this->logger_;
}
