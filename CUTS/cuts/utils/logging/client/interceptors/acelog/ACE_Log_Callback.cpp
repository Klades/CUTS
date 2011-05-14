// $Id$

#include "ACE_Log_Callback.h"

#if !defined (__CUTS_INLINE__)
#include "ACE_Log_Callback.inl"
#endif

#include "cuts/utils/logging/client/logger/Client_Logger.h"

//
// log
//
void CUTS_ACE_Log_Callback::log (ACE_Log_Record &log_record)
{
  // Right now this assumes that the msg_data () is NULL terminated. If
  // this is not the case, then we need to NULL terminate the buffer
  // before calling the log () method.
  this->logger_.log (log_record.priority (),
                     /*log_record.pid ()*/
                     ACE_OS::thr_self (),
                     log_record.msg_data ());

 // Some callback was set previously, invoke it manually
  if (0 != this->old_callback_)
    this->old_callback_->log (log_record);
}
