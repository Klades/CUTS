
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl GME_T2M_PARSER
// ------------------------------
#ifndef GME_T2M_PARSER_EXPORT_H
#define GME_T2M_PARSER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (GME_T2M_PARSER_HAS_DLL)
#  define GME_T2M_PARSER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && GME_T2M_PARSER_HAS_DLL */

#if !defined (GME_T2M_PARSER_HAS_DLL)
#  define GME_T2M_PARSER_HAS_DLL 1
#endif /* ! GME_T2M_PARSER_HAS_DLL */

#if defined (GME_T2M_PARSER_HAS_DLL) && (GME_T2M_PARSER_HAS_DLL == 1)
#  if defined (GME_T2M_PARSER_BUILD_DLL)
#    define GME_T2M_PARSER_Export ACE_Proper_Export_Flag
#    define GME_T2M_PARSER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define GME_T2M_PARSER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* GME_T2M_PARSER_BUILD_DLL */
#    define GME_T2M_PARSER_Export ACE_Proper_Import_Flag
#    define GME_T2M_PARSER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define GME_T2M_PARSER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* GME_T2M_PARSER_BUILD_DLL */
#else /* GME_T2M_PARSER_HAS_DLL == 1 */
#  define GME_T2M_PARSER_Export
#  define GME_T2M_PARSER_SINGLETON_DECLARATION(T)
#  define GME_T2M_PARSER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* GME_T2M_PARSER_HAS_DLL == 1 */

// Set GME_T2M_PARSER_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (GME_T2M_PARSER_NTRACE)
#  if (ACE_NTRACE == 1)
#    define GME_T2M_PARSER_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define GME_T2M_PARSER_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !GME_T2M_PARSER_NTRACE */

#if (GME_T2M_PARSER_NTRACE == 1)
#  define GME_T2M_PARSER_TRACE(X)
#else /* (GME_T2M_PARSER_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define GME_T2M_PARSER_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (GME_T2M_PARSER_NTRACE == 1) */

#endif /* GME_T2M_PARSER_EXPORT_H */

// End of auto generated file.
