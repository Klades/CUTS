// -*- C++ -*-
//
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.7.2
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 *       http://doc.ece.uci.edu/
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

#ifndef SIMPLECOMPONENT_SKEL_EXPORT_H
#define SIMPLECOMPONENT_SKEL_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (SIMPLECOMPONENT_SKEL_HAS_DLL)
#  define SIMPLECOMPONENT_SKEL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && SIMPLECOMPONENT_SKEL_HAS_DLL */

#if !defined (SIMPLECOMPONENT_SKEL_HAS_DLL)
#  define SIMPLECOMPONENT_SKEL_HAS_DLL 1
#endif /* ! SIMPLECOMPONENT_SKEL_HAS_DLL */

#if defined (SIMPLECOMPONENT_SKEL_HAS_DLL) && (SIMPLECOMPONENT_SKEL_HAS_DLL == 1)
#  if defined (SIMPLECOMPONENT_SKEL_BUILD_DLL)
#    define SIMPLECOMPONENT_SKEL_Export ACE_Proper_Export_Flag
#    define SIMPLECOMPONENT_SKEL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define SIMPLECOMPONENT_SKEL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* SIMPLECOMPONENT_SKEL_BUILD_DLL */
#    define SIMPLECOMPONENT_SKEL_Export ACE_Proper_Import_Flag
#    define SIMPLECOMPONENT_SKEL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define SIMPLECOMPONENT_SKEL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* SIMPLECOMPONENT_SKEL_BUILD_DLL */
#else /* SIMPLECOMPONENT_SKEL_HAS_DLL == 1 */
#  define SIMPLECOMPONENT_SKEL_Export
#  define SIMPLECOMPONENT_SKEL_SINGLETON_DECLARATION(T)
#  define SIMPLECOMPONENT_SKEL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* SIMPLECOMPONENT_SKEL_HAS_DLL == 1 */

// Set SIMPLECOMPONENT_SKEL_NTRACE = 0 to turn on library-specific
// tracing even if tracing is turned off for ACE.
#if !defined (SIMPLECOMPONENT_SKEL_NTRACE)
#  if (ACE_NTRACE == 1)
#    define SIMPLECOMPONENT_SKEL_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define SIMPLECOMPONENT_SKEL_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !SIMPLECOMPONENT_SKEL_NTRACE */

#if (SIMPLECOMPONENT_SKEL_NTRACE == 1)
#  define SIMPLECOMPONENT_SKEL_TRACE(X)
#else /* (SIMPLECOMPONENT_SKEL_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define SIMPLECOMPONENT_SKEL_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (SIMPLECOMPONENT_SKEL_NTRACE == 1) */

#endif /* SIMPLECOMPONENT_SKEL_EXPORT_H */

