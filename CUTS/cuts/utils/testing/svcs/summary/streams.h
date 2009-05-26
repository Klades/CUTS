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

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
// Forward decl.
class ACE_Time_Value;
ACE_END_VERSIONED_NAMESPACE_DECL

std::ostream & operator << (std::ostream &, const ACE_Time_Value &);

#endif  // !defined _CUTS_TESTING_SUMMARY_STREAMS_H_
