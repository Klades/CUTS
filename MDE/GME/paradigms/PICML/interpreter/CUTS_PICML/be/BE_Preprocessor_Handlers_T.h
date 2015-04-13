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

#include "PICML/PICML.h"
#include "BE_Visitor_T.h"

// Forward decl.
struct CUTS_BE_Impl_Node;

/**
 * @class CUTS_BE_Preprocessor_Preprocess_Impl_T
 *
 * Preprocessor handler that determines if a monolithic implementation
 * should be processed. If the implementation is preprocessed, then its
 * informtio
 */
template <typename CONTEXT>
class CUTS_BE_Preprocessor_Preprocess_Impl_T
{
public:
  bool generate (const PICML::MonolithicImplementation_in impl);
};

/**
 * @class CUTS_BE_Preprocessor_WorkerFile_T
 *
 * Preprocessor handler for the PICML::WorkerFile type.
 */
template <typename CONTEXT>
class CUTS_BE_Preprocessor_WorkerFile_T
{
public:
  void generate (CUTS_BE_Impl_Node * node, const PICML::WorkerFile_in);
};

/**
 * @class CUTS_BE_Preprocessor_Worker_T
 *
 * Preprocessor handler for the PICML::Worker type.
 */
template <typename CONTEXT>
class CUTS_BE_Preprocessor_Worker_T
{
public:
  void generate (CUTS_BE_Impl_Node *, const PICML::Worker_in);
};

/**
 * @class CUTS_BE_Preprocessor_WorkerLibrary_T
 */
template <typename CONTEXT>
class CUTS_BE_Preprocessor_WorkerLibrary_T
{
public:
  void generate (CUTS_BE_Impl_Node *, const PICML::WorkerLibrary_in);
};

#if defined (__CUTS_INLINE__)
#include "BE_Preprocessor_Handlers_T.inl"
#endif

#include "BE_Preprocessor_Handlers_T.cpp"

#endif  // !defined _CUTS_BE_PREPROCESSOR_HANDLERS_T_H_
