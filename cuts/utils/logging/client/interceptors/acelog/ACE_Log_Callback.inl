// -*- C+-*
// $Id$

//
// CUTS_ACE_Log_Callback
//
CUTS_INLINE
CUTS_ACE_Log_Callback::
CUTS_ACE_Log_Callback (CUTS_Client_Logger & logger)
: logger_ (logger),
  old_callback_(0)
{
}

//
// get_old_callback
//
CUTS_INLINE
ACE_Log_Msg_Callback *
CUTS_ACE_Log_Callback::old_callback (void)
{
  return this->old_callback_;
}

//
// set_old_callback
//
CUTS_INLINE
void CUTS_ACE_Log_Callback::old_callback (ACE_Log_Msg_Callback *old_callback_obj)
{
  this->old_callback_ = old_callback_obj;
}