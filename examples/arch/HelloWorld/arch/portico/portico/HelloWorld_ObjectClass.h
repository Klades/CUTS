// -*- C++ -*-

#ifndef _PORTICO_HELLOWORLD_OBJECTCLASS_H_
#define _PORTICO_HELLOWORLD_OBJECTCLASS_H_

#include "cuts/arch/portico/ccm/Portico_AttributeHandle.h"
#include "cuts/arch/portico/ccm/Portico_ObjectClass.h"
#include "cuts/arch/portico/ccm/Portico_ObjectClass_Factory.h"

#include "RTI.hh"
#include <vector>

#include "HelloWorldC.h"

/**
 * @class Message_ObjectClass
 *
 * The ObjectClass implementation for the ::Message event.
 */
class HELLOWORLD_STUB_Export Message_ObjectClass :
  public Portico_ObjectClass,
  public virtual Message,
  public virtual ::CORBA::DefaultValueRefCountBase
{
public:
  Message_ObjectClass (RTI::ObjectClassHandle handle,
                       RTI::AttributeHandle content_handle,
                       RTI::AttributeHandle time_handle);

  virtual ~Message_ObjectClass (void);

  virtual void content (char * val);
  virtual void content (const char * val);
  virtual void content (const ::CORBA::String_var & val);
  virtual const char *content (void) const;

  virtual void time (const CORBA::Long t);
  virtual ::CORBA::Long time (void) const;

  virtual void __hla_read_attributes (const RTI::AttributeHandleValuePairSet & attrs);
  virtual void __hla_write_attributes (RTI::AttributeHandleValuePairSet & attrs) const;

private:
  Portico_AttributeHandle_T <ACE_CString> content_;

  Portico_AttributeHandle_T <unsigned long> time_;

  CORBA::Boolean _tao_marshal__Message (TAO_OutputCDR &, TAO_ChunkInfo &) const { return false; }
  CORBA::Boolean _tao_unmarshal__Message (TAO_InputCDR &, TAO_ChunkInfo &) { return false; }
};

/**
 * @class Message_ObjectClass_Factory
 *
 * The ObjectClass implementation for the ::Message event.
 */
class HELLOWORLD_STUB_Export Message_ObjectClass_Factory :
  public Portico_ObjectClass_Factory
{
public:
  Message_ObjectClass_Factory (RTI::RTIambassador * rtiamb);
  virtual ~Message_ObjectClass_Factory (void);

  /// Create a new Message_ObjectClass object.
  virtual Message_ObjectClass * create (void);

  virtual void get_attributes (RTI::AttributeHandleSet & handles) const;

private:
  RTI::AttributeHandle content_handle_;

  RTI::AttributeHandle time_handle_;
};

/**
 * @struct Portico_ObjectClass_Trait_T < ::Message >
 *
 * Trait class specialized for the ::Message event type.
 */
template < >
struct Portico_ObjectClass_Trait_T < ::Message >
{
  static const size_t attr_count = 2;

  typedef Message_ObjectClass objectclass_event_type;

  typedef Message_ObjectClass_Factory objectclass_factory_type;
};

#endif  // !defined _PORTICO_HELLOWORLD_OBJECTCLASS_H_
