
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl PubAppAdapter
// ------------------------------
#ifndef PUBAPPADAPTER_EXPORT_H
#define PUBAPPADAPTER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (PUBAPPADAPTER_HAS_DLL)
#  define PUBAPPADAPTER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && PUBAPPADAPTER_HAS_DLL */

#if !defined (PUBAPPADAPTER_HAS_DLL)
#  define PUBAPPADAPTER_HAS_DLL 1
#endif /* ! PUBAPPADAPTER_HAS_DLL */

#if defined (PUBAPPADAPTER_HAS_DLL) && (PUBAPPADAPTER_HAS_DLL == 1)
#  if defined (PUBAPPADAPTER_BUILD_DLL)
#    define PubAppAdapter_Export ACE_Proper_Export_Flag
#    define PUBAPPADAPTER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define PUBAPPADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* PUBAPPADAPTER_BUILD_DLL */
#    define PubAppAdapter_Export ACE_Proper_Import_Flag
#    define PUBAPPADAPTER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define PUBAPPADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* PUBAPPADAPTER_BUILD_DLL */
#else /* PUBAPPADAPTER_HAS_DLL == 1 */
#  define PubAppAdapter_Export
#  define PUBAPPADAPTER_SINGLETON_DECLARATION(T)
#  define PUBAPPADAPTER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* PUBAPPADAPTER_HAS_DLL == 1 */

// Set PUBAPPADAPTER_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (PUBAPPADAPTER_NTRACE)
#  if (ACE_NTRACE == 1)
#    define PUBAPPADAPTER_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define PUBAPPADAPTER_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !PUBAPPADAPTER_NTRACE */

#if (PUBAPPADAPTER_NTRACE == 1)
#  define PUBAPPADAPTER_TRACE(X)
#else /* (PUBAPPADAPTER_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define PUBAPPADAPTER_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (PUBAPPADAPTER_NTRACE == 1) */

#endif /* PUBAPPADAPTER_EXPORT_H */

// End of auto generated file.
