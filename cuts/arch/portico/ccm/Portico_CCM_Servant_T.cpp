// $Id$

#if !defined (__CUTS_INLINE__)
#include "Portico_CCM_Servant_T.inl"
#endif

#include "boost/spirit/include/phoenix.hpp"
#include "boost/spirit/home/phoenix/object/dynamic_cast.hpp"
#include <algorithm>

//
// Portico_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CUTS_INLINE
Portico_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
Portico_CCM_Servant_T (T * _this,
                       const char * name,
                       ::PortableServer::POA_ptr poa,
                       typename EXECUTOR::_ptr_type executor)
: base_type (_this, name, poa, executor)
{

}

//
// Portico_CCM_Servant_T
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
int Portico_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
install (const std::string & fed, const std::string & exec)
{
  try
  {
    if (0 != this->base_type::install (fed, exec))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - base install failed\n")),
                         -1);

    namespace phoenix = boost::phoenix;
    using phoenix::arg_names::arg1;

    std::for_each (this->emits_.begin (),
                   this->emits_.end (),
                   phoenix::bind (&Portico_CCM_Publisher::init,
                                  phoenix::dynamic_cast_ <Portico_CCM_Publisher *> (phoenix::bind (&emits_map_type::ENTRY::item, arg1)),
                                  &this->rtiamb_));

    std::for_each (this->publishes_.begin (),
                   this->publishes_.end (),
                   phoenix::bind (&Portico_CCM_Publisher_Table::init,
                                  phoenix::dynamic_cast_ <Portico_CCM_Publisher_Table *> (phoenix::bind (&publishes_map_type::ENTRY::item, arg1)),
                                  &this->rtiamb_));

    std::for_each (this->consumers_.begin (),
                   this->consumers_.end (),
                   phoenix::bind (&Portico_CCM_EventConsumer::init,
                                  phoenix::dynamic_cast_ <Portico_CCM_EventConsumer *> (phoenix::bind (&consumer_map_type::ENTRY::item, arg1)),
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
void Portico_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::remove (void)
{
  namespace phoenix = boost::phoenix;
  using phoenix::arg_names::arg1;

  std::for_each (this->publishes_.begin (),
                 this->publishes_.end (),
                 phoenix::bind (&Portico_CCM_Publisher_Table::fini,
                                phoenix::dynamic_cast_ <Portico_CCM_Publisher_Table *> (phoenix::bind (&publishes_map_type::ENTRY::item, arg1))));

  // Pass control to the base class.
  Portico_CCM_Servant::remove ();
}

//
// reflectAttributeValues
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void Portico_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
reflectAttributeValues (RTI::ObjectHandle obj_handle,
                        const RTI::AttributeHandleValuePairSet & attrs,
                        const RTI::FedTime &,
                        const char * tag,
                        RTI::EventRetractionHandle)
{
  this->reflectAttributeValues (obj_handle, attrs, tag);
}

//
// reflectAttributeValues
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void Portico_CCM_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
reflectAttributeValues (RTI::ObjectHandle obj_handle,
                        const RTI::AttributeHandleValuePairSet & attrs,
                        const char * tag)
{
  // Iterate over all the event consumers until we locate one
  // that is the owner of this object handle.
  Portico_CCM_EventConsumer * consumer = 0;
  consumer_map_type::ITERATOR iter (this->consumers_);

  for (; !iter.done (); ++ iter)
  {
    // If the object belongs to this consumer, then we need to
    // dispatch the event.
    consumer = dynamic_cast <Portico_CCM_EventConsumer *> (iter->item ());

    if (consumer->is_observed (obj_handle))
      consumer->dispatch_event (attrs);
  }
}
