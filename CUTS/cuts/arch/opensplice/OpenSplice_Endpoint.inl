// -*- C++ -*-
// $Id$

//
// CUTS_OpenSplice_Endpoint
//
CUTS_INLINE
CUTS_OpenSplice_Endpoint::CUTS_OpenSplice_Endpoint (void)
{

}

//
// ~CUTS_OpenSplice_Endpoint
//
CUTS_INLINE
CUTS_OpenSplice_Endpoint::~CUTS_OpenSplice_Endpoint (void)
{
  this->close ();
}

//
// topic
//
CUTS_INLINE
::DDS::Topic_ptr CUTS_OpenSplice_Endpoint::topic (void)
{
  return ::DDS::Topic::_duplicate (this->dds_topic_.in ());
}
 
