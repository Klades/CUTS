// $Id$

#include "Event_Traits_Generator.h"
#include "../../../arch/ccm/CCM.h"
#include "../../../BE_algorithm.h"

namespace CUTS_BE_RTIDDS
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
// Visit_Event
//
void Event_Traits_Generator::Visit_Event (const PICML::Event & ev)
{
  PICML::Aggregate dds_event;
  if (!CUTS_BE_CCM::Cpp::Context::is_dds_event_wrapper (ev, dds_event))
    return;

  const std::string fq_type = CUTS_BE_CPP::fq_type (ev, "::", false);
  const std::string dds_type = CUTS_BE_CPP::fq_type (dds_event, "::", false);

  PICML::File file = CUTS_BE::get_file (dds_event);
  const std::string filename =
    CUTS_BE::get_pathname (file,
                           "/",
                           "",
                           "Support");

  this->out_
    << CUTS_BE_CPP::include ("rtidds/" + filename)
    << std::endl
    << "/**" << std::endl
    << " * @class CUTS_RTIDDS_Traits_T < ::" << fq_type << " >" << std::endl
    << " *" << std::endl
    << " * Trait class for the ::" << fq_type << " event" << std::endl
    << " */" << std::endl
    << "template < >" << std::endl
    << "class " << this->export_ << " CUTS_RTIDDS_Traits_T < " << fq_type << " >"
    << "{"
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("The reader type traits")
    << "typedef ::" << dds_type << "DataReader reader_type;"
    << "typedef reader_type * reader_ptr_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The writer type traits")
    << "typedef ::" << dds_type << "DataWriter writer_type;"
    << "typedef writer_type * writer_ptr_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The DDS event type traits")
    << "typedef ::" << dds_type << " dds_event_type;"
    << "typedef ::" << dds_type << "Seq dds_event_sequence_type;"
    << "typedef ::" << dds_type << "TypeSupport dds_typesupport_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The CORBA event type traits")
    << "typedef ::" << fq_type << " corba_event_type;"
    << "typedef corba_event_type::_var_type corba_event_var_type;"
    << "typedef corba_event_type::_ptr_type corba_event_ptr_type;"
    << "typedef ::OBV_" << fq_type << " corba_obv_event_type;"
    << "};";
}

}
