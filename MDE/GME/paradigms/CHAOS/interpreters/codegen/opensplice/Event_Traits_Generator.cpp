// $Id$

#include "StdAfx.h"
#include "Event_Traits_Generator.h"
#include "cpp/Cpp.h"

namespace CUTS_CHAOS
{
namespace OpenSplice
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
void Event_Traits_Generator::Visit_Event (const CHAOS::Event & event)
{
  std::string fq_type (CUTS_BE_CPP::fq_type (event, "::", false));

  this->out_
    << "/**" << std::endl
    << " * @class CUTS_OpenSplice_Traits_T < ::" << fq_type << " >" << std::endl
    << " *" << std::endl
    << " * Trait class for the ::" << fq_type << " event" << std::endl
    << " */" << std::endl
    << "template < >" << std::endl
    << "class " << this->export_ << " CUTS_OpenSplice_Traits_T < ::CUTS_OSPL::" << fq_type << " >"
    << "{"
    << "public:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("The reader type traits")
    << "typedef ::CUTS_OSPL::" << fq_type << "DataReader reader_type;"
    << "typedef reader_type::_ptr_type reader_ptr_type;"
    << "typedef reader_type::_var_type reader_var_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The writer type traits")
    << "typedef ::CUTS_OSPL::" << fq_type << "DataWriter writer_type;"
    << "typedef writer_type::_ptr_type writer_ptr_type;"
    << "typedef writer_type::_var_type writer_var_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The DDS event type traits")
    << "typedef ::CUTS_OSPL::" << fq_type << " dds_event_type;"
    << "typedef ::CUTS_OSPL::" << fq_type << "Seq dds_event_sequence_type;"
    << "typedef ::CUTS_OSPL::" << fq_type << "Seq_var dds_event_sequence_var_type;"
    << std::endl
    << "typedef ::CUTS_OSPL::" << fq_type << "TypeSupportInterface dds_typesupport_interface_type;"
    << "typedef dds_typesupport_interface_type::_var_type dds_typesupport_interface_var_type;"
    << "typedef dds_typesupport_interface_type::_ptr_type dds_typesupport_interface_ptr_type;"
    << std::endl
    << "typedef ::CUTS_OSPL::" << fq_type << "TypeSupport dds_typesupport_type;"
    << "typedef ::CUTS_OSPL::" << fq_type << "TypeSupport_var dds_typesupport_var_type;"
    << std::endl
    << CUTS_BE_CPP::single_line_comment ("The CORBA event type traits")
    << "typedef ::" << fq_type << " corba_event_type;"
    << "typedef corba_event_type::_var_type corba_event_var_type;"
    << "typedef corba_event_type::_ptr_type corba_event_ptr_type;"
    << "typedef ::OBV_" << fq_type << " corba_obv_event_type;"
    << "};";
}

}
}
