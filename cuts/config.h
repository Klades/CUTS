// -*- C++ -*-

//=============================================================================
/**
 * @file    CUTS.h
 *
 * $Id$
 *
 * This files contains macro definitions that are global to the CUTS
 * module, such as exporting and importing objects
 *
 * @author James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_CONFIG_H_
#define _CUTS_CONFIG_H_

#include "ace/config-all.h"

#if defined (__CUTS_INLINE__)
# define CUTS_INLINE inline
#else
# define CUTS_INLINE
#endif

#define CUTS_DEFAULT_PORT                 3306

#define CUTS_DEFAULT_EVENT_COUNT          20

#define CUTS_EVENT_HANDLER_THREAD_COUNT   1

#define CUTS_UNKNOWN_IMPL                 1

#define CUTS_DEFAULT_LOG_SIZE             50

#define CUTS_UNKNOWN_ID                   -1

#define CUTS_RESULT_DEFAULT_BUFFER_SIZE   1024

#if defined (CUTS_HAS_DOXYGEN)
#include "config-doxygen.h"
#endif

#endif  // !defined _CUTS_CONFIG_H_
