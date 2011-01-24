// $Id$

#include "Event_Traits_Generator.h"
#include "../../../lang/cpp/Cpp.h"
#include "../../../BE_algorithm.h"

namespace CUTS_BE_OpenSplice
{
//
// Event_Traits_Generator
//
Event_Traits_Generator::
Event_Traits_Generator (std::ostream & out, const std::string & exp)
: out_ (out),
  export_ (exp)
{

}

//
// ~Event_Traits_Generator
//
Event_Traits_Generator::~Event_Traits_Generator (void)
{

}

//
// is_event_wrapper
//
bool Event_Traits_Generator::is_event_wrapper (const PICML::Event & ev)
{
  PICML::Aggregate dds_event;
  return Event_Traits_Generator::is_event_wrapper (ev, dds_event);
}

//
// is_event_wrapper
//
bool Event_Traits_Generator::
is_event_wrapper (const PICML::Event & ev, PICML::Aggregate & dds_event)
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
// Visit_Event
//
void Event_Traits_Generator::Visit_Event (const PICML::Event & ev)
{
  PICML::Aggregate dds_event;

  if (!this->is_event_wrapper (ev, dds_event))
    return;

  // Construct the CORBA and DDS event type.
  const std::string evt_type = CUTS_BE_CPP::fq_type (ev, "::", false);
  const std::string dds_type = CUTS_BE_CPP::fq_type (dds_event, "::", false);

  // Make sure we include the DDS event's header file.
  PICML::File file = CUTS_BE::get_file (dds_event);
  const std::string filename =
    CUTS_BE::get_pathname (file,
                           "/",
                           "",
                           "Dcps_impl");

  this->out_
    << CUTS_BE_CPP::include ("opensplice/" + filename)
    << std::endl
    << "/**" << std::endl
    << " * @class CUTS_OpenSplice_Traits_T < ::" << evt_type << " >" << std::endl
    << " *" << std::endl
    << " * Trait class for the ::" << evt_type << " event" << std::endl
    << " */" << std::endl
    << "template < >" << std::endl
    << "class " << this->export_ << " CUTS_OpenSplice_Traits_T < ::" << evt_type << " >"
    << "{"
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("The reader type traits")
    << "typedef ::" << dds_type << "DataReader reader_type;"
    << "typedef reader_type::_ptr_type reader_ptr_type;"
    << "typedef reader_type::_var_type reader_var_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The writer type traits")
    << "typedef ::" << dds_type << "DataWriter writer_type;"
    << "typedef writer_type::_ptr_type writer_ptr_type;"
    << "typedef writer_type::_var_type writer_var_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The DDS event type traits")
    << "typedef ::" << dds_type << " dds_event_type;"
    << "typedef ::" << dds_type << "Seq dds_event_sequence_type;"
    << "typedef ::" << dds_type << "Seq_var dds_event_sequence_var_type;"
    << std::endl
    << "typedef ::" << dds_type << "TypeSupportInterface dds_typesupport_interface_type;"
    << "typedef dds_typesupport_interface_type::_var_type dds_typesupport_interface_var_type;"
    << "typedef dds_typesupport_interface_type::_ptr_type dds_typesupport_interface_ptr_type;"
    << std::endl
    << "typedef ::" << dds_type << "TypeSupport dds_typesupport_type;"
    << "typedef ::" << dds_type << "TypeSupport_var dds_typesupport_var_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The CORBA event type traits")
    << "typedef ::" << evt_type << " corba_event_type;"
    << "typedef corba_event_type::_var_type corba_event_var_type;"
    << "typedef corba_event_type::_ptr_type corba_event_ptr_type;"
    << "typedef ::OBV_" << evt_type << " corba_obv_event_type;"
    << "};";
}

}
