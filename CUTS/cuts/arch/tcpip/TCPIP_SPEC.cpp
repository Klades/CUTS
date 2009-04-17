// $Id$

#include "TCPIP_SPEC.h"

#define CUTS_TCPIP_SPEC_MAGIC_SIZE  4

namespace CUTS_TCPIP
{
  static ACE_CDR::Octet CUTS_TCPIP_SPEC_MAGIC[CUTS_TCPIP_SPEC_MAGIC_SIZE] = {'C', 'U', 'T', 'S'};

  static ACE_CDR::Octet CUTS_TCPIP_SPEC_VERSION[2] = {1, 0};
}


//
// operator <<
//
ACE_CDR::Boolean operator << (ACE_OutputCDR & output, const ACE_Utils::UUID & uuid)
{
  CUTS_TCPIP_TRACE ("operator << (ACE_OutputCDR &, const ACE_Utils::UUID &)");

  output << uuid.time_low ();
  output << uuid.time_mid ();
  output << uuid.time_hi_and_version ();
  output << ACE_OutputCDR::from_octet (uuid.clock_seq_hi_and_reserved ());
  output << ACE_OutputCDR::from_octet (uuid.clock_seq_low ());

  output.write_octet_array (uuid.node ()->node_ID (),
                            ACE_Utils::UUID_Node::NODE_ID_SIZE);

  return output.good_bit ();
}

//
// operator <<
//
ACE_CDR::Boolean operator << (ACE_OutputCDR & output, const CUTS_TCPIP_SPEC & spec)
{
  CUTS_TCPIP_TRACE ("operator << (ACE_OutputCDR &, const CUTS_TCPIP_SPEC &)");

  output.write_octet_array (CUTS_TCPIP::CUTS_TCPIP_SPEC_MAGIC,
                            CUTS_TCPIP_SPEC_MAGIC_SIZE);

  output << ACE_OutputCDR::from_boolean (ACE_CDR::BYTE_ORDER_NATIVE);
  output.write_octet_array (CUTS_TCPIP::CUTS_TCPIP_SPEC_VERSION, 2);

  // padding
  output.write_short_placeholder ();

  output << spec.uuid_;
  output << spec.event_id_;
  output << spec.data_size_;

  return output.good_bit ();
}

//
// operator >>
//
ACE_CDR::Boolean operator >> (ACE_InputCDR & input, ACE_Utils::UUID & uuid)
{
  CUTS_TCPIP_TRACE ("operator >> (ACE_InputCDR &, ACE_Utils::UUID &)");

  ACE_CDR::ULong time_low;
  ACE_CDR::UShort time_mid;
  ACE_CDR::UShort time_hi_and_version;
  ACE_CDR::Octet clock_seq_hi_and_reserved;
  ACE_CDR::Octet clock_seq_low;

  // First, read the contents of the UUID.
  input >> time_low;
  input >> time_mid;
  input >> time_hi_and_version;
  input >> ACE_InputCDR::to_octet (clock_seq_hi_and_reserved);
  input >> ACE_InputCDR::to_octet (clock_seq_low);
  input.read_octet_array (uuid.node ()->node_ID (),
                          ACE_Utils::UUID_Node::NODE_ID_SIZE);

  if (input.good_bit ())
  {
    // Save the contents of the UUID.
    uuid.time_low (time_low);
    uuid.time_mid (time_mid);
    uuid.time_hi_and_version (time_hi_and_version);
    uuid.clock_seq_hi_and_reserved (clock_seq_hi_and_reserved);
    uuid.clock_seq_low (clock_seq_low);

    return true;
  }
  else
    return false;
}

//
// operator >>
//
ACE_CDR::Boolean operator >> (ACE_InputCDR & input, CUTS_TCPIP_SPEC & spec)
{
  CUTS_TCPIP_TRACE ("operator >> (ACE_InputCDR &, CUTS_TCPIP_SPEC &)");

  // First, read the magic from the input stream.
  ACE_CDR::Octet magic[CUTS_TCPIP_SPEC_MAGIC_SIZE];

  if (!((input.read_octet_array (magic, CUTS_TCPIP_SPEC_MAGIC_SIZE)) &&
        (magic[0] == 'C' && magic[1] == 'U' && magic[2] == 'T' && magic[3] == 'S')))
  {
    return false;
  }

  // Read the byte order of the message.
  ACE_CDR::Boolean byte_order;

  if (!(input >> ACE_InputCDR::to_boolean (byte_order)))
    return false;

  // Reset the byte order of the stream.
  input.reset_byte_order (byte_order);

  // Read the version number of the header. It should be 1.0, or
  // else there is something wrong with the header.
  ACE_CDR::Octet version[2];

  if (!(input.read_octet_array (version, 2) &&
        version[0] == 1 && version[1] == 0))
  {
    return false;
  }

  // Read the remaining parts of the SPEC.
  return (input >> spec.uuid_) &&
         (input >> spec.event_id_) &&
         (input >> spec.data_size_);
}

