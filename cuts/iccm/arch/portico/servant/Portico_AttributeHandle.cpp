// $Id$

#include "Portico_AttributeHandle.h"
#include "ace/Log_Msg.h"

namespace iCCM
{

//
// Portico_AttributeHandle
//
Portico_AttributeHandle::
Portico_AttributeHandle (RTI::AttributeHandle handle)
: handle_ (handle)
{

}

//
// Portico_AttributeHandle
//
Portico_AttributeHandle::~Portico_AttributeHandle (void)
{

}

//
// handle
//
RTI::AttributeHandle Portico_AttributeHandle::handle (void)
{
  return this->handle_;
}

//
// operator RTI::AttributeHandle ()
//
Portico_AttributeHandle::operator RTI::AttributeHandle ()
{
  return this->handle_;
}

//
// Portico_AttributeHandle_T
//
Portico_AttributeHandle_T <ACE_CString>::
Portico_AttributeHandle_T (RTI::AttributeHandle handle)
: Portico_AttributeHandle (handle)
{

}

//
// ~Portico_AttributeHandle_T
//
Portico_AttributeHandle_T <ACE_CString>::~Portico_AttributeHandle_T (void)
{

}

//
// read
//
void Portico_AttributeHandle_T <ACE_CString>::
read (const RTI::AttributeHandleValuePairSet & attrs, RTI::ULong i)
{
  ACE_UNUSED_ARG (attrs);
  ACE_UNUSED_ARG (i);
}

//
// write
//
void Portico_AttributeHandle_T <ACE_CString>::
write (RTI::AttributeHandleValuePairSet & attrs) const
{
  attrs.add (this->handle_,
             this->value_.rep (),
             this->value_.length () + 1);
}

//
// value
//
void Portico_AttributeHandle_T <ACE_CString>::value (const ACE_CString & val)
{
  this->value_ = val;
}

//
// value
//
const ACE_CString & Portico_AttributeHandle_T <ACE_CString>::value (void) const
{
  return this->value_;
}

}
