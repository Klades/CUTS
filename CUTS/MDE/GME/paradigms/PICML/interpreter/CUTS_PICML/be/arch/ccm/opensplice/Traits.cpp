// $Id$

#include "Traits.h"

#if !defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#include "../../../BE_IDL_Node.h"
#include "../../../BE_algorithm.h"

namespace CUTS_BE_OpenSplice
{

//
// write_stub_source_files
//
void Traits::
write_stub_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  const std::string name = node.file_.name ();

  // Write the required stub file.
  proj << "    OpenSplice_" + name + "C.cpp" << std::endl;

  if (this->has_dds_events_)
  {
    // Make sure we compile the OpenSplice event sources.
    proj
      << "    opensplice/" + name + "DcpsC.cpp" << std::endl
      //<< "    opensplice/" + name + "DcpsS.cpp" << std::endl
      << "    opensplice/" + name + "SplDcps.cpp" << std::endl
      << "    opensplice/" + name + "Dcps_impl.cpp" << std::endl;
  }
}

//
// write_top
//
void Traits::write_top (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  this->has_dds_events_ = CUTS_BE::has_dds_events (node.file_);

  if (!this->has_dds_events_)
    return;

  const std::string & name = node.name_;
  std::string macro_basename (name);
  std::transform (macro_basename.begin (),
                  macro_basename.end (),
                  macro_basename.begin (),
                  &::toupper);

  proj
    << "project (" << name << "_OSPL_IDL_Gen) : splice_ts_defaults, requires_opensplice {" << std::endl
    << "  custom_only = 1" << std::endl
    << std::endl
    << "  after += " << name << "_IDL_Gen" << std::endl
    << std::endl
    << "  idlflags += -o opensplice \\" << std::endl
    << "              -Wb,export_macro=" << macro_basename << "_STUB_Export \\" << std::endl
    << "              -Wb,export_include=../" << name << "_stub_export.h" << std::endl
    << std::endl
    << "  splice_ts_flags += -d opensplice \\" << std::endl
    << "                     -P " << macro_basename << "_STUB_Export,../" << name << "_stub_export.h" << std::endl
    << std::endl
    << "  SpliceTypeSupport_Files {" << std::endl
    << "    gendir = opensplice" << std::endl
    << std::endl
    << "    " << name << ".idl" << std::endl
    << "  }" << std::endl
    << std::endl
    << "  IDL_Files {" << std::endl
    << "    gendir = opensplice" << std::endl
    << std::endl
    << "    opensplice/" << name << "Dcps.idl" << std::endl
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// write_stub_after
//
void Traits::
write_stub_after (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (this->has_dds_events_)
    proj << " " << node.name_ + "_OSPL_IDL_Gen";
}

}
