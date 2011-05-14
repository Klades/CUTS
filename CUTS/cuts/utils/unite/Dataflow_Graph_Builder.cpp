// $Id$

#include "Dataflow_Graph_Builder.h"

#if !defined (__CUTS_INLINE__)
#include "Dataflow_Graph_Builder.inl"
#endif

#include "Dataflow_Graph.h"
#include "Log_Format.h"
#include <algorithm>
#include "ace/DLL.h"
#include "Log_Format_Adapter.h"
#include "ace/Auto_Ptr.h"


typedef CUTS_Log_Format_Adapter * (* Adapter_creator) (void);
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

    // Add the causality with this relation.
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

    // If there is an adapter then upodate this log format with its variables

    if(this->graph_.adapter ())
    {
      this->graph_.adapter ()->update_log_format (lfmt);
    }

    if (format->relations_p ())
      std::for_each (format->relations ().begin_relation (),
                     format->relations ().end_relation (),
                     process_relation (this->graph_, *lfmt));

    // If adapter is set  then update this log format's relations

    if(this->graph_.adapter ())
    {
      this->graph_.adapter ()->update_relations (lfmt);
    }

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

  // If adapter is set then we will first load the adapter dll

  if (datagraph.adapter_p ())
  {
    // Get the location from the datagraph file

    ACE_DLL adapter_dll;
    const char * location = datagraph.adapter ().c_str ();

    // loadding the dll
    int retval = adapter_dll.open (location,
                                   ACE_DEFAULT_SHLIB_MODE,
                                   false);

    if (0 != retval)
    {
      ACE_ERROR ((LM_ERROR,
                 ACE_TEXT ("%T (%t) - %M - error loading opening %s; %m\n"),
                 location));
    }


    // Get symbols

    void * adapter_symbol = adapter_dll.symbol (CUTS_LOG_FORMAT_ADAPTER_SYMBOL_NAME);



    if (0 == adapter_symbol)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T - %M - failed to extract entry point %s\n",
                         ACE_TEXT ("create_Cuts_Log_Format_Adapter")),
                         -1);
    }

    // The adapter object is set in the datagraph so it can be passed
    // further for calling the other methods

    // Creates the adapter from the loaded dll
    ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (adapter_symbol);
    Adapter_creator adapter_creator = reinterpret_cast <Adapter_creator> (tmp_ptr);

    CUTS_Log_Format_Adapter * adapter = adapter_creator ();

    ACE_Auto_Ptr <CUTS_Log_Format_Adapter> auto_clean (adapter);

    // Intializing the adapter
    auto_clean->init ();

    // Set in the Data_grpah
    graph.adapter (adapter);

    auto_clean.release ();

}

  // Process the log formats.
  std::for_each (datagraph.logformats ().begin_logformat (),
                 datagraph.logformats ().end_logformat (),
                 process_log_format (graph));

  return true;
}