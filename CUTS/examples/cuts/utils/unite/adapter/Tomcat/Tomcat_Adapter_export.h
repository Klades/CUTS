
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl TOMCAT_ADAPTER
// ------------------------------
#ifndef TOMCAT_ADAPTER_EXPORT_H
#define TOMCAT_ADAPTER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (TOMCAT_ADAPTER_HAS_DLL)
#  define TOMCAT_ADAPTER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && TOMCAT_ADAPTER_HAS_DLL */

#if !defined (TOMCAT_ADAPTER_HAS_DLL)
#  define TOMCAT_ADAPTER_HAS_DLL 1
#endif /* ! TOMCAT_ADAPTER_HAS_DLL */

#if defined (TOMCAT_ADAPTER_HAS_DLL) && (TOMCAT_ADAPTER_HAS_DLL == 1)
#  if defined (TOMCAT_ADAPTER_BUILD_DLL)
#    define TOMCAT_ADAPTER_Export ACE_Proper_Export_Flag
#    define TOMCAT_ADAPTER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define TOMCAT_ADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* TOMCAT_ADAPTER_BUILD_DLL */
#    define TOMCAT_ADAPTER_Export ACE_Proper_Import_Flag
#    define TOMCAT_ADAPTER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define TOMCAT_ADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* TOMCAT_ADAPTER_BUILD_DLL */
#else /* TOMCAT_ADAPTER_HAS_DLL == 1 */
#  define TOMCAT_ADAPTER_Export
#  define TOMCAT_ADAPTER_SINGLETON_DECLARATION(T)
#  define TOMCAT_ADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* TOMCAT_ADAPTER_HAS_DLL == 1 */

// Set TOMCAT_ADAPTER_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (TOMCAT_ADAPTER_NTRACE)
#  if (ACE_NTRACE == 1)
#    define TOMCAT_ADAPTER_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define TOMCAT_ADAPTER_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !TOMCAT_ADAPTER_NTRACE */

#if (TOMCAT_ADAPTER_NTRACE == 1)
#  define TOMCAT_ADAPTER_TRACE(X)
#else /* (TOMCAT_ADAPTER_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define TOMCAT_ADAPTER_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (TOMCAT_ADAPTER_NTRACE == 1) */

#endif /* TOMCAT_ADAPTER_EXPORT_H */

// End of auto generated file.
