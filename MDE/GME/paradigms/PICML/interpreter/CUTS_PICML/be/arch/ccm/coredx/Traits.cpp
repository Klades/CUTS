// $Id$

#include "Traits.h"

#if !defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#include "../../../BE_IDL_Node.h"
#include "../../../BE_algorithm.h"

namespace CUTS_BE_CoreDX
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
      << "    CoreDX_" + name + ".cc" << std::endl
      << "    CoreDX_" + name + "DataReader.cc" << std::endl
      << "    CoreDX_" + name + "DataWriter.cc" << std::endl
      << "    CoreDX_" + name + "TypeSupport.cc" << std::endl;
  }

  if (node.has_events_)
  {
    proj
      << "    CoreDX_" + name + "C.cpp" << std::endl;
  }
}

//
// write_top
//
void Traits::write_top (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  // Since we are starting a new file, we need to clear the
  // listing of dependency projects.
  if (!this->stub_after_.empty ())
    this->stub_after_.clear ();

  const std::string & name = node.name_;
  std::string macro_basename (name);
  std::transform (macro_basename.begin (),
                  macro_basename.end (),
                  macro_basename.begin (),
                  &::toupper);

  if (node.has_dds_events_)
  {
    // Because the file has a DDS event, we need to make sure we run
    // the CoreDX IDL preprocessor on this file. This will ensure
    // we have the DDS types defined and implemented.
    const std::string project_name = name + "_CoreDX_IDL_Gen";
    proj
      << "project (" << project_name << ") : coredx_ts_defaults, iccm_coredx_idl2ddl {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  IDL2DDL_Files {" << std::endl
      << "    gendir = ." << std::endl
      << std::endl
      << "    " << name << ".idl" << std::endl
      << "  }" << std::endl
      << std::endl
      << "  CoreDXTypeSupport_Files {" << std::endl
      << "    gendir = ." << std::endl
      << std::endl
      << "    CoreDX_" << name << ".ddl" << std::endl
      << "  }" << std::endl
      << std::endl
      << "}" << std::endl
      << std::endl;

    this->stub_after_.insert (project_name);
  }

  if (node.has_events_ || node.has_components_)
  {
    const std::string project_name = name + "_iCCM_IDL_Gen";

    proj
      << "project (" << project_name << ") : iccm_coredx, requires_coredx {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  iccm_coredx_flags += -Wb,stub_export_macro=" << macro_basename << "_STUB_Export \\" << std::endl
      << "                       -Wb,stub_export_include=" << name << "_stub_export.h \\" << std::endl
      << "                       -Wb,svnt_export_macro=" << macro_basename << "_SVNT_Export \\" << std::endl
      << "                       -Wb,svnt_export_include=" << name << "_svnt_export.h \\" << std::endl
      << "                       -Glem -Gsv" << std::endl
      << std::endl
      << "  ICCM_Files {" << std::endl
      << "    gendir = ." << std::endl
      << std::endl
      << "    " << name << ".idl" << std::endl
      << "  }" << std::endl
      << "}" << std::endl
      << std::endl;

    this->stub_after_.insert (project_name);
  }
}

void Traits::
write_stub_custom (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  // Define dynamicflags to link and export CoreDX stubs properly on windows
  if (node.has_dds_events_)
    proj
      << std::endl
      << "  specific (prop:windows) {" << std::endl
      << "    dynamicflags += COREDX_DLL_TS_EXPORTS LD" << std::endl
      << "  }" << std::endl;
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
