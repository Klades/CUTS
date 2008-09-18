// -*- C++ -*-
// $Id$

//
// CUTS_Port_Agent
//
CUTS_INLINE
CUTS_Port_Agent::CUTS_Port_Agent (void)
: name_ ("unknown"),
  active_ (false),
  log_ (CUTS_DEFAULT_LOG_SIZE)
{
  CUTS_TRACE ("CUTS_Port_Agent::CUTS_Port_Agent");
}

//
// ~CUTS_Port_Agent
//
CUTS_INLINE
CUTS_Port_Agent::~CUTS_Port_Agent (void)
{
  CUTS_TRACE ("CUTS_Port_Agent::~CUTS_Port_Agent");

  this->deactivate ();
}

//
// name
//
CUTS_INLINE
const ACE_CString & CUTS_Port_Agent::name (void) const
{
  CUTS_TRACE ("CUTS_Port_Agent::name");

  return this->name_;
}

//
// name
//
CUTS_INLINE
void CUTS_Port_Agent::name (const ACE_CString & name)
{
  CUTS_TRACE ("CUTS_Port_Agent::name (const ACE_CString &)");

  this->name_ = name;
}

//
// activate
//
CUTS_INLINE
void CUTS_Port_Agent::activate (void)
{
  CUTS_TRACE ("CUTS_Port_Agent::activate");

  this->active_ = true;
}

//
// deactivate
//
CUTS_INLINE
void CUTS_Port_Agent::deactivate (void)
{
  CUTS_TRACE ("CUTS_Port_Agent::deactivate");

  this->active_ = false;
}

//
// is_active
//
CUTS_INLINE
bool CUTS_Port_Agent::is_active (void) const
{
  CUTS_TRACE ("CUTS_Port_Agent::is_active");

  return this->active_;
}

//
// log
//
CUTS_INLINE
const CUTS_Activation_Record_Log & CUTS_Port_Agent::log (void) const
{
  CUTS_TRACE ("CUTS_Port_Agent::log (void) const");

  return this->log_;
}

//
// log
//
CUTS_INLINE
CUTS_Activation_Record_Log & CUTS_Port_Agent::log (void)
{
  CUTS_TRACE ("CUTS_Port_Agent::log (void)");

  return this->log_;
}

//
// record_alloc
//
CUTS_INLINE
CUTS_Activation_Record * CUTS_Port_Agent::record_alloc (void)
{
  CUTS_TRACE ("CUTS_Port_Agent::record_alloc");

  return this->log_.next_free_record ();
}

//
// record_free
//
CUTS_INLINE
void CUTS_Port_Agent::record_free (CUTS_Activation_Record * record)
{
  CUTS_TRACE ("CUTS_Port_Agent::record_free");
}

//
// reset
//
CUTS_INLINE
void CUTS_Port_Agent::reset (void)
{
  CUTS_TRACE ("CUTS_Port_Agent::reset");

  this->log_.reset ();
}

