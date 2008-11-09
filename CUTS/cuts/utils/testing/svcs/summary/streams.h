// -*- C++ -*-

//=============================================================================
/**
 * @file        Basic_Test_Summary_Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TESTING_SUMMARY_STREAMS_H_
#define _CUTS_TESTING_SUMMARY_STREAMS_H_

#include "ace/streams.h"

// Forward decl.
class ACE_Time_Value;

std::ostream & operator << (std::ostream &, const ACE_Time_Value &);

#endif  // !defined _CUTS_TESTING_SUMMARY_STREAMS_H_
