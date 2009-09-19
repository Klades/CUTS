// $Id$

#include "Dataflow_Graph_Builder.h"

#if !defined (__CUTS_INLINE__)
#include "Dataflow_Graph_Builder.inl"
#endif

#include "Dataflow_Graph.h"
#include "Log_Format.h"
#include <algorithm>

/**
 * @class process_causality
 *
 * Functor for processing causality relations of a log format that
 * that appear in an XML document.
 */
class process_causality
{
public:
  typedef ::CUTS::XML::relationType::causality_iterator::value_type value_type;

  process_causality (CUTS_Log_Format_Relation & relation)
    : relation_ (relation)
  {

  }

  void operator () (const value_type & causality)
  {
    // Create a new causality relation.
    CUTS_Relation_Causality rc (causality->cause ().c_str (),
                                causality->effect ().c_str ());

    // Add the causality relation with this relation.
    this->relation_.causality ().push_back (rc);
  }

private:
  CUTS_Log_Format_Relation & relation_;
};

/**
 * @class process_relation
 *
 * Functor for processing log format's relation in a XML document.
 */
class process_relation
{
public:
  typedef ::CUTS::XML::relationList::relation_iterator::value_type value_type;

  process_relation (CUTS_Dataflow_Graph & graph, CUTS_Log_Format & format)
    : graph_ (graph),
      format_ (format)
  {

  }

  void operator () (const value_type & relation) const
  {
    // Locate the log format for this effect.
    CUTS_Log_Format * effect;

    if (this->graph_.create_log_format (relation->effectref ().c_str (), effect))
    {
      // Create an association between the two log formats.
      this->graph_.connect (this->format_.name (), effect->name ());

      // Create a new relation for this item. First, lets set the
      // relation's effect log format.
      CUTS_Log_Format_Relation lfr;
      lfr.effect (effect);

      // Process the causality (variables) for this relation.
      std::for_each (relation->begin_causality (),
                     relation->end_causality (),
                     process_causality (lfr));

      // Save the relation.
      this->format_.relations ().push_back (lfr);
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to process relation %s/%s\n",
                  this->format_.name ().c_str (),
                  relation->effectref ().c_str ()));
    }
  }

private:
  CUTS_Dataflow_Graph & graph_;

  CUTS_Log_Format & format_;
};

/**
 * @class process_log_format
 *
 * Functor for processing a log format in a XML document.
 */
class process_log_format
{
public:
  typedef ::CUTS::XML::logformatList::logformat_iterator::value_type value_type;

  process_log_format (CUTS_Dataflow_Graph & graph)
    : graph_ (graph)
  {

  }

  void operator () (const value_type & format) const
  {
    // Create a new log format in the unit test.
    CUTS_Log_Format * lfmt = 0;
    this->graph_.create_log_format (format->id ().c_str (), lfmt);

    // Compile the log format's value.
    lfmt->compile (format->value ().c_str ());

    if (format->relations_p ())
      std::for_each (format->relations ().begin_relation (),
                     format->relations ().end_relation (),
                     process_relation (this->graph_, *lfmt));
  };

private:
  mutable CUTS_Dataflow_Graph & graph_;
};

//
// build
//
bool CUTS_Dataflow_Graph_Builder::
build (const ::CUTS::XML::datagraphType & datagraph, CUTS_Dataflow_Graph & graph)
{
  // Set the name of the graph.
  graph.name (datagraph.name ().c_str ());

  // Process the log formats.
  std::for_each (datagraph.logformats ().begin_logformat (),
                 datagraph.logformats ().end_logformat (),
                 process_log_format (graph));

  return true;
}
