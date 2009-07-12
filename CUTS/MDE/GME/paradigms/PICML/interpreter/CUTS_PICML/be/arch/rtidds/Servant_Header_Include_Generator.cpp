// $Id$

#include "Servant_Header_Include_Generator.h"
#include "../../lang/cpp/Cpp.h"

#include "boost/bind.hpp"
#include "Uml.h"
#include <algorithm>

namespace CUTS_BE_RTIDDS
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
const PICML::ComponentImplementationContainer & container)
{
  std::set <PICML::MonolithicImplementation> monoimpls =
    container.MonolithicImplementation_kind_children ();

  std::for_each (monoimpls.begin (),
                 monoimpls.end (),
                 boost::bind (&PICML::MonolithicImplementation::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_MonolithicImplementation
//
void Servant_Header_Include_Generator::
Visit_MonolithicImplementation (const PICML::MonolithicImplementation & impl)
{
  PICML::Implements implements =  impl.dstImplements ();

  if (Udm::null != implements)
    implements.Accept (*this);
}

//
// Visit_Implements
//
void Servant_Header_Include_Generator::
Visit_Implements (const PICML::Implements & impl)
{
  PICML::ComponentRef ref = impl.dstImplements_end ();
  ref.Accept (*this);
}

//
// Visit_ComponentRef
//
void Servant_Header_Include_Generator::
Visit_ComponentRef (const PICML::ComponentRef & ref)
{
  PICML::Component component = ref.ref ();

  if (Udm::null != component)
    component.Accept (*this);
}

//
// Visit_Component
//
void Servant_Header_Include_Generator::
Visit_Component (const PICML::Component & component)
{
  PICML::MgaObject obj = component.parent ();

  if (PICML::Package::meta == obj.type ())
    PICML::Package::Cast (obj).Accept (*this);
  else
    PICML::File::Cast (obj).Accept (*this);
}

//
// Visit_Package
//
void Servant_Header_Include_Generator::
Visit_Package (const PICML::Package & package)
{
  PICML::MgaObject obj = package.parent ();

  if (PICML::Package::meta == obj.type ())
    PICML::Package::Cast (obj).Accept (*this);
  else
    PICML::File::Cast (obj).Accept (*this);
}

//
// Visit_File
//
void Servant_Header_Include_Generator::
Visit_File (const PICML::File & file)
{
  std::string name = file.name ();

  if (this->seen_.end () != this->seen_.find (name))
    return;

  this->seen_.insert (name);
  this->out_ << CUTS_BE_CPP::include (name + "S")
             << CUTS_BE_CPP::include ("RTIDDS_" + name + "C")
             << std::endl;
}

}
