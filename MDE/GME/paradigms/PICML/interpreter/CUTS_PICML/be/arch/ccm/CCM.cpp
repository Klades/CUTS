// $Id$

#include "CCM.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{
//
// is_dds_event_wrapper
//
bool Context::
is_dds_event_wrapper (const PICML::Event & ev, PICML::Aggregate & dds_event)
{
  std::vector <PICML::Member> members = ev.Member_children ();

  if (1 != members.size ())
    return false;

  PICML::Member member = members.front ();
  const std::string name = member.name ();

  if (name != "content")
    return false;

  PICML::MemberType mt = member.ref ();
  bool retval = mt.type () == PICML::Aggregate::meta;

  if (retval)
    dds_event = PICML::Aggregate::Cast (mt);

  return retval;
}

//
// is_dds_event_wrapper
//
bool Context::is_dds_event_wrapper (const PICML::Event & ev)
{
  PICML::Aggregate dds_event;
  return Context::is_dds_event_wrapper (ev, dds_event);
}

}
}
