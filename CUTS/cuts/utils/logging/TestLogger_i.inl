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

