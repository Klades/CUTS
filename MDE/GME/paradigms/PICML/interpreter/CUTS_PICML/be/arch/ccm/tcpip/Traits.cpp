// $Id$

#include "Traits.h"

#if !defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#include "../../../BE_IDL_Node.h"
#include "../../../BE_algorithm.h"

//
// svnt_base_project
//
void CUTS_BE_TCPIP_Traits::
write_stub_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (node.has_events_)
    proj << "    TCPIP_" << node.name_ << "C.cpp" << std::endl;
}


//
// write_top
//
void CUTS_BE_TCPIP_Traits::write_top (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  // Construct the macro name for the build.
  const std::string & name = node.name_;
  std::string macro_basename (name);
  std::transform (macro_basename.begin (),
                  macro_basename.end (),
                  macro_basename.begin (),
                  &::toupper);

  if (node.has_events_ || node.has_components_)
  {
    // Generate the iCCM source files.
    const std::string project_name = name + "_iCCM_IDL_Gen";

    proj
      << "project (" << project_name << ") : iccm_tcpip, requires_tcpip {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  iccm_tcpip_flags += -Wb,stub_export_macro=" << macro_basename << "_STUB_Export \\" << std::endl
      << "                      -Wb,stub_export_include=" << name << "_stub_export.h \\" << std::endl
      << "                      -Wb,svnt_export_macro=" << macro_basename << "_SVNT_Export \\" << std::endl
      << "                      -Wb,svnt_export_include=" << name << "_svnt_export.h \\" << std::endl
      << "                      -Glem -Gsv" << std::endl
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
void CUTS_BE_TCPIP_Traits::
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
void CUTS_BE_TCPIP_Traits::
write_exec_idl_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (node.has_components_)
    proj << "    " << node.file_->name () << "_iCCM.idl" << std::endl;
}

//
// write_exec_source_files
//
void CUTS_BE_TCPIP_Traits::
write_exec_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (node.has_components_)
    proj << "    " << node.file_->name () << "_iCCMC.cpp" << std::endl;
}
