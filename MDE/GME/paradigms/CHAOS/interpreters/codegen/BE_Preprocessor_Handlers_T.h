// -*- C++ -*-

//=============================================================================
/**
 * @file          BE_Preprocessor_Handlers_T.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_PREPROCESSOR_HANDLERS_T_H_
#define _CUTS_BE_PREPROCESSOR_HANDLERS_T_H_

#include "../../paradigms/CHAOS.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

/**
 * @struct CUTS_BE_Preprocessor_WorkerFile_T
 *
 * Preprocessor handler for the PICML::WorkerFile type.
 */
template <typename T>
struct CUTS_BE_Preprocessor_WorkerFile_T
{
  static inline bool
    handle (CUTS_BE_Impl_Node * node, const CHAOS::WorkerFile &)
  {
    return false;
  }
};

/**
 * @struct CUTS_BE_Preprocessor_Worker_T
 *
 * Preprocessor handler for the PICML::Worker type.
 */
template <typename T>
struct CUTS_BE_Preprocessor_Worker_T
{
  static inline bool
    handle (CUTS_BE_Impl_Node *, const CHAOS::Worker &)
  {
    return false;
  }
};

/**
 * @struct CUTS_BE_Preprocessor_WorkerLibrary_T
 */
template <typename T>
struct CUTS_BE_Preprocessor_WorkerLibrary_T
{
  static inline bool
    handle (CUTS_BE_Impl_Node *, const CHAOS::WorkerLibrary &)
  {
    return false;
  }
};

#endif  // !defined _CUTS_BE_PREPROCESSOR_HANDLERS_T_H_
