// $Id$

#include "Unit_Test_Builder.h"
#include "Unit_Test.h"
#include "Unite_Datagraph_File.h"
#include "boost/bind.hpp"
#include <algorithm>

//
// CUTS_Unit_Test_Builder
//
CUTS_Unit_Test_Builder::CUTS_Unit_Test_Builder (void)
{

}

//
// ~CUTS_Unit_Test_Builder
//
CUTS_Unit_Test_Builder::~CUTS_Unit_Test_Builder (void)
{

}

//
// build
//
bool CUTS_Unit_Test_Builder::build (const CUTS::testConfig & config,
                                    CUTS_Unit_Test & test)
{
  // Set the basic information.
  test.name (config.name ().c_str ());
  test.evaluation (config.evaluation ().c_str ());
  test.aggregation (config.aggregation ().c_str ());

  if (config.grouping_p ())
  {
    // Process the groupings.
    std::for_each (config.grouping ().begin_groupitem (),
                  config.grouping ().end_groupitem (),
                  boost::bind (&CUTS_Unit_Test_Builder::process_group_item,
                                this,
                                _1,
                                boost::ref (test)));
  }

  return true;
}

//
// process_group_item
//
void CUTS_Unit_Test_Builder::
process_group_item (const CUTS::groupitemType & item,
                    CUTS_Unit_Test & test)
{
  test.groupings ().push_back (item.name ().c_str ());
}
