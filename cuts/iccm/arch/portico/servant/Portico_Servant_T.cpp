// $Id$

#if !defined (__CUTS_INLINE__)
#include "Portico_Servant_T.inl"
#endif

#include "boost/bind.hpp"
#include <algorithm>

namespace iCCM
{

//
// install
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
int Portico_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
install (const std::string & fed, const std::string & exec)
{
  try
  {
    if (0 != this->base_type::install (fed, exec))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - base install failed\n")),
                         -1);

    std::for_each (this->emits_.begin (),
                   this->emits_.end (),
                   boost::bind (&Portico_Publisher::init,
                                boost::bind (&emits_map_type::ENTRY::int_id_, _1),
                                &this->rtiamb_));

    std::for_each (this->publishes_.begin (),
                   this->publishes_.end (),
                   boost::bind (&Portico_Publisher_Table::init,
                                 boost::bind (&publishes_map_type::ENTRY::int_id_, _1),
                                 &this->rtiamb_));

    std::for_each (this->consumers_.begin (),
                   this->consumers_.end (),
                   boost::bind (&Portico_EventConsumer::init,
                                boost::bind (&consumer_map_type::ENTRY::int_id_, _1),
                                &this->rtiamb_));

    return 0;
  }
  catch (const RTI::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._reason));
  }

  return -1;
}

//
// remove
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void Portico_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::remove (void)
{
  std::for_each (this->publishes_.begin (),
                 this->publishes_.end (),
                 boost::bind (&Portico_Publisher_Table::fini,
                              boost::bind (&publishes_map_type::ENTRY::int_id_, _1)));

  // Pass control to the base class.
  Portico_Servant::remove ();
}

//
// reflectAttributeValues
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void Portico_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
reflectAttributeValues (RTI::ObjectHandle obj_handle,
                        const RTI::AttributeHandleValuePairSet & attrs,
                        const RTI::FedTime &,
                        const char * tag,
                        RTI::EventRetractionHandle)
                       throw (RTI::ObjectNotKnown,
                              RTI::AttributeNotKnown,
                              RTI::FederateOwnsAttributes,
                              RTI::FederateInternalError)

{
  this->reflectAttributeValues (obj_handle, attrs, tag);
}

//
// reflectAttributeValues
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void Portico_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
reflectAttributeValues (RTI::ObjectHandle obj_handle,
                        const RTI::AttributeHandleValuePairSet & attrs,
                        const char * tag)
                       throw (RTI::ObjectNotKnown,
                              RTI::AttributeNotKnown,
                              RTI::FederateOwnsAttributes,
                              RTI::FederateInternalError)
{
  // Iterate over all the event consumers until we locate one
  // that is the owner of this object handle.
  Portico_EventConsumer * consumer = 0;
  typename consumer_map_type::ITERATOR iter (this->consumers_);

  for (; !iter.done (); ++ iter)
  {
    // If the object belongs to this consumer, then we need to
    // dispatch the event.
    consumer = dynamic_cast <Portico_EventConsumer *> (iter->item ());

    if (consumer->is_observed (obj_handle))
      consumer->dispatch_event (attrs);
  }

  ACE_UNUSED_ARG (tag);
}

}
