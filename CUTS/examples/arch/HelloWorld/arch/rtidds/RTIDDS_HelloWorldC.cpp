// $Id$

#include "RTIDDS_HelloWorldC.h"


bool operator <<= (Message & corba, const ::CUTS_NDDS::Message & dds)
{
  corba.time () <<= dds.time;
  corba.content (dds.content);
  return true;
}

bool operator >>= (const Message & corba, ::CUTS_NDDS::Message & dds)
{
  corba.time () >>= dds.time;
  dds.content = corba.content ();
  return true;
}

bool operator <<= (TimeValue & corba, const ::CUTS_NDDS::TimeValue & dds)
{
  corba.usec = dds.usec;
  corba.sec = dds.sec;
  return true;
}

bool operator >>= (const TimeValue & corba, ::CUTS_NDDS::TimeValue & dds)
{
  dds.usec = corba.usec;
  dds.sec = corba.sec;
  return true;
}

