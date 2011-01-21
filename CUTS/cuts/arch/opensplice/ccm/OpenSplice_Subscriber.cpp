// $Id$

#include "OpenSplice_Subscriber.h"

//
// CUTS_OpenSplice_CCM_Subscriber
//
CUTS_OpenSplice_CCM_Subscriber::CUTS_OpenSplice_CCM_Subscriber (void)
{

}

//
// ~CUTS_OpenSplice_CCM_Subscriber
//
CUTS_OpenSplice_CCM_Subscriber::~CUTS_OpenSplice_CCM_Subscriber (void)
{
  this->disconnect ();
}

//
// configure
//
void CUTS_OpenSplice_CCM_Subscriber::
configure (::DDS::Publisher_ptr publisher)
{
  this->publisher_ = ::DDS::Publisher::_duplicate (publisher);
}

//
// connect
//
void CUTS_OpenSplice_CCM_Subscriber::
connect (::Components::EventConsumerBase_ptr p)
{
  // The last part is to create a data reader.
  ::DDS::Topic_var topic = this->endpoint_.topic ();

  this->abstract_writer_ =
      this->publisher_->create_datawriter (topic.in (),
                                           DATAWRITER_QOS_DEFAULT,
                                           0,
                                          ::DDS::ANY_STATUS);

  this->consumer_ = ::Components::OpenSplice::EventConsumer::_narrow (p);
}

//
// disconnect
//
::Components::EventConsumerBase_ptr
CUTS_OpenSplice_CCM_Subscriber::disconnect (void)
{
  // Delete the data write for this subscriber.
  DDS::ReturnCode_t retcode;

  if (!::CORBA::is_nil (this->abstract_writer_.in ()))
  {
    retcode = this->publisher_->delete_datawriter (this->abstract_writer_.in ());

    if (retcode == DDS::RETCODE_OK)
      this->abstract_writer_ = ::DDS::DataWriter::_nil ();
    else
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to delete data writer\n")));
  }

  if (!::CORBA::is_nil (this->publisher_.in ()))
    this->publisher_ = ::DDS::Publisher::_nil ();

  if (this->endpoint_.is_open ())
  {
    // First, make sure we close the endpoint.
    if (0 != this->endpoint_.close ())
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to close subscriber endpoint\n")));
  }

  return this->consumer_._retn ();
}

