// $Id$

#include "OpenSplice_Publisher_Table.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Publisher_Table.inl"
#endif

namespace iCCM
{

//
// ~OpenSplice_Publisher_Table
//
OpenSplice_Publisher_Table::~OpenSplice_Publisher_Table (void)
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
void OpenSplice_Publisher_Table::
configure (::DDS::Publisher_ptr publisher, ::DDS::Topic_ptr topic)
{
  this->abstract_writer_ =
    publisher->create_datawriter (topic,
                                  DATAWRITER_QOS_DEFAULT,
                                  0,
                                  ::DDS::ANY_STATUS);
}

}
