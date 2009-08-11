// $Id$

#include "LoggingServer_i.h"

#if !defined (__CUTS_INLINE__)
#include "LoggingServer_i.inl"
#endif

#include "cuts/UUID.h"
#include "boost/bind.hpp"
#include <algorithm>

//
// register_listener
//
::CUTS::UUID * CUTS_LoggingServer_i::
register_listener (const ::CUTS::UUID & test,
                   ::CUTS::LoggingServerListener_ptr listener)
{
  // Extract the test UUID.
  ACE_Utils::UUID test_uuid;
  test >>= test_uuid;

  ACE_Unbounded_Set <reg_t> * listeners;

  if (test_uuid == ACE_Utils::UUID::NIL_UUID)
  {
    listeners = &this->global_listeners_;
  }
  else
  {
    // Locate the bucket for the specified test.
    if (0 != this->listeners_.find (test_uuid, listeners))
    {
      // We need to create a new set for this test.
      ACE_NEW_THROW_EX (listeners,
                        ACE_Unbounded_Set <reg_t> (),
                        ::CORBA::NO_MEMORY ());

      this->listeners_.bind (test_uuid, listeners);
    }
  }

  // Create a new registeration structure.
  reg_t reg;
  ACE_Utils::UUID_GENERATOR::instance ()->generate_UUID (reg.cookie_);
  reg.listener_ = ::CUTS::LoggingServerListener::_duplicate (listener);

  // Save the registration.
  listeners->insert (reg);

  // Return the registration cookie.
  ::CUTS::UUID_var cookie;
  ACE_NEW_THROW_EX (cookie, ::CUTS::UUID (), ::CORBA::NO_MEMORY ());

  *cookie <<= reg.cookie_;

  return cookie._retn ();
}

//
// unregister_listener
//
void CUTS_LoggingServer_i::
unregister_listener (const ::CUTS::UUID & test, const ::CUTS::UUID & cookie)
{
  // Extract the binary version of the UUID's
  ACE_Utils::UUID test_uuid;
  test >>= test_uuid;

  reg_t reg;
  cookie >>= reg.cookie_;

  if (test_uuid == ACE_Utils::UUID::NIL_UUID)
  {
    this->global_listeners_.remove (reg);
  }
  else
  {
    // Locate the listerner group for the specified test.
    listener_map::data_type listeners;

    if (0 == this->listeners_.find (test_uuid, listeners))
    {
      if (0 == listeners->remove (reg))
      {
        if (0 == listeners->size ())
        {
          this->listeners_.unbind (test_uuid);
          delete listeners;
        }
      }
    }
  }
}

//
// handle_messages
//
void CUTS_LoggingServer_i::
handle_messages (const ::CUTS::LogMessagePacket & packet)
{
  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - received %d message(s) from %s\n"),
              packet.msgs.length (),
              packet.hostname.in ()));

  // First, notify the global listeners for the new messages.
  for (ACE_Unbounded_Set <reg_t>::CONST_ITERATOR iter (this->global_listeners_);
       !iter.done ();
       ++ iter)
  {
    (*iter).listener_->handle_messages (packet);
  }

  // Locate the test-specific listener bucket.
  std::for_each (packet.msgs.get_buffer (),
                 packet.msgs.get_buffer () + packet.msgs.length (),
                 boost::bind (&CUTS_LoggingServer_i::handle_log_message,
                              this,
                              packet.hostname.in (),
                              _1));
}

//
// handle_log_message
//
void CUTS_LoggingServer_i::
handle_log_message (const char * hostname, const ::CUTS::TestLogMessage & msg)
{
  // Extract the UUID from its CORBA form.
  ACE_Utils::UUID uuid;
  msg.uuid >>= uuid;

  // Locate listeners registered for extracted UUID.
  listener_map::data_type listeners;

  if (0 == this->listeners_.find (uuid, listeners))
  {
    // Now, notify the specific test of the new messages.
    for (ACE_Unbounded_Set <reg_t>::CONST_ITERATOR iter (*listeners);
         !iter.done ();
         ++ iter)
    {
      (*iter).listener_->handle_message (hostname, msg);
    }
  }
}
