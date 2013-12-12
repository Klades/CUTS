// $Id$

#include "Provides_Svnt_Impl.h"

#include "ast_provides.h"
#include "ast_interface.h"
#include "ast_operation.h"
#include "ast_argument.h"
#include "ast_enum.h"
#include "ast_string.h"
#include "ast_structure.h"

#include "utl_identifier.h"
#include "utl_scope.h"

namespace iCCM
{

/**
 * @class Operation_Return_Type
 */
class Operation_Return_Type : public Scope_Visitor
{
public:
  Operation_Return_Type (std::ofstream & hfile,
                         std::ofstream & sfile)
    : hfile_ (hfile),
      sfile_ (sfile)
  {

  }

  virtual int visit_predefined_type (AST_PredefinedType * node)
  {
    this->hfile_ << node->full_name ();
    this->sfile_ << node->full_name ();
    return 0;
  }

  virtual int visit_enum (AST_Enum * node)
  {
    this->hfile_ << node->full_name ();
    this->sfile_ << node->full_name ();
    return 0;
  }

  virtual int visit_string (AST_String * node)
  {
    this->hfile_ << node->full_name ();
    this->sfile_ << node->full_name ();
    return 0;
  }

  virtual int visit_structure (AST_Structure * node)
  {
    this->hfile_ << node->full_name ();
    this->sfile_ << node->full_name ();

    if (node->size_type () == AST_Type::VARIABLE)
    {
      this->hfile_ << " *";
      this->sfile_ << " *";
    }
    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
};

/**
 * @class Operation_Argument_List
 */
class Operation_Argument_List : public Scope_Visitor
{
public:
  Operation_Argument_List (std::ofstream & hfile,
                           std::ofstream & sfile)
    : hfile_ (hfile),
      sfile_ (sfile),
      first_arg_ (true)
  {

  }

  virtual int visit_argument (AST_Argument * node)
  {
    const char * local_name = node->local_name ()->get_string ();

    if (this->first_arg_)
      this->first_arg_ = false;
    else
    {
      this->hfile_ << ", ";
      this->sfile_ << ", ";
    }

    this->direction_ = node->direction ();
    node->field_type ()->ast_accept (this);

    this->hfile_ << " " << local_name;
    this->sfile_ << " " << local_name;

    return 0;
  }

  virtual int visit_predefined_type (AST_PredefinedType * node)
  {
    this->hfile_ << node->full_name ();
    this->sfile_ << node->full_name ();

    switch (this->direction_)
    {
      case AST_Argument::dir_OUT:
      {
        this->hfile_ << "_out";
        this->sfile_ << "_out";
      }
    }

    return 0;
  }

  virtual int visit_enum (AST_Enum * node)
  {
    this->hfile_ << node->full_name ();
    this->sfile_ << node->full_name ();

    switch (this->direction_)
    {
      case AST_Argument::dir_OUT:
      {
        this->hfile_ << "_out";
        this->sfile_ << "_out";
      }
    }

    return 0;
  }

  virtual int visit_string (AST_String * node)
  {
    // Logic found in $TAO_ROOT/TAO_IDL/be/be_visitor_argument/arglist.cpp
    ACE_CString type;

    if (node->width () == (long) sizeof (char))
    {
      switch (this->direction_)
      {
        case AST_Argument::dir_IN:
          type = "const char *";
          break;
        case AST_Argument::dir_INOUT:
          type = "char *&";
          break;
        case AST_Argument::dir_OUT:
          type = "::CORBA::String_out";
          break;
      }
    }
    else
    {
      switch (this->direction_)
      {
        case AST_Argument::dir_IN:
          type = "const ::CORBA::WChar *";
          break;
        case AST_Argument::dir_INOUT:
          type = "::CORBA::WChar *&";
          break;
        case AST_Argument::dir_OUT:
          type = "::CORBA::WString_out";
          break;
      }
    }

    this->hfile_ << type.c_str ();
    this->sfile_ << type.c_str ();

    return 0;
  }

  virtual int visit_structure (AST_Structure * node)
  {
    ACE_CString prefix, suffix;
    switch (this->direction_)
    {
      case AST_Argument::dir_IN:
      {
        prefix = "const ";
        suffix = " &";
        break;
      }
      case AST_Argument::dir_OUT:
      {
        suffix = "_out";
      }
    }

    this->hfile_ << prefix.c_str () << node->full_name () << suffix.c_str ();
    this->sfile_ << prefix.c_str () << node->full_name () << suffix.c_str ();

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  AST_Argument::Direction direction_;
  bool first_arg_;
};

/**
 * @class Operation_Argument_List
 */
class Operation_Impl_Args : public Scope_Visitor
{
public:
  Operation_Impl_Args (std::ofstream & sfile)
    : sfile_ (sfile),
      first_arg_ (true)
  {

  }

  virtual int visit_argument (AST_Argument * node)
  {
    if (this->first_arg_)
      this->first_arg_ = false;
    else
      this->sfile_ << ", ";

    this->sfile_ << node->local_name ()->get_string ();
    return 0;
  }

private:
  std::ofstream & sfile_;
  bool first_arg_;
};

Provides_Svnt_Impl::Provides_Svnt_Impl (std::ofstream & hfile,
                                        std::ofstream & sfile,
                                        ACE_CString context)
: hfile_ (hfile),
  sfile_ (sfile),
  context_ (context)
{

}

Provides_Svnt_Impl::~Provides_Svnt_Impl (void)
{

}

//
// visit_scope
//
int Provides_Svnt_Impl::visit_scope (UTL_Scope * node)
{
  // Interfaces could be in a different IDL file, so we don't want to
  // skip them as the default visit_scope implementation does
  for (UTL_ScopeActiveIterator si (node, UTL_Scope::IK_decls);
       !si.is_done (); si.next ())
  {
    AST_Decl * d = si.item ();

    if (0 != d->ast_accept (this))
      return -1;
  }
  return 0;
}

//
// visit_provides
//
int Provides_Svnt_Impl::visit_provides (AST_Provides * node)
{
  const char * local_name = node->local_name ()->get_string ();
  const char * flat_name = node->flat_name ();
  const char * full_name = node->full_name ();
  const char * field_type = node->field_type ()->full_name ();

  this->servant_name_ = local_name;
  this->servant_name_ += "_svnt";
  this->servant_name_[0] = toupper (this->servant_name_[0]);

  // Class declaration
  this->hfile_
    << "class " << this->servant_name_ <<std::endl
    << "  : public virtual ::POA_" << field_type << "," << std::endl
    << "    public virtual ::PortableServer::ServantBase" << std::endl
    << "{"
    << "public:" << std::endl;

  // Constructor
  this->hfile_
    << "// Constructor" << std::endl
    << this->servant_name_ << " (" << this->context_ << " * ctx," << std::endl
    << "::CCM_" << field_type << "_ptr impl);"
    << std::endl;

  this->sfile_
    << this->servant_name_ << "::" << this->servant_name_ << " (" << this->context_ << " * ctx," << std::endl
    << "::CCM_" << field_type << "_ptr impl)" << std::endl
    << ": ctx_ (ctx)," << std::endl
    << "  impl_ (impl)" << std::endl
    << "{"
    << std::endl
    << "}";

  // Destructor
  this->hfile_
    << "// Destructor" << std::endl
    << "~" << this->servant_name_ << "(void);"
    << std::endl;

  this->sfile_
    << this->servant_name_ << "::~" << this->servant_name_ << " (void)" << std::endl
    << "{"
    << std::endl
    << "}";

  // Visit the type to generate the interface
  node->provides_type ()->ast_accept (this);

  this->hfile_
    << "private:" << std::endl
    << this->context_ << " * ctx_;"
    << "::CCM_" << field_type << "_ptr impl_;"
    << "};";

  return 0;
}

//
// visit_interface
//
int Provides_Svnt_Impl::visit_interface (AST_Interface * node)
{
  return this->visit_scope (node);
}

//
// visit_operation
//
int Provides_Svnt_Impl::visit_operation (AST_Operation * node)
{
  const char * local_name = node->local_name ()->get_string ();

  Operation_Return_Type return_type (this->hfile_, this->sfile_);
  node->return_type ()->ast_accept (&return_type);

  this->hfile_
    << " " << local_name << " (";

  this->sfile_
    << " " << this->servant_name_ << "::" << local_name << " (";

  // Build the signature
  int arg_count = node->argument_count ();
  if (arg_count == 0)
  {
    this->hfile_ << "void";
    this->sfile_ << "void";
  }
  else
  {
    Operation_Argument_List arg_list (this->hfile_, this->sfile_);
    arg_list.visit_scope (node);
  }

  this->hfile_ << ");";
  this->sfile_ << "){";

  // Start passthrough to impl
  if (arg_count != 0)
    this->sfile_ << "return ";

  this->sfile_ << "this->impl_->" << local_name << " (";

  // Build the passthrough args
  if (arg_count != 0)
  {
    Operation_Impl_Args impl_args (this->sfile_);
    impl_args.visit_scope (node);
  }

  this->sfile_ << ");}";

  return 0;
}

} // namespace iCCM
