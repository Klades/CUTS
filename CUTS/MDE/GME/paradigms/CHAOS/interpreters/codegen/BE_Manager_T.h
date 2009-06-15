// -*- C++ -*-

//=============================================================================
/**
 * @file      BE_Manager_T.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_MANAGER_T_H_
#define _CUTS_BE_MANAGER_T_H_

#include "BE_Manager.h"

/**
 * @class CUTS_BE_Manager_T
 *
 * Main entry point for the backend generator. Each backend generator
 * parameterizes this manager to customize how the points-of-visitation
 * and points-of-generation function.
 */
template <typename CONTEXT>
class CUTS_BE_Manager_T : public CUTS_BE_Manager
{
public:
  /// Type definition of the manager's context.
  typedef CONTEXT context_type;

  /// Default constructor.
  CUTS_BE_Manager_T (void);

  /// Destructor.
  virtual ~CUTS_BE_Manager_T (void);

  // Execute the manager on the root folder.
  virtual bool handle (const CHAOS::RootFolder & root);

private:
  /// The context for the manager.
  CONTEXT context_;
};

#include "BE_Manager_T.cpp"

#endif  // !defined _CUTS_BE_MANAGER_T_H_
