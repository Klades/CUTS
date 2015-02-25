// $Id$

#include "BE_CUTS_Project.h"
#include "modelgen.h"
#include "boost/bind.hpp"
#include <functional>
#include "game/mga/modelgen.h"

// Static decl.
static const char * CUTS_INTERFACE_DEFS = "CUTS_InterfaceDefinitions";

// Static decl.
static const char * CUTS_PREDEFINED_TYPES = "CUTS_PredefinedTypes";

// Static decl.
static const char * CUTS_IDL_FILENAME = "cuts/CUTS";

// Static decl.
static const char * CUTS_PACKAGE_NAME = "CUTS";

// Static decl.
static const char * CUTS_TESTING_SERVICE_OBJECT = "Testing_Service";

//
// CUTS_BE_CUTS_Project
//
CUTS_BE_CUTS_Project::CUTS_BE_CUTS_Project (void)
: valid_ (false),
  message_ ("project has not been initialized")
{

}

//
// ~CUTS_BE_CUTS_Project
//
CUTS_BE_CUTS_Project::~CUTS_BE_CUTS_Project (void)
{

}

//
// message
//
const std::string & CUTS_BE_CUTS_Project::message (void) const
{
  return this->message_;
}

//
// get_testing_service
//
const PICML::Object & CUTS_BE_CUTS_Project::get_testing_service (void) const
{
  return this->testing_service_;
}

//
// get_testing_service
//
const PICML::String & CUTS_BE_CUTS_Project::get_string_type (void) const
{
  return this->string_;
}

//
// is_valid
//
bool CUTS_BE_CUTS_Project::is_valid (void) const
{
  return this->valid_;
}

//
// Visit_RootFolder
//
void CUTS_BE_CUTS_Project::
Visit_RootFolder (const PICML::RootFolder_in root)
{
  this->valid_ = true;

  // Get the <CUTS_InterfaceDefinitions> folder. If we cannot
  // locate it, then we will create a new one.
  PICML::InterfaceDefinitions cutsidefs;

  if (GAME::create_if_not <GAME::Mga_t> (root, cutsidefs,
      GAME::contains <GAME::Mga_t> ([&] (PICML::InterfaceDefinitions curr) {
        return curr->name () == CUTS_INTERFACE_DEFS; })))
  {
    cutsidefs->name (CUTS_INTERFACE_DEFS);
  }

  cutsidefs->accept (this);

  // Get the CUTS_PredefinedTypes folder. If we cannot locate it, then we
  // will create a new one.
  PICML::PredefinedTypes ptypes;

  if (GAME::create_if_not <GAME::Mga_t> (root, ptypes,
      GAME::contains <GAME::Mga_t> ([&] (PICML::PredefinedTypes curr) {
        return curr->name () == CUTS_PREDEFINED_TYPES; })))
  {
    ptypes->name (CUTS_PREDEFINED_TYPES);
  }

  ptypes->accept (this);
}

//
// Visit_InterfaceDefinitions
//
void CUTS_BE_CUTS_Project::
Visit_InterfaceDefinitions (const PICML::InterfaceDefinitions_in idefs)
{
  // Locate the CUTS IDL file. If we are not able to find it then we
  // need to create a new one.
  if (GAME::create_if_not <GAME::Mga_t> (idefs, this->cuts_file_,
      GAME::contains <GAME::Mga_t> ([&] (PICML::File curr) {
        return curr->name () == CUTS_IDL_FILENAME; })))
  {
    this->cuts_file_->name (CUTS_IDL_FILENAME);
  }

  this->cuts_file_->accept (this);
}

//
// Visit_InterfaceDefinitions
//
void CUTS_BE_CUTS_Project::
Visit_PredefinedTypes (const PICML::PredefinedTypes_in ptypes)
{
  // Get a listing of all the strings in the predefined types.
  GAME::Mga::Collection_T <PICML::String> strings = ptypes->children <PICML::String> ();

  if (!strings.count ())
  {
    // Since we did not find a single string type, we need to create
    // one. It will be referenced by all auto generated elements.
    this->string_ = PICML::String::impl_type::_create (ptypes);
    this->string_->name ("String");
  }
  else
  {
    // So we found a string. We need to save it and delete the
    // all the other string types.
    bool first_string = true;

    for (auto string : strings)
    {
      if (first_string)
      {
        this->string_ = string;
        first_string = false;
      }
      else
        string->destroy ();
    }
  }
}

//
// Visit_File
//
void CUTS_BE_CUTS_Project::Visit_File (const PICML::File_in file)
{
  PICML::Package package;

  if (GAME::create_if_not <GAME::Mga_t> (file, package,
      GAME::contains <GAME::Mga_t> ([&] (PICML::Package curr) {
        return curr->name () == CUTS_PACKAGE_NAME; })))
  {
    package->name (CUTS_PACKAGE_NAME);
  }

  package->accept (this);
}

//
// Visit_Package
//
void CUTS_BE_CUTS_Project::Visit_Package (const PICML::Package_in package)
{
  if (GAME::create_if_not <GAME::Mga_t> (package, this->testing_service_,
      GAME::contains <GAME::Mga_t> ([&] (PICML::Object curr) {
        return curr->name () == CUTS_TESTING_SERVICE_OBJECT; })))
  {
    package->name (CUTS_TESTING_SERVICE_OBJECT);
  }
}

//
// get_cuts_file
//
const PICML::File & CUTS_BE_CUTS_Project::get_cuts_file (void) const
{
  return this->cuts_file_;
}
