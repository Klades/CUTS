// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_Windows_Registry_Key

//
// CUTS_Windows_Registry_Key
//
CUTS_INLINE
CUTS_Windows_Registry_Key::CUTS_Windows_Registry_Key (void)
: key_ (0),
  requires_close_ (false)
{

}

//
// CUTS_Windows_Registry_Key
//
CUTS_INLINE
CUTS_Windows_Registry_Key::
CUTS_Windows_Registry_Key (HKEY key, const char * subkey)
: key_ (0),
  requires_close_ (false)
{
  this->open (key, subkey);
}

//
// CUTS_Windows_Registry_Key
//
CUTS_INLINE
int CUTS_Windows_Registry_Key::
open (const CUTS_Windows_Registry_Key & key, const char * subkey)
{
  return this->open (key.key_, subkey);
}

//
// ~CUTS_Windows_Registry_Key
//
CUTS_INLINE
CUTS_Windows_Registry_Key::~CUTS_Windows_Registry_Key (void)
{
  this->close ();
}

//
// is_valid
//
CUTS_INLINE
bool CUTS_Windows_Registry_Key::is_valid (void) const
{
  return 0 != this->key_;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_Windows_Registry_Key_Iterator

//
// ~CUTS_Windows_Registry_Key_Iterator
//
CUTS_INLINE
CUTS_Windows_Registry_Key_Iterator::~CUTS_Windows_Registry_Key_Iterator (void)
{

}

//
// ~CUTS_Windows_Registry_Key_Iterator
//
CUTS_INLINE
const char * CUTS_Windows_Registry_Key_Iterator::name (void) const
{
  return this->buffer_.get ();
}

//
// done
//
CUTS_INLINE
bool CUTS_Windows_Registry_Key_Iterator::done (void) const
{
  return this->index_ >= this->count_;
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_Windows_Registry_Value_Iterator

//
// CUTS_Windows_Registry_Value_Iterator
//
CUTS_INLINE
CUTS_Windows_Registry_Value_Iterator::
CUTS_Windows_Registry_Value_Iterator (const CUTS_Windows_Registry_Key & key,
                                      u_char * buffer,
                                      u_long bufsize)
: key_ (key),
  is_done_ (false),
  index_ (0),
  buffer_ (buffer),
  bufsize_ (bufsize),
  datasize_ (bufsize_)
{
  this->advance ();
}

//
// ~CUTS_Windows_Registry_Value_Iterator
//
CUTS_INLINE
CUTS_Windows_Registry_Value_Iterator::
~CUTS_Windows_Registry_Value_Iterator (void)
{

}

//
// advance
//
CUTS_INLINE
int CUTS_Windows_Registry_Value_Iterator::advance (void)
{
  return this->advance (this->buffer_, this->datasize_);
}

//
// done
//
CUTS_INLINE
bool CUTS_Windows_Registry_Value_Iterator::done (void)
{
  return this->is_done_;
}
