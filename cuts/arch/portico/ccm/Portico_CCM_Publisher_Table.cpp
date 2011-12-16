// Id: CCM_Publisher_Table.cpp.tmpl 3238 2011-12-07 04:12:45Z hillj Portico_Publisher_Table.cpp 3086 2011-01-22 05:53:51Z hillj

#include "Portico_CCM_Publisher_Table.h"

#if !defined (__CUTS_INLINE__)
#include "Portico_CCM_Publisher_Table.inl"
#endif

//
// ~Portico_CCM_Publisher_Table
//
Portico_CCM_Publisher_Table::~Portico_CCM_Publisher_Table (void)
{
}

//
// fini
//
void Portico_CCM_Publisher_Table::fini (void)
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
