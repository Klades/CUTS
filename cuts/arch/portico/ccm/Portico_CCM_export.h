// -*- C++ -*-

#ifndef _PORTICO_CCM_EXPORT_H_
#define _PORTICO_CCM_EXPORT_H_

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (PORTICO_CCM_HAS_DLL)
#  define PORTICO_CCM_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && PORTICO_CCM_HAS_DLL */

#if !defined (PORTICO_CCM_HAS_DLL)
#  define PORTICO_CCM_HAS_DLL 1
#endif /* ! PORTICO_CCM_HAS_DLL */

#if defined (PORTICO_CCM_HAS_DLL) && (PORTICO_CCM_HAS_DLL == 1)
#  if defined (PORTICO_CCM_BUILD_DLL)
#    define PORTICO_CCM_Export ACE_Proper_Export_Flag
#    define PORTICO_CCM_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define PORTICO_CCM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* PORTICO_CCM_BUILD_DLL */
#    define PORTICO_CCM_Export ACE_Proper_Import_Flag
#    define PORTICO_CCM_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define PORTICO_CCM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* PORTICO_CCM_BUILD_DLL */
#else /* PORTICO_CCM_HAS_DLL == 1 */
#  define PORTICO_CCM_Export
#  define PORTICO_CCM_SINGLETON_DECLARATION(T)
#  define PORTICO_CCM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* PORTICO_CCM_HAS_DLL == 1 */

// Set PORTICO_CCM_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (PORTICO_CCM_NTRACE)
#  if (ACE_NTRACE == 1)
#    define PORTICO_CCM_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define PORTICO_CCM_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !PORTICO_CCM_NTRACE */

#if (Portico_CCM_NTRACE == 1)
#  define PORTICO_CCM_TRACE(X)
#else /* (PORTICO_CCM_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define PORTICO_CCM_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (PORTICO_CCM_NTRACE == 1) */

#endif /* PORTICO_CCM_EXPORT_H */
