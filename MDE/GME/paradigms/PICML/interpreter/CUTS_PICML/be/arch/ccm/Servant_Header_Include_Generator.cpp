// $Id$

#include "Servant_Header_Include_Generator.h"
#include "../../lang/cpp/Cpp.h"

#include <algorithm>

namespace CUTS_BE_OpenSplice
{
//
// Servant_Header_Include_Generator
//
Servant_Header_Include_Generator::
Servant_Header_Include_Generator (std::ostream & out)
: out_ (out)
{

}

//
// ~Servant_Header_Include_Generator
//
Servant_Header_Include_Generator::
~Servant_Header_Include_Generator (void)
{

}

//
// Visit_ComponentImplementationContainer
//
void Servant_Header_Include_Generator::
Visit_ComponentImplementationContainer (
const PICML::ComponentImplementationContainer_in container)
{
  for (auto monoimpl : container->get_MonolithicImplementations ())
    monoimpl->accept (this);
}

//
// Visit_MonolithicImplementation
//
void Servant_Header_Include_Generator::
Visit_MonolithicImplementation (const PICML::MonolithicImplementation_in impl)
{
  if (!impl->has_src_of_Implements ())
    return;

  impl->src_of_Implements ()->accept (this);
}

//
// Visit_Implements
//
void Servant_Header_Include_Generator::
Visit_Implements (const PICML::Implements_in impl)
{
  impl->dst_ComponentRef ()->accept (this);
}

//
// Visit_ComponentRef
//
void Servant_Header_Include_Generator::
Visit_ComponentRef (const PICML::ComponentRef_in ref)
{
  if (ref->Component_is_nil ())
    return;

  ref->refers_to_Component ()->accept (this);
}

//
// Visit_Component
//
void Servant_Header_Include_Generator::
Visit_Component (const PICML::Component_in component)
{
  component->parent ()->accept (this);
}

//
// Visit_Package
//
void Servant_Header_Include_Generator::
Visit_Package (const PICML::Package_in package)
{
  package->parent ()->accept (this);
}

//
// Visit_File
//
void Servant_Header_Include_Generator::
Visit_File (const PICML::File_in file)
{
  std::string name = file->name ();

  if (this->seen_.end () != this->seen_.find (name))
    return;

  this->seen_.insert (name);
  this->out_ << CUTS_BE_CPP::include (name + "S")
             << CUTS_BE_CPP::include ("OpenSplice_" + name + "C")
             << std::endl;
}

}
