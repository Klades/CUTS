// $Id$

#include "Proto_File.h"

#include "Context.h"

#include "be_extern.h"
#include "be_global.h"

#include "ast_root.h"
#include "ast_structure.h"
#include "ast_module.h"
#include "ast_field.h"
#include "ast_enum.h"
#include "ast_string.h"

#include "utl_identifier.h"

#include <iomanip>
#include <iostream>

namespace iCCM
{

/**
 * @class Proto_Type
 *
 * Identifies the proper data type in Proto from the provided
 * IDL type.
 */
class Proto_Type : public Scope_Visitor
{
public:
  Proto_Type (ACE_CString & out)
  : out_ (out)
  {

  }

  virtual int visit_enum (AST_Enum * node)
  {
    this->out_ = node->full_name ();
    return 0;
  }

  virtual int visit_string (AST_String * node)
  {
    this->out_ = "string";
    return 0;
  }

  virtual int visit_structure (AST_Structure * node)
  {
    this->out_ = node->full_name ();
    return 0;
  }

  virtual int visit_predefined_type (AST_PredefinedType * node)
  {
    switch (node->pt ())
    {
    case AST_PredefinedType::PT_boolean:
      this->out_ = "bool";
      break;

    case AST_PredefinedType::PT_char:
    case AST_PredefinedType::PT_wchar:
    case AST_PredefinedType::PT_octet:
      this->out_ = "bytes";
      break;

    case AST_PredefinedType::PT_short:
    case AST_PredefinedType::PT_long:
      this->out_ = "sint32";
      break;

    case AST_PredefinedType::PT_ushort:
    case AST_PredefinedType::PT_ulong:
      this->out_ = "uint32";
      break;

    case AST_PredefinedType::PT_longlong:
      this->out_ = "sint64";
      break;

    case AST_PredefinedType::PT_ulonglong:
      this->out_ = "uint64";
      break;

    case AST_PredefinedType::PT_float:
      this->out_ = "float";
      break;

    case AST_PredefinedType::PT_longdouble:
    case AST_PredefinedType::PT_double:
      this->out_ = "double";
      break;
    }

    return 0;
  }

private:
  ACE_CString & out_;
};

//
// Proto_File
//
Proto_File::Proto_File (const ACE_CString & package)
: package_ (package),
  counter_ (0)
{

}

//
// ~Proto_File
//
Proto_File::~Proto_File (void)
{
  this->proto_file_.close ();
}

//
// init
//
int Proto_File::init (const ACE_CString & filename)
{
  this->proto_file_.open (filename.c_str ());

  if (!this->proto_file_.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to open %s\n"),
                       filename.c_str ()),
                       -1);

  this->proto_file_
    << "package " << this->package_ << ";" << std::endl
    << std::endl;

  return 0;
}

//
// visit_root
//
int Proto_File::visit_root (AST_Root * node)
{
  iCCM::QpidPB::Context * cdx_context = dynamic_cast <iCCM::QpidPB::Context *> (be_global);

  if (!cdx_context)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to convert Context\n")),
                       -1);

  this->init (cdx_context->get_proto_filename ());

  this->visit_scope (node);

  return 0;
}

//
// visit_module
//
int Proto_File::visit_module (AST_Module * node)
{
  ACE_CString local_name (node->local_name ()->get_string());

  // Only one package can be defined per file.  Recursively create new files
  // per module.
  Proto_File module_generator (this->package_ + "." + local_name);
  ACE_CString module_file (be_global->get_source_basename () + "." + local_name + ".proto");

  module_generator.init (module_file);
  module_generator.visit_scope (node);

  this->proto_file_
    << "import " << module_file << ";" << std::endl
    << std::endl;

  return 0;
}

//
// visit_structure
//
int Proto_File::visit_structure (AST_Structure * node)
{
  const char * local_name = node->local_name ()->get_string ();

  this->proto_file_
    << "message " << local_name << std::endl
    << "{" << std::endl;

  this->counter_ = 0;
  this->visit_scope (node);

  this->proto_file_
    << "}";

  return 0;
}

//
// visit_field
//
int Proto_File::visit_field (AST_Field * node)
{
  AST_Type * field_type = node->field_type ();
  const char * local_name = node->local_name ()->get_string ();
  const char * param_type = field_type->full_name ();

  ++this->counter_;

  // Figure out the datatype for the field for proto
  ACE_CString proto_type;
  Proto_Type pt (proto_type);
  field_type->ast_accept (&pt);

  if (!proto_type.empty ())
  {
    this->proto_file_
      << "  optional " << proto_type << " " << local_name
      << " = " << this->counter_ << ";" << std::endl;
    return 0;
  }
  else
  {
    this->proto_file_
      << "  optional " << param_type << " " << local_name
      << " = " << this->counter_ << ";" << std::endl;
  }

  return 0;
}

}
