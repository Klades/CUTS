// $Id$

#include "Project_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Project_Generator.inl"
#endif

#include "../../BE_IDL_Node.h"
#include "../../BE_algorithm.h"

//
// CUTS_BE_Project_Write_T
//
void CUTS_BE_Project_Write_T <CUTS_BE_OpenSplice::Context, CUTS_BE_IDL_Node>::
generate (const CUTS_BE_IDL_Node & node)
{
  std::string name (node.file_.name ());
  bool has_events = CUTS_BE::has_events (node.file_);

  this->stub_files_.insert ("OpenSplice_" + name + "C.cpp");

  if (has_events)
  {
    std::string macro_basename (name);
    std::transform (macro_basename.begin (),
                    macro_basename.end (),
                    macro_basename.begin (),
                    &::toupper);

    this->stub_files_.insert ("./ddstypes/" + name + "_DDSC.cpp");
    this->stub_files_.insert ("./ddstypes/" + name + "_DDSS.cpp");
    this->stub_files_.insert ("./ddstypes/" + name + "_DDSDcpsC.cpp");
    this->stub_files_.insert ("./ddstypes/" + name + "_DDSDcpsS.cpp");
    this->stub_files_.insert ("./ddstypes/" + name + "_DDSSplDcps.cpp");
    this->stub_files_.insert ("./ddstypes/" + name + "_DDSDcps_impl.cpp");

    this->ctx_.project_
      << std::endl
      << "project (" << name << "_DDS_IDL_Gen) : splice_ts_defaults, requires_opensplice {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  idlflags += -o ./ddstypes \\" << std::endl
      << "              -Wb,export_macro=" << macro_basename << "_STUB_Export \\" << std::endl
      << "              -Wb,export_include=../" << name << "_stub_export.h" << std::endl
      << std::endl
      << "  splice_ts_flags += -d ./ddstypes \\" << std::endl
      << "                     -P " << macro_basename << "_STUB_Export,../" << name << "_stub_export.h" << std::endl
      << std::endl
      << "  SpliceTypeSupport_Files {" << std::endl
      << "    gendir = ./ddstypes" << std::endl
      << std::endl
      << "    " << name << "_DDS.idl" << std::endl
      << "  }" << std::endl
      << std::endl
      << "  IDL_Files {" << std::endl
      << "    gendir = ./ddstypes" << std::endl
      << std::endl
      << "    " << name << "_DDS.idl" << std::endl
      << "    ./ddstypes/" << name << "_DDSDcps.idl" << std::endl
      << "  }" << std::endl
      << "}" << std::endl
      << std::endl;

    this->stub_after_ = name + "_DDS_IDL_Gen";
  }
  else
  {
    this->stub_after_.clear ();
  }

  base_type::generate (node);
}
