// $Id:

#include "Event_ObjectClass_Factory.h"

#include "be_extern.h"
#include "be_global.h"

#include "ast_module.h"
#include "ast_eventtype.h"
#include "ast_field.h"

#include "utl_identifier.h"
#include <iostream>

/**
 * @class Event_ObjectClass_Factory_Ctor
 */
class Event_ObjectClass_Factory_Ctor : public iCCM::Scope_Visitor
{
public:
  //
  // Event_ObjectClass_Factory_Ctor
  //
  Event_ObjectClass_Factory_Ctor (std::ofstream & hfile, std::ofstream & sfile, ACE_CString & class_name)
   : hfile_ (hfile),
     sfile_ (sfile),
     class_name_ (class_name)
  {

  }

  //
  // visit_eventtype
  //
  int visit_eventtype (AST_EventType * node)
  {
    this->hfile_
      << this->class_name_ << " (RTI::RTIambassador * rtiamb);";

    ACE_CString target_HLA_event;
    if (!be_global->get_wrapper_eventtype (node, target_HLA_event))
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("Invalid event encountered while generating ObjectClass_Factory ")
                  ACE_TEXT ("for ObjectClass [%s]"),
                  this->class_name_.c_str ()));
      return 1;
    }

    this->sfile_
      << this->class_name_ << "::" << std::endl
      << this->class_name_ << " (RTI::RTIambassador * rtiamb)" << std::endl
      << ": Portico_ObjectClass_Factory (rtiamb->getObjectClassHandle "
        << "(\"ObjectRoot." << target_HLA_event << "\"))";

    this->visit_scope (node);

    this->sfile_
      << "{" << std::endl
      << "}";

    return 0;
  }

  //
  // visit_field
  //
  int visit_field (AST_Field * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    this->sfile_
      << "," << std::endl
      << "  " << local_name << "_handle_ (rtiamb->getAttributeHandle (\"" << local_name
        << "\", handle_))";
    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString & class_name_;
};

/**
 * @class Event_ObjectClass_Factory_Create
 */
class Event_ObjectClass_Factory_Create : public iCCM::Scope_Visitor
{
public:
  //
  // Event_ObjectClass_Factory_Attributes
  //
  Event_ObjectClass_Factory_Create (std::ofstream & hfile, std::ofstream & sfile, ACE_CString & class_name)
   : hfile_ (hfile),
     sfile_ (sfile),
     class_name_ (class_name)
  {

  }

  //
  // visit_eventtype
  //
  int visit_eventtype (AST_EventType * node)
  {

    this->hfile_
      << "virtual void get_attributes (RTI::AttributeHandleSet & handles) const;";

    this->sfile_
      << "void " << this->class_name_ << "::" << std::endl
      << "get_attributes (RTI::AttributeHandleSet & handles) const"<< std::endl
      << "{";

    this->visit_scope (node);

    this->sfile_
      << "}";

    return 0;
  }

  //
  // visit_field
  //
  int visit_field (AST_Field * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    this->sfile_
      << "attrs.add (this->" << local_name << "_handle_);";
    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString & class_name_;
};

/**
 * @class Event_ObjectClass_Factory_Attributes
 */
class Event_ObjectClass_Factory_Attributes : public iCCM::Scope_Visitor
{
public:
  //
  // Event_ObjectClass_Factory_Attributes
  //
  Event_ObjectClass_Factory_Attributes (std::ofstream & hfile, std::ofstream & sfile, ACE_CString & class_name)
   : hfile_ (hfile),
     sfile_ (sfile),
     class_name_ (class_name)
  {

  }

  //
  // visit_eventtype
  //
  int visit_eventtype (AST_EventType * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    ACE_CString target_objectclass = ACE_CString (local_name) + "_ObjectClass";

    this->hfile_
      << "virtual " <<  target_objectclass << " * create (void);";

    this->sfile_
      << target_objectclass << " * "
      << this->class_name_ << "::" << std::endl
      << "create (void)" << std::endl
      << "{"
      << "return new " << target_objectclass << " (this->handle_";

    this->visit_scope (node);

    this->sfile_
      << ");"
      << "}";

    return 0;
  }

  //
  // visit_field
  //
  int visit_field (AST_Field * node)
  {
    const char * local_name = node->local_name ()->get_string ();
    this->sfile_
      << "," << std::endl
      << "this->" << local_name << "_handle_";
    return 0;
  }

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString & class_name_;
};

namespace iCCM
{

//
// Event_ObjectClass_Factory
//
Event_ObjectClass_Factory::Event_ObjectClass_Factory (std::ofstream & hfile, std::ofstream & sfile)
: hfile_ (hfile),
  sfile_ (sfile)
{

}

//
// ~Event_ObjectClass_Factory
//
Event_ObjectClass_Factory::~Event_ObjectClass_Factory (void)
{

}

//
// visit_module
//
int Event_ObjectClass_Factory::visit_module (AST_Module * node)
{
  return this->visit_scope (node);
}

//
// visit_eventtype
//
int Event_ObjectClass_Factory::visit_eventtype (AST_EventType * node)
{
  const char * local_name = node->local_name ()->get_string ();
  ACE_CString class_name = ACE_CString (local_name) + "_ObjectClass_Factory";
  ACE_CString target_objectclass = ACE_CString (local_name) + "_ObjectClass";

  // Define the class with constructor and destructor
  this->hfile_
    << "class ";

  if (!be_global->stub_export_macro_.empty ())
    this->hfile_ << be_global->stub_export_macro_ << " ";

  this->hfile_
    << class_name << " :" << std::endl
    << "  public ::iCCM::Portico_ObjectClass_Factory" << std::endl
    << "{"
    << "public:" << std::endl;

  // Generate the constructor
  Event_ObjectClass_Factory_Ctor ctor (this->hfile_, this->sfile_, class_name);
  node->ast_accept (&ctor);

  // Generate the destructor
  this->hfile_
    << "virtual ~" << class_name << " (void);";

  this->sfile_
    << class_name << "::~" << class_name << " (void)" << std::endl
    << "{" << std::endl
    << "}";

  // Generate the create method
  Event_ObjectClass_Factory_Create create (this->hfile_, this->sfile_, class_name);
  node->ast_accept (&create);

  // Generate the get_attributes method
  Event_ObjectClass_Factory_Attributes attributes (this->hfile_, this->sfile_, class_name);
  node->ast_accept (&attributes);

  this->hfile_
    << std::endl
    << "private:" << std::endl;

  // Generate the private attributehandles
  this->visit_scope (node);

  this->hfile_
    << "};";

  return 0;
}

//
// visit_field
//
int Event_ObjectClass_Factory::visit_field (AST_Field * node)
{
  const char * local_name = node->local_name ()->get_string ();

  this->hfile_
    << "RTI::AttributeHandle " << local_name << "_handle_;";
  return 0;
}

}
