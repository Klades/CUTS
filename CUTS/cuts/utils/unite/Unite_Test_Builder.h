// -*- C++ -*-

//=============================================================================
/**
 * @file        Unite_Config_File.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_UNIT_TEST_BUILDER_H_
#define _CUTS_UNITE_UNIT_TEST_BUILDER_H_

#include "cuts-unite.h"

// Forward decl.
class CUTS_Unite_Test;

// Forward decl.
class CUTS_Log_Format;

// Forward decl.
class CUTS_Log_Format_Relation;

/**
 * @ingroup UNITE_XML
 *
 * @class CUTS_Unite_Test_Builder
 *
 * Helper class that converts the datagraph in a XML file into a
 * CUTS_Unite_Test object.
 */
class CUTS_UNITE_XML_Export CUTS_Unite_Test_Builder
{
public:
  /// Default constructor.
  CUTS_Unite_Test_Builder (void);

  /// Destructor.
  ~CUTS_Unite_Test_Builder (void);

  /**
   * Build the unit test.
   *
   * @param[in]       config        Source configuration
   * @param[out]      test          Target unit test object.
   */
  bool build (const ::CUTS::XML::testConfig & config, CUTS_Unite_Test & test);
};

#endif  // !defined _CUTS_UNITE_UNIT_TEST_BUILDER_H_
