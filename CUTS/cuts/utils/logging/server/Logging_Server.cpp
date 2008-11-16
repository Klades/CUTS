// $Id$

#include "Logging_Server.h"

#if !defined (__CUTS_INLINE__)
#include "Logging_Server.inl"
#endif

#include "TestLoggerServer_i.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Get_Opt.h"

//
// CUTS_Test_Logging_Server
//
int CUTS_Test_Logging_Server::run_main (int argc, char * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (this->parse_args (argc, argv) == -1)
      return 1;

    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolving initial reference to RootPOA\n"));

    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting reference to POAManager\n"));
    this->poa_mgr_ = this->root_poa_->the_POAManager ();
    this->poa_mgr_->activate ();

    // Activate the servant.
    PortableServer::ObjectId_var id =
      this->root_poa_->activate_object (&this->server_);

    // Convert the object id into a string.
    obj = this->root_poa_->id_to_reference (id.in ());
    CORBA::String_var objstr = this->orb_->object_to_string (obj.in ());

    // Register the server w/ the IORTable
    if (CUTS_Test_Logging_Server::
        register_with_iortable ("CUTS/TestLoggerServer", objstr.in ()) == -1)
    {
      ACE_ERROR ((LM_WARNING,
                  "%T (%t) - %M - failed to register with IOR table\n"));
    }

    // Activate the task, and wait for all threads to exit.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating server task\n"));
    this->task_.activate ();
    this->task_.wait ();

    // Destroy the RootPOA.
    this->root_poa_->destroy (1, 1);

    // Destroy the ORB.
    this->orb_->destroy ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return 1;
}

//
// parse_args
//
int CUTS_Test_Logging_Server::parse_args (int argc, char * argv[])
{
  // Initailize the ORB.
  this->orb_ = CORBA::ORB_init (argc, argv);

  const char * optstr = "hv";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  char ch;

  while ((ch = get_opt ()) != EOF)
  {
    switch (ch)
    {
    case 0:
      if (ACE_OS::strcmp ("verbose", get_opt.long_option ()) == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp ("debug", get_opt.long_option ()) == 0)
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_DEBUG;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      else if (ACE_OS::strcmp ("help", get_opt.long_option ()) == 0)
      {
        //this->print_help ();
      }

      break;

    case 'v':
      {
        u_long mask =
          ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

        mask |= LM_INFO;

        ACE_Log_Msg::instance ()->priority_mask (mask, ACE_Log_Msg::PROCESS);
      }
      break;

    case 'h':
      break;
    }
  }


  return 0;
}

//
// shutdown
//
void CUTS_Test_Logging_Server::shutdown (void)
{
  try
  {
    if (!CORBA::is_nil (this->orb_.in ()))
      this->orb_->shutdown (1);
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// register_with_iortable
//
int CUTS_Test_Logging_Server::
register_with_iortable (const char * name, const char * objstr)
{
  try
  {
    // Locate the IORTable for the application.
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("IORTable");
    IORTable::Table_var ior_table = IORTable::Table::_narrow (obj.in ());

    if (::CORBA::is_nil (ior_table.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to resolve IOR table\n"),
                         -1);
    }

    // Bind the object to the IOR table.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - registering object with IOR table (%s)\n",
                name));

    ior_table->bind (name, objstr);
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}
