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
class CUTS_Unit_Test;

// Forward decl.
class CUTS_Log_Format;

// Forward decl.
class CUTS_Log_Format_Relation;

/**
 * @class CUTS_Unit_Test_Builder
 *
 * Helper class that converts the datagraph in a XML file into
 * a CUTS_Unit_Test object.
 */
class CUTS_Unit_Test_Builder
{
public:
  /// Default constructor.
  CUTS_Unit_Test_Builder (void);

  /// Destructor.
  ~CUTS_Unit_Test_Builder (void);

  /**
   * Build the unit test.
   *
   * @param[in]       config        Source configuration
   * @param[out]      test          Target unit test object.
   */
  bool build (const CUTS::uniteConfig & config,
              CUTS_Unit_Test & test);

private:
  void process_relation (const CUTS::relationType & relation,
                         CUTS_Unit_Test & test,
                         CUTS_Log_Format & format);

  void process_causality (const CUTS::causalityType & causality,
                          CUTS_Log_Format_Relation & relation);

  void process_group_item (const CUTS::groupitemType & causality,
                           CUTS_Unit_Test & test);
};

#endif  // !defined _CUTS_UNITE_UNIT_TEST_BUILDER_H_
