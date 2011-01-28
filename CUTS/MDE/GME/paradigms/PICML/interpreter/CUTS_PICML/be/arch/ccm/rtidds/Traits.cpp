// $Id$

#include "Traits.h"

#if !defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#include "../../../BE_IDL_Node.h"
#include "../../../BE_algorithm.h"

namespace CUTS_BE_RTIDDS
{

//
// write_top
//
void Traits::write_top (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (!node.has_dds_events_)
    return;

  // Construct the macro name for the build.
  const std::string & name = node.name_;
  std::string macro_basename (name);
  std::transform (macro_basename.begin (),
                  macro_basename.end (),
                  macro_basename.begin (),
                  &::toupper);

  proj
    << "project (" << name << "_NDDS_IDL_Gen) : ndds_ts_defaults, requires_rtidds {" << std::endl
    << "  custom_only = 1" << std::endl
    << std::endl
    << "  after += " << name << "_IDL_Gen" << std::endl
    << std::endl
    << "  ndds_ts_flags += -d rtidds" << std::endl
    << std::endl
    << "  NDDSTypeSupport_Files {" << std::endl
    << "    gendir = rtidds" << std::endl
    << std::endl
    << "    " << name << ".idl" << std::endl
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// write_stub_source_files
//
void Traits::
write_stub_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  const std::string name = node.file_.name ();

  // Write the required stub file.
  proj << "    RTIDDS_" + name + "C.cpp" << std::endl;

  if (node.has_dds_events_)
    proj
      << "    rtidds/" + name + ".cxx" << std::endl
      << "    rtidds/" + name + "Plugin.cxx" << std::endl
      << "    rtidds/" + name + "Support.cxx" << std::endl;
}

//
// write_stub_after
//
void Traits::
write_stub_after (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (node.has_dds_events_)
    proj << " " << node.name_ + "_NDDS_IDL_Gen";
}

}
