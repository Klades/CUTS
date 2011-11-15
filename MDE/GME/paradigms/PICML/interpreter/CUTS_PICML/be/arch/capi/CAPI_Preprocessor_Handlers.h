// -*- C++ -*-

//=============================================================================
/**
 * @file        CAPI_Preprocess_Handlers.h
 *
 * Preprocessor handlers for the CAPI backend generator
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CAPI_PREPROCESSOR_HANDLERS_H_
#define _CUTS_BE_CAPI_PREPROCESSOR_HANDLERS_H_

#include "CAPI_Ctx.h"
#include "../../BE_Preprocessor_Handlers_T.h"

/**
 * @struct CUTS_BE_Preprocessor_Worker_T
 *
 * Updates the 'imports' for the current implementation.
 */
template < >
class CUTS_BE_Preprocessor_Worker_T <CUTS_BE_Capi::Context>
{
public:
  CUTS_BE_Preprocessor_Worker_T (void);

  virtual ~CUTS_BE_Preprocessor_Worker_T (void);

  void generate (CUTS_BE_Impl_Node * node, const PICML::Worker &);
};

/**
 * @struct CUTS_BE_Preprocessor_WorkerLibrary_T
 */
template < >
class CUTS_BE_Preprocessor_WorkerLibrary_T <CUTS_BE_Capi::Context>
{
public:
  CUTS_BE_Preprocessor_WorkerLibrary_T (void);

  virtual ~CUTS_BE_Preprocessor_WorkerLibrary_T (void);

  void generate (CUTS_BE_Impl_Node * node,
                 const PICML::WorkerLibrary & lib);
};

#if defined (__CUTS_INLINE__)
#include "CAPI_Preprocessor_Handlers.inl"
#endif

#endif  // !defined _CUTS_BE_CAPI_PREPROCESSOR_HANDLERS_H_
