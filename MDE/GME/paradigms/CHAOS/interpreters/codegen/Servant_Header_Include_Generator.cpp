// $Id$

#include "StdAfx.h"
#include "Servant_Header_Include_Generator.h"
#include "cpp/Cpp.h"

#include "boost/bind.hpp"
#include "Uml.h"
#include <algorithm>

namespace CUTS_CHAOS
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
const CHAOS::ComponentImplementationContainer & container)
{
  std::set <CHAOS::MonolithicImplementation> monoimpls =
    container.MonolithicImplementation_kind_children ();

  for (auto monoimpl : monoimpls)
    monoimpl.Accept (*this);
}

//
// Visit_MonolithicImplementation
//
void Servant_Header_Include_Generator::
Visit_MonolithicImplementation (const CHAOS::MonolithicImplementation & impl)
{
  CHAOS::Implements implements =  impl.dstImplements ();

  if (Udm::null != implements)
    implements.Accept (*this);
}

//
// Visit_Implements
//
void Servant_Header_Include_Generator::
Visit_Implements (const CHAOS::Implements & impl)
{
  CHAOS::ComponentRef ref = impl.dstImplements_end ();
  ref.Accept (*this);
}

//
// Visit_ComponentRef
//
void Servant_Header_Include_Generator::
Visit_ComponentRef (const CHAOS::ComponentRef & ref)
{
  CHAOS::Component component = ref.ref ();

  if (Udm::null != component)
    component.Accept (*this);
}

//
// Visit_Component
//
void Servant_Header_Include_Generator::
Visit_Component (const CHAOS::Component & component)
{
  CHAOS::MgaObject obj = component.parent ();

  if (CHAOS::Package::meta == obj.type ())
    CHAOS::Package::Cast (obj).Accept (*this);
  else
    CHAOS::File::Cast (obj).Accept (*this);
}

//
// Visit_Package
//
void Servant_Header_Include_Generator::
Visit_Package (const CHAOS::Package & package)
{
  CHAOS::MgaObject obj = package.parent ();

  if (CHAOS::Package::meta == obj.type ())
    CHAOS::Package::Cast (obj).Accept (*this);
  else
    CHAOS::File::Cast (obj).Accept (*this);
}

//
// Visit_File
//
void Servant_Header_Include_Generator::
Visit_File (const CHAOS::File & file)
{
  std::string name = file.name ();

  if (this->seen_.end () != this->seen_.find (name))
    return;

  this->seen_.insert (name);
  this->out_ << CUTS_BE_CPP::include (name + "S")
             << CUTS_BE_CPP::include ("OpenSplice_" + name + "C")
             << CUTS_BE_CPP::include ("TCPIP_" + name + "C")
             << std::endl;
}

}
