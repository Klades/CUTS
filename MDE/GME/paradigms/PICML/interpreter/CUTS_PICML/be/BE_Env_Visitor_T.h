// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Env_Visitor_T.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_ENV_VISITOR_H_
#define _CUTS_BE_ENV_VISITOR_H_

#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include "BE_Generators_T.h"

/**
 * @class CUTS_BE_Env_Visitor_T
 *
 * Visitor for the environment portions of the model.
 */
template <typename CONTEXT>
class CUTS_BE_Env_Visitor_T : public PICML::Visitor
{
public:
  /// Type definition of the architecture for the code generator
  typedef typename CONTEXT::architecture_type architecture_type;

  /// Type definition of the behavior.
  typedef typename CONTEXT::behavior_type behavior_type;

  /// Constructor.
  CUTS_BE_Env_Visitor_T (CONTEXT & context);

  /// Destructor.
  virtual ~CUTS_BE_Env_Visitor_T (void);

protected:
  void Visit_Environment (
    const PICML::Environment_in env);

  void Visit_MultiInput (
    const PICML::MultiInput_in input);

  void Visit_MultiInputAction (
    const PICML::MultiInputAction_in action);

private:
  /// Target context for generation.
  CONTEXT & context_;
};

#include "BE_Env_Visitor_T.cpp"

#endif  // !defined _CUTS_BE_ENV_VISITOR_H_
