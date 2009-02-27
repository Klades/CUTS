// $Id$

#include "Unite_App.h"
#include "Unite_Config_File.h"
#include "Unit_Test.h"
#include "Unit_Test_Builder.h"
#include "Unit_Test_Evaluator.h"
#include "Unit_Test_Result.h"
#include "cuts/utils/testing/Test_Database.h"
#include "ace/Get_Opt.h"
#include "ace/Env_Value_T.h"
#include "XSC/utils/XML_Error_Handler.h"

//
// operator <<
//
std::ostream & operator << (std::ostream & ostr, const CUTS_Unit_Test_Result & result)
{
  if (result.groups ().current_size () == 0)
  {
    ostr << "Result = " << result.result ().c_str ();
  }
  else
  {
    ostr << "Group Results:" << std::endl;

    for (CUTS_Unit_Test_Group_Result::CONST_ITERATOR iter (result.groups ());
         !iter.done (); ++ iter)
    {
      ostr << ". " << iter->key ().c_str ()
           << " = " << iter->item ().c_str ()
           << std::endl;
    }
  }

  return ostr;
}

//
// CUTS_Unite_App
//
CUTS_Unite_App::CUTS_Unite_App (void)
: sandbox_ (".")
{

}

//
// CUTS_Unite_App
//
CUTS_Unite_App::~CUTS_Unite_App (void)
{

}

//
// run_main
//
int CUTS_Unite_App::run_main (int argc, char * argv [])
{
  if (this->parse_args (argc, argv) == -1)
    return -1;

  // Load the configuration file.
  CUTS_Unite_Config_File config_file;
  CUTS::uniteConfig config ("", "", "", CUTS::logformatList (std::list <CUTS::logformatType> ()));

  XSC::XML::XML_Error_Handler error_handler;
  config_file->setErrorHandler (&error_handler);

  if (config_file.read (this->config_.c_str ()))
    config_file >>= config;

  CUTS_Unit_Test unit_test;
  CUTS_Unit_Test_Builder builder;

  if (!builder.build (config, unit_test))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to build unit test in %s\n",
                       this->config_.c_str ()),
                       -1);

  // Open the database that contains the test data.
  CUTS_Test_Database testdata;

  if (!testdata.open (this->datafile_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to open %s\n",
                       this->datafile_.c_str ()),
                       -1);

  // Evaluate the unit test.
  CUTS_Unit_Test_Result result;
  CUTS_Unit_Test_Evaluator evaluator (this->sandbox_);

  if (!evaluator.evaluate (testdata, unit_test, result))
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to evaluate unit test\n"));

  // Print the result.
  std::cout << result << std::endl;

  return 0;
}

//
// parse_args
//
int CUTS_Unite_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "c:f:";

  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("datafile", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("sandbox", ACE_Get_Opt::ARG_REQUIRED);

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "config") == 0)
      {
        this->config_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "datafile") == 0)
      {
        this->datafile_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "sandbox") == 0)
      {
        this->sandbox_ = get_opt.opt_arg ();
      }
      break;

    case 'c':
      this->config_ = get_opt.opt_arg ();
      break;

    case 'f':
      this->datafile_ = get_opt.opt_arg ();
      break;
    }
  }

  return 0;
}
