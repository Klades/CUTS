// $Id$

#include "Antispam_App.h"
#include "Antispam_Config_File.h"
#include "Propagate_Arrival_Rates.h"
#include "Response_Time_Evaluator.h"
#include "cuts-antispam.h"
#include "Component.h"
#include "Host.h"
#include "ace/Get_Opt.h"
#include "boost/bind.hpp"

//
// CUTS_Antispam_App
//
CUTS_Antispam_App::CUTS_Antispam_App (void)
: assembly_ ("antispam")
{

}

//
// ~CUTS_Antispam_App
//
CUTS_Antispam_App::~CUTS_Antispam_App (void)
{

}

//
// run_main
//
int CUTS_Antispam_App::run_main (int argc, char * argv [])
{
  // Parse the command-line arguments.
  if (this->parse_args (argc, argv) != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to parse command-line arguments\n"),
                       -1);

  if (this->construct_model ())
  {
    // Propagate the arrival rates for the assembly.
    CUTS_Propagate_Arrival_Rates propogate;
    propogate.propogate (this->assembly_);

    // Calculate the response time for each port.
    CUTS_Response_Time_Evaluator rt_eval;
    CUTS_Response_Time_Evaluator::result_type results;

    if (rt_eval.evaluate (this->assembly_, this->deployment_, results) != 0)
      return 1;

    CUTS_Response_Time_Evaluator::result_type::ITERATOR iter (results);

    // Print the results.
    for (; !iter.done (); ++ iter)
    {
      std::cout << ". " << iter->key ()
                << " = " << iter->item ().response_time_
                << ' ' << iter->item ().my_service_
                << ' ' << iter->item ().my_util_
                << ' ' << iter->item ().host_util_
                << ' ' << iter->item ().count_
                << std::endl;
    }
  }
  else
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to construct model\n"));

  return 0;
}

//
// construct_model
//
bool CUTS_Antispam_App::construct_model (void)
{
  // Read the configuration file.
  CUTS_Antispam_Config_File file;

  if (!file.read (this->config_.c_str ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to read configuration file [%s]\n",
                       this->config_.c_str ()),
                       false);

  CUTS::antispamConfig config;
  file >>= config;

  if (config.components_p ())
  {
    std::for_each (config.components ().begin_component (),
                   config.components ().end_component (),
                   boost::bind (&CUTS_Antispam_App::process_component_type,
                                this,
                                _1));
  }

  if (config.assembly_p ())
  {
    std::for_each (config.assembly ().begin_instance (),
                   config.assembly ().end_instance (),
                   boost::bind (&CUTS_Antispam_App::process_instance,
                                this,
                                _1));

    std::for_each (config.assembly ().begin_connection (),
                   config.assembly ().end_connection (),
                   boost::bind (&CUTS_Antispam_App::process_connection,
                                this,
                                _1));
  }

  if (config.deployment_p ())
  {
    std::for_each (config.deployment ().begin_host (),
                   config.deployment ().end_host (),
                   boost::bind (&CUTS_Antispam_App::process_host,
                                this,
                                _1));
  }

  return true;
}

//
// parse_args
//
int CUTS_Antispam_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "f:";

  ACE_Get_Opt get_opt (argc, argv, optstr);
  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);

  char opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (ACE_OS::strcmp ("file", get_opt.opt_arg ()) == 0)
      {
        this->config_ = get_opt.opt_arg ();
      }
      break;

    case 'f':
      this->config_ = get_opt.opt_arg ();
      break;

    default:
      return -1;
    }
  }

  if (this->config_.length () == 0)
    return -1;

  return 0;
}

//
// process_component_type
//
void CUTS_Antispam_App::
process_component_type (const CUTS::componentType & type)
{
  CUTS_Component * component = 0;

  if (this->mgr_.create (type.type ().c_str (), component) == 0)
  {
    std::for_each (type.begin_input (),
                   type.end_input (),
                   boost::bind (&CUTS_Antispam_App::process_input,
                                this,
                                component,
                                _1));
  }
}

//
// process_input
//
void CUTS_Antispam_App::
process_input (CUTS_Component * component, const CUTS::inputType & input)
{
  CUTS::inputType::output_const_iterator
    iter = input.begin_output (),
    iter_end = input.end_output ();

  for (; iter != iter_end; ++ iter)
    component->associate (input.name ().c_str (), iter->c_str ());
}

//
// process_instance
//
void CUTS_Antispam_App::
process_instance (const CUTS::instanceType & inst_info)
{
  CUTS_Component * type = 0;

  if (this->mgr_.items ().find (inst_info.type ().c_str (), type) == 0)
  {
    CUTS_Component_Instance * instance = 0;

    int retval = this->assembly_.new_instance (inst_info.name ().c_str (),
                                               *type,
                                               instance);

    if (retval == 0)
    {
      // Initialize the inputs for this instance.
      CUTS::instanceType::input_const_iterator
        iter = inst_info.begin_input (),
        iter_end = inst_info.end_input ();

      ACE_CString port_name;
      CUTS_Port_Details details;

      for ( ; iter != iter_end; ++ iter)
      {
        // Construct the name of the port.
        port_name = inst_info.name ().c_str ();
        port_name += ACE_CString ('.') + iter->name ().c_str ();

        // Initialize the details of the port.
        this->assembly_.get_port_details (port_name, details);
        details.service_time_ = iter->baseline ();

        if (iter->arrival_p ())
        {
          details.arrival_rate_ = iter->arrival ();
          this->assembly_.set_start_port (port_name);
        }
        else
        {
          details.arrival_rate_ = 0.0;
        }

        // Set the port details.
        if (!this->assembly_.set_port_details (port_name, details))
          ACE_ERROR ((LM_ERROR,
                      "%T (%t) - %M - failed to set instance %s port %s details\n",
                      inst_info.name ().c_str (),
                      iter->name ().c_str ()));

      }
    }
    else
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to create instance %s\n",
                  inst_info.name ().c_str ()));

  }
}

//
// process_connection
//
void CUTS_Antispam_App::
process_connection (const CUTS::connectionType & conn)
{
  if (!this->assembly_.associate (conn.src ().c_str (),
                                  conn.dst ().c_str (),
                                  false))
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to create connection (%s -> %s)\n",
                conn.src ().c_str (),
                conn.dst ().c_str ()));
  }
}

//
// process_host
//
void CUTS_Antispam_App::
process_host (const CUTS::hostType & host_info)
{
  // First, create a new host in the model.
  CUTS_Host * host = 0;

  if (this->deployment_.create (host_info.name ().c_str (), host) == 0)
  {
    CUTS_Component_Instance * instance = 0;

    CUTS::hostType::instance_const_iterator
      iter = host_info.begin_instance (),
      iter_end = host_info.end_instance ();

    for (; iter != iter_end; ++ iter)
    {
      if (this->assembly_.instances ().find (iter->c_str (), instance) == 0)
      {
        // Deploy each instance on the host.
        host->instances ().insert (instance);
      }
      else
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to deploy instance %s\n",
                    iter->c_str ()));
    }
  }
  else
    ACE_ERROR ((LM_ERROR,
                "%T - %M - failed to create host %s\n",
                host_info.name ().c_str ()));
}
