// $Id$

#include "Unit_Test_Graph_Builder.h"

#if !defined (__CUTS_INLINE__)
#include "Unit_Test_Graph_Builder.inl"
#endif

#include "Log_Format.h"
#include "Unit_Test_Graph.h"
#include "boost/bind.hpp"
#include <algorithm>

//
// build
//
bool CUTS_Unit_Test_Graph_Builder::
build (const CUTS::datagraphType & datagraph, CUTS_Unit_Test_Graph & graph)
{
  // Set the name of the graph.
  graph.name (datagraph.name ().c_str ());

  // Process the log formats.
  std::for_each (datagraph.logformats ().begin_logformat (),
                 datagraph.logformats ().end_logformat (),
                 boost::bind (&CUTS_Unit_Test_Graph_Builder::process_log_format,
                              this,
                              _1,
                              boost::ref (graph)));

  return true;
}

//
// process_log_format
//
void CUTS_Unit_Test_Graph_Builder::
process_log_format (const CUTS::logformatType & format,
                    CUTS_Unit_Test_Graph & graph)
{
  // Create a new log format in the unit test.
  CUTS_Log_Format * lfmt = 0;
  graph.create_log_format (format.id ().c_str (), lfmt);

  // Compile the log format's value.
  lfmt->compile (format.value ().c_str ());

  if (format.relations_p ())
  {
    // Process the relations for this log format.
    std::for_each (format.relations ().begin_relation (),
                   format.relations ().end_relation (),
                   boost::bind (&CUTS_Unit_Test_Graph_Builder::process_relation,
                                this,
                                _1,
                                boost::ref (graph),
                                boost::ref (*lfmt)));
  }
}

//
// process_relation
//
void CUTS_Unit_Test_Graph_Builder::
process_relation (const CUTS::relationType & relation,
                  CUTS_Unit_Test_Graph & graph,
                  CUTS_Log_Format & format)
{
  // Locate the log format for this effect.
  CUTS_Log_Format * effect;

  if (!graph.create_log_format (relation.effectref ().c_str (), effect))
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to process relation %s/%s\n",
                format.name ().c_str (),
                relation.effectref ().c_str ()));
    return;
  }

  /// @todo Use the vertex iterator to create connections between log
  ///       formats. The current method is slow and requires searching
  ///       the entire graph when locating the log formats vertex.

  // Create an association between the two log formats.
  graph.connect (format.name (), effect->name ());

  // Create a new relation for this item. First, lets set the
  // relation's effect log format.
  CUTS_Log_Format_Relation lfr;
  lfr.effect (effect);

  // Process the causality (variables) for this relation.
  std::for_each (relation.begin_causality (),
                 relation.end_causality (),
                 boost::bind (&CUTS_Unit_Test_Graph_Builder::process_causality,
                              this,
                              _1,
                              boost::ref (lfr)));

  // Save the relation.
  format.relations ().push_back (lfr);
}

//
// process_casaulity
//
void CUTS_Unit_Test_Graph_Builder::
process_causality (const CUTS::causalityType & causality,
                   CUTS_Log_Format_Relation & relation)
{
  CUTS_Relation_Causality rc (causality.cause ().c_str (),
                              causality.effect ().c_str ());

  relation.causality ().push_back (rc);
}
