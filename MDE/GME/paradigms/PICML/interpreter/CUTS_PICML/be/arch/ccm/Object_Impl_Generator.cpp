// $Id$

#include "Object_Impl_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Object_Impl_Generator.inl"
#endif  // !defined __CUTS_INLINE__

#include "boost/bind.hpp"
#include <algorithm>
#include "../../UDM_Utility_T.h"
#include "../../lang/cpp/Behavior_Generator.h"
#include "../../BE_Execution_Visitor_T.h"
#include "In_Type_Generator.h"
#include "Out_Type_Generator.h"
#include "InOut_Type_Generator.h"
#include "Retn_Type_Generator.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{

//
// generate
//
void Object_Impl_Generator::
generate (const PICML::Component & component)
{
  this->component_name_ = component.name ();
  std::vector <PICML::ProvidedRequestPort> facets =
    component.ProvidedRequestPort_kind_children ();

  std::for_each (facets.begin (),
                 facets.end (),
                 boost::bind (&PICML::ProvidedRequestPort::Accept,
                              _1,
                              boost::ref (*this)));
}

//
// Visit_ProvidedRequestPort
//
void Object_Impl_Generator::
Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort & facet)
{
  PICML::Object obj = PICML::Object::Cast (facet.ref ());

  if (obj == Udm::null)
    return;

  // Gather all the MultiInputAction elements in a map <name, MultiInputAction>
  // such that the MultiInputAction can be located when we visit the corresponding
  // OneWayOperation and TwoWayOperation to generates its behavior.
  typedef std::set <PICML::MultiInput> MultiInput_Set;
  MultiInput_Set inputs = facet.dstMultiInput ();
  std::for_each (inputs.begin (),
                 inputs.end (),
                 boost::bind (&Object_Impl_Generator::build_inputs,
                              this, _1));

  std::string basetype (obj.name ());
  const std::string scope (CUTS_BE_CPP::scope (obj));
  this->impl_name_ = facet.name ();
  this->impl_name_ += "_i";
  this->impl_name_[0] = toupper (this->impl_name_[0]);

  // Generate the class definition
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("Object class implementation")
    << "class " << this->impl_name_ << std::endl
    << ": public virtual " << scope << "CCM_" << basetype << "," << std::endl
    << "public virtual ::CORBA::LocalObject" << std::endl
    << "{"
    << "public:" << std::endl;

  // Generate the constructor
  this->ctx_.header_
    << "// Constructor" << std::endl
    << this->impl_name_ << " (" << this->component_name_ << " * parent);" << std::endl;

  this->ctx_.source_
    << CUTS_BE_CPP::function_header (this->impl_name_)
    << this->impl_name_ << "::" << this->impl_name_ << " (" << this->component_name_ << " * parent)" << std::endl
    << ": parent_ (parent)"
    << "{}";

  // Generate the destructor
  this->ctx_.header_
    << "// Destructor" << std::endl
    << "~" << this->impl_name_ << " (void);" << std::endl;

  this->ctx_.source_
    << CUTS_BE_CPP::function_header ("~" + this->impl_name_)
    << this->impl_name_ << "::~" << this->impl_name_ << " (void)" << std::endl
    << "{}";

  // Visit the objet
  obj.Accept (*this);

  // Close the class
  this->ctx_.header_
    << "private:" << std::endl
    << CUTS_BE_CPP::single_line_comment ("The parent component")
    << this->component_name_ << " * parent_;"
    << "};";
}

//
// build_inputs
//
void Object_Impl_Generator::
build_inputs (const PICML::MultiInput & input)
{
  PICML::MultiInputAction action = input.dstMultiInput_end ();
  this->actions_.insert (std::pair <std::string,
                                    PICML::MultiInputAction>
                         (action.name (), action));
}

//
// Visit_Object
//
void Object_Impl_Generator::
Visit_Object (const PICML::Object & object)
{
  typedef std::vector <PICML::OnewayOperation> OnewayOperation_Set;
  OnewayOperation_Set oneways = object.OnewayOperation_kind_children ();

  std::for_each (oneways.begin (),
                 oneways.end (),
                 boost::bind (&PICML::OnewayOperation::Accept,
                 _1, boost::ref (*this)));

  typedef std::vector <PICML::TwowayOperation> TwowayOperation_Set;
  TwowayOperation_Set twoways = object.TwowayOperation_kind_children ();

  std::for_each (twoways.begin (),
                 twoways.end (),
                 boost::bind (&PICML::TwowayOperation::Accept,
                 _1, boost::ref (*this)));
}

//
// Visit_OnewayOperation
//
void Object_Impl_Generator::
Visit_OnewayOperation (const PICML::OnewayOperation & oneway)
{
  std::string method_name (oneway.name ());

  // Get the parameters
  typedef std::vector <PICML::ParameterType> ParameterType_Set;
  ParameterType_Set params =
    oneway.ParameterType_kind_children_sorted (
    Sort_By_Position <PICML::ParameterType> ());

  // Write the prefix
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment (method_name)
    << "void ";
  this->ctx_.source_
    << CUTS_BE_CPP::function_header (method_name)
    << "void ";

  // Write the signature
  this->write_signature (method_name, params);

  // Write the implementation
  this->ctx_.source_
    << "{/*";

  CUTS_BE_Execution_Visitor_T <CUTS_BE_CPP::Context> exec_visitor (this->ctx_);
  typedef std::map <std::string, PICML::MultiInputAction>::iterator Map_Iter;
  Map_Iter iter = this->actions_.find (oneway.name ());
  if (iter != this->actions_.end ())
    iter->second.Accept (exec_visitor);
  else
    this->ctx_.source_ << "// Unable to find MultiInputAction for operation " << oneway.name () << std::endl;

  this->ctx_.source_
    << "*/}";
}

//
// Visit_TwowayOperation
//
void Object_Impl_Generator::
Visit_TwowayOperation (const PICML::TwowayOperation & twoway)
{
  std::string method_name (twoway.name ());

  // Get the return type
  PICML::ReturnType retn_type = twoway.ReturnType_child ();

  // Get the parameters
  typedef std::vector <PICML::ParameterType> ParameterType_Set;
  ParameterType_Set params =
    twoway.ParameterType_kind_children_sorted (
    Sort_By_Position <PICML::ParameterType> ());

  // Write the prefix
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment (method_name);
  this->ctx_.source_
    << CUTS_BE_CPP::function_header (method_name);

  // Write the signature
  this->write_signature (retn_type, method_name, params);

  // Write the implementation
  this->ctx_.source_
    << "{/*";

  CUTS_BE_Execution_Visitor_T <CUTS_BE_CPP::Context> exec_visitor (this->ctx_);
  typedef std::map <std::string, PICML::MultiInputAction>::iterator Map_Iter;
  Map_Iter iter = this->actions_.find (twoway.name ());
  if (iter != this->actions_.end ())
    iter->second.Accept (exec_visitor);
  else
    this->ctx_.source_ << "// Unable to find MultiInputAction for operation " << twoway.name () << std::endl;

  this->ctx_.source_
    << "*/}";
}

//
// write_signature
//
void Object_Impl_Generator::
write_signature (const PICML::ReturnType & retn,
                 std::string & method_name,
                 std::vector <PICML::ParameterType> & params)
{
  // Generate the return value
  if (retn != Udm::null)
  {
    PICML::MemberType retn_member = retn.ref ();
    if (retn_member != Udm::null)
    {
      Retn_Type_Generator retn_gen_h (this->ctx_.header_);
      Retn_Type_Generator retn_gen_cpp (this->ctx_.source_);
      retn_gen_h.generate (retn_member);
      retn_gen_cpp.generate (retn_member);
      this->ctx_.header_ << " ";
      this->ctx_.source_ << " ";
    }
  }
  else
  {
    this->ctx_.header_ << "void ";
    this->ctx_.source_ << "void ";
  }

  this->write_signature (method_name, params);
}

//
// write_signature
//
void Object_Impl_Generator::
write_signature (std::string & method_name,
                 std::vector <PICML::ParameterType> & params)
{
  // Generate the method name
  this->ctx_.header_
    << method_name << " (";
  this->ctx_.source_
    << this->impl_name_ << "::" << std::endl
    << method_name << " (";

  // Generate the parameters
  if (!params.empty ())
  {
    // Write first parameter without comma prefix
    std::vector <PICML::ParameterType>::iterator iter = params.begin ();
    this->write_parameter (*iter++, false);

    // Write the rest of the parameters with comma separators.
    std::for_each (iter,
                   params.end (),
                   boost::bind (&Object_Impl_Generator::write_parameter,
                                this, _1, true));
  }
  else
  {
    // Print the correct trailing macro for no arguments.
    this->ctx_.header_
      << "void";
    this->ctx_.source_
      << "void";
  }

  // Close the signature
  this->ctx_.header_
    << ");"  << std::endl;
  this->ctx_.source_
    << ")" << std::endl;
}
//
// write_parameter
//
void Object_Impl_Generator::
write_parameter (const PICML::ParameterType & param, bool comma_prefix)
{
  Uml::Class type = param.type ();
  PICML::MemberType member = param.ref ();

  if (comma_prefix)
  {
    this->ctx_.header_ << ", ";
    this->ctx_.source_ << ", ";
  }

  // Write the appropriate type
  if (type == PICML::InParameter::meta)
  {
    In_Type_Generator in_gen_h (this->ctx_.header_);
    In_Type_Generator in_gen_cpp (this->ctx_.source_);
    in_gen_h.generate (member);
    in_gen_cpp.generate (member);
  }
  else if (type == PICML::OutParameter::meta)
  {
    Out_Type_Generator out_gen_h (this->ctx_.header_);
    Out_Type_Generator out_gen_cpp (this->ctx_.source_);
    out_gen_h.generate (member);
    out_gen_cpp.generate (member);
  }
  else if (type == PICML::InoutParameter::meta)
  {
    InOut_Type_Generator inout_gen_h (this->ctx_.header_);
    InOut_Type_Generator inout_gen_cpp (this->ctx_.source_);
    inout_gen_h.generate (member);
    inout_gen_cpp.generate (member);
  }

  // Name the variable
  this->ctx_.header_
    << " " << param.name ();
  this->ctx_.source_
    << " " << param.name ();
}

} // namespace CUTS_BE_CCM
} // namespace Cpp
