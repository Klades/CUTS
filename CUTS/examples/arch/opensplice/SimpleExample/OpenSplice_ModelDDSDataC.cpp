// $Id$

#include "OpenSplice_ModelDDSDataC.h"


bool operator <<= (Aggregate & corba, const ::CUTS_DDS::Aggregate & dds)
{
  corba.Member = dds.Member;
  return true;
}

bool operator >>= (const Aggregate & corba, ::CUTS_DDS::Aggregate & dds)
{
  dds.Member = corba.Member;
  return true;
}

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

