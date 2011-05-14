// $Id$

#include "ACE_Msg_Backend.h"

#if !defined (__CUTS_INLINE__)
#include "ACE_Msg_Backend.inl"
#endif

#include "ace/Log_Msg.h"
#include "ace/OS_Memory.h"

//
// log
//
ssize_t CUTS_ACE_Msg_Backend::log (ACE_Log_Record &log_record)
{
  this->logger_.log (log_record.priority (),
                     /*log_record.pid (),*/
                     ACE_OS::thr_self (),
                     log_record.msg_data (),
                     log_record.length ());

  // Manually invoke the old message callback
  if (this->old_msg_backend_ != 0)
    this->old_msg_backend_->log (log_record);

  return log_record.length ();
}