// -*- C++ -*-

//=============================================================================
/**
 * @file        BE_Assembly_Generator_T.h
 *
 * Backend parser logic for generating assemblies
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_ASSEMBLY_GENERATOR_H_
#define _CUTS_BE_ASSEMBLY_GENERATOR_H_

#include "cuts/config.h"
#include "BE_Generators_T.h"

//=============================================================================
/**
 * @class CUTS_BE_Assembly_Generator_T
 *
 * Visitor that defines the parser logic for generating component
 * assemblies from the model. The parameter type specializaes the
 * different points-of-generation to dictate what metadata to
 * generate when invoked.
 */
//=============================================================================

template <typename T>
class CUTS_BE_Assembly_Generator_T : public PICML::Visitor
{
public:
  /// Default constructor.
  CUTS_BE_Assembly_Generator_T (void);

  /// Destructor.
  virtual ~CUTS_BE_Assembly_Generator_T (void);

  virtual void Visit_ComponentAssembly (
    const PICML::ComponentAssembly & assembly);

  virtual void Visit_Component (
    const PICML::Component & component);

  virtual void Visit_PublishConnector (
    const PICML::PublishConnector & connector);

  virtual void Visit_emit (
    const PICML::emit & emit);
};

#if defined (__CUTS_INLINE__)
#include "BE_Assembly_Generator_T.inl"
#endif

#include "BE_Assembly_Generator_T.cpp"

#endif
