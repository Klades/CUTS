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
void CUTS_BE_Project_Write_T <CUTS_BE_RTIDDS::Context, CUTS_BE_IDL_Node>::
generate (const CUTS_BE_IDL_Node & node)
{
  std::string name (node.file_.name ());
  bool has_events = CUTS_BE::has_events (node.file_);

  this->stub_files_.insert ("RTIDDS_" + name + "C.cpp");

  if (has_events)
  {
    const std::string ndds_idl_file = name + "_NDDS.idl";

    this->stub_files_.insert ("./rtidds/" + name + "_NDDS.cxx");
    this->stub_files_.insert ("./rtidds/" + name + "_NDDSPlugin.cxx");
    this->stub_files_.insert ("./rtidds/" + name + "_NDDSSupport.cxx");
    this->idl_gen_files_.insert (ndds_idl_file);

    this->ctx_.project_
      << std::endl
      << "project (" << name << "_NDDS_IDL_Gen) : ndds_ts_defaults, requires_rtidds {" << std::endl
      << "  custom_only = 1" << std::endl
      << std::endl
      << "  after += " << name << "_IDL_Gen" << std::endl
      << std::endl
      << "  ndds_ts_flags += -d ./rtidds" << std::endl
      << std::endl
      << "  NDDSTypeSupport_Files {" << std::endl
      << "    gendir = ./rtidds" << std::endl
      << "    " << ndds_idl_file << std::endl
      << "  }" << std::endl
      << "}" << std::endl
      << std::endl;

    this->stub_after_ = name + "_NDDS_IDL_Gen";
  }
  else
  {
    this->stub_after_.clear ();
  }

  base_type::generate (node);
}
