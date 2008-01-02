
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl TEST_LOG_FORMATS
// ------------------------------
#ifndef TEST_LOG_FORMATS_EXPORT_H
#define TEST_LOG_FORMATS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (TEST_LOG_FORMATS_HAS_DLL)
#  define TEST_LOG_FORMATS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && TEST_LOG_FORMATS_HAS_DLL */

#if !defined (TEST_LOG_FORMATS_HAS_DLL)
#  define TEST_LOG_FORMATS_HAS_DLL 1
#endif /* ! TEST_LOG_FORMATS_HAS_DLL */

#if defined (TEST_LOG_FORMATS_HAS_DLL) && (TEST_LOG_FORMATS_HAS_DLL == 1)
#  if defined (TEST_LOG_FORMATS_BUILD_DLL)
#    define TEST_LOG_FORMATS_Export ACE_Proper_Export_Flag
#    define TEST_LOG_FORMATS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define TEST_LOG_FORMATS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* TEST_LOG_FORMATS_BUILD_DLL */
#    define TEST_LOG_FORMATS_Export ACE_Proper_Import_Flag
#    define TEST_LOG_FORMATS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define TEST_LOG_FORMATS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* TEST_LOG_FORMATS_BUILD_DLL */
#else /* TEST_LOG_FORMATS_HAS_DLL == 1 */
#  define TEST_LOG_FORMATS_Export
#  define TEST_LOG_FORMATS_SINGLETON_DECLARATION(T)
#  define TEST_LOG_FORMATS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* TEST_LOG_FORMATS_HAS_DLL == 1 */

// Set TEST_LOG_FORMATS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (TEST_LOG_FORMATS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define TEST_LOG_FORMATS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define TEST_LOG_FORMATS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !TEST_LOG_FORMATS_NTRACE */

#if (TEST_LOG_FORMATS_NTRACE == 1)
#  define TEST_LOG_FORMATS_TRACE(X)
#else /* (TEST_LOG_FORMATS_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define TEST_LOG_FORMATS_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (TEST_LOG_FORMATS_NTRACE == 1) */

#endif /* TEST_LOG_FORMATS_EXPORT_H */

// End of auto generated file.
