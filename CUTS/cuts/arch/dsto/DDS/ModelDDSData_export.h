
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl ModelDDSData
// ------------------------------
#ifndef MODELDDSDATA_EXPORT_H
#define MODELDDSDATA_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (MODELDDSDATA_HAS_DLL)
#  define MODELDDSDATA_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && MODELDDSDATA_HAS_DLL */

#if !defined (MODELDDSDATA_HAS_DLL)
#  define MODELDDSDATA_HAS_DLL 1
#endif /* ! MODELDDSDATA_HAS_DLL */

#if defined (MODELDDSDATA_HAS_DLL) && (MODELDDSDATA_HAS_DLL == 1)
#  if defined (MODELDDSDATA_BUILD_DLL)
#    define ModelDDSData_Export ACE_Proper_Export_Flag
#    define MODELDDSDATA_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define MODELDDSDATA_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* MODELDDSDATA_BUILD_DLL */
#    define ModelDDSData_Export ACE_Proper_Import_Flag
#    define MODELDDSDATA_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define MODELDDSDATA_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* MODELDDSDATA_BUILD_DLL */
#else /* MODELDDSDATA_HAS_DLL == 1 */
#  define ModelDDSData_Export
#  define MODELDDSDATA_SINGLETON_DECLARATION(T)
#  define MODELDDSDATA_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* MODELDDSDATA_HAS_DLL == 1 */

// Set MODELDDSDATA_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (MODELDDSDATA_NTRACE)
#  if (ACE_NTRACE == 1)
#    define MODELDDSDATA_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define MODELDDSDATA_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !MODELDDSDATA_NTRACE */

#if (MODELDDSDATA_NTRACE == 1)
#  define MODELDDSDATA_TRACE(X)
#else /* (MODELDDSDATA_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define MODELDDSDATA_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (MODELDDSDATA_NTRACE == 1) */

#endif /* MODELDDSDATA_EXPORT_H */

// End of auto generated file.
