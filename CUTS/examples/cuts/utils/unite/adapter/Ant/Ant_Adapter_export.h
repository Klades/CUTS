
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl ANT_ADAPTER
// ------------------------------
#ifndef ANT_ADAPTER_EXPORT_H
#define ANT_ADAPTER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (ANT_ADAPTER_HAS_DLL)
#  define ANT_ADAPTER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && ANT_ADAPTER_HAS_DLL */

#if !defined (ANT_ADAPTER_HAS_DLL)
#  define ANT_ADAPTER_HAS_DLL 1
#endif /* ! ANT_ADAPTER_HAS_DLL */

#if defined (ANT_ADAPTER_HAS_DLL) && (ANT_ADAPTER_HAS_DLL == 1)
#  if defined (ANT_ADAPTER_BUILD_DLL)
#    define ANT_ADAPTER_Export ACE_Proper_Export_Flag
#    define ANT_ADAPTER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define ANT_ADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* ANT_ADAPTER_BUILD_DLL */
#    define ANT_ADAPTER_Export ACE_Proper_Import_Flag
#    define ANT_ADAPTER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define ANT_ADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* ANT_ADAPTER_BUILD_DLL */
#else /* ANT_ADAPTER_HAS_DLL == 1 */
#  define ANT_ADAPTER_Export
#  define ANT_ADAPTER_SINGLETON_DECLARATION(T)
#  define ANT_ADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* ANT_ADAPTER_HAS_DLL == 1 */

// Set ANT_ADAPTER_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (ANT_ADAPTER_NTRACE)
#  if (ACE_NTRACE == 1)
#    define ANT_ADAPTER_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define ANT_ADAPTER_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !ANT_ADAPTER_NTRACE */

#if (ANT_ADAPTER_NTRACE == 1)
#  define ANT_ADAPTER_TRACE(X)
#else /* (ANT_ADAPTER_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define ANT_ADAPTER_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (ANT_ADAPTER_NTRACE == 1) */

#endif /* ANT_ADAPTER_EXPORT_H */

// End of auto generated file.
