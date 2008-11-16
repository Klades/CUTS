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
