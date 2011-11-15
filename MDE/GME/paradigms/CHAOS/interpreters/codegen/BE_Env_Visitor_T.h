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

#include "../../paradigms/CHAOS.h"
#include "BE_Generators_T.h"

/**
 * @class CUTS_BE_Env_Visitor_T
 *
 * Visitor for the environment portions of the model.
 */
template <typename CONTEXT>
class CUTS_BE_Env_Visitor_T : public CHAOS::Visitor
{
public:
  /// Constructor.
  CUTS_BE_Env_Visitor_T (CONTEXT & context);

  /// Destructor.
  virtual ~CUTS_BE_Env_Visitor_T (void);

protected:
  void Visit_Environment (
    const CHAOS::Environment & env);

  void Visit_MultiInput (
    const CHAOS::MultiInput & input);

  void Visit_MultiInputAction (
    const CHAOS::MultiInputAction & action);

private:
  /// Target context for generation.
  CONTEXT & context_;
};

#include "BE_Env_Visitor_T.cpp"

#endif  // !defined _CUTS_BE_ENV_VISITOR_H_
