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
is_dds_event_wrapper (const PICML::Event_in ev, PICML::Aggregate_in dds_event)
{
  auto members = ev->get_Members ();

  if (members.count () != 1)
    return false;

  PICML::Member member = members.first ();
  const std::string name = member->name ();

  if (name != "content")
    return false;

  PICML::MemberType mt = member->refers_to_MemberType ();
  bool retval = mt->meta ()->name () == PICML::Aggregate::impl_type::metaname;

  if (retval)
    dds_event = PICML::Aggregate::_narrow (mt);

  return retval;
}

//
// is_dds_event_wrapper
//
bool Context::is_dds_event_wrapper (const PICML::Event_in ev)
{
  PICML::Aggregate dds_event;
  return Context::is_dds_event_wrapper (ev, dds_event);
}

}
}
