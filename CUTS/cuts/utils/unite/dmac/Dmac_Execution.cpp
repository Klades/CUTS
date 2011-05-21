#include "Dmac_Execution.h"
#include "cuts/Auto_Functor_T.h"
#include <sstream>
#include <iostream>
#include "ace/CORBA_macros.h"

//
// CUTS_Dmac_Execution
//
CUTS_Dmac_Execution::CUTS_Dmac_Execution (ACE_CString host_name,
                                          int thread_id,
                                          CUTS_Test_Database & test_data,
                                          std::vector <CUTS_Dmac_Log_Format *> & final_patterns)
: host_name_ (host_name),
  thread_id_ (thread_id),
  test_data_ (test_data),
  final_patterns_ (final_patterns),
  lf_graph_ (0)
{


}

//
// ~CUTS_Dmac_Execution
//
CUTS_Dmac_Execution::~CUTS_Dmac_Execution ()
{


}

//
// thread_id
//
int CUTS_Dmac_Execution::thread_id ()
{
  return this->thread_id_;
}

//
// host_name
//
ACE_CString CUTS_Dmac_Execution::host_name ()
{
  return this->host_name_;
}

//
// Extract_Relations
//
void CUTS_Dmac_Execution::Extract_Relations ()
{
  ADBC::SQLite::Query * query = this->test_data_.create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
    query, &ADBC::SQLite::Query::destroy);

  std::ostringstream sqlstr;

  // Select the traces categorized by the thread_id and the
  // host_name

  sqlstr << "SELECT * FROM cuts_logging WHERE ";
  sqlstr << "hostname='" << this->host_name_.c_str () << "' AND ";
  sqlstr << "thread_id='" << this->thread_id_ << "'";
  sqlstr << " ORDER BY lid";

  ADBC::SQLite::Record * record =
    &query->execute (sqlstr.str ().c_str ());

  char message[1024];

  // check the log format with each message in the trace and
  // fill the execution history in terms of the log formats
  for ( ; !record->done (); record->advance ())
  {
    int cur_id = 0;
    CUTS_DMAC_UTILS::string_vector trace_items;
    record->get_data (5, message, sizeof (message));
    std::string message_str (message);
    CUTS_DMAC_UTILS::tokenize (message_str, trace_items);

    cur_id = this->match_log_format (trace_items);

    if (cur_id > -1)
      this->lf_order_list_.push_back (cur_id);

  }
  record->reset ();

  // Finally create the dataflow graph
  this->create_data_flow_graph ();

}

//
// match_log_format
//
int CUTS_Dmac_Execution::match_log_format (CUTS_DMAC_UTILS::string_vector & trace_items)
{
  std::string empty_str ("{}");
  int matching_format = -1;

  for (unsigned int i = 0; i < this->final_patterns_.size (); i++)
  {
    // Staic parts should be matched and if it is a mismatch
    // the log format should have a {} in the corrsponding
    // item for continue the matching
    CUTS_DMAC_UTILS::string_vector & log_format =
        this->final_patterns_ [i]->log_format_items ();

    if (trace_items.size () == log_format.size ())
    {
      for (unsigned int j = 0; j < log_format.size (); j++)
      {
        if (log_format [j].compare (empty_str) != 0)
        {
          if (log_format [j].compare (trace_items [j]) != 0)
          {
            matching_format = -1;
            break;
          }
          else
            matching_format = this->final_patterns_ [i]->id ();
        }
      }

      // For each matching log message incrment the coverage
      // value for this log format.

      if (matching_format >= 0)
      {
        this->final_patterns_ [i]->add_varaible_values (trace_items);
        this->final_patterns_ [i]->increment_coverage ();
        break;
      }
    }
  }

  return matching_format;
}

//
// create_data_flow_graph
//
void CUTS_Dmac_Execution::create_data_flow_graph ()
{
  ACE_NEW_THROW_EX (this->lf_graph_,
                    CUTS_Dmac_Log_Format_Graph (this->lf_order_list_,
                                                this->final_patterns_),
                    ACE_bad_alloc ());

  this->lf_graph_->build_graph (this);

  std::vector <CUTS_Dmac_Log_Format *>::iterator it;

  for (it = this->final_patterns_.begin (); it != this->final_patterns_.end ();
       it++)
    (*it)->print_relations (this);
}

//
// == operator
//
bool
CUTS_Dmac_Execution::operator == (CUTS_Dmac_Execution & execution)
{
  // Check whether the host_name and the thread_id of two
  // executions are the same.

  if (execution.host_name_ == this->host_name_ &&
      execution.thread_id_ == this->thread_id_)
      return true;
  else
    return false;
}