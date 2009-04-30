
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl SubAppDDS
// ------------------------------
#ifndef SUBAPPDDS_EXPORT_H
#define SUBAPPDDS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (SUBAPPDDS_HAS_DLL)
#  define SUBAPPDDS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && SUBAPPDDS_HAS_DLL */

#if !defined (SUBAPPDDS_HAS_DLL)
#  define SUBAPPDDS_HAS_DLL 1
#endif /* ! SUBAPPDDS_HAS_DLL */

#if defined (SUBAPPDDS_HAS_DLL) && (SUBAPPDDS_HAS_DLL == 1)
#  if defined (SUBAPPDDS_BUILD_DLL)
#    define SubAppDDS_Export ACE_Proper_Export_Flag
#    define SUBAPPDDS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define SUBAPPDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* SUBAPPDDS_BUILD_DLL */
#    define SubAppDDS_Export ACE_Proper_Import_Flag
#    define SUBAPPDDS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define SUBAPPDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* SUBAPPDDS_BUILD_DLL */
#else /* SUBAPPDDS_HAS_DLL == 1 */
#  define SubAppDDS_Export
#  define SUBAPPDDS_SINGLETON_DECLARATION(T)
#  define SUBAPPDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* SUBAPPDDS_HAS_DLL == 1 */

// Set SUBAPPDDS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (SUBAPPDDS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define SUBAPPDDS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define SUBAPPDDS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !SUBAPPDDS_NTRACE */

#if (SUBAPPDDS_NTRACE == 1)
#  define SUBAPPDDS_TRACE(X)
#else /* (SUBAPPDDS_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define SUBAPPDDS_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (SUBAPPDDS_NTRACE == 1) */

#endif /* SUBAPPDDS_EXPORT_H */

// End of auto generated file.
