// $Id$

#include "Unit_Test_Builder.h"
#include "Unit_Test.h"
#include "Log_Format.h"
#include "Relation.h"
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
bool CUTS_Unit_Test_Builder::
build (const CUTS::uniteConfig & config, CUTS_Unit_Test & test)
{
  // Set the basic information.
  test.name (config.name ().c_str ());
  test.evaluation (config.evaluation ().c_str ());
  test.aggregation (config.aggregation ().c_str ());

  // Process the log formats.
  std::for_each (config.logformats ().begin_logformat (),
                 config.logformats ().end_logformat (),
                 boost::bind (&CUTS_Unit_Test_Builder::process_log_format,
                              this,
                              _1,
                              boost::ref (test)));

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
// process_log_format
//
void CUTS_Unit_Test_Builder::
process_log_format (const CUTS::logformatType & format,
                    CUTS_Unit_Test & test)
{
  // Create a new log format in the unit test.
  CUTS_Log_Format * lfmt = 0;
  test.create_log_format (format.id ().c_str (), lfmt);

  // Compile the log format's value.
  lfmt->compile (format.value ().c_str ());

  if (format.relations_p ())
  {
    // Process the relations for this log format.
    std::for_each (format.relations ().begin_relation (),
                   format.relations ().end_relation (),
                   boost::bind (&CUTS_Unit_Test_Builder::process_relation,
                                this,
                                _1,
                                boost::ref (test),
                                boost::ref (*lfmt)));
  }
}

//
// process_relation
//
void CUTS_Unit_Test_Builder::
process_relation (const CUTS::relationType & relation,
                  CUTS_Unit_Test & test,
                  CUTS_Log_Format & format)
{
  // Locate the log format for this effect.
  CUTS_Log_Format * effect;

  if (!test.create_log_format (relation.effectref ().c_str (), effect))
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to process relation %s/%s\n",
                format.name ().c_str (),
                relation.effectref ().c_str ()));
    return;
  }

  // Create an association between the two log formats.
  test.associate (format.name (), effect->name ());

  // Create a new relation for this item. First, lets set the
  // relation's effect log format.
  CUTS_Log_Format_Relation lfr;
  lfr.effect (effect);

  // Process the causality (variables) for this relation.
  std::for_each (relation.begin_causality (),
                 relation.end_causality (),
                 boost::bind (&CUTS_Unit_Test_Builder::process_causality,
                              this,
                              _1,
                              boost::ref (lfr)));

  // Save the relation.
  format.relations ().push_back (lfr);
}

//
// process_casaulity
//
void CUTS_Unit_Test_Builder::
process_causality (const CUTS::causalityType & causality,
                   CUTS_Log_Format_Relation & relation)
{
  CUTS_Relation_Causality rc (causality.cause ().c_str (),
                              causality.effect ().c_str ());

  relation.causality ().push_back (rc);
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
