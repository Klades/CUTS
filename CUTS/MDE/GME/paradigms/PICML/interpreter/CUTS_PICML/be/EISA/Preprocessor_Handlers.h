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

#ifndef _CUTS_BE_EISA_PREPROCESSOR_HANDLERS_H_
#define _CUTS_BE_EISA_PREPROCESSOR_HANDLERS_H_

#include "Context.h"
#include "../BE_Preprocessor_Handlers_T.h"

/**
 * @struct CUTS_BE_Preprocessor_WorkerLibrary_T
 *
 * Updates the 'includes' for the current implementation.
 */
template < >
struct CUTS_BE_Preprocessor_WorkerLibrary_T <CUTS_BE_Eisa>
{
  static bool handle (CUTS_BE_Impl_Node *, const PICML::WorkerLibrary & lib);
};

/**
 * @struct CUTS_BE_Preprocessor_WorkerFile_T
 *
 * Preprocessor handler for the PICML::WorkerFile type.
 */
template < >
struct CUTS_BE_Preprocessor_WorkerFile_T <CUTS_BE_Eisa>
{
  static bool handle (CUTS_BE_Impl_Node * , const PICML::WorkerFile &);
};

#endif  // !defined _CUTS_BE_EISA_PREPROCESSOR_HANDLERS_H_
