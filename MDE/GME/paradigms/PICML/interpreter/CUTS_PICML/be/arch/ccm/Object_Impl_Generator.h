// -*- C++ -*-

//==============================================================================
/**
 *  @file        Object_Impl_Generator.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _CUTS_BE_CCM_CPP_OBJECT_IMPL_GENERATOR_H_
#define _CUTS_BE_CCM_CPP_OBJECT_IMPL_GENERATOR_H_

#include "../../BE_Generators_T.h"
#include "PICML/PICML.h"
#include "CCM.h"

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @class Object_Impl_Generator
 *
 * Visitor for generating object implementations
 */
class CUTS_BE_CCM_Export Object_Impl_Generator
  : public CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor>
{
public:
  typedef CUTS_BE_Visitor_T <CUTS_BE_CCM::Cpp::Context, PICML::Visitor> visitor_type;

  /// Constructor.
  Object_Impl_Generator (CUTS_BE_CCM::Cpp::Context & context);

  /// Destructor.
  virtual ~Object_Impl_Generator (void);

  // generate
  void generate (const PICML::Component & component);

  // Visit methods
  virtual void Visit_ProvidedRequestPort (const PICML::ProvidedRequestPort & facet);
  virtual void Visit_Object (const PICML::Object & object);
  virtual void Visit_OnewayOperation (const PICML::OnewayOperation & oneway);
  virtual void Visit_TwowayOperation (const PICML::TwowayOperation & twoway);

private:
  // Helper for gathering input actions
  void build_inputs (const PICML::MultiInput & input);

  // Helper for writing signatures
  void write_signature (const PICML::ReturnType & retn,
                        std::string & method_name,
                        std::vector <PICML::ParameterType> & params);

  // Overload for when there is no return type
  void write_signature (std::string & method_name,
                        std::vector <PICML::ParameterType> & params);

  // Helper for writing parameters
  void write_parameter (const PICML::ParameterType & param, bool comma_prefix);

  // The parent component class name
  std::string component_name_;

  // The objects implementation name
  std::string impl_name_;

  // Map of MultiInput names and MultiInputActions
  std::map <std::string, PICML::MultiInputAction> actions_;
};

} // namespace CUTS_BE_CCM
} // namespace Cpp

#if defined (__CUTS_INLINE__)
#include "Object_Impl_Generator.inl"
#endif  // !defined __CUTS_INLINE__

#endif  // _CUTS_BE_CCM_CPP_OBJECT_IMPL_GENERATOR_H_
