// $Id$

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

//
// id
//
CUTS_INLINE
size_t CUTS_TestLogger_i::id (void) const
{
  return this->logid_;
}
