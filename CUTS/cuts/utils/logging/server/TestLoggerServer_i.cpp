// $Id$

#include "TestLoggerServer_i.h"

#if !defined (__CUTS_INLINE__)
#include "TestLoggerServer_i.inl"
#endif

#include "cuts/UUID.h"

//
// send_message_packet
//
void CUTS_TestLoggerServer_i::
send_message_packet (const CUTS::LogMessagePacket & packet)
{
  // Extract the UUID from the packet.
  ACE_Utils::UUID uuid;
  packet.uuid >>= uuid;

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - received %d message(s) from %s for test %s\n",
              packet.messages.length (),
              packet.hostname.in (),
              uuid.to_string ()->c_str ()));
}
