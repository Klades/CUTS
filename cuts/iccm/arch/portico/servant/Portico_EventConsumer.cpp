// $Id: EventConsumer.cpp

#include "Portico_EventConsumer.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_EventConsumer.inl"
#endif

namespace iCCM
{

//
// observe_object
//
void Portico_EventConsumer::observe_object (const char * tag)
{
  // Get the object instance handle for this tag.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - adding instance <%s> to ")
              ACE_TEXT ("observation list\n"),
              tag));

  RTI::ObjectHandle obj_handle = this->rtiamb_->getObjectInstanceHandle (tag);
  this->handles_.insert (obj_handle);
}

//
// unobserve_object
//
void Portico_EventConsumer::
unobserve_object (const char * tag)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - removing instance <%s> from ")
              ACE_TEXT ("observation list\n"),
              tag));

  RTI::ObjectHandle obj_handle = this->rtiamb_->getObjectInstanceHandle (tag);
  this->handles_.remove (obj_handle);
}

//
// fini
//
void Portico_EventConsumer::fini (void)
{

}

}
