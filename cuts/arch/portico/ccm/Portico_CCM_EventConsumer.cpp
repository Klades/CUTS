// Id: CCM_EventConsumer.cpp.tmpl 3238 2011-12-07 04:12:45Z hillj Portico_CCM_EventConsumer.cpp 3030 2010-11-05 03:44:54Z hillj

#include "Portico_CCM_EventConsumer.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_CCM_EventConsumer.inl"
#endif

//
// observe_object
//
void Portico_CCM_EventConsumer::observe_object (const char * tag)
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
void Portico_CCM_EventConsumer::
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
void Portico_CCM_EventConsumer::fini (void)
{

}
