// $Id$

#include "Logger_i.h"

#if !defined (__CUTS_INLINE__)
#include "Logger_i.inl"
#endif

#include "Log_Message_Handler.h"

//
// log
//
void CUTS_Logger_i::log (const ::CUTS::LogMessage & logmsg)
{
  if (0 != this->handler_->handle_log_message (this->uuid_, logmsg))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to handle log message\n")));
}
