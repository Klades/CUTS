// $Id$

#include "Test_Archive_Server.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Archive_Server.inl"
#endif

#include "cuts/ORB_Server_Task.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"

const char * __HELP__ =
"CUTS archive server for storing test results\n"
"\n"
"  Usage: cutsarc_d [OPTIONS]\n"
"\n"
"Main options:\n"
"  --host=HOST                location of database [default='localhost']\n"
"  --usernane=USERNAME        username of connection [default='cuts']\n"
"  --password=PASSWORD        password for authentication [default='cuts']\n"
"\n"
"  -o, --output=DIR           upload test results to DIR\n"
"\n"
"Informative output:\n"
"  -h, --help                 display this help screen\n"
"  -v, --verbose              display verbose information\n"
"  --debug                    display debug useful debug information\n";

//
// run_main
//
int CUTS_Test_Archive_Server::run_main (int argc, char * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (this->parse_args (argc, argv) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to parse command-line arguments\n"),
                         -1);
    }

    // Resolve the RootPOA
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolve RootPOA\n"));

    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = PortableServer::POA::_narrow (obj.in ());

    // Activate the POA's manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating RootPOA's manager\n"));

    PortableServer::POAManager_var mgr = this->root_poa_->the_POAManager ();
    mgr->activate ();

    // Allocate the servant object.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - initializing archive servant\n"));

    if (this->archive_.init (this->root_poa_.in ()) != 0)
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T - %M - failed to initialize server\n"),
                         -1);

    // Now, activate the test archive servant.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating archive servant\n"));

    PortableServer::ObjectId_var oid =
      this->root_poa_->activate_object (&this->archive_);

    obj = this->root_poa_->id_to_reference (oid.in ());
    CORBA::String_var objstr = this->orb_->object_to_string (obj.in ());

    if (this->register_with_iortable ("CUTS/TestArchive", objstr.in ()) == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to register with IORTable\n"));
    }

    // Finally, run ORB's main event loop.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating server's task\n"));

    CUTS_ORB_Server_Task task (this->orb_.in ());

    if (task.activate () == 0)
    {
      // Wait for the task to return.
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - waiting for server task to return\n"));

      task.wait ();
    }
    else
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to activate task\n"),
                         -1);
    }

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

//
// shutdown
//
void CUTS_Test_Archive_Server::shutdown (void)
{
  try
  {
    this->orb_->shutdown ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// parse_args
//
int CUTS_Test_Archive_Server::parse_args (int argc, char * argv [])
{
  this->orb_ = CORBA::ORB_init (argc, argv, argv[0]);

  const char * optstr = "f:vh";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("file", 'f', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("output", 'o', ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);

  get_opt.long_option ("host", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("username", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("password", ACE_Get_Opt::ARG_REQUIRED);

  int opt;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (ACE_OS::strcmp ("file", get_opt.long_option ()) == 0)
      {
        this->archive_.opts ().archive_file_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("output", get_opt.long_option ()) == 0)
      {
        this->archive_.opts ().upload_dir_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("host", get_opt.long_option ()) == 0)
      {
        this->archive_.opts ().hostname_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("username", get_opt.long_option ()) == 0)
      {
        this->archive_.opts ().username_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("password", get_opt.long_option ()) == 0)
      {
        this->archive_.opts ().password_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp ("verbose", get_opt.long_option ()) == 0)
      {

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
      this->archive_.opts ().archive_file_ = get_opt.opt_arg ();
      break;

    case 'o':
      this->archive_.opts ().upload_dir_ = get_opt.opt_arg ();
      break;

    case 'v':
      break;
    }
  }

  return 0;
}

//
// destroy
//
void CUTS_Test_Archive_Server::destroy (void)
{
  try
  {
    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destroying the RootPOA\n"));

    if (CORBA::is_nil (this->root_poa_.in ()))
      this->root_poa_->destroy (1, 1);

    // Destroy the ORB.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destroying the ORB\n"));

    if (!CORBA::is_nil (this->orb_.in ()))
      this->orb_->destroy ();
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
int CUTS_Test_Archive_Server::
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
                "%T (%t) - %M - registering servant with the IOR table [%s]\n",
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

//
// print_help
//
void CUTS_Test_Archive_Server::print_help (void)
{
  std::cout << __HELP__ << std::endl;
  ACE_OS::exit (0);
}
