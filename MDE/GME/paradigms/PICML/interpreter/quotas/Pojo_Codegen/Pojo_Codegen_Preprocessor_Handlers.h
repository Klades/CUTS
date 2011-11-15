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

#ifndef _POJO_CODEGEN_PREPROCESSOR_HANDLERS_H_
#define _POJO_CODEGEN_PREPROCESSOR_HANDLERS_H_

#include "be/BE_Preprocessor_Handlers_T.h"
#include "Pojo_Codegen_Ctx.h"

/**
 * @class CUTS_BE_Preprocessor_Preprocess_Impl_T
 */
template < >
class CUTS_BE_Preprocessor_Preprocess_Impl_T <Quotas::Pojo::Codegen::Context>
{
public:
  bool generate (const PICML::MonolithicImplementation & impl);
};

/**
 * @class CUTS_BE_Preprocessor_Worker_T
 */
template < >
class CUTS_BE_Preprocessor_Worker_T <Quotas::Pojo::Codegen::Context>
{
public:
  void generate (CUTS_BE_Impl_Node * node, const PICML::Worker &);
};

/**
 * @class CUTS_BE_Preprocessor_WorkerLibrary_T
 */
template < >
class CUTS_BE_Preprocessor_WorkerLibrary_T <Quotas::Pojo::Codegen::Context>
{
public:
  void generate (CUTS_BE_Impl_Node * node, const PICML::WorkerLibrary & lib);
};

#if defined (__CUTS_INLINE__)
#include "Pojo_Codegen_Preprocessor_Handlers.inl"
#endif

#endif  // !defined _POJO_CODEGEN_PREPROCESSOR_HANDLERS_H_
