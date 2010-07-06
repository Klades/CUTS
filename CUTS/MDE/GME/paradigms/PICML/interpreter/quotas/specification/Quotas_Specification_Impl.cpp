// $Id$

#include "stdafx.h"
#include "Quotas_Specification.h"
#include "Quotas_Specification_Impl.h"
#include "Quotas_Driver_Component.h"

#include "game/Attribute.h"
#include "game/Model.h"
#include "game/MetaModel.h"
#include "game/Project.h"
#include "game/Reference.h"
#include "game/ComponentEx.h"
#include "game/utils/modelgen.h"

#include "boost/bind.hpp"

#include <functional>

#include "game/be/ComponentEx_T.h"
#include "game/be/ComponentEx_Impl_T.h"
#include "game/be/Interpreter_Impl_Base.h"

typedef GAME::ComponentEx_Impl_T <Quotas_Specification_Impl> Quotas_Specification_Interpreter;
DECLARE_GAME_COMPONENT_EX (Quotas_Specification_Interpreter, Quotas_Specification);

const std::string Quotas_Specification_Impl::
Quotas_InterfaceDefinitions ("Quotas_InterfaceDefinitions");


namespace GAME
{

template <typename T>
class auto_stack
{
public:
  typedef typename T::value_type value_type;

  auto_stack (T & stack, value_type & value)
    : stack_ (stack),
      value_ (value)
  {
    // Save the current value on the stack.
    this->stack_.push (value);
  }

  ~auto_stack (void)
  {
    // Restore the value and pop the stack.
    this->value_ = this->stack_.top ();
    this->stack_.pop ();
  }

private:
  /// The target stack.
  T & stack_;

  /// The value to store/restore.
  value_type & value_;
};

}

namespace meta
{
  static const std::string InterfaceDefinitions ("InterfaceDefinitions");
  static const std::string File ("File");
  static const std::string Package ("Package");

  static const std::string Object ("Object");
  static const std::string Component ("Component");
  static const std::string ProvidedRequestPort ("ProvidedRequestPort");

  static const std::string Attribute ("Attribute");
  static const std::string ReadonlyAttribute ("ReadonlyAttribute");

  static const std::string AttributeMember ("AttributeMember");
}

namespace types
{
  typedef GAME::auto_stack < std::stack <GAME::Model> > auto_stack;
}

//
// Quotas_Specification_Impl
//
Quotas_Specification_Impl::Quotas_Specification_Impl (void)
: GAME::Interpreter_Impl_Base ("Quotas Specification", "Quotas.Interpreter.Specification", "PICML")
{

}

//
// ~Quotas_Specification_Impl
//
Quotas_Specification_Impl::~Quotas_Specification_Impl (void)
{
  if (this->configurator_)
    this->configurator_->resetConfiguration ();
}

//
// initialize
//
int Quotas_Specification_Impl::initialize (GAME::Project & project)
{
  // Get the set of add-ons for this project.
  std::vector <GAME::ComponentEx> addons;
  project.addon_components (addons);

  // Let's see if we can find the PICMLManager addon. It will have
  // the progid of MGA.AddOn.PICMLManager.
  static const std::string name ("MGA.AddOn.PICMLManager");

  std::vector <GAME::ComponentEx>::const_iterator 
    result = std::find_if (addons.begin (),
                           addons.end (),
                           boost::bind (std::equal_to <std::string> (),
                                        name,
                                        boost::bind (&GAME::ComponentEx::progid, _1)));
                                          
  if (result != addons.end ())
  {
    HRESULT hr = (*result)->QueryInterface (&this->configurator_);

    if (hr == S_OK)
    {
      this->configurator_->setImplementationFolder (L"Quotas_ComponentImplementations");
      this->configurator_->setArtifactFolder (L"Quotas_ImplmentationArtifacts");
    }
  }

  return 0;
}

//
// invoke_ex
//
int Quotas_Specification_Impl::
invoke_ex (GAME::Project & project,
           GAME::FCO & fco,
           std::vector <GAME::FCO> & selected,
           long flags)
{
  using GAME::Folder;

  try
  {
    // Start a new transaction.
    project.begin_transaction ();

    // Obtain the root folder for the project.
    Folder root_folder = project.root_folder ();

    std::vector <GAME::Folder> idl_folders;
    root_folder.children (meta::InterfaceDefinitions, idl_folders); 

    // First, make sure the target directory for the generated driver
    // components exists in the current model.
    if (GAME::create_if_not (root_folder,
                             meta::InterfaceDefinitions, 
                             idl_folders, 
                             this->quotas_idl_folder_,
        GAME::contains (boost::bind (std::equal_to <std::string> (),
                                     Quotas_InterfaceDefinitions,
                                     boost::bind (&Folder::name, _1)))))
    {
      this->quotas_idl_folder_.name (Quotas_InterfaceDefinitions);
    }

    // Now that we have the interface definition folder, let's go through
    // the remaining interface definitions and generate (1) the wrapper
    // component for each object or (2) the driver component (i.e., C')
    // for the current component.
    std::for_each (idl_folders.begin (),
                   idl_folders.end (),
                   boost::bind (&Quotas_Specification_Impl::visit_interface_definitions,
                                this,
                                _1));

    Quotas_Driver_Component_Generator driver_gen (this->quotas_idl_folder_);
    std::for_each (this->components_.begin (),
                   this->components_.end (),
                   boost::bind (&Quotas_Driver_Component_Generator::generate,
                                boost::ref (driver_gen),
                                _1));

    project.commit_transaction ();
  }
  catch (...)
  {
    project.abort_transaction ();
  }
    
  return 0;
}

//
// visit_interface_definitions
//
void Quotas_Specification_Impl::
visit_interface_definitions (const GAME::Folder & folder)
{
  if (folder.name () == Quotas_InterfaceDefinitions)
    return;

  // Select all the children File elements and visit them.
  std::vector <GAME::Model> files;
  folder.children (meta::File, files);

  std::for_each (files.begin (),
                 files.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_file,
                              this,
                              _1));
}

//
// visit_file
//
void Quotas_Specification_Impl::visit_file (const GAME::Model & file)
{
  // First, we need to create a Quotas file for the current file,
  // which is prefixed with the Quotas_ string. This is where all 
  // auto-generates specifications will be placed. 
  std::string quotas_filename ("Quotas_");
  quotas_filename.append (file.name ());

  // Let's create the Quotas file element if it does not already
  // exist in the model.
  std::vector <GAME::Model> quotas_files;
  this->quotas_idl_folder_.children (meta::File, quotas_files);

  if (GAME::create_if_not (this->quotas_idl_folder_,
                           meta::File, 
                           quotas_files, 
                           this->active_model_,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   quotas_filename,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    this->active_model_.name (quotas_filename);
  }

  // Set the correct path for the Quotas file.
  std::string path ("Quotas");
  const std::string current_path (file.attribute ("Path").string_value ());
  
  if (!current_path.empty ())
    path += "/" + current_path;

  this->active_model_.attribute ("Path").string_value (path);

  // Next, place all elements under the Quotas namespace. This 
  // is done by creating a package in the current file with the
  // name Quotas.
  const std::string Quotas ("Quotas");
  if (GAME::create_if_not (this->active_model_,
                           meta::Package, 
                           this->active_model_,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   Quotas,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    this->active_model_.name (Quotas);
  }

  // Now, visit the contents of the file we are processing.
  this->visit_file_package (file);
}

//
// visit_package
//
void Quotas_Specification_Impl::visit_package (const GAME::Model & package)
{
  types::auto_stack as (this->stack_, this->active_model_);
  std::string name (package.name ());

  // Create a duplicate package in the active model.
  if (GAME::create_if_not (this->active_model_,
                           meta::Package, 
                           this->active_model_,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   name,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    this->active_model_.name (name);
  }

  // Visit the contents of this package.
  this->visit_file_package (package);
}

//
// visit_file_package
//
void Quotas_Specification_Impl::
visit_file_package (const GAME::Model & model)
{
  // First, let's visit the interface elements in the model.
  std::vector <GAME::Model> objects;
  model.children (meta::Object, objects);

  std::for_each (objects.begin (),
                 objects.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_object,
                              this,
                              _1));

  // Now, let's visit the component elements in the model.

  // Finally, visit all the package elements in this model.
  std::vector <GAME::Model> packages;
  model.children (meta::Package, packages);

  std::for_each (packages.begin (),
                 packages.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_package,
                              this,
                              _1));
}

//
// visit_object
//
void Quotas_Specification_Impl::visit_object (const GAME::Model & object)
{
  types::auto_stack as (this->stack_, this->active_model_);

  // First, create a wrapper component for this object. Ideally,
  // we should be using the *Supports* object, but it is not clear
  // if DAnCE supports such capabilities. So, we are going to wrap
  // the object using a *provides* specification, and for each attribute
  // on the object, we are going to map it to an attribute on the 
  // wrapper component.
  const std::string name (object.name ());
  const std::string component_name = name + "_ComponentWrapper";
  const std::string facet_name = name + "_quotas";

  // Here we are creating the component wrapper for the object.
  if (GAME::create_if_not (this->active_model_,
                           meta::Component, 
                           this->active_model_,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   name,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    this->active_model_.name (name);
  }  

  // Store the component so we can create the driver's 
  // skeleton (or interface).
  this->components_.insert (this->active_model_);

  // Now, make the object a Facet on this component. The facet
  // will provide the specified interface (i.e., the object passed
  // into this method).
  GAME::Reference facet;

  if (GAME::create_if_not (this->active_model_,
                           meta::ProvidedRequestPort, 
                           facet,
      GAME::contains (boost::bind (std::equal_to <GAME::FCO> (),
                                   object,
                                   boost::bind (&GAME::Reference::refers_to, _1)))))
  {
    facet.refers_to (object);
  }  

  facet.name (facet_name);

  // Next, we need to mirror each of the attributes on the object
  // on this component. These should be delegated to the object
  // contained in this component.
  std::vector <GAME::Model> attrs;
  object.children (meta::Attribute, attrs);

  // [Attribute]
  std::for_each (attrs.begin (),
                 attrs.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_attribute_kind,
                              this,
                              _1));

  attrs.clear ();

  // [ReadonlyAttribute]
  object.children (meta::ReadonlyAttribute, attrs);
  std::for_each (attrs.begin (),
                 attrs.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_attribute_kind,
                              this,
                              _1));
}

//
// visit_attribute_kind
//
void Quotas_Specification_Impl::
visit_attribute_kind (const GAME::Model & attr)
{
  types::auto_stack as (this->stack_, this->active_model_);

  // Duplicate the attribute in the wrapper component.
  GAME::Model attribute;
  const std::string name (attr.name ());

  if (GAME::create_if_not (this->active_model_,
                           attr.meta ().name (), 
                           this->active_model_,
      GAME::contains (boost::bind (std::equal_to <std::string> (),
                                   name,
                                   boost::bind (&GAME::Model::name, _1)))))
  {
    this->active_model_.name (name);
  }  

  // We need to create the attribute member for the attribute.
  std::vector <GAME::Reference> members;
  attr.children (meta::AttributeMember, members);

  if (!members.empty ())
    this->visit_attribute_member (members.front ());
}

//
// visit_attribute_member
//
void Quotas_Specification_Impl::
visit_attribute_member (const GAME::Reference & member)
{
  using GAME::Reference;

  Reference attr_member;
  std::vector <Reference> members;
  this->active_model_.children (meta::AttributeMember, members);

  if (members.empty ())
    attr_member = Reference::_create (this->active_model_, meta::AttributeMember);
  else
    attr_member = members.front ();

  attr_member.refers_to (member.refers_to ());
}
