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

//
// mine_relations
//
void CUTS_Dmac_Relation_Miner::mine_relations (void)
{
  this->find_relations ();

  // Generate the datagraph file.
  this->generate_datagraph_file ();

}

//
// delims
//
void CUTS_Dmac_Relation_Miner::delims (std::string delims)
{
  this->delims_ = delims;
}

//
// find_relations
//
void CUTS_Dmac_Relation_Miner::find_relations (void)
{
  CUTS_Dmac_Log_Format_Graph_Builder builder;

  builder.build (this->graph_,
                 this->testdata_,
                 this->final_log_formats_);

}

//
// generate_datagraph_file
//
void CUTS_Dmac_Relation_Miner::generate_datagraph_file (void)
{
  // Generate the datagraph file using all identified
  // log formats.
  CUTS_Dmac_Dataflow_File_Generator generator (this->final_log_formats_,
                                               this->name_.c_str ());

  generator.open_file ();

  generator.init_xml ();

  generator.generate_xml ();

  generator.close_file ();

}