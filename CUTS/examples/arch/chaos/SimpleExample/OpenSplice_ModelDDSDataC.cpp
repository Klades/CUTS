// $Id$

#include "OpenSplice_ModelDDSDataC.h"

namespace Outer
{
  namespace Inner
  {
    // struct: Data_DDS
    bool operator <<= (Data_DDS & corba_type, const ::CUTS_DDS::Outer::Inner::Data_DDS & dds_type)
    {
      corba_type.name = ::CORBA::string_dup (dds_type.name);
      corba_type.id = dds_type.id;
      corba_type.urgent = dds_type.urgent;
      return true;
    }

    bool operator >>= (const Data_DDS & corba_type, ::CUTS_DDS::Outer::Inner::Data_DDS & dds_type)
    {
      dds_type.name = ::CORBA::string_dup (corba_type.name);
      dds_type.id = corba_type.id;
      dds_type.urgent = corba_type.urgent;
      return true;
    }
  }

  // event: TestData_DDS

  bool operator <<= (TestData_DDS & corba_ev, const ::CUTS_DDS::Outer::TestData_DDS & dds_ev)
  {
    corba_ev.key (dds_ev.key);
    corba_ev.packet () <<= dds_ev.packet;
    return true;
  }
  
  bool operator >>= (const TestData_DDS & corba_ev, ::CUTS_DDS::Outer::TestData_DDS & dds_ev)
  {
    dds_ev.key = corba_ev.key ();
    corba_ev.packet () >>= dds_ev.packet;
    return true;
  }
}
