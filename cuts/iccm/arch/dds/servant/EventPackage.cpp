#include "DDS_Event_Listener_T.h"

template <typename EVENT_TRAITS, typename INFO, typename READER>
EventPackage<EVENT_TRAITS, INFO, READER>::EventPackage (event_seq * event, INFO * info, READER * reader)
  : event_(event)
  , info_(info)
  , reader_(reader)
{
}

template <typename EVENT_TRAITS, typename INFO, typename READER>
EventPackage<EVENT_TRAITS, INFO, READER>::~EventPackage (void)
{
#ifdef ICCM_DDS_USES_POINTERS
  reader_->return_loan(&event_, &info_);
#else
  reader_->return_loan(event_, info_);
#endif

  delete event_;
  delete info_;
  // Need to delete pointers?
}

template <typename EVENT_TRAITS, typename INFO, typename READER>
event_seq * EventPackage<EVENT_TRAITS, INFO, READER>::get (void) 
{
  return event_;
}
