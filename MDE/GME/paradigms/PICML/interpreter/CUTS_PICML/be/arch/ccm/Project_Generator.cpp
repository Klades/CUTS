// $Id$

#include "Project_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Project_Generator.inl"
#endif

#include "../../BE_algorithm.h"
#include "../../BE_Options.h"
#include "../../BE_Impl_Node.h"
#include "boost/bind.hpp"

template <typename COND>
class generate_listing_t
{
public:
  typedef std::set <const CUTS_BE_IDL_Node *> IDL_Node_Set;

  typedef COND condition_type;

  generate_listing_t (std::ostream & proj, IDL_Node_Set & visited)
    : proj_ (proj),
      visited_ (visited)
  {

  }

  void operator () (const CUTS_BE_IDL_Node * node)
  {
    IDL_Node_Set::const_iterator iter = this->visited_.find (node);

    if (iter != this->visited_.end ())
      return;

    // Save the node as being visited.
    this->visited_.insert (node);

    if (COND::validate (node))
      this->proj_
          << " \\" << std::endl
          << "    " << node->name_ << COND::get_suffix ();

    std::for_each (node->references_.begin (),
                   node->references_.end (),
                   generate_listing_t <COND> (this->proj_, this->visited_));
  }

private:
  /// The output stream of the project.
  std::ostream & proj_;

  /// A collection of IDL nodes.
  IDL_Node_Set & visited_;
};

/**
 * @class stub_listing
 *
 * Functor that generates the skeleton inclusion for a project.
 */
struct stub_t
{
  static bool validate (const CUTS_BE_IDL_Node * node)
  {
    return true;
  }

  static const char * get_suffix (void)
  {
    return "_stub";
  }
};

/**
 * @class skel_listing
 *
 * Functor that generates the skeleton inclusion for a project.
 */
struct skel_t
{
  static bool validate (const CUTS_BE_IDL_Node * node)
  {
    return node->has_components_ ||
           node->has_events_ ||
           node->has_interfaces_;
  }

  static const char * get_suffix (void)
  {
    return "_skel";
  }
};

/**
 * @class generate_skel_listing_t
 *
 * Functor that generates the skeleton inclusion for a project.
 */
struct exec_t
{
  static bool validate (const CUTS_BE_IDL_Node * node)
  {
    return node->has_components_ || node->has_interfaces_;
  }

  static const char * get_suffix (void)
  {
    return "_exec";
  }
};

/**
 * @class generate_eidl_listing_t
 *
 * Functor that generates the skeleton inclusion for a project.
 */
struct eidl_t
{
  static bool validate (const CUTS_BE_IDL_Node * node)
  {
    return node->has_components_ || node->has_events_ || node->has_interfaces_;
  }

  static const char * get_suffix (void)
  {
    return "_EIDL_Gen";
  }
};


///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Open_T

void CUTS_BE_Project_File_Open_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node & node)
{
  std::string pathname (CUTS_BE_OPTIONS ()->output_directory_);
  pathname += "/" + node.name_ + ".mpc";

  this->ctx_.project_.open (pathname.c_str ());
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Begin_T

void CUTS_BE_Project_File_Begin_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node &)
{
  this->ctx_.project_
    << CUTS_BE_CPP::single_line_comment ("This project file was generated by:")
    << CUTS_BE_CPP::single_line_comment (__FILE__)
    << std::endl;
}

//
// CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>
//
void
CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node & node)
{
  // Let's reset the <visited_nodes_> object, if necessary.
  if (!this->visited_nodes_.empty ())
    this->visited_nodes_.clear ();

  this->generate_impl_project (node);
}

//
// generate_impl_project
//
void CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>::
generate_impl_project (const CUTS_BE_Impl_Node & node)
{
  std::string impl_basename = node.exec_artifact_.name ();
  std::string container_name (node.container_.name ());

  // Create the export name for the project.
  std::string impl_export (impl_basename);

  std::transform (impl_export.begin (),
                  impl_export.end (),
                  impl_export.begin (),
                  &::toupper);

  // Generate the executor project.
  this->ctx_.project_
    << "project (" << impl_basename
    << ") : cuts_coworker_exec {" << std::endl
    << "  sharedname    = " << impl_basename << std::endl
    << std::endl
    << "  dynamicflags += " << impl_export << "_BUILD_DLL" << std::endl
    << std::endl
    << "  prebuild = perl -- $(ACE_ROOT)/bin/generate_export_file.pl "
    << impl_export << " > $(PROJECT_ROOT)/"
    << impl_basename << "_export.h" << std::endl;

  if (!node.references_.empty ())
  {
    // Filter the nodes correctly.
    std::vector <const CUTS_BE_IDL_Node *> nodes (node.references_.size ());
    std::copy (node.references_.begin (),
               node.references_.end (),
               nodes.begin ());

    typedef bool (* FUNCTOR)(const CUTS_BE_IDL_Node *);

    std::vector <const CUTS_BE_IDL_Node *>::iterator last_iter =
      std::remove_if (nodes.begin (),
                      nodes.end (),
                      reinterpret_cast <FUNCTOR> (&CUTS_BE::requires_executor));

    this->ctx_.project_
      << "  after += ";

    this->visited_nodes_.clear ();
    std::for_each (node.references_.begin (),
                   node.references_.end (),
                   generate_listing_t <exec_t> (this->ctx_.project_, this->visited_nodes_));

    this->visited_nodes_.clear ();
    std::for_each (nodes.begin (),
                   nodes.end (),
                   generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

    this->ctx_.project_
      << std::endl
      << std::endl;

    // Clear the visited nodes so we can iterate over them once
    // more. This time we are generating the libs declaration.

    this->ctx_.project_
      << "  libs += ";

    this->visited_nodes_.clear ();
    std::for_each (last_iter,
                   nodes.end (),
                   generate_listing_t <exec_t> (this->ctx_.project_, this->visited_nodes_));

    this->visited_nodes_.clear ();
    std::for_each (nodes.begin (),
                   nodes.end (),
                   generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

    this->ctx_.project_
      << std::endl
      << std::endl;
  }

  generate_mpc_i (node);

  this->ctx_.project_
    // Generate the source files.
    << "  Source_Files {" << std::endl
    << "    " << node.name_ << ".cpp" << std::endl
    << "  }" << std::endl
    << std::endl
    // Generate the header files.
    << "  Header_Files {" << std::endl
    << std::endl
    << "  }" << std::endl
    << std::endl
    << "  Inline_Files {" << std::endl
    << std::endl
    << "  }" << std::endl
    << std::endl
    << "  IDL_Files {" << std::endl
    << std::endl
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// genereate_mpc_i
//
void CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>::
generate_mpc_i (const CUTS_BE_Impl_Node & node)
{
  this->generate_mpc_values ("includes", node.include_paths_);
  this->generate_mpc_values ("libpaths", node.lib_paths_);
  this->generate_mpc_values ("libs", node.lib_);
}

//
// generate_mpc_values
//
void CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>::
generate_mpc_values (const std::string & heading,
                     const CUTS_String_Set & listing)
{
  if (listing.empty ())
    return;

  this->ctx_.project_
    << "  " << heading << " +=";

  for (CUTS_String_Set::const_iterator iter = listing.begin ();
       iter != listing.end ();
       iter ++)
  {
    this->ctx_.project_
      << " \\" << std::endl
      << "    " << iter->c_str ();
  }

  this->ctx_.project_
    << std::endl
    << std::endl;
}


//
// CUTS_BE_Project_File_End_T
//
void
CUTS_BE_Project_File_End_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>::
generate (const CUTS_BE_Impl_Node & node)
{
  this->ctx_.project_
    << CUTS_BE_CPP::single_line_comment("end of auto-generated project file")
    << std::endl;
}

//
// CUTS_BE_Project_File_Close_T
//
void
CUTS_BE_Project_File_Close_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_Impl_Node>::
generate (void)
{
  if (this->ctx_.project_.is_open ())
    this->ctx_.project_.close ();
}

///////////////////////////////////////////////////////////////////////////////
// project generators [CUTS_BE_IDL_Node]

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Open_T

void CUTS_BE_Project_File_Open_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate (const CUTS_BE_IDL_Node & node)
{
  // Construct the name of the project file.
  std::string pathname (CUTS_BE_OPTIONS ()->output_directory_);

  const std::string filepath (node.file_.Path ());

  if (!filepath.empty ())
    pathname += "/" + filepath;

  pathname += "/" + std::string (node.file_.name ()) + ".mpc";

  // Open the project for writing.
  this->ctx_.project_.open (pathname.c_str ());
}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Begin_T

void CUTS_BE_Project_File_Begin_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate (const CUTS_BE_IDL_Node & node)
{
  // Write the preamble for the project.
  this->ctx_.project_
    << CUTS_BE_CPP::single_line_comment ("This project file was generated by")
    << CUTS_BE_CPP::single_line_comment ("$Id$")
    << std::endl;

  // Let the traits write to the top of the project.
  this->ctx_.traits_->write_top (this->ctx_.project_, node);
}

//
// CUTS_BE_Project_Write_T <C>
//
void
CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate (const CUTS_BE_IDL_Node & node)
{
  this->generate_idlgen_project (node);
  this->generate_stub_project (node);

  if (node.has_components_ || node.has_events_ || node.has_interfaces_)
  {
    this->generate_skel_project (node);
    this->generate_eidl_project (node);

    if (node.has_components_ || node.has_interfaces_)
    {
      this->generate_exec_project (node);

      if (node.has_components_)
        this->generate_svnt_project (node);
    }
  }
}

//
// generate_idlgen_project
//
void
CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate_idlgen_project (const CUTS_BE_IDL_Node & node)
{
  // Generate the export file for the project.
  std::string macro_basename (node.name_);

  std::transform (macro_basename.begin (),
                  macro_basename.end (),
                  macro_basename.begin (),
                  &toupper);

  // Generate the project.
  this->ctx_.project_
    << "project (" << node.name_ << "_IDL_Gen) : ";

  this->ctx_.project_
    << (node.has_components_ || node.has_events_ ? "component" : "ciao")
    << "idldefaults, cuts_codegen_defaults {" << std::endl
    << "  custom_only = 1" << std::endl
    << std::endl
    << "  idlflags += -Wb,stub_export_macro=" << macro_basename << "_STUB_Export \\" << std::endl
    << "              -Wb,stub_export_include=" << node.name_ << "_stub_export.h \\" << std::endl
    << "              -Wb,skel_export_macro=" << macro_basename << "_SKEL_Export \\" << std::endl
    << "              -Wb,skel_export_include=" << node.name_ << "_skel_export.h \\" << std::endl
    << "              -Gxhst -Gxhsk \\" << std::endl;

  if (node.has_events_ || node.has_components_ || node.has_interfaces_)
  {
    this->ctx_.project_
      << "              -Wb,exec_export_macro=" << macro_basename << "_EXEC_Export \\" << std::endl
      << "              -Wb,exec_export_include=" << node.name_ << "_exec_export.h \\" << std::endl
      << "              -Gxhex \\" << std::endl;

    if (node.has_components_)
      this->ctx_.project_
        << "              -Wb,svnt_export_macro=" << macro_basename << "_SVNT_Export \\" << std::endl
        << "              -Wb,svnt_export_include=" << node.name_ << "_svnt_export.h \\" << std::endl
        << "              -Gxhsv \\" << std::endl;
  }

  this->ctx_.project_
    << "              -Sa -Sal -St" << std::endl;

  if (node.has_components_ && !this->ctx_.traits_->generate_default_servant ())
  {
    this->ctx_.project_
      << std::endl
      << "  idlflags -= -Gsv" << std::endl;
  }

  this->ctx_.project_
    << std::endl
    << "  IDL_Files {" << std::endl
    << "    " << node.name_ << ".idl" << std::endl;

  this->ctx_.traits_->write_idl_gen_files (this->ctx_.project_, node);

  this->ctx_.project_
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// generate_stub_project
//
void
CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate_stub_project (const CUTS_BE_IDL_Node & node)
{
  // Generate the export file for the project.
  std::string stub_name (node.name_);
  stub_name += "_stub";

  // Construct the export name for the project.
  std::string stub_export (stub_name);
  std::transform (stub_export.begin (),
                  stub_export.end (),
                  stub_export.begin (),
                  &toupper);

  std::string stub_export_macro = stub_export + "_Export";
  std::string stub_export_file = stub_name + "_export.h";

  // Generate the project.
  this->ctx_.project_
    << "project (" << stub_name << ") : avoids_ace_for_tao, "
    << this->ctx_.traits_->stub_base_project ()
    << ", cuts_codegen_defaults {" << std::endl
    << "  sharedname    = " << stub_name << std::endl
    << "  dynamicflags += " << stub_export << "_BUILD_DLL" << std::endl
    << std::endl
    << "  after        += " << node.file_.name () << "_IDL_Gen";

  this->ctx_.traits_->write_stub_after (this->ctx_.project_, node);

  this->ctx_.project_
    << std::endl;

  if (!node.references_.empty ())
  {
    // Generate the dependencies for this project. This will be
    // all the client projects of the references for this node.
    this->ctx_.project_
      << std::endl
      << "  // listing of project dependencies" << std::endl
      << "  after +=";

    this->visited_nodes_.clear ();
    std::for_each (node.references_.begin (),
                   node.references_.end (),
                   generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

    // Generate the import libraries for this project. This will be
    // all client project of the references for this node. The will
    // also be the same as those specified in the "after" tag.

    this->ctx_.project_
      << std::endl
      << std::endl
      << "  libs  +=";

    this->visited_nodes_.clear ();
    std::for_each (node.references_.begin (),
                   node.references_.end (),
                   generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

    this->ctx_.project_
      << std::endl;
  }

  // Allow the backend to write custom declarations to the project.
  this->ctx_.traits_->write_stub_custom (this->ctx_.project_, node);

  this->ctx_.project_
    << std::endl
    // Generate the IDL files for this project.
    << "  IDL_Files {" << std::endl
    << std::endl
    << "  }" << std::endl
    << std::endl
    // Generate the source files for this project.
    << "  Source_Files {" << std::endl
    << "    " << node.name_ << "C.cpp" << std::endl;

  this->ctx_.traits_->write_stub_source_files (this->ctx_.project_, node);

  this->ctx_.project_
    << "  }" << std::endl
    << std::endl
    // Generate the header files for this project.
    << "  Header_Files {" << std::endl
    << "    " << node.name_ << "C.h" << std::endl
    << "  }" << std::endl
    << std::endl
    << "  Inline_Files {" << std::endl
    << "    " << node.name_ << "C.inl" << std::endl
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// generate_skel_project
//
void
CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate_skel_project (const CUTS_BE_IDL_Node & node)
{
  // Generate the export file for the project.
  std::string skel_name = node.basename_ + "_skel";

  // Construct the export name for the project.
  std::string skel_export = skel_name;
  std::transform (skel_export.begin (),
                  skel_export.end (),
                  skel_export.begin (),
                  &toupper);

  std::string skel_export_macro = skel_export + "_Export";
  std::string skel_export_file = skel_name + "_export.h";

  // Generate the project.
  this->ctx_.project_
    << "project (" << skel_name << ") : avoids_ace_for_tao, ";

  const std::string skel_base = this->ctx_.traits_->skel_base_project ();

  if (!skel_base.empty ())
    this->ctx_.project_ << skel_base << ", ";

  this->ctx_.project_
    << "cuts_codegen_defaults {" << std::endl
    << "  sharedname   = " << skel_name << std::endl
    << "  dynamicflags = " << skel_export << "_BUILD_DLL" << std::endl
    << std::endl
    << "  after       += " << node.name_ << "_stub" << std::endl
    << "  libs        += " << node.name_ << "_stub" << std::endl
    << std::endl;

  if (!node.references_.empty ())
  {
    // Generate the dependencies for this project. This will be all
    // the client projects of the references for this node.
    this->ctx_.project_
      << std::endl
      << "  after +=";

    this->visited_nodes_.clear ();
    std::for_each (node.references_.begin (),
                   node.references_.end (),
                   generate_listing_t <skel_t> (this->ctx_.project_, this->visited_nodes_));

    // Generate the import libraries for this project. This will be
    // all client project of the references for this node. The will
    // also be the same as those specified in the "after" tag.

    this->ctx_.project_
      << std::endl
      << std::endl
      << "  libs  +=";

    this->visited_nodes_.clear ();
    std::for_each (node.references_.begin (),
                   node.references_.end (),
                   generate_listing_t <skel_t> (this->ctx_.project_, this->visited_nodes_));

    this->visited_nodes_.clear ();
    std::for_each (node.references_.begin (),
                   node.references_.end (),
                   generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

    this->ctx_.project_
      << std::endl;
  }

  this->ctx_.project_
    << std::endl
    // Generate the IDL files for this project.
    << "  IDL_Files {" << std::endl
    << std::endl
    << "  }" << std::endl
    << std::endl

    // Generate the source files for this project.
    << "  Source_Files {" << std::endl
    << "    " << node.name_ << "S.cpp" << std::endl
    << "  }" << std::endl
    << std::endl
    // Generate the header files for this project.
    << "  Header_Files {" << std::endl
    << "    " << node.name_ << "S.h" << std::endl
    << "  }" << std::endl
    << std::endl
    << "  Inline_Files {" << std::endl
    << "    " << node.name_ << "S.inl" << std::endl
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// generate_eidl_project
//
void CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate_eidl_project (const CUTS_BE_IDL_Node & node)
{
  std::string name (node.file_.name ());

  this->ctx_.project_
    << "project (" << name << "_EIDL_Gen) : ciaoidldefaults, cuts_codegen_defaults {" << std::endl
    << "  custom_only = 1" << std::endl
    << std::endl
    << "  after    += " << name << "_IDL_Gen " << name << "_iCCM_IDL_Gen";

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <eidl_t> (this->ctx_.project_, this->visited_nodes_));

  this->ctx_.project_
    << std::endl;

  std::string export_basename (name);
  std::transform (export_basename.begin (),
                  export_basename.end (),
                  export_basename.begin (),
                  &::toupper);

  this->ctx_.project_
    << std::endl
    << "  idlflags += -Wb,export_macro=" << export_basename << "_EXEC_Export \\" << std::endl
    << "              -Wb,export_include=" << name << "_exec_export.h \\" << std::endl
    << "              -Sa -Sal -SS" << std::endl
    << std::endl
    << "  IDL_Files {" << std::endl
    << "    " << name << "E.idl" << std::endl;

  this->ctx_.traits_->write_exec_idl_files (this->ctx_.project_, node);

  this->ctx_.project_
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// generate_exec_project
//
void CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate_exec_project (const CUTS_BE_IDL_Node & node)
{
  std::string name (node.file_.name ());
  std::string project_name = name + "_exec";

  std::string macro_basename (name);
  std::transform (macro_basename.begin (),
                  macro_basename.end (),
                  macro_basename.begin (),
                  &::toupper);

  this->ctx_.project_
    << "project (" << project_name << ") : ";

  const std::string skel_base = this->ctx_.traits_->skel_base_project ();

  if (!skel_base.empty ())
    this->ctx_.project_ << skel_base << ", ";

  this->ctx_.project_
    << "cuts_codegen_defaults {" << std::endl
    << "  sharedname    = " << project_name << std::endl
    << "  dynamicflags += " << macro_basename << "_EXEC_BUILD_DLL" << std::endl
    << std::endl
    << "  after += " << name << "_EIDL_Gen \\" << std::endl
    << "    " << name << "_stub";

  std::vector <const CUTS_BE_IDL_Node *> nodes (node.references_.size ());
  std::copy (node.references_.begin (),
             node.references_.end (),
             nodes.begin ());

  typedef bool (* FUNCTOR)(const CUTS_BE_IDL_Node *);

  std::vector <const CUTS_BE_IDL_Node *>::iterator last_iter =
    std::remove_if (nodes.begin (),
                    nodes.end (),
                    reinterpret_cast <FUNCTOR> (&CUTS_BE::has_interface));

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <exec_t> (this->ctx_.project_, this->visited_nodes_));

  this->ctx_.project_
    << std::endl
    << std::endl
    << "  libs  += " << name << "_stub";

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <exec_t> (this->ctx_.project_, this->visited_nodes_));

  this->ctx_.project_
    << std::endl
    << std::endl
    << "  Source_Files {" << std::endl
    << "    " << name << "EC.cpp" << std::endl;

  this->ctx_.traits_->write_exec_source_files (this->ctx_.project_, node);

  this->ctx_.project_
    << "  }" << std::endl
    << std::endl
    << "  Inline_Files {" << std::endl
    << "  }" << std::endl
    << std::endl
    << "  Header_Files {" << std::endl
    << "    " << name << "EC.h" << std::endl
    << "  }" << std::endl
    << std::endl
    << "  IDL_Files {" << std::endl
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// generate_svnt_project
//
void
CUTS_BE_Project_Write_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate_svnt_project (const CUTS_BE_IDL_Node & node)
{
  // Construct the names of the servant and skeleton project.
  std::string name (node.file_.name ());
  std::string svnt_project = name + "_svnt";

  // Create the export name for the project.
  std::string export_basename (svnt_project);
  std::transform (export_basename.begin (),
                  export_basename.end (),
                  export_basename.begin (),
                  &toupper);

  this->ctx_.project_
    << "project (" << svnt_project << ") : "
    << this->ctx_.traits_->svnt_base_project ()
    << ", cuts_codegen_defaults {" << std::endl
    << "  sharedname   = " << svnt_project << std::endl
    << "  dynamicflags = " << export_basename << "_BUILD_DLL" << std::endl
    << std::endl
    << "  after += "
    << name << "_exec "
    << name << "_stub "
    << name << "_skel";

  // Filter the nodes correctly.
  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <skel_t> (this->ctx_.project_, this->visited_nodes_));

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <exec_t> (this->ctx_.project_, this->visited_nodes_));

  this->ctx_.project_
    << std::endl
    << std::endl;

  // Clear the visited nodes so we can iterate over them once
  // more. This time we are generating the libs declaration.

  this->ctx_.project_
    << "  libs += "
    << name << "_exec "
    << name << "_stub "
    << name << "_skel";

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <stub_t> (this->ctx_.project_, this->visited_nodes_));

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <skel_t> (this->ctx_.project_, this->visited_nodes_));

  this->visited_nodes_.clear ();
  std::for_each (node.references_.begin (),
                 node.references_.end (),
                 generate_listing_t <exec_t> (this->ctx_.project_, this->visited_nodes_));

  this->ctx_.project_
    << std::endl
    << std::endl;

  this->ctx_.project_
    // Generate the source files
    << "  Source_Files {" << std::endl
    << "    " << name << "_svnt.cpp" << std::endl
    << "  }" << std::endl
    << std::endl
    // Generate the header files
    << "  Header_Files {" << std::endl
    << "    " << name << "_svnt.h" << std::endl
    << "  }" << std::endl
    << std::endl
    << "  Inline_Files {" << std::endl
    << std::endl
    << "  }" << std::endl
    << "  IDL_Files {" << std::endl
    << std::endl
    << "  }" << std::endl
    << "}" << std::endl
    << std::endl;
}

//
// CUTS_BE_Project_File_End_T
//
bool CUTS_BE_Project_File_End_T <CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::
generate (const CUTS_BE_IDL_Node & node)
{
  this->ctx_.project_
    << "// end of auto-generated project file" << std::endl;

  return true;
}

//
// CUTS_BE_Project_File_Close_T
//
void CUTS_BE_Project_File_Close_T <
CUTS_BE_CCM::Cpp::Context, CUTS_BE_IDL_Node>::generate (void)
{
  if (this->ctx_.project_.is_open ())
    this->ctx_.project_.close ();
}
