// $Id$

#include "RTIDDS_ModelDDSDataC.h"


namespace Outer
{
  bool operator <<= (TestData_DDS & corba, const ::CUTS_DDS::Outer::TestData_DDS & dds)
  {
    corba.key (dds.key);
    corba.packet () <<= dds.packet;
    return true;
  }

  bool operator >>= (const TestData_DDS & corba, ::CUTS_DDS::Outer::TestData_DDS & dds)
  {
    dds.key = corba.key ();
    corba.packet () >>= dds.packet;
    return true;
  }

  namespace Inner
  {
    bool operator <<= (Data_DDS & corba, const ::CUTS_DDS::Outer::Inner::Data_DDS & dds)
    {
      corba.urgent = dds.urgent;
      corba.id = dds.id;
      corba.name = ::CORBA::string_dup (dds.name);
      return true;
    }

    bool operator >>= (const Data_DDS & corba, ::CUTS_DDS::Outer::Inner::Data_DDS & dds)
    {
      dds.urgent = corba.urgent;
      dds.id = corba.id;
      dds.name = ::CORBA::string_dup (corba.name);
      return true;
    }
  }
}

