// -*- C++ -*-

//=============================================================================
/**
 * @file        Component_Impl_Generator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CPP_COMPONENT_IMPL_GENERATOR_H_
#define _CUTS_BE_CPP_COMPONENT_IMPL_GENERATOR_H_

#include <ostream>
#include "PICML/PICML.h"
#include "Cpp_export.h"

namespace CUTS_BE_CPP
{
/**
 * @class Base_Member_Init
 *
 * Visitor that is responsible for generating the base member
 * initialization section for a class.
 */
class CUTS_BE_CPP_Export Base_Member_Init : public PICML::Visitor
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       out           Target output stream.
   */
  Base_Member_Init (std::ostream & out);

  /// Destructor
  virtual ~Base_Member_Init (void);

  virtual void Visit_Component (const PICML::Component & component);

  virtual void Visit_Variable (const PICML::Variable & variable);

private:
  /// Target output stream.
  std::ostream & out_;
};

class CUTS_BE_CPP_Export Initialize_Entity : public PICML::Visitor
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       out           Target output stream.
   */
  Initialize_Entity (std::ostream & out);

  /// Destructor
  virtual ~Initialize_Entity (void);

  virtual void Visit_PeriodicEvent (const PICML::PeriodicEvent & periodic);

  virtual void Visit_InEventPort (const PICML::InEventPort & in);

private:
  /// Target output stream.
  std::ostream & out_;
};
};

#endif  // !define _CUTS_BE_CPP_COMPONENT_IMPL_GENERATOR_H_
