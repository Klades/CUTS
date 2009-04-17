
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl ModelData
// ------------------------------
#ifndef MODELDATA_EXPORT_H
#define MODELDATA_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (MODELDATA_HAS_DLL)
#  define MODELDATA_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && MODELDATA_HAS_DLL */

#if !defined (MODELDATA_HAS_DLL)
#  define MODELDATA_HAS_DLL 1
#endif /* ! MODELDATA_HAS_DLL */

#if defined (MODELDATA_HAS_DLL) && (MODELDATA_HAS_DLL == 1)
#  if defined (MODELDATA_BUILD_DLL)
#    define ModelData_Export ACE_Proper_Export_Flag
#    define MODELDATA_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define MODELDATA_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* MODELDATA_BUILD_DLL */
#    define ModelData_Export ACE_Proper_Import_Flag
#    define MODELDATA_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define MODELDATA_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* MODELDATA_BUILD_DLL */
#else /* MODELDATA_HAS_DLL == 1 */
#  define ModelData_Export
#  define MODELDATA_SINGLETON_DECLARATION(T)
#  define MODELDATA_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* MODELDATA_HAS_DLL == 1 */

// Set MODELDATA_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (MODELDATA_NTRACE)
#  if (ACE_NTRACE == 1)
#    define MODELDATA_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define MODELDATA_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !MODELDATA_NTRACE */

#if (MODELDATA_NTRACE == 1)
#  define MODELDATA_TRACE(X)
#else /* (MODELDATA_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define MODELDATA_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (MODELDATA_NTRACE == 1) */

#endif /* MODELDATA_EXPORT_H */

// End of auto generated file.
