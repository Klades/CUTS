#include <fstream>
#include <sstream>
#include <stdio.h>
#include "Dmac_App.h"
#include "ace/Get_Opt.h"
#include "ace/CORBA_macros.h"
#include "ace/Log_Msg.h"
#include "ace/Process_Manager.h"
#include "ace/Process.h"

static const char * __HELP__ =
"cuts-dmac - Generate the dataflow model for a given system execution trace\n"
"\n"
"USAGE: cuts-dmac [OPTIONS]\n"
"\n"
"General options:\n"
"  -f, --file=FILE        Database file containing the system execution trace\n"
"  -s, --min-sup=MIN-SUP  Minimum support\n"
"  -n, --name=PATH        Name of the dataflow model\n"
"  -l, --spade-loc=LOCATION location of spade\n"
"  -d                     Delete inter\n"
"  -h, --help             print this help message\n";

//
// CUTS_Dmac_App
//
CUTS_Dmac_App::CUTS_Dmac_App (void)
{
  this->delete_intermediate_ = false;
  this->spade_location_ = "";
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

  // Convert to vertical format
  std::cout << "Converting to...." << std::endl;
  if (this->convert_to_vertical () == -1)
    return -1;

  // Sequence minging
  std::cout << "Frequent-Sequence mining...." << std::endl;
  if (this->mine_sequences () == -1)
    return -1;

  // Generation of dataflow
  std::cout << "Generating Dataflow...." << std::endl << std::endl;
  if (this->generate_dataflow () == -1)
    return -1;

  // Delete intermediate files created in the previous steps
  if (this->delete_intermediate_)
  {
    if (remove ("frequent-sequences") != 0)
      return -1;

    if (remove ("Vertical.data") != 0)
      return -1;
  }

  std::cout << std::endl;
  std::cout << "Done." << std::endl;

  return 0;
}

//
// convert_to_vertical
//
int CUTS_Dmac_App::convert_to_vertical ()
{
  std::stringstream data_file;
  data_file << this->data_file_.c_str ();

  // set the output file
  std::string vertical_str (
    "cuts-dmac-vertical --file=" + data_file.str ());

  int flags = O_WRONLY | O_CREAT;
  ACE_HANDLE pipe = ACE_OS::open ("Vertical.data", flags);

  // Run the vertical converter
  if (pipe != ACE_INVALID_HANDLE)
    return this->execute_process (vertical_str.c_str (), ".", pipe);
  else
    return -1;

}

//
// mine_sequences
//
int CUTS_Dmac_App::mine_sequences ()
{
  std::stringstream min_sup;
  std::string sequence_str;
  min_sup << this->min_sup_.c_str ();

  // set the spade location
  if (this->spade_location_ == "")
    sequence_str = "sequence-test -i Vertical.data -s " + min_sup.str () + " -p";
  else
  {
    std::string s (this->spade_location_.c_str ());
    sequence_str = s +  "/sequence-test -i Vertical.data -s " + min_sup.str () + " -p";
  }

  int flags = O_WRONLY | O_CREAT;
  ACE_HANDLE pipe = ACE_OS::open ("frequent-sequences", flags);

  // Run the sequence minign app
  if (pipe != ACE_INVALID_HANDLE)
    return this->execute_process (sequence_str.c_str (), ".", pipe);
  else
    return -1;

}


//
// generate_dataflow
//
int CUTS_Dmac_App::generate_dataflow ()
{
  // final log format mingng

  std::stringstream data_file;
  data_file << this->data_file_.c_str ();

  std::stringstream name;
  name << this->name_.c_str ();

  std::string dmac_core_str (
    "cuts-dmac-core -i frequent-sequences -f " + data_file.str ()
    + " -n" + name.str ());

  ACE_HANDLE handle = ACE_INVALID_HANDLE;

  return execute_process (dmac_core_str.c_str (), ".", handle);

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

int CUTS_Dmac_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "dhf:s:n:l:";

  ACE_Get_Opt get_opt (argc, argv, optstr);
  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("min-sup", 's', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("spade-loc", 'l', ACE_Get_Opt::ARG_OPTIONAL);
  get_opt.long_option ("delete", 'd');
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
      else if (ACE_OS::strcmp (get_opt.long_option (), "min-sup") == 0)
      {
        this->min_sup_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "name") == 0)
      {
        this->name_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "spade-loc") == 0)
      {
        this->spade_location_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "help") == 0)
      {
        this->print_help ();
      }
      break;

    case 'f':
      this->data_file_ = get_opt.opt_arg ();
      break;

    case 's':
      this->min_sup_ = get_opt.opt_arg ();
      break;

    case 'n':
      this->name_ = get_opt.opt_arg ();
      break;

    case 'l':
      this->spade_location_ = get_opt.opt_arg ();
      break;

    case 'd':
      this->delete_intermediate_ = true;
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