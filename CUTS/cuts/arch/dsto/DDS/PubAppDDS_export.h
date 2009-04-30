
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl PubAppDDS
// ------------------------------
#ifndef PUBAPPDDS_EXPORT_H
#define PUBAPPDDS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (PUBAPPDDS_HAS_DLL)
#  define PUBAPPDDS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && PUBAPPDDS_HAS_DLL */

#if !defined (PUBAPPDDS_HAS_DLL)
#  define PUBAPPDDS_HAS_DLL 1
#endif /* ! PUBAPPDDS_HAS_DLL */

#if defined (PUBAPPDDS_HAS_DLL) && (PUBAPPDDS_HAS_DLL == 1)
#  if defined (PUBAPPDDS_BUILD_DLL)
#    define PubAppDDS_Export ACE_Proper_Export_Flag
#    define PUBAPPDDS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define PUBAPPDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* PUBAPPDDS_BUILD_DLL */
#    define PubAppDDS_Export ACE_Proper_Import_Flag
#    define PUBAPPDDS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define PUBAPPDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* PUBAPPDDS_BUILD_DLL */
#else /* PUBAPPDDS_HAS_DLL == 1 */
#  define PubAppDDS_Export
#  define PUBAPPDDS_SINGLETON_DECLARATION(T)
#  define PUBAPPDDS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* PUBAPPDDS_HAS_DLL == 1 */

// Set PUBAPPDDS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (PUBAPPDDS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define PUBAPPDDS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define PUBAPPDDS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !PUBAPPDDS_NTRACE */

#if (PUBAPPDDS_NTRACE == 1)
#  define PUBAPPDDS_TRACE(X)
#else /* (PUBAPPDDS_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define PUBAPPDDS_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (PUBAPPDDS_NTRACE == 1) */

#endif /* PUBAPPDDS_EXPORT_H */

// End of auto generated file.
