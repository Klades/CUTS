// $Id$

#include "OpenSplice_EventConsumer.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_EventConsumer.inl"
#endif

namespace iCCM
{

//
// ~OpenSplice_EventConsumer
//
OpenSplice_EventConsumer::~OpenSplice_EventConsumer (void)
{
  if (::CORBA::is_nil (this->abstract_reader_.in ()))
    return;

  // Destroy the data writer owned by this event producer.
  ::DDS::Subscriber_var subscriber = this->abstract_reader_->get_subscriber ();
  ::DDS::ReturnCode_t retcode = subscriber->delete_datareader (this->abstract_reader_.in ());

  if (retcode != DDS::RETCODE_OK)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to delete data reader\n")));
}

}
