// $Id$

#include "HelloWorld_ObjectClass.h"

//
// Message_ObjectClass
//
Message_ObjectClass::
Message_ObjectClass (RTI::ObjectClassHandle type,
                     RTI::AttributeHandle content_handle,
                     RTI::AttributeHandle time_handle)
: Portico_ObjectClass (type),
  content_ (content_handle),
  time_ (time_handle)
{

}

//
// ~Message_ObjectClass
//
Message_ObjectClass::~Message_ObjectClass (void)
{

}

//
// content
//
void Message_ObjectClass::content (char * val)
{
  this->content_.value (val);
}

//
// content
//
void Message_ObjectClass::content (const char * val)
{
  this->content_.value (val);
}

//
// content
//
void Message_ObjectClass::content (const ::CORBA::String_var & val)
{
  this->content_.value (val.in ());
}

//
// content
//
const char * Message_ObjectClass::content (void) const
{
  return this->content_.value ().c_str ();
}

//
// time
//
void Message_ObjectClass::time (const ::CORBA::Long t)
{
  this->time_.value (t);
}

//
// time
//
::CORBA::Long Message_ObjectClass::time (void) const
{
  return this->time_.value ();
}

//
// __hla_read_attributes
//
void Message_ObjectClass::
__hla_read_attributes (const RTI::AttributeHandleValuePairSet & attrs)
{
  const RTI::ULong attr_length = attrs.size ();

  for (RTI::ULong i = 0; i < attr_length; ++ i)
  {
    RTI::Handle handle = attrs.getHandle (i);

    if (handle == this->content_)
      this->content_.read (attrs, i);
    else if (handle == this->time_)
      this->time_.read (attrs, i);
  }
}

//
// __hla_write_attributes
//
void Message_ObjectClass::
__hla_write_attributes (RTI::AttributeHandleValuePairSet & attrs) const
{
  this->content_.write (attrs);
  this->time_.write (attrs);
}

//
// Message_ObjectClass_Factory
//
Message_ObjectClass_Factory::
Message_ObjectClass_Factory (RTI::RTIambassador * rtiamb)
: Portico_ObjectClass_Factory (rtiamb->getObjectClassHandle ("ObjectRoot.Message")),
  content_handle_ (rtiamb->getAttributeHandle ("content", handle_)),
  time_handle_ (rtiamb->getAttributeHandle ("time", handle_))
{

}

//
// ~Message_ObjectClass_Factory
//
Message_ObjectClass_Factory::~Message_ObjectClass_Factory (void)
{

}

//
// create
//
Message_ObjectClass * Message_ObjectClass_Factory::create (void)
{
  return new Message_ObjectClass (this->handle_,
                                  this->content_handle_,
                                  this->time_handle_);
}

//
// get_attributes
//
void Message_ObjectClass_Factory::
get_attributes (RTI::AttributeHandleSet & attrs) const
{
  attrs.add (this->content_handle_);
  attrs.add (this->time_handle_);
}
