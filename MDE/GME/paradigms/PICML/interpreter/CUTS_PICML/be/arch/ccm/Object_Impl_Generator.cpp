// $Id$

#include "Object_Impl_Generator.h"

#if !defined (__CUTS_INLINE__)
#include "Object_Impl_Generator.inl"
#endif  // !defined __CUTS_INLINE__

#include "boost/bind.hpp"
#include <algorithm>
#include "../../lang/cpp/Behavior_Generator.h"
#include "../../BE_Execution_Visitor_T.h"
#include "In_Type_Generator.h"
#include "Out_Type_Generator.h"
#include "InOut_Type_Generator.h"
#include "Retn_Type_Generator.h"
#include "game/mga/utils/Position_Sort_T.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{

template <typename T, typename SORTER>
struct collection_sort
{
public:
std::vector <T> operator () (GAME::Mga::Collection_T <T> & collection, const std::string & aspect) const
{
  typedef GAME::Mga::Position_Sort_T <T, SORTER> sorter_t;
  sorter_t sorter (aspect, SORTER ());

  std::vector <T> result;

  for (T item : collection)
    result.push_back (item);

  std::sort (result.begin (), result.end (), sorter);
  return result;
}
};

//
// generate
//
void Object_Impl_Generator::
generate (const PICML::Component_in component)
{
  this->component_name_ = component->name ();

  for (auto facet : component->get_ProvidedRequestPorts ())
    facet->accept (this);
}

//
// Visit_ProvidedRequestPort
//
void Object_Impl_Generator::
visit_ProvidedRequestPort (PICML::ProvidedRequestPort_in facet)
{
  PICML::Object obj = facet->refers_to_Provideable ();

  // Gather all the MultiInputAction elements in a map <name, MultiInputAction>
  // such that the MultiInputAction can be located when we visit the corresponding
  // OneWayOperation and TwoWayOperation to generates its behavior.
  for (auto input : facet->src_of_MultiInput ())
    this->build_inputs (input);

  std::string basetype (obj->name ());
  const std::string scope (CUTS_BE_CPP::scope (obj));
  this->impl_name_ = facet->name ();
  this->impl_name_ += "_i";
  this->impl_name_[0] = toupper (this->impl_name_[0]);

  // Generate the class definition
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment ("Object class implementation")
    << "typedef ::iCCM::FacetImpl_T < " << this->component_name_
    << ", CCM_" << basetype << "> " << this->impl_name_ << "_Base;"
    << "class " << this->impl_name_ << std::endl
    << ": public virtual " << this->impl_name_ << "_Base" << std::endl
    << "{"
    << "public:" << std::endl
    << "typedef " << this->impl_name_ << "_Base base_type;";

  // Generate the constructor
  this->ctx_.header_
    << "// Constructor" << std::endl
    << this->impl_name_ << " (" << this->component_name_ << " * parent);" << std::endl;

  this->ctx_.source_
    << CUTS_BE_CPP::function_header (this->impl_name_)
    << this->impl_name_ << "::" << this->impl_name_ << " (" << this->component_name_ << " * parent)" << std::endl
    << ": base_type (parent)"
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
  obj->accept (this);

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
build_inputs (PICML::MultiInput_in input)
{
  PICML::MultiInputAction action = input->dst_MultiInputAction ();
  this->actions_.insert (std::pair <std::string,
                                    PICML::MultiInputAction>
                         (action->name (), action));
}

//
// Visit_Object
//
void Object_Impl_Generator::
visit_Object (PICML::Object_in object)
{
  for (auto oneway : object->get_OnewayOperations ())
    oneway->accept (this);

  for (auto twoway : object->get_TwowayOperations ())
    twoway->accept (this);
}

//
// Visit_OnewayOperation
//
void Object_Impl_Generator::
visit_OnewayOperation (PICML::OnewayOperation_in oneway)
{
  std::string method_name (oneway->name ());

  // Write the prefix
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment (method_name)
    << "void ";
  this->ctx_.source_
    << CUTS_BE_CPP::function_header (method_name)
    << "void ";

  // Write the signature
  typedef collection_sort <PICML::ParameterType, GAME::Mga::PS_Left_To_Right> param_sorter;
  this->write_signature (method_name, param_sorter () (oneway->children <PICML::ParameterType> (), "InterfaceDefinition"));

  // Write the implementation
  this->ctx_.source_
    << "{";

  CUTS_BE_Execution_Visitor_T <CUTS_BE_CPP::Context> exec_visitor (this->ctx_);

  typedef std::map <std::string, PICML::MultiInputAction>::iterator Map_Iter;
  Map_Iter iter = this->actions_.find (oneway->name ());

  if (iter != this->actions_.end ())
    iter->second->accept (&exec_visitor);
  else
    this->ctx_.source_ << "// Unable to find MultiInputAction for operation " << oneway->name () << std::endl;

  this->ctx_.source_
    << "}";
}

//
// Visit_TwowayOperation
//
void Object_Impl_Generator::
visit_TwowayOperation (PICML::TwowayOperation_in twoway)
{
  std::string method_name (twoway->name ());

  // Write the prefix
  this->ctx_.header_
    << CUTS_BE_CPP::single_line_comment (method_name);
  this->ctx_.source_
    << CUTS_BE_CPP::function_header (method_name);

  // Write the signature
  typedef collection_sort <PICML::ParameterType, GAME::Mga::PS_Left_To_Right> param_sorter;

  // Get the return type
  if (twoway->has_ReturnType ())
    this->write_signature (twoway->get_ReturnType (), method_name, param_sorter () (twoway->children <PICML::ParameterType> (), "InterfaceDefinition"));
  else
  {
    this->ctx_.header_ << "void ";
    this->ctx_.source_ << "void ";
    this->write_signature (method_name, param_sorter () (twoway->children <PICML::ParameterType> (), "InterfaceDefinition"));
  }

  // Write the implementation
  this->ctx_.source_
    << "{";

  CUTS_BE_Execution_Visitor_T <CUTS_BE_CPP::Context> exec_visitor (this->ctx_);

  typedef std::map <std::string, PICML::MultiInputAction>::iterator Map_Iter;
  Map_Iter iter = this->actions_.find (twoway->name ());

  if (iter != this->actions_.end ())
    iter->second->accept (&exec_visitor);
  else
    this->ctx_.source_ << "// Unable to find MultiInputAction for operation " << twoway->name () << std::endl;

  this->ctx_.source_
    << "}";
}

//
// write_signature
//
void Object_Impl_Generator::
write_signature (PICML::ReturnType_in retn,
                 std::string & method_name,
                 std::vector <PICML::ParameterType> & params)
{
  // Generate the return value
  if (!retn->MemberType_is_nil ())
  {
    PICML::MemberType retn_member = retn->refers_to_MemberType ();
    Retn_Type_Generator retn_gen_h (this->ctx_.header_);
    Retn_Type_Generator retn_gen_cpp (this->ctx_.source_);
    retn_gen_h.generate (retn_member);
    retn_gen_cpp.generate (retn_member);
    this->ctx_.header_ << " ";
    this->ctx_.source_ << " ";
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
write_parameter (PICML::ParameterType_in param, bool comma_prefix)
{
  std::string type (param->meta ()->name ());
  PICML::MemberType member = param->refers_to_MemberType ();

  if (comma_prefix)
  {
    this->ctx_.header_ << ", ";
    this->ctx_.source_ << ", ";
  }

  // Write the appropriate type
  if (type == PICML::InParameter::impl_type::metaname)
  {
    In_Type_Generator in_gen_h (this->ctx_.header_);
    In_Type_Generator in_gen_cpp (this->ctx_.source_);
    in_gen_h.generate (member);
    in_gen_cpp.generate (member);
  }
  else if (type == PICML::OutParameter::impl_type::metaname)
  {
    Out_Type_Generator out_gen_h (this->ctx_.header_);
    Out_Type_Generator out_gen_cpp (this->ctx_.source_);
    out_gen_h.generate (member);
    out_gen_cpp.generate (member);
  }
  else if (type == PICML::InoutParameter::impl_type::metaname)
  {
    InOut_Type_Generator inout_gen_h (this->ctx_.header_);
    InOut_Type_Generator inout_gen_cpp (this->ctx_.source_);
    inout_gen_h.generate (member);
    inout_gen_cpp.generate (member);
  }

  // Name the variable
  this->ctx_.header_
    << " " << param->name ();
  this->ctx_.source_
    << " " << param->name ();
}

} // namespace CUTS_BE_CCM
} // namespace Cpp
