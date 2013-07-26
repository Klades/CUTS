// $Id$

#include "Servant_Context.h"
#include "be_extern.h"
#include "be_global.h"

#include "ast_component.h"
#include "ast_publishes.h"
#include "ast_emits.h"
#include "ast_uses.h"

#include "utl_identifier.h"

namespace iCCM
{
/**
 * @class Push_Method
 *
 * Visitor responsible for generating the push_ methods for a
 * publish/emit event port.
 */
class Push_Method : public Scope_Visitor
{
public:
  Push_Method (std::ofstream & hfile,
               std::ofstream & sfile,
               const ACE_CString & context)
    : hfile_ (hfile),
      sfile_ (sfile),
      context_ (context)
  {

  }

  virtual ~Push_Method (void)
  {

  }

  //
  // visit_publishes
  //
  virtual int visit_publishes (AST_Publishes * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    this->hfile_
      << "virtual void push_" << local_name << " (::" << field_type << " *ev);"
      << std::endl;

    this->sfile_
      << "void " << this->context_ << "::"
      << "push_" << local_name << " (::" << field_type << " *ev)"
      << "{"
      << "this->" << local_name << "_.send_event (ev);"
      << "}";

    return 0;
  }

  //
  // visit_emits
  //
  virtual int visit_emits (AST_Emits * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    this->hfile_
      << "virtual void push_" << local_name << " (::" << field_type << " *ev);"
      << std::endl;

    this->sfile_
      << "void " << this->context_ << "::"
      << "push_" << local_name << " (::" << field_type << " *ev)"
      << "{"
      << "this->" << local_name << "_.send_event (ev);"
      << "}";

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & context_;
};

/**
 * @class New_Event_Method
 *
 * Visitor responsible for generating the new_*_event methods for
 * a publish/emit event port. This method is an iCCM extension!
 */
class New_Event_Method : public Scope_Visitor
{
public:
  New_Event_Method (std::ofstream & hfile,
                    std::ofstream & sfile,
                    const ACE_CString & context)
    : hfile_ (hfile),
      sfile_ (sfile),
      context_ (context)
  {

  }

  virtual ~New_Event_Method (void)
  {

  }

  //
  // visit_publishes
  //
  virtual int visit_publishes (AST_Publishes * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    this->hfile_
      << "virtual ::" << field_type << " * new_" << local_name << "_event (void);"
      << std::endl;

    this->sfile_
      << "::" << field_type << " * "
      << this->context_ << "::new_" << local_name << "_event (void)"
      << "{"
      << "return this->" << local_name << "_.allocate_event ();"
      << "}";

    return 0;
  }

  //
  // visit_emits
  //
  virtual int visit_emits (AST_Emits * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * field_type = node->field_type ()->full_name ();

    this->hfile_
      << "virtual ::" << field_type << " * new_" << local_name << "_event (void);"
      << std::endl;

    this->sfile_
      << "::" << field_type << " * "
      << this->context_ << "::new_" << local_name << "_event (void)"
      << "{"
      << "return this->" << local_name << "_.allocate_event ();"
      << "}";

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & context_;
};

/**
 * @class New_Event_Method
 *
 * Visitor responsible for generating the new_*_event methods for
 * a publish/emit event port. This method is an iCCM extension!
 */
class Publisher_Variable : public Scope_Visitor
{
public:
  Publisher_Variable (std::ofstream & hfile,
                      std::ofstream & sfile)
    : hfile_ (hfile),
      sfile_ (sfile)
  {

  }

  virtual ~Publisher_Variable (void)
  {

  }

  //
  // visit_publishes
  //
  virtual int visit_publishes (AST_Publishes * node)
  {
    this->hfile_
      << be_global->get_publisher_table_template_typename ()
      << " < " << node->field_type ()->full_name () << " > "
      << node->local_name ()->get_string () << "_;"
      << std::endl;

    return 0;
  }

  //
  // visit_emits
  //
  virtual int visit_emits (AST_Emits * node)
  {
    this->hfile_
      << be_global->get_publisher_template_typename ()
      << " < " << node->field_type ()->full_name () << " > "
      << node->local_name ()->get_string () << "_;"
      << std::endl;

    return 0;
  }

  //
  // visit_uses
  //
  virtual int visit_uses (AST_Uses * node)
  {
    this->hfile_
      << "::iCCM::Receptacle_T < "
      << node->field_type ()->local_name ()->get_string ()
      << " > " << node->local_name ()->get_string () << "_;"
      << std::endl;

    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
};

/**
 * @class New_Event_Method
 *
 * Visitor responsible for generating the new_*_event methods for
 * a publish/emit event port. This method is an iCCM extension!
 */
class Publisher_Accessor_Method : public Scope_Visitor
{
public:
  Publisher_Accessor_Method (std::ofstream & hfile,
                             std::ofstream & sfile,
                             const ACE_CString & context)
    : hfile_ (hfile),
      sfile_ (sfile),
      context_ (context)
  {

  }

  virtual ~Publisher_Accessor_Method (void)
  {

  }

  virtual int visit_publishes (AST_Publishes * node)
  {
    const char * local_name = node->local_name ()->get_string ();

    this->hfile_
      << be_global->get_publisher_table_typename ()
      << " & get_" << local_name << "_publisher_table (void);"
      << std::endl;

    this->sfile_
      << be_global->get_publisher_table_typename ()
      << " & " << this->context_
      << "::get_" << local_name << "_publisher_table (void)"
      << "{"
      << "return this->" << local_name << "_;"
      << "}";

    return 0;
  }

  virtual int visit_emits (AST_Emits * node)
  {
    const char * local_name = node->local_name ()->get_string ();

    this->hfile_
      << be_global->get_publisher_typename ()
      << " & get_" << local_name << "_publisher (void);"
      << std::endl;

    this->sfile_
      << be_global->get_publisher_typename ()
      << " & " << this->context_
      << "::get_" << local_name << "_publisher (void)"
      << "{"
      << "return this->" << local_name << "_;"
      << "}";

    return 0;
  }

  virtual int visit_uses (AST_Uses * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    const char * type = node->uses_type ()->local_name ()->get_string ();

    this->hfile_
      << "virtual ::" << type << "_ptr "
      << "get_connection_" << local_name << " (void);" << std::endl
      << "iCCM::Receptacle & get_" << local_name << "_receptacle (void);" << std::endl;

    this->sfile_
      << "::" << type << "_ptr " << this->context_
      << "::get_connection_" << local_name << "(void)"
      << "{"
      << "return this->" << local_name << "_.get_connection ();"
      << "}"
      << "iCCM::Receptacle & " << this->context_
      << "::get_" << local_name << "_receptacle (void)"
      << "{"
      << "return this->" << local_name << "_;"
      << "}";
    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & context_;
};

//
// Servant_Context
//
Servant_Context::
Servant_Context (std::ofstream & hfile, std::ofstream & sfile)
: hfile_ (hfile),
  sfile_ (sfile)
{

}

//
// ~Servant_Context
//
Servant_Context::~Servant_Context (void)
{

}

//
// visit_component
//
int Servant_Context::visit_component (AST_Component * node)
{
  const ACE_CString context =
    ACE_CString (node->local_name ()->get_string ()) + "_Context";

  const ACE_CString servant =
    ACE_CString (node->local_name ()->get_string ()) + "_Servant";

  this->hfile_
    << "// Forward decl." << std::endl
    << "class " << servant << ";"
    << std::endl
    << "// Type definition of the servant type." << std::endl
    << "typedef "
    << be_global->get_context_typename ()
    << " < iCCM_" << context << ", " << servant << " > "
    << context << "_Base;"
    << std::endl
    << "/**" << std::endl
    << " * @class " << context << std::endl
    << " *" << std::endl
    << " * Implementation of the iCCM_" << context << " interface." << std::endl
    << " */" << std::endl
    << "class ";

  if (!be_global->svnt_export_macro_.empty ())
    this->hfile_ << be_global->svnt_export_macro_ << " ";

  this->hfile_
    << context << " :" << std::endl
    << "  public " << context << "_Base"
    << "{"
    << "public:" << std::endl
    << "// Default constructor" << std::endl
    << context << " (" << servant << " & parent);"
    << std::endl
    << "// Destructor" << std::endl
    << "virtual ~" << context << " (void);"
    << std::endl;

  this->sfile_
    << context << "::" << context << " (" << servant << " & parent)" << std::endl
    << ": " <<  context << "_Base (parent)"
    << "{"
    << "}"
    << context << "::~" << context << " (void)"
    << "{"
    << "}";

  // Generate the push_* methods.
  Push_Method push_method (this->hfile_, this->sfile_, context);
  push_method.visit_scope (node);

  // Generate the new_*_event methods.
  New_Event_Method new_event_method (this->hfile_, this->sfile_, context);
  new_event_method.visit_scope (node);

  Publisher_Accessor_Method pam (this->hfile_, this->sfile_, context);
  pam.visit_scope (node);

  this->hfile_
    << "private:" << std::endl;

  // Generate the emits/publisher member variables.
  Publisher_Variable pubs (this->hfile_, this->sfile_);
  pubs.visit_scope (node);

  this->hfile_
    << "};";

  return 0;
}

}
