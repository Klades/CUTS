// $Id$

#include "stdafx.h"
#include "Quotas_Specification.h"
#include "Quotas_Specification_Impl.h"

#include "game/mga/Attribute.h"
#include "game/mga/Model.h"
#include "game/mga/MetaModel.h"
#include "game/mga/Project.h"
#include "game/mga/Reference.h"
#include "game/mga/ComponentEx.h"
#include "game/mga/Transaction.h"
#include "game/mga/modelgen.h"

#include "boost/bind.hpp"

#include "game/mga/component/ComponentEx_T.h"
#include "game/mga/component/ComponentEx_Impl_T.h"
#include "game/mga/component/Interpreter_Impl_Base.h"

#include <functional>

typedef GAME::Mga::ComponentEx_Impl_T <Quotas_Specification_Impl> Quotas_Specification_Interpreter;
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
  typedef GAME::auto_stack < std::stack <GAME::Mga::Model> > auto_stack;
}

//
// Quotas_Specification_Impl
//
Quotas_Specification_Impl::Quotas_Specification_Impl (void)
: GAME::Mga::Interpreter_Impl_Base ("Quotas Specification",
                                    "Quotas.Interpreter.Specification",
                                    "PICML")
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
int Quotas_Specification_Impl::initialize (GAME::Mga::Project project)
{
  // Get the set of add-ons for this project.
  std::vector <GAME::Mga::ComponentEx> addons;
  project.addon_components (addons);

  // Let's see if we can find the PICMLManager addon. It will have
  // the progid of MGA.AddOn.PICMLManager.
  static const std::string name ("MGA.AddOn.PICMLManager");

  std::vector <GAME::Mga::ComponentEx>::const_iterator
    result = std::find_if (addons.begin (),
                           addons.end (),
                           boost::bind (std::equal_to <std::string> (),
                                        name,
                                        boost::bind (&GAME::Mga::ComponentEx::impl_type::progid,
                                        boost::bind (&GAME::Mga::ComponentEx::get, _1))));

  if (result != addons.end ())
  {
    HRESULT hr = (*result)->impl ()->QueryInterface (&this->configurator_);

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
invoke_ex (GAME::Mga::Project project,
           GAME::Mga::FCO_in fco,
           std::vector <GAME::Mga::FCO> & selected,
           long flags)
{
  using GAME::Mga::Folder;
  using GAME::Mga_t;

  // Start a new transaction.
  GAME::Mga::Transaction t (project);

  // Obtain the root folder for the project.
  Folder root_folder = project.root_folder ();

  std::vector <Folder> idl_folders;
  root_folder->children (meta::InterfaceDefinitions, idl_folders);

  // First, make sure the target directory for the generated driver
  // components exists in the current model.
  if (GAME::create_if_not <Mga_t> (root_folder, meta::InterfaceDefinitions, this->quotas_idl_folder_,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              Quotas_InterfaceDefinitions,
                              boost::bind (&GAME::Mga::Folder::impl_type::name,
                                           boost::bind (&GAME::Mga::Folder::get, _1))))))
  {
    this->quotas_idl_folder_->name (Quotas_InterfaceDefinitions);
  }

  // Now that we have the interface definition folder, let's go through
  // the remaining interface definitions and generate the wrapper
  // component for each object
  std::for_each (idl_folders.begin (),
                 idl_folders.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_interface_definitions,
                              this,
                              _1));

  // Commit the transaction.
  t.commit ();

  return 0;
}

//
// visit_interface_definitions
//
void Quotas_Specification_Impl::
visit_interface_definitions (const GAME::Mga::Folder_in folder)
{
  if (folder->name () == Quotas_InterfaceDefinitions)
    return;

  // Select all the children File elements and visit them.
  std::vector <GAME::Mga::Model> files;
  folder->children (meta::File, files);

  std::for_each (files.begin (),
                 files.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_file,
                              this,
                              _1));
}

//
// visit_file
//
void Quotas_Specification_Impl::visit_file (const GAME::Mga::Model_in file)
{
  using GAME::Mga_t;

  // First, we need to create a Quotas file for the current file,
  // which is prefixed with the Quotas_ string. This is where all
  // auto-generates specifications will be placed.
  const std::string quotas_filename = "Quotas_" + file->name ();

  // Let's create the Quotas file element if it does not already
  // exist in the model.
  std::vector <GAME::Mga::Model> quotas_files;
  this->quotas_idl_folder_->children (meta::File, quotas_files);

  if (GAME::create_if_not <Mga_t> (this->quotas_idl_folder_, meta::File, this->active_model_,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              quotas_filename,
                              boost::bind (&GAME::Mga::Model::impl_type::name,
                                           boost::bind (&GAME::Mga::Model::get, _1))))))
  {
    this->active_model_->name (quotas_filename);
  }

  // Set the correct path for the Quotas file.
  std::string path ("Quotas");
  const std::string current_path = file->attribute ("Path")->string_value ();

  if (!current_path.empty ())
    path += "/" + current_path;

  this->active_model_->attribute ("Path")->string_value (path);

  // Next, place all elements under the Quotas namespace. This
  // is done by creating a package in the current file with the
  // name Quotas.
  const std::string Quotas ("Quotas");
  if (GAME::create_if_not <Mga_t> (this->active_model_, meta::Package, this->active_model_,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              Quotas,
                              boost::bind (&GAME::Mga::Model::impl_type::name,
                                           boost::bind (&GAME::Mga::Model::get, _1))))))
  {
    this->active_model_->name (Quotas);
  }

  // Now, visit the contents of the file we are processing.
  this->visit_file_package (file);
}

//
// visit_package
//
void Quotas_Specification_Impl::visit_package (const GAME::Mga::Model_in package)
{
  using GAME::Mga_t;

  types::auto_stack as (this->stack_, this->active_model_);
  const std::string name = package->name ();

  // Create a duplicate package in the active model.
  if (GAME::create_if_not <Mga_t> (this->active_model_, meta::Package, this->active_model_,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              name,
                              boost::bind (&GAME::Mga::Model::impl_type::name,
                                           boost::bind (&GAME::Mga::Model::get, _1))))))
  {
    this->active_model_->name (name);
  }

  // Visit the contents of this package.
  this->visit_file_package (package);
}

//
// visit_file_package
//
void Quotas_Specification_Impl::
visit_file_package (const GAME::Mga::Model_in model)
{
  // First, let's visit the interface elements in the model.
  std::vector <GAME::Mga::Model> objects;
  model->children (meta::Object, objects);

  std::for_each (objects.begin (),
                 objects.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_object,
                              this,
                              _1));

  // Now, let's visit the component elements in the model.

  // Finally, visit all the package elements in this model.
  std::vector <GAME::Mga::Model> packages;
  model->children (meta::Package, packages);

  std::for_each (packages.begin (),
                 packages.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_package,
                              this,
                              _1));
}

//
// visit_object
//
void Quotas_Specification_Impl::visit_object (const GAME::Mga::Model_in object)
{
  using GAME::Mga_t;
  types::auto_stack as (this->stack_, this->active_model_);

  // First, create a wrapper component for this object. Ideally,
  // we should be using the *Supports* object, but it is not clear
  // if DAnCE supports such capabilities. So, we are going to wrap
  // the object using a *provides* specification, and for each attribute
  // on the object, we are going to map it to an attribute on the
  // wrapper component.
  const std::string name = object->name ();
  const std::string component_name = name + "_ComponentFacade";
  const std::string facet_name = name + "_quotas";

  // Here we are creating the component wrapper for the object.
  if (GAME::create_if_not <Mga_t> (this->active_model_, meta::Component, this->active_model_,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              component_name,
                              boost::bind (&GAME::Mga::Model::impl_type::name,
                                           boost::bind (&GAME::Mga::Model::get, _1))))))
  {
    this->active_model_->name (component_name);
  }

  // Store the component so we can create the driver's
  // skeleton (or interface).
  this->components_.insert (this->active_model_);

  // Now, make the object a Facet on this component. The facet
  // will provide the specified interface (i.e., the object passed
  // into this method).
  GAME::Mga::Reference facet;

  if (GAME::create_if_not <Mga_t> (this->active_model_, meta::ProvidedRequestPort, facet,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <GAME::Mga::FCO> (),
                              object,
                              boost::bind (&GAME::Mga::Reference::impl_type::refers_to,
                                           boost::bind (&GAME::Mga::Reference::get, _1))))))
  {
    facet->refers_to (object);
  }

  facet->name (facet_name);

  // Next, we need to mirror each of the attributes on the object
  // on this component. These should be delegated to the object
  // contained in this component.
  std::vector <GAME::Mga::Model> attrs;
  object->children (meta::Attribute, attrs);

  // [Attribute]
  std::for_each (attrs.begin (),
                 attrs.end (),
                 boost::bind (&Quotas_Specification_Impl::visit_attribute_kind,
                              this,
                              _1));

  attrs.clear ();

  // [ReadonlyAttribute]
  object->children (meta::ReadonlyAttribute, attrs);
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
visit_attribute_kind (const GAME::Mga::Model_in attr)
{
  using GAME::Mga_t;

  types::auto_stack as (this->stack_, this->active_model_);

  // Duplicate the attribute in the wrapper component.
  GAME::Mga::Model attribute;
  const std::string name (attr->name ());
  const std::string attr_metaname (attr->meta ()->name ());

  if (GAME::create_if_not <Mga_t> (this->active_model_, attr_metaname, this->active_model_,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              name,
                              boost::bind (&GAME::Mga::Model::impl_type::name,
                                           boost::bind (&GAME::Mga::Model::get, _1))))))
  {
    this->active_model_->name (name);
  }

  // We need to create the attribute member for the attribute.
  std::vector <GAME::Mga::Reference> members;
  attr->children (meta::AttributeMember, members);

  if (!members.empty ())
    this->visit_attribute_member (members.front ());
}

//
// visit_attribute_member
//
void Quotas_Specification_Impl::
visit_attribute_member (const GAME::Mga::Reference_in member)
{
  using GAME::Mga::Reference;

  Reference attr_member;
  std::vector <Reference> members;
  this->active_model_->children (meta::AttributeMember, members);

  if (members.empty ())
    attr_member = Reference::impl_type::_create (this->active_model_, meta::AttributeMember);
  else
    attr_member = members.front ();

  attr_member->refers_to (member->refers_to ());
}
