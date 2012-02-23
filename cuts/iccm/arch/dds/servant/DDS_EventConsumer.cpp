// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_EventConsumer.inl"
#endif

namespace iCCM
{

//
// ~DDS_EventConsumer
//
template <typename T>
DDS_EventConsumer <T>::~DDS_EventConsumer (void)
{
  if (!T::_is_nil (this->abs_reader_))
  {
    // Destroy the data writer owned by this event producer.
    typedef typename T::subscriber_var_type subscriber_var_type;
    typedef typename T::returncode_type returncode_type;

    subscriber_var_type subscriber = this->abs_reader_->get_subscriber ();
    returncode_type retcode = subscriber->delete_datareader (this->abs_reader_);

    if (0 != retcode)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to delete data reader\n")));
  }
}

}
