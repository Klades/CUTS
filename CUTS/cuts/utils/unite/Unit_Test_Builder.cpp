// $Id$

#include "Unit_Test_Builder.h"
#include "Unit_Test.h"
#include "Unite_Datagraph_File.h"
#include <algorithm>

/**
 * @class process_group_item
 *
 * Functor for processing the grouping items of a unit test that
 * appear in an XML document.
 */
class process_group_item
{
public:
  typedef ::CUTS::XML::groupingType::groupitem_iterator::value_type value_type;

  process_group_item (CUTS_Unit_Test & test)
    : test_ (test)
  {

  }

  void operator () (const value_type & item)
  {
    this->test_.groupings ().push_back (item->name ().c_str ());
  }

private:
  CUTS_Unit_Test & test_;
};

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
bool CUTS_Unit_Test_Builder::
build (const ::CUTS::XML::testConfig & config,
       CUTS_Unit_Test & test)
{
  // Set the basic information.
  test.name (config.name ().c_str ());
  test.evaluation (config.evaluation ().c_str ());
  test.aggregation (config.aggregation ().c_str ());

  if (config.grouping_p ())
    std::for_each (config.grouping ().begin_groupitem (),
                   config.grouping ().end_groupitem (),
                   process_group_item (test));

  return true;
}
