// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_Log_Message

//
// CUTS_Log_Message
//
CUTS_INLINE
CUTS_Log_Message::CUTS_Log_Message (void)
: next_ (0)
{

}

//
// set_next
//
CUTS_INLINE
void CUTS_Log_Message::set_next (CUTS_Log_Message * next)
{
  this->next_ = next;
}

//
// get_next
//
CUTS_INLINE
CUTS_Log_Message * CUTS_Log_Message::get_next (void)
{
  return this->next_;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_TestLogger_i

//
// handle_timeout
//
CUTS_INLINE
int CUTS_TestLogger_i::
handle_timeout (const ACE_Time_Value &, const void *)
{
  this->send_messages ();
  return 0;
}

