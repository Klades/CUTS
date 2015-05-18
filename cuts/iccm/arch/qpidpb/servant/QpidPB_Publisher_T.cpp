// $IdQpidPB_Publisher_T.cpp 3086 2011-01-22 05:53:51Z hillj $

#if !defined (__CUTS_INLINE__)
#include "QpidPB_Publisher_T.inl"
#endif

namespace iCCM
{

//
// connect
//
template <typename EVENT>
void QpidPB_Publisher_T <EVENT>::
connect (::Components::EventConsumerBase_ptr p)
{
  // Pass control the base class.
  QpidPB_Publisher::connect (p);
}

//
// activate
//
template <typename EVENT>
void QpidPB_Publisher_T <EVENT>::activate (void)
{
  QpidPB_Publisher::activate ();
  this->sender_.activate (this->connection_, this->queue_);
}

//
// passivate
//
template <typename EVENT>
void QpidPB_Publisher_T <EVENT>::passivate (void)
{
  this->sender_.passivate ();
  QpidPB_Publisher::passivate ();
}


//
// allocate_event
//
template <typename EVENT>
EVENT * QpidPB_Publisher_T <EVENT>::allocate_event (void)
{
  return this->sender_.allocate_event ();
}

//
// send_event
//
template <typename EVENT>
void QpidPB_Publisher_T <EVENT>::send_event (EVENT * ev)
{
  this->sender_.send_event (ev);
}

}
