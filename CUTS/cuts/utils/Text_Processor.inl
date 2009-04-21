// -*- C++ -*-
// $Id$

//
// CUTS_Text_Processor
//
CUTS_INLINE
CUTS_Text_Processor::
CUTS_Text_Processor (const CUTS_Property_Map & map)
: stream_actor_ (buffer_),
  property_eval_ (map, stream_actor_)
{

}

//
// ~CUTS_Text_Processor
//
CUTS_INLINE
CUTS_Text_Processor::~CUTS_Text_Processor (void)
{

}
