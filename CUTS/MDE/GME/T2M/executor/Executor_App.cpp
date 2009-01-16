// $Id$

#include "Executor_App.h"

#if !defined (__CUTS_INLINE__)
#include "Executor_App.inl"
#endif

#include "../parsers/T2M_Parser.h"
#include "ace/ACE.h"
#include "ace/Get_Opt.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_unistd.h"
#include "ace/DLL.h"
#include "ace/streams.h"
#include "game/XML.h"
#include <sstream>

static const char * __HELP__ =
"GME's text-2-model executor application\n"
"\n"
"USAGE: gmet2m-exec [OPTIONS]\n"
"\n"
"General Options:\n"
"  -f, --filename=FILE             use FILE for input\n"
"  -p, --project=PROJECT           import file into PROJECT\n"
"  --target=PATH                   use element at PATH as parent\n"
"  --parser=LIBRARY                load text-2-model parser in LIBRARY\n"
"\n"
"Informative Options:\n"
"  -h, --help                      print this help message\n";

//
// run_main
//
int CUTS_T2M_Executor_App::run_main (int argc, char * argv [])
{
  if (this->parse_args (argc, argv) != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to parse command-line arguments\n"),
                       -1);

  // Open the project for writing.
  if (this->open_gme_project () != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open GME project [file=%s]\n",
                       this->opts_.project_.c_str ()),
                       -1);

  // Load the parser from its file.
  ACE_DLL dll;

  if (dll.open (this->opts_.parser_.c_str ()) == 0)
  {
    // Begin a new transaction.
    this->project_.begin_transaction ();

    void * symbol = dll.symbol (GME_T2M_CREATE_PARSER_FUNC_STR);

    if (symbol == 0)
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to load factory symbol [%s]\n",
                         GME_T2M_CREATE_PARSER_FUNC_STR),
                         -1);

    // Cast the symbol to a facotry function.
    typedef GME_T2M_Parser * (* CREATION_FUNCTION) (void);
    CREATION_FUNCTION factory = reinterpret_cast <CREATION_FUNCTION> (symbol);

    // Create the parser using the factory.
    GME_T2M_Parser * parser = factory ();

    if (parser != 0)
    {
      // Get the root folder of the project.
      GME::Folder root_folder = this->project_.root_folder ();

      // Determine what is the parent object for parsing.
      GME::Object target;

      if (this->opts_.target_.empty ())
        target = this->project_.root_folder ();
      else
        target = root_folder.find_object_by_path (this->opts_.target_);

      if (parser->parse (this->opts_.filename_.c_str (), target))
      {
        ACE_DEBUG ((LM_DEBUG,
                    "%T (%t) - %M - successully parsed %s\n",
                    this->opts_.filename_.c_str ()));

        this->project_.commit_transaction ();
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to parse %s\n",
                    this->opts_.filename_.c_str ()));

        this->project_.abort_transaction ();
      }

      // Destroy the parser.
      parser->destroy ();
    }
    else
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to create parser\n"),
                         -1);
  }
  else
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open parser module [%m]\n"),
                       -1);

  return 0;
}

//
// parse_args
//
int CUTS_T2M_Executor_App::parse_args (int argc, char * argv [])
{
  const char * optargs = "hp:f:";

  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("project", 'p', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("parser", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("target", ACE_Get_Opt::ARG_REQUIRED);

  char opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (ACE_OS::strcmp ("project", get_opt.long_option ()) == 0)
      {
        this->opts_.project_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("file", get_opt.long_option ()) == 0)
      {
        this->opts_.filename_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("parser", get_opt.long_option ()) == 0)
      {
        this->opts_.parser_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("target", get_opt.long_option ()) == 0)
      {
        this->opts_.target_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("help", get_opt.long_option ()) == 0)
      {
        this->print_help ();
      }
      break;

    case 'h':
      this->print_help ();
      break;

    case 'f':
      this->opts_.filename_ = get_opt.opt_arg ();
      break;

    case 'p':
      this->opts_.project_ = get_opt.opt_arg ();
      break;
    }
  }

  // Validate the command-line arguments.
  return this->opts_.validate () ? 0 : -1;
}

//
// print_help
//
void CUTS_T2M_Executor_App::print_help (void)
{
  std::cerr << ::__HELP__ << std::endl;
  ACE_OS::exit (0);
}

//
// open_gme_project
//
int CUTS_T2M_Executor_App::open_gme_project (void)
{
  if (this->opts_.is_mga_file_)
  {
    std::ostringstream connstr;
    connstr << "MGA=" << this->opts_.project_;

    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - opening %s for processing\n",
                this->opts_.project_.c_str ()));

    this->project_.open (connstr.str ());
  }
  else
  {
    // Get information about the XML file.
    GME::XML_Parser parser;
    GME::XML_Info info;

    parser.get_info (this->opts_.project_, info);

    ACE_TCHAR pathname[MAX_PATH];

    if (ACE::get_temp_dir (pathname, MAX_PATH - 20) != -1)
    {
      // Create a temporary filename for the project.
      ACE_OS::strcat (pathname, "picmlin-XXXXXX.mga");
      ACE_HANDLE fd = ACE_OS::mkstemp (pathname);

      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - creating temporary file '%s'\n",
                  pathname));

      if (fd == 0)
        return -1;

      // Delete the temporary file, which we aren't using.
      ACE_OS::close (fd);
      ACE_OS::unlink (pathname);

      // Create the full pathname.
      std::ostringstream connstr;
      connstr << "MGA=" << pathname;

      // Create a empty PICML project and import the XML file.
      ACE_DEBUG ((LM_INFO,
                  "%T (%t) - %M - importing '%s' for processing\n",
                  this->opts_.project_.c_str ()));

      this->project_.create (connstr.str (), info.paradigm_);
      parser.parse (this->opts_.project_, this->project_);
    }
    else
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to open temp file [%m]\n"),
                         -1);
  }

  // Make sure we have the add-ons enabled. Otherwise, the project
  // may enter an inconsistent state.
  if (this->opts_.enable_auto_addons_)
    this->project_.enable_auto_addons (true);

  return 0;
}
