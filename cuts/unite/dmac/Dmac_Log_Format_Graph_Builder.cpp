#include "Dmac_Log_Format_Graph_Builder.h"
#include "Dmac_Execution.h"
#include "ace/Log_Msg.h"
#include "adbc/SQLite/Connection.h"
#include "cuts/Auto_Functor_T.h"
#include "ace/OS_Memory.h"
#include "ace/CORBA_macros.h"


/**
 * @class process_execution
 *
 * Functor for processing an Execution Context.
 */
class process_execution
{
public:

  typedef std::vector <CUTS_Dmac_Execution *>::iterator::value_type value_type;

  process_execution (CUTS_Dmac_Log_Format_Graph & graph,
                     std::vector <CUTS_Dmac_Log_Format *> & log_formats)
    : graph_ (graph),
      log_formats_ (log_formats)
  {
  }

  void operator () (const value_type & execution) const
  {
    this->graph_.extend_graph (this->log_formats_, execution);
  }

private:
  mutable CUTS_Dmac_Log_Format_Graph & graph_;
  std::vector <CUTS_Dmac_Log_Format *> & log_formats_;
};


//
// CUTS_Dmac_Log_Format_Graph_Builder
//
CUTS_Dmac_Log_Format_Graph_Builder::
CUTS_Dmac_Log_Format_Graph_Builder (void)
{

}

//
// ~CUTS_Dmac_Log_Format_Graph_Builder
//
CUTS_Dmac_Log_Format_Graph_Builder::
~CUTS_Dmac_Log_Format_Graph_Builder (void)
{

}

//
// build
//
bool CUTS_Dmac_Log_Format_Graph_Builder::
build (CUTS_Dmac_Log_Format_Graph & graph,
       CUTS_Test_Database & testdata,
       std::vector <CUTS_Dmac_Log_Format *> & log_formats)
{

  // First get all the different execution contexts.

  ADBC::SQLite::Query * query = testdata.create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
    query, &ADBC::SQLite::Query::destroy);

  ADBC::SQLite::Record * record = &query->execute (
    "SELECT DISTINCT hostname, thread_id FROM cuts_logging ORDER BY hostname");

  ACE_CString host_name;
  long thread_id = 0;
  std::vector <CUTS_Dmac_Execution *> executions_list;

  for ( ; !record->done (); record->advance ())
  {
    // Create an execution contex for each different
    // thread_id and host_name pair

    record->get_data (0, host_name);
    record->get_data (1, thread_id);

    CUTS_Dmac_Execution * execution = 0;

    ACE_NEW_THROW_EX (execution,
                      CUTS_Dmac_Execution (host_name,
                                           thread_id,
                                           testdata,
                                           log_formats),
                      ACE_bad_alloc ());

    std::string delimitters = " \n\t";
    execution->delims (delimitters);

    // Get the execution history in terms of abstract
    // log formats.

    execution->create_order_list ();

    executions_list.push_back (execution);
  }
  record->reset ();

  // Process the log formats.
  std::for_each (executions_list.begin (),
                 executions_list.end (),
                 process_execution (graph, log_formats));

  graph.find_inter_ec_relations (log_formats, testdata);

  return true;

}