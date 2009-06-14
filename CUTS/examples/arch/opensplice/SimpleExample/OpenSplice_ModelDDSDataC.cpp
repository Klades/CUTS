// $Id$

#include "OpenSplice_ModelDDSDataC.h"


namespace Outer
{
  bool operator <<= (TestData_DDS & corba, const ::CUTS_DDS::Outer::TestData_DDS & dds)
  {
    corba.packet () <<= dds.packet;
    corba.key (dds.key);
    return true;
  }

  bool operator >>= (const TestData_DDS & corba, ::CUTS_DDS::Outer::TestData_DDS & dds)
  {
    corba.packet () >>= dds.packet;
    dds.key = corba.key ();
    return true;
  }

  namespace Inner
  {
    bool operator <<= (Data_DDS & corba, const ::CUTS_DDS::Outer::Inner::Data_DDS & dds)
    {
      corba.name = ::CORBA::string_dup (dds.name);
      corba.id = dds.id;
      corba.urgent = dds.urgent;
      return true;
    }

    bool operator >>= (const Data_DDS & corba, ::CUTS_DDS::Outer::Inner::Data_DDS & dds)
    {
      dds.name = ::CORBA::string_dup (corba.name);
      dds.id = corba.id;
      dds.urgent = corba.urgent;
      return true;
    }
  }
}

