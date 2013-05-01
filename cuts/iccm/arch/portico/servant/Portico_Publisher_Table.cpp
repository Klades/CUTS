// $Id$

#include "Portico_Publisher_Table.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_Publisher_Table.inl"
#endif

namespace iCCM
{

//
// fini
//
void Portico_Publisher_Table::fini (void)
{
  if (0 != this->obj_handle_)
  {
    // Delete this object instance. We need to tick () the RTI so it
    // can notify all federates the object instance has been deleted.
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - deleting object instance <%d>\n"),
                this->obj_handle_));

    this->rtiamb_->deleteObjectInstance (this->obj_handle_, 0);
    this->obj_handle_ = 0;

    this->rtiamb_->tick ();
  }

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - reseting publisher table's state\n"),
              this->obj_handle_));

  // Reset the state of this object.
  this->tag_ = ACE_Utils::UUID::NIL_UUID;
  this->rtiamb_ = 0;
}


}
