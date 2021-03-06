
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl HELLORECEIVER_IMPL
// ------------------------------
#ifndef HELLORECEIVER_IMPL_EXPORT_H
#define HELLORECEIVER_IMPL_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (HELLORECEIVER_IMPL_HAS_DLL)
#  define HELLORECEIVER_IMPL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && HELLORECEIVER_IMPL_HAS_DLL */

#if !defined (HELLORECEIVER_IMPL_HAS_DLL)
#  define HELLORECEIVER_IMPL_HAS_DLL 1
#endif /* ! HELLORECEIVER_IMPL_HAS_DLL */

#if defined (HELLORECEIVER_IMPL_HAS_DLL) && (HELLORECEIVER_IMPL_HAS_DLL == 1)
#  if defined (HELLORECEIVER_IMPL_BUILD_DLL)
#    define HELLORECEIVER_IMPL_Export ACE_Proper_Export_Flag
#    define HELLORECEIVER_IMPL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define HELLORECEIVER_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* HELLORECEIVER_IMPL_BUILD_DLL */
#    define HELLORECEIVER_IMPL_Export ACE_Proper_Import_Flag
#    define HELLORECEIVER_IMPL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define HELLORECEIVER_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* HELLORECEIVER_IMPL_BUILD_DLL */
#else /* HELLORECEIVER_IMPL_HAS_DLL == 1 */
#  define HELLORECEIVER_IMPL_Export
#  define HELLORECEIVER_IMPL_SINGLETON_DECLARATION(T)
#  define HELLORECEIVER_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* HELLORECEIVER_IMPL_HAS_DLL == 1 */

// Set HELLORECEIVER_IMPL_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (HELLORECEIVER_IMPL_NTRACE)
#  if (ACE_NTRACE == 1)
#    define HELLORECEIVER_IMPL_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define HELLORECEIVER_IMPL_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !HELLORECEIVER_IMPL_NTRACE */

#if (HELLORECEIVER_IMPL_NTRACE == 1)
#  define HELLORECEIVER_IMPL_TRACE(X)
#else /* (HELLORECEIVER_IMPL_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define HELLORECEIVER_IMPL_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (HELLORECEIVER_IMPL_NTRACE == 1) */

#endif /* HELLORECEIVER_IMPL_EXPORT_H */

// End of auto generated file.
