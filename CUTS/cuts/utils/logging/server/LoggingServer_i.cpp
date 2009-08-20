// $Id$

#include "LoggingServer_i.h"

#if !defined (__CUTS_INLINE__)
#include "LoggingServer_i.inl"
#endif

#include "cuts/UUID.h"
#include "boost/bind.hpp"
#include <algorithm>
#include "ace/OS_NS_unistd.h"

//
// register_listener
//
::CUTS::UUID * CUTS_LoggingServer_i::
register_listener (const ::CUTS::UUID & test,
                   ::CUTS::LoggingServerListener_ptr listener)
{
  ACE_WRITE_GUARD_RETURN (ACE_RW_Thread_Mutex,
                          guard,
                          this->busy_mutex_,
                          0);

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
  ACE_WRITE_GUARD (ACE_RW_Thread_Mutex, guard, this->busy_mutex_);

  // Extract the binary version of the UUID's
  ACE_Utils::UUID test_uuid;
  test >>= test_uuid;

  reg_t reg;
  cookie >>= reg.cookie_;

  ACE_DEBUG ((LM_ERROR,
              ACE_TEXT ("%T (%t) - %M - unregistering listener for test %s\n"),
              test_uuid.to_string ()->c_str ()));

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
send_messages (const char * hostname,
               const ::CUTS::UUID & test,
               const ::CUTS::LogMessages & messages)
{
  ACE_READ_GUARD (ACE_RW_Thread_Mutex, guard, this->busy_mutex_);

  try
  {
    ACE_Utils::UUID test_uuid;
    test >>= test_uuid;

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - received %d message(s) for test %s from %s\n"),
                messages.length (),
                test_uuid.to_string ()->c_str (),
                hostname));

    // First, notify the global listeners for the new messages.
    for (ACE_Unbounded_Set <reg_t>::CONST_ITERATOR iter (this->global_listeners_);
         !iter.done ();
         ++ iter)
    {
      (*iter).listener_->handle_messages (hostname, test, messages);
    }

    // Locate listeners registered for extracted UUID.
    listener_map::data_type listeners;

    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - notifying test-specific listeners\n")));

    if (0 == this->listeners_.find (test_uuid, listeners))
    {
      // Now, notify the specific test of the new messages.
      for (ACE_Unbounded_Set <reg_t>::CONST_ITERATOR iter (*listeners);
           !iter.done ();
           ++ iter)
      {
        ACE_ERROR ((LM_ERROR, "hummm...\n"));

        if (!::CORBA::is_nil ((*iter).listener_.in ()))
        {
          (*iter).listener_->handle_messages (hostname, test, messages);
        }
        else
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - listener is NIL\n")));
        }

        ACE_ERROR ((LM_ERROR, "ok...\n"));
      }
    }

    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - leaving send_messages ()\n")));
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception (%N:%l)\n")));
  }
}
