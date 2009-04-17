
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl PubApp
// ------------------------------
#ifndef PUBAPP_EXPORT_H
#define PUBAPP_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (PUBAPP_HAS_DLL)
#  define PUBAPP_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && PUBAPP_HAS_DLL */

#if !defined (PUBAPP_HAS_DLL)
#  define PUBAPP_HAS_DLL 1
#endif /* ! PUBAPP_HAS_DLL */

#if defined (PUBAPP_HAS_DLL) && (PUBAPP_HAS_DLL == 1)
#  if defined (PUBAPP_BUILD_DLL)
#    define PubApp_Export ACE_Proper_Export_Flag
#    define PUBAPP_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define PUBAPP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* PUBAPP_BUILD_DLL */
#    define PubApp_Export ACE_Proper_Import_Flag
#    define PUBAPP_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define PUBAPP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* PUBAPP_BUILD_DLL */
#else /* PUBAPP_HAS_DLL == 1 */
#  define PubApp_Export
#  define PUBAPP_SINGLETON_DECLARATION(T)
#  define PUBAPP_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* PUBAPP_HAS_DLL == 1 */

// Set PUBAPP_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (PUBAPP_NTRACE)
#  if (ACE_NTRACE == 1)
#    define PUBAPP_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define PUBAPP_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !PUBAPP_NTRACE */

#if (PUBAPP_NTRACE == 1)
#  define PUBAPP_TRACE(X)
#else /* (PUBAPP_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define PUBAPP_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (PUBAPP_NTRACE == 1) */

#endif /* PUBAPP_EXPORT_H */

// End of auto generated file.
