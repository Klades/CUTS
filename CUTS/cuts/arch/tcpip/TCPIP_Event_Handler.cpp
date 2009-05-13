// $Id$

#include "TCPIP_Event_Handler.h"

#if !defined (__CUTS_INLINE__)
#include "TCPIP_Event_Handler.inl"
#endif

#include "TCPIP_InputCDR.h"
#include "TCPIP_Servant.h"
#include "TCPIP_Servant_Manager.h"
#include "TCPIP_SPEC.h"

//
// handle_input
//
int CUTS_TCPIP_Event_Handler::handle_input (ACE_HANDLE fd)
{
  // Set the ACE_HANDLE as a socket stream.
  ACE_SOCK_Stream stream (fd);


  // @todo Since the header size is constant, we can create free list
  //       of the message blocks that are used to read the header from
  //       the stream.

  // Read the event from the stream. The first chunk of the event
  // is be the header information, which is of constrant size.
  static const ssize_t header_size = 4 +        // magic
                                     4 +        // byte order
                                     2 +        // version (x.x)
                                     2 +        // padding
                                     16 +       // UUID
                                     4 +        // event id
                                     4;         // payload size

  ACE_Message_Block header (header_size);
  ssize_t retcode = stream.recv_n (header.wr_ptr (), header_size);

  if (retcode != header_size)
    return -1;

  // Reflect the number of bytes read from the stream.
  header.wr_ptr (header_size);

  // Extract the header from the message block.
  CUTS_TCPIP_SPEC spec;
  ACE_CDR::ULong datasize;

  CUTS_TCPIP_InputCDR input (header.rd_ptr (), header_size);

  // Read the SPEC and the datasize from the packet.
  input >> spec;
  input >> datasize;

  if (!input.good_bit ())
    return -1;

  // Construct a chain of message blocks to read the payload associated
  // with the received event.
  ACE_Message_Block * mb = 0;
  ACE_NEW_RETURN (mb, ACE_Message_Block (ACE_CDR::DEFAULT_BUFSIZE), -1);

  ssize_t read_count;
  ACE_Message_Block * head = mb;
  ACE_Auto_Ptr <ACE_Message_Block> auto_clean (head);

  for (size_t remaining = datasize; 0 != remaining; )
  {
    // Determine how much should be read in this attempt.
    read_count =
      ACE_CDR::DEFAULT_BUFSIZE < remaining ?
      ACE_CDR::DEFAULT_BUFSIZE : remaining;

    // Read the data from the stream.
    retcode = stream.recv_n (mb->wr_ptr (), read_count);

    if (retcode != read_count)
      ACE_ERROR_RETURN ((LM_ERROR,
                          "%T - %M - %m\n"),
                          -1);


    // Substract the amount from the remaining count.
    mb->wr_ptr (read_count);
    remaining -= read_count;

    if (0 != remaining)
    {
      // Allocate a new block for the chain.
      ACE_Message_Block * temp = 0;

      ACE_NEW_RETURN (temp,
                      ACE_Message_Block (ACE_CDR::DEFAULT_BUFSIZE),
                      -1);

      // Insert new block in the chain and move forward.
      mb->cont (temp);
      mb = temp;
    }
  }

  // Since we have made it this far, we have successfully read the
  // event and its payload from the socket. Now, pass the message
  // the object manger, so it can dispatch it accordingly.

  if (this->obj_mgr_ != 0)
  {
    CUTS_TCPIP_Servant * svnt = 0;
    int retval = this->obj_mgr_->find_object (spec.uuid_, svnt);

    if (0 == retval)
    {
      // Signal the object to handle the event.
      CUTS_TCPIP_InputCDR event (head, input.byte_order ());
      retval = svnt->handle_event (spec.event_id_, event);

      if (-1 == retval)
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to handle event [%s]\n",
                    spec.uuid_.to_string ()->c_str ()));
    }
    else
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to locate object with id [%s]\n",
                  spec.uuid_.to_string ()->c_str ()));
  }

  // Release the message block.
  // head->release ();

  return 0;
}
