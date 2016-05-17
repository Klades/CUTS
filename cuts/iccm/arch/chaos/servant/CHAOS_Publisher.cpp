// $IdCHAOS_Publisher.cpp 3086 2011-01-22 05:53:51Z hillj $

#include "CHAOS_Publisher.h"

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Publisher.inl"
#endif

namespace iCCM
{

void
CHAOS_Publisher::connect (::Components::EventConsumerBase_ptr consumer)
{
  if (this->impl_ == 0)
    return;

  ::Components::CHAOS::EventConsumer_var ec =
    ::Components::CHAOS::EventConsumer::_narrow (consumer);

  if (CORBA::is_nil (ec.in ()))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unexpected consumer type\n")));

    throw ::Components::InvalidConnection ();
  }

  // Get the underlying consumer so we can make the connection.
  ::Components::EventConsumerBase_var target = ec->get_consumer ();
  this->impl_->connect (target.in ());
}

}
