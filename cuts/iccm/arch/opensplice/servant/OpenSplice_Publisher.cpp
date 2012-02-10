// $Id$

#include "OpenSplice_Publisher.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher.inl"
#endif

namespace iCCM
{

//
// ~OpenSplice_Publisher
//
OpenSplice_Publisher::~OpenSplice_Publisher (void)
{
  if (::CORBA::is_nil (this->abstract_writer_.in ()))
    return;

  // Destroy the data writer owned by this event producer.
  ::DDS::Publisher_var publisher = this->abstract_writer_->get_publisher ();
  ::DDS::ReturnCode_t retcode = publisher->delete_datawriter (this->abstract_writer_.in ());

  if (retcode != DDS::RETCODE_OK)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to delete data writer\n")));
}

//
// configure
//
void OpenSplice_Publisher::
configure (::DDS::Publisher_ptr publisher,
           const ::DDS::TopicQos & qos,
           ::DDS::Topic_ptr topic)
{
  this->abstract_writer_ =
    publisher->create_datawriter (topic,
                                  DATAWRITER_QOS_DEFAULT,
                                  0,
                                  ::DDS::ANY_STATUS);
}

//
// connect
//
void OpenSplice_Publisher::
connect (::Components::EventConsumerBase_ptr p)
{
  this->consumer_ = ::Components::OpenSplice::EventConsumer::_narrow (p);
}

//
// disconnect
//
::Components::EventConsumerBase_ptr OpenSplice_Publisher::disconnect (void)
{
  return this->consumer_._retn ();
}

}
