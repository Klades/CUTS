#include "ace/Get_Opt.h"
#include <iostream>
#include <fstream>
#include "cuts/utils/testing/Test_Database.h"
#include "ace/Log_Msg.h"
#include "adbc/SQLite/Connection.h"
#include "cuts/Auto_Functor_T.h"
#include "Dmac_Relation_Miner.h"
#include "Dmac_Log_Format_Graph.h"
#include "ace/OS_Memory.h"
#include "ace/CORBA_macros.h"
#include "Dmac_Dataflow_File_Generator.h"


//
// CUTS_Dmac_Relation_Miner
//
CUTS_Dmac_Relation_Miner::CUTS_Dmac_Relation_Miner (
    ACE_CString & name,
    CUTS_Test_Database & testdata,
    std::vector <CUTS_Dmac_Log_Format *> & log_formats)
: name_ (name),
  testdata_ (testdata),
  final_log_formats_ (log_formats)
{

}

//
// ~CUTS_Dmac_Relation_Miner
//
CUTS_Dmac_Relation_Miner::~CUTS_Dmac_Relation_Miner (void)
{

}


void CUTS_Dmac_Relation_Miner::mine_relations (void)
{
  this->find_relations ();

  // Generate the datagraph file.
  this->generate_datagraph_file ();

}

void CUTS_Dmac_Relation_Miner::delims (std::string delims)
{
  this->delims_ = delims;
}

//
// find_relations
//
void CUTS_Dmac_Relation_Miner::find_relations (void)
{
  // Get all the distinct host_name and thread_id
  // pairs
  ADBC::SQLite::Query * query = this->testdata_.create_query ();

  CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
    query, &ADBC::SQLite::Query::destroy);

  ADBC::SQLite::Record * record = &query->execute (
    "SELECT DISTINCT hostname, thread_id FROM cuts_logging ORDER BY hostname");

  int i = 0;
  ACE_CString host_name;
  long thread_id = 0;

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
                                           this->testdata_,
                                           this->final_log_formats_),
                      ACE_bad_alloc ());

    // Extract relations for each different execution

    std::cout << "Relations for Thread-" << thread_id << std::endl;

    execution->delims (this->delims_);

    execution->Extract_Relations ();

    this->executions_list_.push_back (execution);

    std::cout << "----------------------------" << std::endl;
    std::cout << std::endl;
  }
  record->reset ();
}

//
// generate_datagraph_file
//
void CUTS_Dmac_Relation_Miner::generate_datagraph_file (void)
{
  // Generate the datagraph file using all identified
  // log formats.
  // Each execution context is a different datagraph in the
  // datagraph file.

  CUTS_Dmac_Dataflow_File_Generator generator (this->final_log_formats_,
                                               this->name_.c_str ());

  generator.open_file ();

  generator.init_xml ();

  std::vector <CUTS_Dmac_Execution *>::iterator it;

  for (it = this->executions_list_.begin ();
       it != this->executions_list_.end (); it++)
    generator.generate_xml (*it);

  generator.close_file ();

}

