// -*- C++ -*-
// $Id$

CUTS_INLINE
CUTS_Log_Message_Handler::~CUTS_Log_Message_Handler (void)
{

}

CUTS_INLINE
int CUTS_Log_Message_Handler::
handle_log_message(const ACE_Utils::UUID & , const CUTS::LogMessage & )
{
  return 0;
}
