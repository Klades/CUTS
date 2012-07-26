// $Id$

#include "Logger_i.h"

#if !defined (__CUTS_INLINE__)
#include "Logger_i.inl"
#endif

#include "Log_Message_Handler.h"
#include "cuts/UUID.h"
#include "ace/Trace.h"

//
// log
//
void CUTS_Logger_i::log (const ::CUTS::LogMessage & logmsg)
{
  ::CUTS::LogMessage * message = 0;

  do
  {
    ACE_GUARD (ACE_Thread_Mutex, guard, this->flush_lock_);

    if (this->queue_.is_full ())
      this->is_empty_.wait ();

    // Get the next free record in the queue.
    message = this->queue_.next_free_record ();
  } while (0);

  // Copy the contents of the message.
  message->severity       = logmsg.severity;
  message->thread_id       = logmsg.thread_id;
  message->timestamp.sec  = logmsg.timestamp.sec;
  message->timestamp.usec = logmsg.timestamp.usec;

  ::CORBA::ULong msglen = logmsg.message.length ();
  message->message.length (msglen);

  ACE_OS::memcpy (message->message.get_buffer (),
                  logmsg.message.get_buffer (),
                  logmsg.message.length ());

  if (this->queue_.is_full ())
  {
    // Perform double-check locking on the queue to ensure that only
    // one thread is able to flush the contents of the queue. If the
    // queue has already been flushed, then we can just continue on
    // about our business.
    ACE_GUARD (ACE_Thread_Mutex, guard, this->flush_lock_);

    if (this->queue_.is_full ())
      this->flush ();
  }
}

//
// flush
//
void CUTS_Logger_i::flush (void)
{
  if (!ACE_Trace::is_tracing ())
    ACE_Trace::start_tracing ();

  ACE_Trace t ("CUTS_Logger_i::flush", __LINE__, __FILE__);

  // Package the messages.
  ::CORBA::ULong used_size = this->queue_.used_size ();

  if (used_size == 0)
    return;

  ::CUTS::LogMessages messages (used_size,
                                used_size,
                                this->queue_.get_buffer (),
                                false);

  // Send the messages to the server.
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - sending %d message(s) to the server\n"),
              used_size));

  this->handler_->handle_log_messages (this->uuid_, messages);

  // Reset the contents of the queue.
  this->queue_.reset_no_lock ();
  this->is_empty_.broadcast ();
}

//
// uuid
//
::CUTS::UUID * CUTS_Logger_i::uuid (void)
{
  // Allocate a new UUID to return to the client.
  ::CUTS::UUID_var uuid;

  ACE_NEW_THROW_EX (uuid,
                    ::CUTS::UUID (),
                    ::CORBA::NO_MEMORY ());

  uuid <<= this->uuid_;
  return uuid._retn ();
}