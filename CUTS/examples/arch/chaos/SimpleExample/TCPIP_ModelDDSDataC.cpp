// $Id$

#include "TCPIP_ModelDDSDataC.h"


namespace Outer
{
  ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const TestData_DDS & ev)
  {
    stream << ev.key ();
    stream << ev.packet ();
    return stream.good_bit ();
  }

  ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, TestData_DDS & ev)
  {
    ACE_CDR::Short _val_300000031;
    stream >> _val_300000031;
    ev.key (_val_300000031);

    stream >> ev.packet ();
    return stream.good_bit ();
  }

  namespace Inner
  {
    ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & stream, const Data_DDS & val)
    {
      stream << val.name;
      stream << val.id;
      stream << val.urgent;
      return stream.good_bit ();
    }

    ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, Data_DDS & val)
    {
      ACE_CString val_name;
      stream >> val_name;
      val.name = val_name.c_str ();

      stream >> val.id;
      stream >> CUTS_TCPIP_InputCDR::to_boolean (val.urgent);
      return stream.good_bit ();
    }
  }
}

