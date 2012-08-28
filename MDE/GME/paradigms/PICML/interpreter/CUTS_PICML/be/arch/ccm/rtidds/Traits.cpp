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
// write_stub_source_files
//
void Traits::
write_stub_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  const std::string name = node.file_.name ();

  if (node.has_dds_events_)
  {
    proj
      << "    " + name + ".cxx" << std::endl
      << "    " + name + "Plugin.cxx" << std::endl
      << "    " + name + "Support.cxx" << std::endl;
  }

  if (node.has_events_)
  {
    proj
      << "    RTIDDS_" + name + "C.cpp" << std::endl;
  }
}

//
// write_top
//
void Traits::write_top (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  // Construct the macro name for the build.
  const std::string & name = node.name_;
  std::string macro_basename (name);
  std::transform (macro_basename.begin (),
                  macro_basename.end (),
                  macro_basename.begin (),
                  &::toupper);

  if (node.has_dds_events_)
  {
    // Write the project that generates type support for the
    // dds events in the idl file.
    const std::string project_name = name + "_NDDS_IDL_Gen";

    proj
      << "project (" << project_name << ") : ndds_cck_ts_defaults, requires_rtidds {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  ndds_ts_flags += -d ." << std::endl
      << "  ndds_ts_flags -= $(PLATFORM_NDDS_FLAGS)" << std::endl
      << std::endl
      << "  NDDSTypeSupport_Files {" << std::endl
      << "    " << name << ".idl" << std::endl
      << "  }" << std::endl
      << "}" << std::endl
      << std::endl;

    // Make sure the stub builds after this project.
    this->stub_after_.insert (project_name);
  }

  if (node.has_events_)
  {
    // Generate the iCCM source files.
    const std::string project_name = name + "_iCCM_IDL_Gen";

    proj
      << "project (" << project_name << ") : iccm_rtidds, requires_rtidds {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  iccm_rtidds_flags += -Wb,stub_export_macro=" << macro_basename << "_STUB_Export \\" << std::endl
      << "                       -Wb,stub_export_include=" << name << "_stub_export.h \\" << std::endl
      << "                       -Wb,svnt_export_macro=" << macro_basename << "_SVNT_Export \\" << std::endl
      << "                       -Wb,svnt_export_include=" << name << "_svnt_export.h" << std::endl
      << "                       -Glem -Gsv" << std::endl
      << std::endl
      << "  ICCM_Files {" << std::endl
      << "    gendir = ." << std::endl
      << std::endl
      << "    " << name << ".idl" << std::endl
      << "  }" << std::endl
      << "}" << std::endl
      << std::endl;

    // Make sure the stub project builds after this project.
    this->stub_after_.insert (project_name);
  }
}

//
// write_stub_after
//
void Traits::
write_stub_after (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  std::set <std::string>::const_iterator
    iter = this->stub_after_.begin (),
    iter_end = this->stub_after_.end ();

  for (; iter != iter_end; ++ iter)
    proj << " " << *iter;
}

//
// write_exec_idl_files
//
void Traits::
write_exec_idl_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (node.has_components_)
    proj << "    " << node.file_.name () << "_iCCM.idl" << std::endl;
}

//
// write_exec_source_files
//
void Traits::
write_exec_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (node.has_components_)
    proj << "    " << node.file_.name () << "_iCCMC.cpp" << std::endl;
}

}
