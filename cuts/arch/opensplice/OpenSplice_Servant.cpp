// $Id$

#include "OpenSplice_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "OpenSplice_Servant.inl"
#endif

#include "ace/CORBA_macros.h"

//
// remove
//
::DDS::DomainParticipant_ptr CUTS_OpenSplice_Servant::remove_participant (void)
{
  // There is no need to continue if we do not have a participant defined
  // for this servant.
  if (::CORBA::is_nil (this->participant_.in ()))
    return this->participant_._retn ();

  if (!::CORBA::is_nil (this->subscriber_.in ()))
  {
    // Delete the subscriber.
    ::DDS::ReturnCode_t retcode =
      this->participant_->delete_subscriber (this->subscriber_.in ());

    if (retcode == ::DDS::RETCODE_OK)
      this->subscriber_ = ::DDS::Subscriber::_nil ();
    else
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to delete subscriber (retcode=%d)\n"),
                  retcode));
  }

  if (!::CORBA::is_nil (this->publisher_.in ()))
  {
    // Delete the subscriber.
    ::DDS::ReturnCode_t retcode =
      this->participant_->delete_publisher (this->publisher_.in ());

    if (retcode == ::DDS::RETCODE_OK)
      this->publisher_ = ::DDS::Publisher::_nil ();
    else
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to delete subscriber (retcode=%d)\n"),
                  retcode));
  }

  return this->participant_._retn ();
}

