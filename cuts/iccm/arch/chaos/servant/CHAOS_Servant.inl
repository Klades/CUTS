// -*- C++ -*-
// $Id$

namespace iCCM
{

CUTS_INLINE
CHAOS_Servant::CHAOS_Servant (const char * name)
: Servant (name)
{

}

CUTS_INLINE
const CHAOS_Servant::servant_map_type & CHAOS_Servant::servants (void) const
{
  return this->servants_;
}

}
