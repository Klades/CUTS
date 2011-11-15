// $Id$

#include "RTIDDS_ModelDDSDataC.h"


namespace Outer
{
  bool operator <<= (TestData_DDS & corba, const ::CUTS_NDDS::Outer::TestData_DDS & dds)
  {
    corba.packet () <<= dds.packet;
    corba.key (dds.key);
    return true;
  }

  bool operator >>= (const TestData_DDS & corba, ::CUTS_NDDS::Outer::TestData_DDS & dds)
  {
    corba.packet () >>= dds.packet;
    dds.key = corba.key ();
    return true;
  }

  namespace Inner
  {
    bool operator <<= (Data_DDS & corba, const ::CUTS_NDDS::Outer::Inner::Data_DDS & dds)
    {
      corba.name = ::CORBA::string_dup (dds.name);
      corba.urgent = dds.urgent;
      corba.id = dds.id;
      return true;
    }

    bool operator >>= (const Data_DDS & corba, ::CUTS_NDDS::Outer::Inner::Data_DDS & dds)
    {
      dds.name = ::CORBA::string_dup (corba.name);
      dds.urgent = corba.urgent;
      dds.id = corba.id;
      return true;
    }
  }
}

