// $Id$

#include "Template_App.h"
#include "boost/spirit/iterator/file_iterator.hpp"
#include "cuts/utils/Property_Map_File.h"
#include "cuts/utils/Property_Parser.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"

static const char * __HELP__ =
"Template expansion engine for property-based configuration files\n"
"\n"
"USAGE: cutstmpl [OPTIONS] TEMPLATE\n"
"\n"
"OPTIONS:\n"
"  -c, --config=FILE          property configuration file\n"
"  -Dname=VALUE               define property name with VALUE\n"
"  --use-env                  use environment variables\n"
"\n"
"  -o OUTFILE                 output expansion to OUTFILE\n"
"\n"
"  -v, --verbose              print verbose infomration\n"
"  --debug                    print debugging information\n"
"  -h, --help                 print this help message\n";

//
// CUTS_Template_App
//
CUTS_Template_App::CUTS_Template_App (void)
: expander_ (prop_map_)
{

}

//
// ~CUTS_Template_App
//
CUTS_Template_App::~CUTS_Template_App (void)
{

}

//
// run_main
//
int CUTS_Template_App::run_main (int argc, char * argv [])
{
  if (this->parse_args (argc, argv) == -1)
    return 1;

  // First, load the configuration file if the user specified one
  // on the command-line.
  if (!this->opts_.config_.empty ())
  {
    if (this->load_property_file (this->opts_.config_))
    {
      ACE_DEBUG ((LM_INFO,
                  "%T - %M - successfully loaded property file %s\n",
                  this->opts_.config_.c_str ()));
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to load property file %s\n",
                  this->opts_.config_.c_str ()));
    }
  }

  // Next, parse the properties explicitly defined on the command-line.
  // These take precedence over the properties defined in the configuration
  // file.
  if (this->opts_.defines_.size () > 0)
  {
    CUTS_Property_Parser parser (this->prop_map_);
    ACE_Vector <ACE_CString>::ITERATOR iter (this->opts_.defines_);

    for ( ; !iter.done (); iter.advance ())
    {
      ACE_CString * item = 0;
      iter.next (item);

      parser.parse (item->c_str ());
    }
  }

  // Now, we are ready to parse the template file. We are either going to
  // output the concrete file to standard output, or a file.
  if (!this->opts_.output_.empty ())
  {
    std::ofstream outfile;
    outfile.open (this->opts_.output_.c_str ());

    if (outfile.is_open ())
    {
      // Expand the template into the output file.
      this->expand_into (outfile);

      // Close the output file.
      outfile.close ();
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to open %s for writing\n",
                  this->opts_.output_.c_str ()));
    }
  }
  else
  {
    // Expand the contents of the template file to standard output.
    this->expand_into (std::cout);
  }

  return 0;
}

//
// parse_args
//
int CUTS_Template_App::parse_args (int argc, char * argv [])
{
  const char * optargs = "ho:vc:D:";
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("use-env", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp ("help", get_opt.long_option ()) == 0)
      {
        this->print_help ();
      }
      else if (ACE_OS::strcmp ("use-env", get_opt.long_option ()) == 0)
      {
        this->opts_.use_env_ = true;
      }
      else if (ACE_OS::strcmp ("debug", get_opt.long_option ()) == 0)
      {
        this->enable_logmsg_severity (LM_DEBUG);
      }
      else if (ACE_OS::strcmp ("verbose", get_opt.long_option ()) == 0)
      {
        this->enable_logmsg_severity (LM_INFO);
      }
      else if (ACE_OS::strcmp ("config", get_opt.long_option ()) == 0)
      {
        this->opts_.config_ = get_opt.opt_arg ();
      }
      break;

    case 'o':
      this->opts_.output_ = get_opt.opt_arg ();
      break;

    case 'h':
      this->print_help ();
      break;

    case 'D':
      this->opts_.defines_.push_back (get_opt.opt_arg ());
      break;

    case 'c':
      this->opts_.config_ = get_opt.opt_arg ();
      break;

    case 'v':
      this->enable_logmsg_severity (LM_INFO);
      break;

    case '?':
      ACE_ERROR ((LM_WARNING,
                  "%T - %M - -%c is an unknown option; ignoring\n",
                  get_opt.opt_opt ()));
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T - %M - -%c is missing an argument\n",
                         get_opt.opt_opt ()),
                         -1);
      break;
    }
  }

  // Get the option for the name of the input file. This will be the
  // last option identified by get_opt.
  this->opts_.input_ = argv[get_opt.opt_ind ()];
  return 0;
}

//
// print_help
//
void CUTS_Template_App::print_help (void)
{
  std::cout << __HELP__ << std::endl;
  ACE_OS::exit (0);
}

//
// expand_into
//
void CUTS_Template_App::expand_into (std::ostream & out)
{
  // Find the start of the file.
  boost::spirit::file_iterator <char> begin (this->opts_.input_.c_str ());

  if (begin)
  {
    // Find the end of the file.
    boost::spirit::file_iterator <char> end = begin.make_end ();

    if (this->expander_.expand (begin, end, this->opts_.use_env_, out))
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - successfully converted template file\n"));
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - failed to convert template file [file=%s]\n",
                  this->opts_.input_.c_str ()));
    }
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to open file %s for reading\n",
                this->opts_.input_.c_str ()));
  }
}

//
// enable_logmsg_severity
//
void CUTS_Template_App::enable_logmsg_severity (u_long severity)
{
  u_long mask =
    ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

  mask |= severity;

  ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
}

//
// load_property_config
//
bool CUTS_Template_App::
load_property_file (const ACE_CString & filename)
{
  ACE_DEBUG ((LM_DEBUG,
              "%T - %M - loading property file %s\n",
              filename.c_str ()));

  CUTS_Property_Map_File file (this->prop_map_);
  return file.read (filename.c_str ());
}
