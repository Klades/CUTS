
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl BUTTON_IMPL
// ------------------------------
#ifndef BUTTON_IMPL_EXPORT_H
#define BUTTON_IMPL_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (BUTTON_IMPL_HAS_DLL)
#  define BUTTON_IMPL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && BUTTON_IMPL_HAS_DLL */

#if !defined (BUTTON_IMPL_HAS_DLL)
#  define BUTTON_IMPL_HAS_DLL 1
#endif /* ! BUTTON_IMPL_HAS_DLL */

#if defined (BUTTON_IMPL_HAS_DLL) && (BUTTON_IMPL_HAS_DLL == 1)
#  if defined (BUTTON_IMPL_BUILD_DLL)
#    define BUTTON_IMPL_Export ACE_Proper_Export_Flag
#    define BUTTON_IMPL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define BUTTON_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* BUTTON_IMPL_BUILD_DLL */
#    define BUTTON_IMPL_Export ACE_Proper_Import_Flag
#    define BUTTON_IMPL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define BUTTON_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* BUTTON_IMPL_BUILD_DLL */
#else /* BUTTON_IMPL_HAS_DLL == 1 */
#  define BUTTON_IMPL_Export
#  define BUTTON_IMPL_SINGLETON_DECLARATION(T)
#  define BUTTON_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* BUTTON_IMPL_HAS_DLL == 1 */

// Set BUTTON_IMPL_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (BUTTON_IMPL_NTRACE)
#  if (ACE_NTRACE == 1)
#    define BUTTON_IMPL_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define BUTTON_IMPL_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !BUTTON_IMPL_NTRACE */

#if (BUTTON_IMPL_NTRACE == 1)
#  define BUTTON_IMPL_TRACE(X)
#else /* (BUTTON_IMPL_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define BUTTON_IMPL_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (BUTTON_IMPL_NTRACE == 1) */

#endif /* BUTTON_IMPL_EXPORT_H */

// End of auto generated file.
