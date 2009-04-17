
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl SubApp
// ------------------------------
#ifndef SUBAPP_EXPORT_H
#define SUBAPP_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (SUBAPP_HAS_DLL)
#  define SUBAPP_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && SUBAPP_HAS_DLL */

#if !defined (SUBAPP_HAS_DLL)
#  define SUBAPP_HAS_DLL 1
#endif /* ! SUBAPP_HAS_DLL */

#if defined (SUBAPP_HAS_DLL) && (SUBAPP_HAS_DLL == 1)
#  if defined (SUBAPP_BUILD_DLL)
#    define SubApp_Export ACE_Proper_Export_Flag
#    define SUBAPP_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define SUBAPP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* SUBAPP_BUILD_DLL */
#    define SubApp_Export ACE_Proper_Import_Flag
#    define SUBAPP_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define SUBAPP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* SUBAPP_BUILD_DLL */
#else /* SUBAPP_HAS_DLL == 1 */
#  define SubApp_Export
#  define SUBAPP_SINGLETON_DECLARATION(T)
#  define SUBAPP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* SUBAPP_HAS_DLL == 1 */

// Set SUBAPP_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (SUBAPP_NTRACE)
#  if (ACE_NTRACE == 1)
#    define SUBAPP_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define SUBAPP_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !SUBAPP_NTRACE */

#if (SUBAPP_NTRACE == 1)
#  define SUBAPP_TRACE(X)
#else /* (SUBAPP_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define SUBAPP_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (SUBAPP_NTRACE == 1) */

#endif /* SUBAPP_EXPORT_H */

// End of auto generated file.
