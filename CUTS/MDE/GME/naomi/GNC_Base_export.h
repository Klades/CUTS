
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl GNC_BASE
// ------------------------------
#ifndef GNC_BASE_EXPORT_H
#define GNC_BASE_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (GNC_BASE_HAS_DLL)
#  define GNC_BASE_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && GNC_BASE_HAS_DLL */

#if !defined (GNC_BASE_HAS_DLL)
#  define GNC_BASE_HAS_DLL 1
#endif /* ! GNC_BASE_HAS_DLL */

#if defined (GNC_BASE_HAS_DLL) && (GNC_BASE_HAS_DLL == 1)
#  if defined (GNC_BASE_BUILD_DLL)
#    define GNC_BASE_Export ACE_Proper_Export_Flag
#    define GNC_BASE_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define GNC_BASE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* GNC_BASE_BUILD_DLL */
#    define GNC_BASE_Export ACE_Proper_Import_Flag
#    define GNC_BASE_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define GNC_BASE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* GNC_BASE_BUILD_DLL */
#else /* GNC_BASE_HAS_DLL == 1 */
#  define GNC_BASE_Export
#  define GNC_BASE_SINGLETON_DECLARATION(T)
#  define GNC_BASE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* GNC_BASE_HAS_DLL == 1 */

// Set GNC_BASE_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (GNC_BASE_NTRACE)
#  if (ACE_NTRACE == 1)
#    define GNC_BASE_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define GNC_BASE_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !GNC_BASE_NTRACE */

#if (GNC_BASE_NTRACE == 1)
#  define GNC_BASE_TRACE(X)
#else /* (GNC_BASE_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define GNC_BASE_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (GNC_BASE_NTRACE == 1) */

#endif /* GNC_BASE_EXPORT_H */

// End of auto generated file.
