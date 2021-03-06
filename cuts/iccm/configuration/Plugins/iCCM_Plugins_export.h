
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl ICCM_PLUGINS
// ------------------------------
#ifndef ICCM_PLUGINS_EXPORT_H
#define ICCM_PLUGINS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (ICCM_PLUGINS_HAS_DLL)
#  define ICCM_PLUGINS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && ICCM_PLUGINS_HAS_DLL */

#if !defined (ICCM_PLUGINS_HAS_DLL)
#  define ICCM_PLUGINS_HAS_DLL 1
#endif /* ! ICCM_PLUGINS_HAS_DLL */

#if defined (ICCM_PLUGINS_HAS_DLL) && (ICCM_PLUGINS_HAS_DLL == 1)
#  if defined (ICCM_PLUGINS_BUILD_DLL)
#    define ICCM_PLUGINS_Export ACE_Proper_Export_Flag
#    define ICCM_PLUGINS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define ICCM_PLUGINS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* ICCM_PLUGINS_BUILD_DLL */
#    define ICCM_PLUGINS_Export ACE_Proper_Import_Flag
#    define ICCM_PLUGINS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define ICCM_PLUGINS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* ICCM_PLUGINS_BUILD_DLL */
#else /* ICCM_PLUGINS_HAS_DLL == 1 */
#  define ICCM_PLUGINS_Export
#  define ICCM_PLUGINS_SINGLETON_DECLARATION(T)
#  define ICCM_PLUGINS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* ICCM_PLUGINS_HAS_DLL == 1 */

// Set ICCM_PLUGINS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (ICCM_PLUGINS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define ICCM_PLUGINS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define ICCM_PLUGINS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !ICCM_PLUGINS_NTRACE */

#if (ICCM_PLUGINS_NTRACE == 1)
#  define ICCM_PLUGINS_TRACE(X)
#else /* (ICCM_PLUGINS_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define ICCM_PLUGINS_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (ICCM_PLUGINS_NTRACE == 1) */

#endif /* ICCM_PLUGINS_EXPORT_H */

// End of auto generated file.
