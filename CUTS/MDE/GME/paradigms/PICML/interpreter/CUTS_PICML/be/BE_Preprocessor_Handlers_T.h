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
 * @class CUTS_BE_Preprocessor_WorkerFile_T
 *
 * Preprocessor handler for the PICML::WorkerFile type.
 */
template <typename CONTEXT>
class CUTS_BE_Preprocessor_WorkerFile_T
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       context         Context for the generator.
   */
  CUTS_BE_Preprocessor_WorkerFile_T (void);

  /// Destructor.
  virtual ~CUTS_BE_Preprocessor_WorkerFile_T (void);

  void generate (CUTS_BE_Impl_Node * node, const PICML::WorkerFile &);
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
  /**
   * Initializing constructor.
   *
   * @param[in]       context         Context for the generator.
   */
  CUTS_BE_Preprocessor_Worker_T (void);

  /// Destructor.
  virtual ~CUTS_BE_Preprocessor_Worker_T (void);

  void generate (CUTS_BE_Impl_Node *, const PICML::Worker &);
};

/**
 * @class CUTS_BE_Preprocessor_WorkerLibrary_T
 */
template <typename CONTEXT>
class CUTS_BE_Preprocessor_WorkerLibrary_T
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       context         Context for the generator.
   */
  CUTS_BE_Preprocessor_WorkerLibrary_T (void);

  /// Destructor.
  virtual ~CUTS_BE_Preprocessor_WorkerLibrary_T (void);

  void generate (CUTS_BE_Impl_Node *, const PICML::WorkerLibrary &);
};

#if defined (__CUTS_INLINE__)
#include "BE_Preprocessor_Handlers_T.inl"
#endif

#include "BE_Preprocessor_Handlers_T.cpp"

#endif  // !defined _CUTS_BE_PREPROCESSOR_HANDLERS_T_H_
