// -*- C++ -*-

#ifndef _RTIDDS_HELLOWORLD_COMPONENTSC_H_
#define _RTIDDS_HELLOWORLD_COMPONENTSC_H_

#include "HelloWorld_ComponentsC.h"
#include "cuts/iccm/arch/qpidpb/servant/QpidPB_Traits_T.h"

#include "HelloWorld.pb.h"

#include "HelloWorld_Components_stub_export.h"

class HELLOWORLD_COMPONENTS_STUB_Export MessageEventUpcall :
  public virtual MessageEvent,
  public virtual ::CORBA::DefaultValueRefCountBase
{
  public:
  MessageEventUpcall (qpidpb::Message & pb_event);
  virtual ~MessageEventUpcall (void);

  virtual void content (char *);
  virtual void content (const char *);
  virtual void content (const ::CORBA::String_var &);
  virtual const char * content (void) const;

  virtual void time (const ::CORBA::Long);
  virtual CORBA::Long time (void) const;

  private:
  qpidpb::Message & pb_event_;

  ::CORBA::Boolean _tao_marshal__MessageEvent (TAO_OutputCDR &, TAO_ChunkInfo &) const;
  ::CORBA::Boolean _tao_unmarshal__MessageEvent (TAO_InputCDR &, TAO_ChunkInfo &);
};

class HELLOWORLD_COMPONENTS_STUB_Export MessageEventDowncall :
  public virtual MessageEvent,
  public virtual ::CORBA::DefaultValueRefCountBase
{
  public:
  MessageEventDowncall (void);
  virtual ~MessageEventDowncall (void);

  const qpidpb::Message & protobuf_event (void) const;

  virtual void content (char *);
  virtual void content (const char *);
  virtual void content (const ::CORBA::String_var &);
  virtual const char * content (void) const;

  virtual void time (const ::CORBA::Long);
  virtual CORBA::Long time (void) const;

  private:
  qpidpb::Message pb_event_;

  ::CORBA::Boolean _tao_marshal__MessageEvent (TAO_OutputCDR &, TAO_ChunkInfo &) const;
  ::CORBA::Boolean _tao_unmarshal__MessageEvent (TAO_InputCDR &, TAO_ChunkInfo &);
};

/**
 * @class iCCM::DDS_Traits_T < ::MessageEvent >
 *
 * Trait information for MessageEventEvent event type.
 */
namespace iCCM 
{
  template < >
  class QpidPB_Traits_T < ::MessageEvent >
  {
    public:
    // event mapping types
    typedef ::qpidpb::Message protobuf_event_type;
    typedef ::MessageEventUpcall upcall_event_type;
    typedef ::MessageEventDowncall downcall_event_type;
    typedef ::MessageEvent corba_event_type;
  };
}

#endif  // !defined _RTIDDS_HELLOWORLD_COMPONENTSC_H_
