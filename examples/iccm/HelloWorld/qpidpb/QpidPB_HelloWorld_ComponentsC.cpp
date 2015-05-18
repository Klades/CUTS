// $Id$

#include "QpidPB_HelloWorld_ComponentsC.h"

MessageEventUpcall::MessageEventUpcall (qpidpb::Message & pb_event)
: pb_event_ (pb_event)
{
}

MessageEventUpcall::~MessageEventUpcall (void)
{
}

void MessageEventUpcall::content (char * val)
{
  this->pb_event_.set_content (val);
}

void MessageEventUpcall::content (const char * val)
{
  this->pb_event_.set_content (CORBA::string_dup (val));
}

void MessageEventUpcall::content (const ::CORBA::String_var & val)
{
  ::CORBA::String_var dup = val;
  this->pb_event_.set_content (dup._retn ());
}

const char * MessageEventUpcall::content (void) const 
{
  return this->pb_event_.content ().c_str ();
}

void MessageEventUpcall::time (const ::CORBA::Long val)
{
  this->pb_event_.set_time (val);
}

CORBA::Long MessageEventUpcall::time (void) const
{
  return this->pb_event_.time ();
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

const qpidpb::Message & MessageEventDowncall::protobuf_event (void) const
{
  return this->pb_event_;
}

void MessageEventDowncall::content (char * val)
{
  this->pb_event_.set_content (val);
}

void MessageEventDowncall::content (const char * val)
{
  this->pb_event_.set_content (CORBA::string_dup (val));
}

void MessageEventDowncall::content (const ::CORBA::String_var & val)
{
  ::CORBA::String_var dup = val;
  this->pb_event_.set_content (dup._retn ());
}

const char * MessageEventDowncall::content (void) const 
{
  return this->pb_event_.content ().c_str ();
}

void MessageEventDowncall::time (const ::CORBA::Long val)
{
  this->pb_event_.set_time (val);
}

CORBA::Long MessageEventDowncall::time (void) const
{
  return this->pb_event_.time ();
}

::CORBA::Boolean MessageEventDowncall::_tao_marshal__MessageEvent (TAO_OutputCDR &, TAO_ChunkInfo &) const
{
  return false;
}

::CORBA::Boolean MessageEventDowncall::_tao_unmarshal__MessageEvent (TAO_InputCDR &, TAO_ChunkInfo &)
{
  return false;
}

