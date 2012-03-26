#include "Dmac_Execution.h"
#include "cuts/Auto_Functor_T.h"
#include <sstream>
#include <iostream>
#include "ace/CORBA_macros.h"

//
// CUTS_Dmac_Execution
//
CUTS_Dmac_Execution::CUTS_Dmac_Execution (
    ACE_CString host_name,
    int thread_id,
    CUTS_Test_Database & test_data,
    std::vector <CUTS_Dmac_Log_Format *> & final_patterns)
: host_name_ (host_name),
  thread_id_ (thread_id),
  test_data_ (test_data),
  final_patterns_ (final_patterns)
{


}

//
// ~CUTS_Dmac_Execution
//
CUTS_Dmac_Execution::~CUTS_Dmac_Execution (void)
{


}

//
// thread_id
//
int CUTS_Dmac_Execution::thread_id (void)
{
  return this->thread_id_;
}

//
// host_name
//
ACE_CString CUTS_Dmac_Execution::host_name (void)
{
  return this->host_name_;
}

void CUTS_Dmac_Execution::delims (std::string delims)
{
  this->delims_ = delims;
}

//
// create_execution_order_list
//
void CUTS_Dmac_Execution::create_order_list (void)
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

  char message[10000];

  // check the log format with each message in the trace and
  // fill the execution history in terms of the log formats
  for ( ; !record->done (); record->advance ())
  {
    int cur_id = 0;
    CUTS_DMAC_UTILS::string_vector trace_items;
    record->get_data (5, message, sizeof (message));
    std::string message_str (message);
    CUTS_DMAC_UTILS::tokenize (message_str,
                               trace_items,
                               this->delims_);

    //cur_id = this->match_log_format (trace_items);
    cur_id = CUTS_DMAC_UTILS::match_log_format (trace_items,
                                                this->final_patterns_,
                                                true);

    if (cur_id > -1)
      this->lf_order_list_.push_back (cur_id);
  }
  record->reset ();
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