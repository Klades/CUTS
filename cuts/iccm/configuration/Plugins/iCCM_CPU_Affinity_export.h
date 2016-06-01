
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl ICCM_CPU_AFFINITY
// ------------------------------
#ifndef ICCM_CPU_AFFINITY_EXPORT_H
#define ICCM_CPU_AFFINITY_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (ICCM_CPU_AFFINITY_HAS_DLL)
#  define ICCM_CPU_AFFINITY_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && ICCM_CPU_AFFINITY_HAS_DLL */

#if !defined (ICCM_CPU_AFFINITY_HAS_DLL)
#  define ICCM_CPU_AFFINITY_HAS_DLL 1
#endif /* ! ICCM_CPU_AFFINITY_HAS_DLL */

#if defined (ICCM_CPU_AFFINITY_HAS_DLL) && (ICCM_CPU_AFFINITY_HAS_DLL == 1)
#  if defined (ICCM_CPU_AFFINITY_BUILD_DLL)
#    define ICCM_CPU_AFFINITY_Export ACE_Proper_Export_Flag
#    define ICCM_CPU_AFFINITY_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define ICCM_CPU_AFFINITY_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* ICCM_CPU_AFFINITY_BUILD_DLL */
#    define ICCM_CPU_AFFINITY_Export ACE_Proper_Import_Flag
#    define ICCM_CPU_AFFINITY_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define ICCM_CPU_AFFINITY_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* ICCM_CPU_AFFINITY_BUILD_DLL */
#else /* ICCM_CPU_AFFINITY_HAS_DLL == 1 */
#  define ICCM_CPU_AFFINITY_Export
#  define ICCM_CPU_AFFINITY_SINGLETON_DECLARATION(T)
#  define ICCM_CPU_AFFINITY_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* ICCM_CPU_AFFINITY_HAS_DLL == 1 */

// Set ICCM_CPU_AFFINITY_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (ICCM_CPU_AFFINITY_NTRACE)
#  if (ACE_NTRACE == 1)
#    define ICCM_CPU_AFFINITY_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define ICCM_CPU_AFFINITY_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !ICCM_CPU_AFFINITY_NTRACE */

#if (ICCM_CPU_AFFINITY_NTRACE == 1)
#  define ICCM_CPU_AFFINITY_TRACE(X)
#else /* (ICCM_CPU_AFFINITY_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define ICCM_CPU_AFFINITY_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (ICCM_CPU_AFFINITY_NTRACE == 1) */

#endif /* ICCM_CPU_AFFINITY_EXPORT_H */

// End of auto generated file.
