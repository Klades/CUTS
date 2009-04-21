// $Id$

#include "TCPIP_HelloWorldC.h"
#include "ace/OS_NS_sys_time.h"
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Stream.h"
#include "ace/OS_NS_unistd.h"
#include "cuts/arch/tcpip/TCPIP_SPEC.h"

//
// main
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    ACE_INET_Addr server_addr (argv[1]);

    ACE_SOCK_Stream stream;
    ACE_SOCK_Connector connector;

    if (-1 == connector.connect (stream, server_addr))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to connect to %s [%m]\n"),
                         argv[1]),
                         1);

    // Construct the header for the message.
    CUTS_TCPIP_SPEC spec;
    spec.uuid_.from_string (argv[2]);
    spec.event_id_ = 0;
    spec.data_size_ = 0;

    char * ph_datasize = 0;
    ACE_OutputCDR packet;

    ph_datasize = (packet << spec);

    if (0 == ph_datasize)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T - %M - failed to create packet header\n")),
                         -1);

    // Get the current time of day.
    ACE_Time_Value tv = ACE_OS::gettimeofday ();

    // Construct the message payload.
    TCPIP::Message message;
    message.message ("Hello, World!!!");
    message.time ().sec = tv.sec ();
    message.time ().usec = tv.usec ();

    if (!(packet << message))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T - %M - failed to create packet payload\n")),
                         -1);

    // Update the data size of the packet.
    size_t datasize = packet.total_length () - CUTS_TCPIP_SPEC::BINARY_SIZE;
    packet.replace (static_cast <ACE_CDR::Long> (datasize), ph_datasize);

    // Send the packet across the wire.
    stream.send_n (packet.begin ());

    ACE_OS::sleep (10);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception\n"));
  }

  return -1;
}
