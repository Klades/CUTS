#include <fstream>
#include <sstream>
#include <stdio.h>
#include "Dmac_App.h"
#include "ace/Get_Opt.h"
#include "ace/CORBA_macros.h"
#include "ace/Log_Msg.h"
#include "ace/Process_Manager.h"
#include "ace/Process.h"
#include "Dmac_Log_File_Miner.h"
#include "Dmac_Log_Database_Miner.h"
#include "Dmac_Vertical_Generator.h"
#include "Dmac_Relation_Miner.h"
#include "cuts/Auto_Functor_T.h"

#define COVERAGE 80

static const char * __HELP__ =
"cuts-dmac - Generate the dataflow model for a given system execution trace\n"
"\n"
"USAGE: cuts-dmac [OPTIONS]\n"
"\n"
"General options:\n"
"  -f, --file=FILE        Database file containing the system execution trace\n"
"  -s, --min-sup=MIN-SUP  Minimum support\n"
"  -n, --name=PATH        Name of the dataflow model\n"
"  -d, --delims=DELIMITERS Set of the delimiters to break the message\n"
"  -h, --help             print this help message\n";

//
// CUTS_Dmac_App
//
CUTS_Dmac_App::CUTS_Dmac_App (void)
: round_ (0),
  coverage_ (0.0),
  current_coverage_ (0)
{

}

//
// ~CUTS_Dmac_App
//
CUTS_Dmac_App::~CUTS_Dmac_App (void)
{

}

//
// run_main
//
int CUTS_Dmac_App::run_main (int argc, char * argv [])
{
  if (this->parse_args (argc, argv) == -1)
    return -1;

  // Open the database

  if (!this->open_database ())
    return -1;

  // Find the log formats
  // this->find_log_formats ();

  // this->print_final_patterns ();

  // this->print_coverage ();

  // std::cout << std::endl;

  // Generation of dataflow
  std::cout << "Generating Dataflow...." << std::endl << std::endl;

  this->create_log_formats_from_file ();

  // Relation mining step
  CUTS_Dmac_Relation_Miner rel_miner (this->name_,
                                      this->testdata_,
                                      this->log_formats_);

  std::string temp (this->delims_.c_str ());
  //std::string delimitters = " \n\t" + temp;
  std::string delimitters (" \n\t");

  rel_miner.delims (delimitters);

  rel_miner.mine_relations ();

  std::cout << std::endl;
  std::cout << "Done." << std::endl;

  return 0;
}

//
// find_log_formats
//
void CUTS_Dmac_App::find_log_formats ()
{
  // Add the user provided delimitters to the
  // default delimitters

  std::string temp (this->delims_.c_str ());
  std::string delimitters = " \n\t" + temp;

  // In the first round we always mine the database file

  this->round_ = 1;

  CUTS_Dmac_DB_Vertical_Generator db_vgen (delimitters);

  if ((db_vgen.generate (this->data_file_, this->round_)) == -1)
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - Vertical generator failed"));

  // Frequent-sequence mining step
  if (this->mine_sequences () == -1)
    return;

  std::stringstream pattern_file;

  pattern_file << this->round_ << "-sequence";

  ACE_CString str (pattern_file.str ().c_str ());

  // Now we have the frequent-sequences , lets construct the log formats
  CUTS_Dmac_Log_Database_Miner db_miner (str,
                                         this->data_file_,
                                         this->log_formats_,
                                         this->testdata_);

  // set the delimitters
  db_miner.delim (delimitters);

  // Find the maximal sequences
  db_miner.refine ();

  // Mine for log formats
  db_miner.mine ();

  // Generate the next dataset for next round of mining
  db_miner.create_next_dataset (this->round_);

  // Accumulate the results
  this->accumulate (&db_miner);

  // Keep on iterating the process until we get a
  // satisfiable coverage

  while (this->coverage_ < COVERAGE)
  {
    // Now we do the mining process for the intermediate datasets
    // which are stored in files
    this->round_++;
    std::stringstream data_file;

    // File name

    data_file << this->round_ << "-dataset";
    ACE_CString file_name (data_file.str ().c_str ());

    // Vertical generation

    CUTS_Dmac_File_Vertical_Generator file_vgen (delimitters);
    file_vgen.generate (file_name, this->round_);

    this->current_records_ = file_vgen.row_count_;

    // Sequence mining

    if (this->mine_sequences () == -1)
      return;

    std::stringstream new_pattern_file;
    new_pattern_file << this->round_ << "-sequence";
    ACE_CString new_str (new_pattern_file.str ().c_str ());
    CUTS_Dmac_Log_File_Miner file_miner (new_str,
                                         file_name,
                                         this->log_formats_);

    // log format mining

    file_miner.delim (delimitters);

    file_miner.refine ();

    file_miner.mine ();

    // create the next dataset

    file_miner.create_next_dataset (this->round_);

    // Add the found log formats to the log format list

    this->accumulate (&file_miner);
  }
}

//
// mine_sequences
//
int CUTS_Dmac_App::mine_sequences ()
{
  std::stringstream min_sup;
  std::stringstream v_data_file;
  std::string sequence_str;
  std::stringstream output_stream;

  // For the first round we use the min-sup provided
  // by the user.

  if (this->round_ == 1)
    min_sup << this->min_sup_.c_str ();

  // Otherwise we calculate the min-sup based on the ratio of
  // the current number of records in the dataset and the total
  // number of records

  else
  {
    float reducing_factor = 1 / (float)this->round_;
    long original = ACE_OS::atol (this->min_sup_.c_str ());
    long relative_min_sup = (long)((float)original / (float)this->total_records_ *
                            (float)this->current_records_ * reducing_factor);
    min_sup << relative_min_sup;
    std::cout << "Minimum support is " << relative_min_sup << std::endl;
  }
  // Name of the vertical data file

  v_data_file << this->round_ << ".data";

  // Command to execute the sequence mining tool
  sequence_str = "sequence-test -i " + v_data_file.str () +
                 " -s " + min_sup.str () + " -p";

  // Name of the file where the output of sequence mining is written

  output_stream << this->round_ << "-sequence";

  int flags = O_WRONLY | O_CREAT;

  ACE_HANDLE pipe = ACE_OS::open (output_stream.str ().c_str (), flags);

  // Run the sequence minign app
  if (pipe != ACE_INVALID_HANDLE)
    return this->execute_process (sequence_str.c_str (), ".", pipe);
  else
    return -1;
}

//
// accumulate
//
void CUTS_Dmac_App::accumulate (CUTS_Dmac_Log_Miner * log_miner)
{
  // Get the current log format set

  std::vector <CUTS_Dmac_Log_Format *> temp
    = log_miner->current_items ();

  std::vector <CUTS_Dmac_Log_Format *>::iterator it;

  for (it = temp.begin (); it != temp.end (); it++)
  {
    // Add the new log formats and Increment the coverage
    this->log_formats_.push_back (*it);
    this->current_coverage_ += (*it)->coverage ();
  }

  // Update the current coverage

  this->coverage_ = ((float)this->current_coverage_/
                    (float)this->total_records_)*100;
}


bool CUTS_Dmac_App::open_database ()
{
  // Open the connection with the database

  if (!this->testdata_.open (this->data_file_))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       data_file_.c_str()),
                       false);
  }
  else
  {
    // Find the total number of log messages

    ADBC::SQLite::Query * query = this->testdata_.create_query ();

    CUTS_Auto_Functor_T <ADBC::SQLite::Query> auto_clean (
      query, &ADBC::SQLite::Query::destroy);

    ADBC::SQLite::Record * record = &query->execute (
          "SELECT COUNT(*) AS result FROM cuts_logging");

    long count;
    record->get_data (0, count);

    this->total_records_ = count;

    record->reset ();

    return true;

  }
}


//
// print_coverage
//
void CUTS_Dmac_App::print_coverage ()
{
  std::cout << "Total Records = " << this->total_records_ << std::endl;
  float total_coverage = 0;

  for (unsigned int i=0; i < this->log_formats_.size (); i++)
  {
    // Print the log formats and the coverage
    long count = this->log_formats_ [i]->coverage ();
    float percentage = ((float)count/(float)this->total_records_)*100;
    total_coverage += percentage;
    std::stringstream lfstring;
    lfstring << " LF" << this->log_formats_[i]->id () << " - ";
    lfstring << "Count = " << count << " Percent = " << percentage << "%";
    std::cout << lfstring.str ();
    std::cout << std::endl;
  }
  std::cout << "Total coverage : " << total_coverage;
}

//
// print_final_patterns
//
void CUTS_Dmac_App::print_final_patterns ()
{
  // Print the results

  std::cout << "Results" << std::endl;
  std::cout << "=======" << std::endl << std::endl;
  for (unsigned int i=0; i < this->log_formats_.size (); i++)
  {
    std::stringstream lfstring;
    lfstring << " LF" << this->log_formats_[i]->id ();
    std::cout << lfstring.str () <<" = ";

    for (unsigned int j=0;
         j < this->log_formats_[i]->log_format_items ().size ();
         j++)
      std::cout << this->log_formats_[i]->log_format_items ().at (j) <<" ";

    std::cout << std::endl;
  }
}


//
// print_help
//
void CUTS_Dmac_App::print_help (void)
{
  std::cerr << __HELP__ << std::endl;
  ACE_OS::exit (0);
}


//
// parse arguments
//

//int CUTS_Dmac_App::parse_args (int argc, char * argv [])
//{
//  const char * optstr = "hf:s:n:d:";
//
//  ACE_Get_Opt get_opt (argc, argv, optstr);
//  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);
//  get_opt.long_option ("min-sup", 's', ACE_Get_Opt::ARG_REQUIRED);
//  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
//  get_opt.long_option ("delims", 'd', ACE_Get_Opt::ARG_REQUIRED);
//  get_opt.long_option ("help", 'h');
//
//  char ch;
//
//  while ((ch = get_opt ()) != EOF)
//  {
//    switch (ch)
//    {
//    case 0:
//      if (ACE_OS::strcmp (get_opt.long_option (), "file") == 0)
//      {
//        this->data_file_ = get_opt.opt_arg ();
//      }
//      else if (ACE_OS::strcmp (get_opt.long_option (), "min-sup") == 0)
//      {
//        this->min_sup_ = get_opt.opt_arg ();
//      }
//      else if (ACE_OS::strcmp (get_opt.long_option (), "name") == 0)
//      {
//        this->name_ = get_opt.opt_arg ();
//      }
//      else if (ACE_OS::strcmp (get_opt.long_option (), "delims") == 0)
//      {
//        this->delims_ = get_opt.opt_arg ();
//      }
//      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
//      {
//        this->print_help ();
//      }
//      break;
//
//    case 'f':
//      this->data_file_ = get_opt.opt_arg ();
//      break;
//
//    case 's':
//      this->min_sup_ = get_opt.opt_arg ();
//      break;
//
//    case 'n':
//      this->name_ = get_opt.opt_arg ();
//      break;
//
//    case 'd':
//      this->delims_ = get_opt.opt_arg ();
//      break;
//
//    case 'h':
//      this->print_help ();
//    }
//  }
//  return 0;
//}


int CUTS_Dmac_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "hf:l:n:";

  ACE_Get_Opt get_opt (argc, argv, optstr);
  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("lffile", 'l', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h');

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "file") == 0)
      {
        this->data_file_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "lffile") == 0)
      {
        this->lf_file_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "name") == 0)
      {
        this->name_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        this->print_help ();
      }
      break;

    case 'f':
      this->data_file_ = get_opt.opt_arg ();
      break;

    case 'l':
      this->lf_file_ = get_opt.opt_arg ();
      break;

    case 'n':
      this->name_ = get_opt.opt_arg ();
      break;

   case 'h':
      this->print_help ();
    }
  }
  return 0;
}


//
// execute_process
//
int CUTS_Dmac_App::execute_process (const char * args,
                                    const char * working_dir,
                                    ACE_HANDLE & pipe)
{
  ACE_Process_Options options;

  // set the options
  options.command_line ("%s", args);
  options.working_directory (working_dir);
  options.set_handles (ACE_INVALID_HANDLE, pipe, ACE_INVALID_HANDLE);

  ACE_Process_Manager * proc_man = ACE_Process_Manager::instance ();

  // spwan the process
  pid_t pid = proc_man->spawn (options);

  if (pid == ACE_INVALID_PID)
    ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to execute process"),
                         -1);

  else
    ACE_OS::close (pipe);

  // wait for the process to return
  if (proc_man->wait () == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - Failed to wait for the project"),
                         -1);

  return 0;

}

void CUTS_Dmac_App::
create_log_formats_from_file ()
{
  std::string delims (" \t\n");
  ifstream lf_file;
  lf_file.open (this->lf_file_.c_str ());
  lf_file.seekg (0, ios::beg);
  if (lf_file.is_open ())
  {
    size_t i = 0;
    while (lf_file.good ())
    {
      CUTS_DMAC_UTILS::string_vector word_list;
      std::string row;
      getline (lf_file, row);
      CUTS_DMAC_UTILS::tokenize (row, word_list, delims);
      i++;
      CUTS_Dmac_Log_Format * lf = new CUTS_Dmac_Log_Format (i, word_list);
      this->log_formats_.push_back (lf);
    }
    lf_file.close ();
  }
}