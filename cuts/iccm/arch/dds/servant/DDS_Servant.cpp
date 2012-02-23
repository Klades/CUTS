// $Id$

#if !defined (__CUTS_INLINE__)
#include "DDS_Servant.inl"
#endif

namespace iCCM
{

//
// DDS_Servant
//
template <typename T>
DDS_Servant <T>::DDS_Servant (const char * name)
: Servant (name)
{
  // Create the participant for this servant.
  typedef typename T::domainparticipantfactory_var_type domainparticipantfactory_var_type;
  domainparticipantfactory_var_type factory = T::get_domainparticipantfactory_instance ();

  this->participant_ =
    factory->create_participant (0,
                                 T::domainparticipant_qos_default (),
                                 0,
                                 T::ANY_STATUS);
}


//
// do_default_configure
//
template <typename T>
void DDS_Servant <T>::do_default_configure (void)
{
  this->subscriber_ =
    this->participant_->create_subscriber (T::subscriber_qos_default (),
                                           0,
                                           T::ANY_STATUS);

  this->publisher_ =
    this->participant_->create_publisher (T::publisher_qos_default (),
                                          0,
                                          T::ANY_STATUS);
}


}
