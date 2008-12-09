// -*- C++ -*-

//=============================================================================
/**
 * @file        Test_Summary_Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_XML_TEST_SUMMARY_IMPL_H_
#define _CUTS_XML_TEST_SUMMARY_IMPL_H_

#include "Test_Summary_Impl.h"

/**
 * @class CUTS_XML_Test_Summary_Impl
 *
 * Generate test summary in a XML format.
 */
class CUTS_XML_Test_Summary_Impl : public CUTS_Test_Summary_Impl
{
public:
  /// Default constructor.
  CUTS_XML_Test_Summary_Impl (void);

  /// Destructor.
  virtual ~CUTS_XML_Test_Summary_Impl (void);

  /**
   * Generate the test summary
   *
   * @param[in]         out         Target output stream
   * @param[in]         app         Pointer to test application
   */
  int generate (std::ostream & out, const CUTS_Testing_App_Base & app) const;
};

#if defined (__CUTS_INLINE__)
#include "XML_Test_Summary_Impl.inl"
#endif

#endif  // !defined _CUTS_XML_TEST_SUMMARY_IMPL_H_
