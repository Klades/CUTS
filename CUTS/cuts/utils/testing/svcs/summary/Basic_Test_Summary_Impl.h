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

#ifndef _CUTS_BASIC_TEST_SUMMARY_IMPL_H_
#define _CUTS_BASIC_TEST_SUMMARY_IMPL_H_

#include "Test_Summary_Impl.h"

/**
 * @class CUTS_Basic_Test_Summary_Impl
 */
class CUTS_Basic_Test_Summary_Impl : public CUTS_Test_Summary_Impl
{
public:
  /// Default constructor
  CUTS_Basic_Test_Summary_Impl (void);

  /// Destructor
  virtual ~CUTS_Basic_Test_Summary_Impl (void);

  /**
   *
   */
  int generate (std::ostream & out, const CUTS_Testing_App & app) const;
};

#if defined (__CUTS_INLINE__)
#include "Basic_Test_Summary_Impl.inl"
#endif

#endif  // !defined _CUTS_BASIC_TEST_SUMMARY_IMPL_H_
