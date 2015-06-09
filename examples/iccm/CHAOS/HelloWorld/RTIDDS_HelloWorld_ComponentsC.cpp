// $Id$

#include "RTIDDS_HelloWorld_ComponentsC.h"

MessageEventUpcall::MessageEventUpcall (Message & dds_event)
: dds_event_ (dds_event)
{
}

MessageEventUpcall::~MessageEventUpcall (void)
{
}

void MessageEventUpcall::content (char * val)
{
  this->dds_event_.content = val;
}

void MessageEventUpcall::content (const char * val)
{
  this->dds_event_.content = CORBA::string_dup (val);
}

void MessageEventUpcall::content (const ::CORBA::String_var & val)
{
  ::CORBA::String_var dup = val;
  this->dds_event_.content = dup._retn ();
}

const char * MessageEventUpcall::content (void) const 
{
  return this->dds_event_.content.in ();
}

void MessageEventUpcall::time (const ::CORBA::Long val)
{
  this->dds_event_.time = val;
}

CORBA::Long MessageEventUpcall::time (void) const
{
  return this->dds_event_.time;
}

::CORBA::Boolean MessageEventUpcall::_tao_marshal__MessageEvent (TAO_OutputCDR &, TAO_ChunkInfo &) const
{
  return false;
}

::CORBA::Boolean MessageEventUpcall::_tao_unmarshal__MessageEvent (TAO_InputCDR &, TAO_ChunkInfo &)
{
  return false;
}

MessageEventDowncall::MessageEventDowncall (void)
{
}

MessageEventDowncall::~MessageEventDowncall (void)
{
}

const Message & MessageEventDowncall::dds_event (void) const
{
  return this->dds_event_;
}

void MessageEventDowncall::content (char * val)
{
  this->dds_event_.content = val;
}

void MessageEventDowncall::content (const char * val)
{
  this->dds_event_.content = CORBA::string_dup (val);
}

void MessageEventDowncall::content (const ::CORBA::String_var & val)
{
  ::CORBA::String_var dup = val;
  this->dds_event_.content = dup._retn ();
}

const char * MessageEventDowncall::content (void) const 
{
  return this->dds_event_.content.in ();
}

void MessageEventDowncall::time (const ::CORBA::Long val)
{
  this->dds_event_.time = val;
}

CORBA::Long MessageEventDowncall::time (void) const
{
  return this->dds_event_.time;
}

::CORBA::Boolean MessageEventDowncall::_tao_marshal__MessageEvent (TAO_OutputCDR &, TAO_ChunkInfo &) const
{
  return false;
}

::CORBA::Boolean MessageEventDowncall::_tao_unmarshal__MessageEvent (TAO_InputCDR &, TAO_ChunkInfo &)
{
  return false;
}

