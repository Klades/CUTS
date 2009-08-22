// $Id$

//
// CUTS_Logger_i
//
CUTS_INLINE
CUTS_Logger_i::
CUTS_Logger_i (CUTS_Log_Message_Handler * handler, const ACE_Utils::UUID & uuid)
: handler_ (handler),
  uuid_ (uuid),
  queue_ (50),
  is_empty_ (flush_lock_)
{

}

//
// ~CUTS_Logger_i
//
CUTS_INLINE
CUTS_Logger_i::~CUTS_Logger_i (void)
{
  this->flush ();
}
