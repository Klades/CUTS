// -*- C++ -*-

//=============================================================================
/**
 * @file        Correctness_Test_File.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CORRECTNESS_TEST_FILE_H_
#define _CUTS_CORRECTNESS_TEST_FILE_H_

#include "cuts-unite.h"
#include "XSC/utils/XML_Schema_Resolver.h"
#include "XSCRT/utils/File_Reader_T.h"

/**
 * @ingroup UNITE_XML
 *
 * @class CUTS_Correctness_Test_File
 *
 * Helper class for parsing XML documents that contains a
 * correctness test.
 */
class CUTS_UNITE_XML_Export CUTS_Correctness_Test_File :
  public XSCRT::utils::File_Reader_T < ::CUTS::XML::correctnessTestType >
{
public:
  /// Type definition of the XML reader type.
  typedef XSCRT::utils::File_Reader_T < ::CUTS::XML::correctnessTestType > reader_type;

  /// Default constructor.
  CUTS_Correctness_Test_File (void);

  /// Destructor.
  ~CUTS_Correctness_Test_File (void);

private:
  void configure (void);

  XSC::XML::Basic_Resolver < > br_;

  XSC::XML::XML_Schema_Resolver < ::XSC::XML::Basic_Resolver < > > resolver_;
};

#if defined (__CUTS_INLINE__)
#include "Correctness_Test_File.inl"
#endif

#endif  // !defined _CUTS_CORRECTNESS_TEST_FILE_H_
