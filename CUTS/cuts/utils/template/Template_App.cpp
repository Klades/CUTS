// $Id$

#include "Template_App.h"
#include "Template_Engine.h"
#include "Template_Config_List_Parser.h"
#include "File_Generator.h"
#include "cuts/utils/Property_Map_File.h"
#include "cuts/utils/Property_Parser.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"
#include "boost/bind.hpp"
#include <algorithm>

static const char * __HELP__ =
"Template engine for property-based configuration files\n"
"\n"
"USAGE: cuts-template [OPTIONS]\n"
"\n"
"General Options:\n"
"  --template=TEMPLATE        generate configuration for TEMPLATE\n"
"  -c, --config=FILE          use configuration in FILE\n"
"  -o OUTFILE                 output expansion to OUTFILE\n"
"\n"
"  -Dname=VALUE               define property name with VALUE\n"
"\n"
"Expansion Options:\n"
"  --use-env                  use environment variables\n"
"  --ignore-variables         do not expand variables in template\n"
"  --ignore-commands          do not expand commands in template\n"
"\n"
"Print Options:\n"
"  -v, --verbose              print verbose infomration\n"
"  --debug                    print debugging information\n"
"  -h, --help                 print this help message\n";

//
// CUTS_Template_App
//
CUTS_Template_App::CUTS_Template_App (void)
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
  // Parse the command-line options.
  if (this->parse_args (argc, argv) == -1)
    return 1;

  // First, load configuration file if user specified one.
  if (!this->opts_.config_.empty ())
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - loading property file %s\n",
                this->opts_.config_.c_str ()));

    CUTS_Property_Map_File file (this->prop_map_);

    if (file.read (this->opts_.config_.c_str ()))
    {
      ACE_DEBUG ((LM_INFO,
                  "%T (%t) - %M - successfully loaded property file %s\n",
                  this->opts_.config_.c_str ()));
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to load property file %s\n",
                  this->opts_.config_.c_str ()));
    }
  }

  // First, parse the properties explicitly defined on the command-line.
  // These take precedence over properties defined in configuration file.
  CUTS_Property_Map overrides;

  if (this->opts_.defines_.size () > 0)
  {
    CUTS_Property_Parser parser (overrides);
    ACE_Vector <ACE_CString>::ITERATOR iter (this->opts_.defines_);

    std::for_each (this->opts_.defines_.begin (),
                   this->opts_.defines_.end (),
                   boost::bind (&CUTS_Property_Parser::parse_str,
                                boost::ref (parser),
                                _1));
  }

  // Join the overwrites with the default property map.
  this->prop_map_.join (overrides, true);

  if (this->opts_.config_list_.empty ())
  {
    // Now, we are ready to parse the template file. We are either going to
    // output the concrete file to standard output, or a file.
    if (!this->opts_.output_.empty ())
    {
      std::ofstream outfile;
      outfile.open (this->opts_.output_.c_str ());

      if (outfile.is_open ())
      {
        this->expand_into (outfile);
        outfile.close ();
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to open %s for writing\n",
                    this->opts_.output_.c_str ()));
      }
    }
    else
    {
      this->expand_into (std::cout);
    }
  }
  else
  {
    // Initialize the output directory, if necessary.
    if (this->opts_.output_.empty ())
      this->opts_.output_ = ".";

    // Use the configuration list.
    CUTS_File_Generator file (this->opts_.use_env_,
                              this->opts_.ignore_variables_,
                              this->opts_.ignore_commands_,
                              this->opts_.input_,
                              this->opts_.output_);

    CUTS_Template_Config_List_Parser parser (&file, overrides);
    parser.parse (this->opts_.config_list_.c_str ());
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

  get_opt.long_option ("verbose", 'v');
  get_opt.long_option ("debug");
  get_opt.long_option ("help", 'h');
  get_opt.long_option ("use-env");
  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("config-list", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("template", ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("ignore-variables");
  get_opt.long_option ("ignore-commands");

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
      else if (ACE_OS::strcmp ("template", get_opt.long_option ()) == 0)
      {
        this->opts_.input_ = get_opt.opt_arg ();
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
      else if (ACE_OS::strcmp ("config-list", get_opt.long_option ()) == 0)
      {
        this->opts_.config_list_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("ignore-commands", get_opt.long_option ()) == 0)
      {
        this->opts_.ignore_commands_ = true;
      }
      else if (ACE_OS::strcmp ("ignore-variables", get_opt.long_option ()) == 0)
      {
        this->opts_.ignore_variables_ = true;
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
                  "%T (%t) - %M - -%c is an unknown option; ignoring\n",
                  get_opt.opt_opt ()));
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - -%c is missing an argument\n",
                         get_opt.opt_opt ()),
                         -1);
      break;
    }
  }

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
  CUTS_Template_Engine engine (this->prop_map_);

  if (engine.process (this->opts_.input_.c_str (),
                      out,
                      this->opts_.use_env_,
                      this->opts_.ignore_variables_,
                      this->opts_.ignore_commands_))
  {
    ACE_DEBUG ((LM_INFO,
                "%T (%t) - %M - successully processed %s\n",
                this->opts_.input_.c_str ()));
  }
  else
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - failed to process %s\n",
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
