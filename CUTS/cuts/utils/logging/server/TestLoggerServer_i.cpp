// $Id$

#include "TestLoggerServer_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestLoggerServer_i.inl"
#endif

#include "cuts/UUID.h"
#include "ace/streams.h"

//
// send_message_packet
//
void CUTS_TestLoggerServer_i::
send_message_packet (const CUTS::LogMessagePacket & packet)
{
  std::cerr << "GREAT!!!" << std::endl;

  // Extract the UUID from the packet.
  ACE_Utils::UUID uuid;
  packet.uuid >>= uuid;

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - received %d message(s) from %s for test %s\n",
              packet.messages.length (),
              packet.hostname.in (),
              uuid.to_string ()->c_str ()));

  // Set the packet to all the callbacks.
  callbacks_type::iterator iter (this->callbacks_);

  for (; !iter.done (); ++ iter)
    (*iter)->handle_messages (packet);
}

//
// install_callback
//
int CUTS_TestLoggerServer_i::
install_callback (CUTS::TestLoggerServerCallback_ptr callback)
{
  CUTS::TestLoggerServerCallback_var temp =
    CUTS::TestLoggerServerCallback::_duplicate (callback);

  return this->callbacks_.insert (temp);
}
