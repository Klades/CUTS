// $Id$

#include "ACE_Msg_Backend.h"
#include "ace/Log_Msg.h"
#include "ace/OS_Memory.h"

//
// CUTS_ACE_Msg_Backend_Interceptor
//
CUTS_ACE_Msg_Backend::CUTS_ACE_Msg_Backend (void)
: logger_ ("CUTS_ACE_Msg_Backend")
{

}

//
// ~CUTS_ACE_Msg_Backend_Interceptor
//
CUTS_ACE_Msg_Backend::~CUTS_ACE_Msg_Backend (void)
{
}

//
// open
//
int CUTS_ACE_Msg_Backend::open (const ACE_TCHAR *logger_key)
{
  return this->logger_.connect (logger_key);
}

//
// reset
//
int CUTS_ACE_Msg_Backend::reset (void)
{
  return 0;
}

//
// close
//
int CUTS_ACE_Msg_Backend::close (void)
{
  return this->logger_.disconnect ();
}

//
// log
//
ssize_t CUTS_ACE_Msg_Backend::log (ACE_Log_Record &log_record)
{
  this->logger_.log (log_record.priority (),
                     log_record.msg_data (),
                     log_record.length ());

  // Manually invoke the old message callback
  if (this->old_msg_backend_ != 0)
    this->old_msg_backend_->log (log_record);

  return log_record.length ();
}

//
// get_old_msg_backend
//
ACE_Log_Msg_Backend *
CUTS_ACE_Msg_Backend::old_msg_backend (void)
{
  return this->old_msg_backend_;
}

//
// set_old_msg_backend
//
void
CUTS_ACE_Msg_Backend::old_msg_backend
(ACE_Log_Msg_Backend * old_msg_backend_obj)
{
  this->old_msg_backend_ = old_msg_backend_obj;
}
