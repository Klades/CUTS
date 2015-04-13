// -*- C++ -*-

//=============================================================================
/**
 * @file            Preprocessor_Handlers.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_COREDX_PREPROCESSOR_HANDLERS_H_
#define _CUTS_BE_COREDX_PREPROCESSOR_HANDLERS_H_

#include "../../../BE_Preprocessor_Handlers_T.h"
#include "Context.h"

/**
 * @struct CUTS_BE_Preprocessor_WorkerLibrary_T
 *
 * Updates the 'includes' for the current implementation.
 */
template < >
class CUTS_BE_Preprocessor_WorkerLibrary_T <CUTS_BE_CoreDX::Context>
{
public:
  CUTS_BE_Preprocessor_WorkerLibrary_T (void);

  virtual ~CUTS_BE_Preprocessor_WorkerLibrary_T (void);

  void generate (CUTS_BE_Impl_Node * node, const PICML::WorkerLibrary_in lib);
};

/**
 * @struct CUTS_BE_Preprocessor_WorkerFile_T
 *
 * Preprocessor handler for the PICML::WorkerFile type.
 */
template < >
class CUTS_BE_Preprocessor_WorkerFile_T <CUTS_BE_CoreDX::Context>
{
public:
  CUTS_BE_Preprocessor_WorkerFile_T (void);

  virtual ~CUTS_BE_Preprocessor_WorkerFile_T (void);

  void generate (CUTS_BE_Impl_Node * node, const PICML::WorkerFile_in);
};

#if defined (__CUTS_INLINE__)
#include "Preprocessor_Handlers.inl"
#endif

#endif  // !defined _CUTS_BE_COREDX_PREPROCESSOR_HANDLERS_H_
