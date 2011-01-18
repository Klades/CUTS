// $Id$

#include "stdafx.h"
#include "Quotas_Driver_Component.h"

#include "game/Model.h"
#include "game/Folder.h"
#include "game/Attribute.h"
#include "game/Reference.h"
#include "game/modelgen.h"

#include "boost/bind.hpp"

#include <functional>
#include <stack>

namespace meta
{
  static const std::string File ("File");
  static const std::string Package ("Package");
  static const std::string Component ("Component");

  static const std::string Object ("Object");
  static const std::string ProvidedRequestPort ("ProvidedRequestPort");
  static const std::string RequiredRequestPort ("RequiredRequestPort");
}

/**
 * @struct create_receptacle_t
 *
 * Functor that creates a receptacle for a given facet.
 */
struct create_receptacle_t
{
  create_receptacle_t (GAME::Model_in component)
    : component_ (component)
  {

  }

  void operator () (const GAME::Reference_in facet) const
  {
    using GAME::Mga_t;

    const std::string name = facet->name ();
    GAME::FCO refobj = facet->refers_to ();

    if (refobj.is_nil ())
      return;

    GAME::Reference receptacle;

    if (GAME::create_if_not <Mga_t> (this->component_, meta::RequiredRequestPort, receptacle,
        GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                                name,
                                boost::bind (&GAME::Reference::impl_type::name,
                                             boost::bind (&GAME::Reference::get, _1))))))
    {
      receptacle->name (name);
    }

    // Make sure the receptacle is referencing the correct
    // object interface.
    receptacle->refers_to (refobj);
  }

private:
  GAME::Model component_;
};

//
// Quotas_Driver_Component_Generator
//
Quotas_Driver_Component_Generator::
Quotas_Driver_Component_Generator (GAME::Folder_in folder)
: folder_ (folder)
{

}

//
// ~Quotas_Driver_Component_Generator
//
Quotas_Driver_Component_Generator::~Quotas_Driver_Component_Generator (void)
{

}

//
// generate
//
bool Quotas_Driver_Component_Generator::
generate (const GAME::Model_in component, GAME::Model & driver)
{
  using GAME::Mga_t;

  // Locate the file for this model element.
  fileinfo_t info;
  this->get_file_info (component, info);

  // Create a new file for the driver component.
  std::string driver_filename = info.file_->name () + "Driver";
  GAME::Model driver_file;

  if (GAME::create_if_not <Mga_t> (this->folder_, meta::File, driver_file,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              driver_filename,
                              boost::bind (&GAME::Model::impl_type::name,
                                           boost::bind (&GAME::Model::get, _1))))))
  {
    driver_file->name (driver_filename);
  }

  // Set the path of the driver file.
  std::string path = info.file_->attribute ("Path")->string_value ();
  driver_file->attribute ("Path")->string_value (path);

  // Duplicate package structure based on original component.
  GAME::Model package;
  this->duplicate_package_structure (info.package_, driver_file, package);

  // We need to create a driver component that will be used to
  // push data to the *real* component under test. It is to placed
  // under the current <package> variable. It should also have the
  // same name as the file that contains it.
  if (GAME::create_if_not <Mga_t> (package, meta::Component, driver,
      GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                              driver_filename,
                              boost::bind (&GAME::Model::impl_type::name,
                                           boost::bind (&GAME::Model::get, _1))))))
  {
    driver->name (driver_filename);
  }

  // The last step is to create a receptacle that is of the same
  // type that the driver component is testing.
  std::vector <GAME::Reference> facets;
  component->children (meta::ProvidedRequestPort, facets);

  std::for_each (facets.begin (),
                 facets.end (),
                 create_receptacle_t (driver));

  return true;
}

//
// get_file_info
//
void Quotas_Driver_Component_Generator::
get_file_info (const GAME::Model_in component, fileinfo_t & info)
{
  GAME::Object parent = component->parent ();
  std::stack <GAME::Object> scope;

  // Locate the File element while saving each of the Package
  // elements we encounter along the way.
  while (parent->meta ()->name () != meta::File)
  {
    scope.push (parent);
    parent = parent->parent ();
  }

  // Save the package to the info structure. This is done by
  // converting the scope stack to a vector.
  while (!scope.empty ())
  {
    info.package_.push_back (GAME::Model::_narrow (scope.top ()));
    scope.pop ();
  }

  // Save the file to the info structure.
  info.file_ = GAME::Model::_narrow (parent);
}

//
// duplicate_package_structure
//
void Quotas_Driver_Component_Generator::
duplicate_package_structure (const std::vector <GAME::Model> & packages,
                             const GAME::Model_in start,
                             GAME::Model & package)
{
  using GAME::Mga_t;

  std::vector <GAME::Model>::const_iterator
    iter = packages.begin (), iter_end = packages.end ();

  std::string name;

  // In the beginning, the final package is equal to the start
  // model. This will change if there are elements in the vector.
  package = start;

  for (; iter != iter_end; ++ iter)
  {
    // Save the name of the package.
    name = (*iter)->name ();

    // Create a new Package if it does not exist.
    if (GAME::create_if_not <Mga_t> (package, meta::Package, package,
        GAME::contains <Mga_t> (boost::bind (std::equal_to <std::string> (),
                                name,
                                boost::bind (&GAME::Model::impl_type::name,
                                             boost::bind (&GAME::Model::get, _1))))))
    {
      package->name (name);
    }
  }
}
