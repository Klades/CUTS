// $Id$

#if !defined (__CUTS_INLINE__)
#include "Servant_Manager_T.inl"
#endif

///////////////////////////////////////////////////////////////////////////////
// CUTS_Servant_Manager_T

//
// ~CUTS_Servant_Manager_T
//
template <typename T>
CUTS_Servant_Manager_T <T>::~CUTS_Servant_Manager_T (void)
{
  this->deactivate ();

  if (this->is_managed_ && 0 != this->servant_)
    delete this->servant_;
}

//
// reset
//
template <typename T>
int CUTS_Servant_Manager_T <T>::reset (T * servant, bool managed)
{
  if (!::CORBA::is_nil (this->poa_.in ()))
    return -1;

  if (this->is_managed_ && 0 != this->servant_)
    delete this->servant_;

  this->servant_ = servant;
  this->is_managed_ = managed;
  return 0;
}

//
// activate
//
template <typename T>
void CUTS_Servant_Manager_T <T>::activate (::PortableServer::POA_ptr poa)
{
  ::PortableServer::ObjectId_var oid = poa->activate_object (this->servant_);
  this->poa_ = ::PortableServer::POA::_duplicate (poa);
}

//
// deactivate
//
template <typename T>
void CUTS_Servant_Manager_T <T>::deactivate (void)
{
  if (::CORBA::is_nil (this->poa_.in ()))
    return;

  // Deactivate the object.
  ::PortableServer::ObjectId_var oid = this->poa_->servant_to_id (this->servant_);
  this->poa_->deactivate_object (oid.in ());

  this->poa_ = ::PortableServer::POA::_nil ();
}

//
// get_reference
//
template <typename T>
::CORBA::Object_ptr CUTS_Servant_Manager_T <T>::get_reference (void)
{
  if (!::CORBA::is_nil (this->poa_.in ()))
    return this->poa_->servant_to_reference (this->servant_);

  return ::CORBA::Object::_nil ();
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_Servant_Manager_Ex_T

//
// activate
//
template <typename T, typename TRAITS>
void CUTS_Servant_Manager_Ex_T <T, TRAITS>::activate (::PortableServer::POA_ptr poa)
{
  // Pass control to the base class.
  CUTS_Servant_Manager_T <T>::activate (poa);

  // Notify traits of the activation.
  ::CORBA::Object_var obj = this->poa_->servant_to_reference (this->servant_);
  int retval = this->traits_.handle_activate (obj.in ());

  if (0 != retval)
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - %d traits failed at activation\n"),
                retval));
}

//
// deactivate
//
template <typename T, typename TRAITS>
void CUTS_Servant_Manager_Ex_T <T, TRAITS>::deactivate (void)
{
  if (::CORBA::is_nil (this->poa_.in ()))
    return;

  // Notify traits of the deactivation.
  ::CORBA::Object_var obj = this->poa_->servant_to_reference (this->servant_);
  int retval = this->traits_.handle_deactivate (obj.in ());

  if (0 != retval)
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("%T (%t) - %M - %d traits failed at deactivation\n"),
                retval));


  // Pass control to the base class.
  CUTS_Servant_Manager_T <T>::deactivate ();
}
