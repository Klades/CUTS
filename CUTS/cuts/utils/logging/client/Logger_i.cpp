// $Id$

#include "Logger_i.h"

#if !defined (__CUTS_INLINE__)
#include "Logger_i.inl"
#endif

#include "Log_Message_Handler.h"

//
// log
//
void CUTS_Logger_i::log (const ::CUTS::LogMessage & logmsg)
{
  if (this->queue_.is_full ())
  {
    // Perform double-check locking on the queue to ensure that only
    // one thread is able to flush the contents of the queue. If the
    // queue has already been flushed, then we can just continue on
    // about our business.
    ACE_WRITE_GUARD (ACE_RW_Thread_Mutex, guard, this->flush_lock_);

    if (this->queue_.is_full ())
      this->flush ();
  }

  // Get the next free record in the queue.
  ACE_READ_GUARD (ACE_RW_Thread_Mutex, guard, this->flush_lock_);
  ::CUTS::LogMessage * message = this->queue_.next_free_record ();

  // Copy the contents of the message.
  message->severity       = logmsg.severity;
  message->timestamp.sec  = logmsg.timestamp.sec;
  message->timestamp.usec = logmsg.timestamp.usec;

  ::CORBA::ULong msglen = logmsg.message.length ();
  message->message.length (msglen);

  ACE_OS::memcpy (message->message.get_buffer (),
                  logmsg.message.get_buffer (),
                  logmsg.message.length ());
}

//
// flush
//
void CUTS_Logger_i::flush (void)
{
  // Package the messages.
  ::CORBA::ULong used_size = this->queue_.used_size ();
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
}
