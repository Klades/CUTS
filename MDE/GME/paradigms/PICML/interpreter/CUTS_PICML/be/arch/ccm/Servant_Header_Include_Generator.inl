// $Id$

#include "Servant_Header_Include_Generator.h"
#include "../../../lang/cpp/Cpp.h"

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
// visit_ComponentImplementationContainer
//
void Servant_Header_Include_Generator::
visit_ComponentImplementationContainer (PICML::ComponentImplementationContainer_in container)
{
  for (auto monoimpl : container->get_MonolithicImplementations ())
    monoimpl->accept (this);
}

//
// visit_MonolithicImplementation
//
void Servant_Header_Include_Generator::
visit_MonolithicImplementation (PICML::MonolithicImplementation_in impl)
{
  if (!impl->has_src_of_Implements ())
    return

  impl->src_of_Implements ()->accept (this);
}

//
// visit_Implements
//
void Servant_Header_Include_Generator::
visit_Implements (PICML::Implements_in impl)
{
  impl->dst_ComponentRef ()->accept (this);
}

//
// visit_ComponentRef
//
void Servant_Header_Include_Generator::
visit_ComponentRef (PICML::ComponentRef_in ref)
{
  if (ref->Component_is_nil ())
    return;

  ref->refers_to_Component ()->accept (this);
}

//
// visit_Component
//
void Servant_Header_Include_Generator::
visit_Component (PICML::Component_in component)
{
  component->parent ()->accept (this);
}

//
// visit_Package
//
void Servant_Header_Include_Generator::
visit_Package (PICML::Package_in package)
{
  package->parent ()->accept (this);
}

//
// visit_File
//
void Servant_Header_Include_Generator::
visit_File (PICML::File_in file)
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
