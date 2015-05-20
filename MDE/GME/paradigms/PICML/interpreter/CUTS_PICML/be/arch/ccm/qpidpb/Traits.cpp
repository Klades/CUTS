// $Id$

#include "Traits.h"

#if !defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#include "../../../BE_IDL_Node.h"
#include "../../../BE_algorithm.h"

namespace CUTS_BE_QpidPB
{

//
// write_stub_source_files
//
void Traits::
write_stub_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  const std::string name = node.file_->name ();

  if (node.has_dds_events_)
  {
    proj
      << "    " + name + ".pb.cc" << std::endl;
  }

  if (node.has_events_)
  {
    proj
      << "    QpidPB_" + name + "C.cpp" << std::endl;
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
    // the QpidPB IDL preprocessor on this file. This will ensure
    // we have the DDS types defined and implemented.
    const std::string idl2proto_project_name = name + "_QpidPB_IDL2Proto_Gen";
    proj
      << "project (" << idl2proto_project_name << ") : requires_qpidpb, iccm_qpidpb_idl2proto {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  IDL2Proto_Files {" << std::endl
      << "    gendir = ." << std::endl
      << std::endl
      << "    " << name << ".idl" << std::endl
      << "  }" << std::endl
      << "}" << std::endl
      << std::endl;

    const std::string protogen_project_name = name + "_QpidPB_Proto_Gen";
    proj
      << "project (" << protogen_project_name << ") : requires_qpidpb, cuts_protoc {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << idl2proto_project_name << std::endl
      << std::endl
      << "  Protoc_Files {" << std::endl
      << "    gendir = ." << std::endl
      << std::endl
      << "    " << name << ".proto" << std::endl
      << "  }" << std::endl
      << "}" << std::endl
      << std::endl;

    this->stub_after_.insert (protogen_project_name);
  }

  if (node.has_events_ || node.has_components_)
  {
    const std::string project_name = name + "_iCCM_IDL_Gen";

    proj
      << "project (" << project_name << ") : iccm_qpidpb, requires_qpidpb {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  iccm_qpidpb_flags += -Wb,stub_export_macro=" << macro_basename << "_STUB_Export \\" << std::endl
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
    proj << "    " << node.file_->name () << "_iCCM.idl" << std::endl;
}

//
// write_exec_source_files
//
void Traits::
write_exec_source_files (std::ostream & proj, const CUTS_BE_IDL_Node & node)
{
  if (node.has_components_)
    proj << "    " << node.file_->name () << "_iCCMC.cpp" << std::endl;
}

}
