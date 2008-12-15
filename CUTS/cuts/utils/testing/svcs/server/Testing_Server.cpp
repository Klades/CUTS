// $Id$

#include "Testing_Server.h"
#include "cuts/utils/testing/Testing_App.h"
#include "tao/TAO_Singleton_Manager.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Thread_Manager.h"
#include "ace/Get_Opt.h"
#include "ace/Guard_T.h"
#include "ace/streams.h"

CUTS_TESTING_SERVICE_IMPL (CUTS_Testing_Server, _make_CUTS_Testing_Server);

//
// CUTS_Testing_Server
//
CUTS_Testing_Server::CUTS_Testing_Server (void)
: register_with_ns_ (false)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::CUTS_Testing_Server (void)");

  CUTS_TestManager_i * manager = 0;
  ACE_NEW_THROW_EX (manager,
                    CUTS_TestManager_i (*this),
                    CORBA::NO_MEMORY ());

  this->test_manager_.reset (manager);
}

//
// CUTS_Testing_Server
//
CUTS_Testing_Server::~CUTS_Testing_Server (void)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::~CUTS_Testing_Server (void)");
}

//
// run_main
//
int CUTS_Testing_Server::init (int argc, char * argv [])
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::init (int, char * [])");

  if (this->parse_args (argc, argv) == -1)
  {
    ACE_ERROR_RETURN  ((LM_ERROR,
                        "%T (%t) - %M - failed to parse command-line options\n"),
                        -1);
  }

  try
  {
    // Get a reference to the <RootPOA>
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolving initial reference to RootPOA\n"));
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_poa_ = PortableServer::POA::_narrow (obj.in ());

    // Activate the RootPOA's manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting reference to POAManager\n"));

    PortableServer::POAManager_var poa_mgr = this->root_poa_->the_POAManager ();
    poa_mgr->activate ();

    // Activate the object and transfer ownership.
    PortableServer::ObjectId_var id =
      this->root_poa_->activate_object (this->test_manager_.get ());

    // Convert the object id into a string.
    obj = this->root_poa_->id_to_reference (id.in ());
    CORBA::String_var objstr = this->orb_->object_to_string (obj.in ());

    // Register the test manager with the IORTable for the ORB.
    int retval = 0;
      //CUTS_Testing_Server::register_with_iortable (this->orb_.in (),
      //                                             "CUTS/TestManager",
      //                                             objstr.in ());

    if (retval == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to register with IOR table\n"));
    }

    // Register the test manager with the naming service, if applicable.
    if (this->register_with_ns_)
    {
      if (this->register_with_name_service () == -1)
      {
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to register %s with naming service",
                    this->test_app ()->options ().name_.c_str ()));
      }
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating the server's task\n"));

    this->task_.reset (this->orb_.in ());
    retval = this->task_.activate ();

    if (retval == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T (%t) - %M - failed to activate server task\n"));
    }

    return retval;
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
// parse_args
//
int CUTS_Testing_Server::parse_args (int argc, char * argv [])
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::parse_args (int, char * [])");

  try
  {
    CUTS_TAO_Testing_Service::init (argc, argv);

    const char * optargs = "";
    ACE_Get_Opt get_opt (argc, argv, optargs);

    get_opt.long_option ("register-with-ns", ACE_Get_Opt::NO_ARG);

    char opt;

    while ((opt = get_opt ()) != EOF)
    {
      switch (opt)
      {
      case 0:
        if (ACE_OS::strcmp ("register-with-ns", get_opt.long_option ()) == 0)
        {
          this->register_with_ns_ = true;
        }
        break;

      }
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
// fini
//
int CUTS_Testing_Server::fini (void)
{
  CUTS_TESTING_SERVER_TRACE ("CUTS_Testing_Server::fini (void)");

  try
  {
    // We need to unregister the object with the naming service before we
    // shutdown the ORB.
    if (this->register_with_ns_)
      this->unregister_with_name_service ();

    // Stop the main event loop for the ORB.
    ACE_DEBUG ((LM_DEBUG, "%T (%t) - %M - shutting down the ORB\n"));
    this->orb_->shutdown ();
    this->task_.wait ();

    // Destroy the RootPOA.
    ACE_DEBUG ((LM_DEBUG, "%T (%t) - %M - destroying the RootPOA\n"));
    this->root_poa_->destroy (1, 1);

    // Finally, pass control to the base class
    CUTS_TAO_Testing_Service::fini ();
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
// register_with_iortable
//
int CUTS_Testing_Server::
register_with_iortable (CORBA::ORB_ptr orb,
                        const char * name,
                        const char * objstr)
{
  try
  {
    // Locate the IORTable for the application.
    CORBA::Object_var obj = orb->resolve_initial_references ("IORTable");
    IORTable::Table_var ior_table = IORTable::Table::_narrow (obj.in ());

    if (::CORBA::is_nil (ior_table.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to resolve IOR table\n"),
                         -1);
    }

    // Bind the object to the IOR table.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - registering test manager with the IOR table [%s]\n",
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
// register_with_name_service
//
int CUTS_Testing_Server::register_with_name_service (void)
{
  try
  {
    // Get the root context of the naming service.
    CORBA::Object_var obj =
      this->orb_->resolve_initial_references ("NameService");

    this->root_ctx_ = CosNaming::NamingContextExt::_narrow (obj.in ());

    // Construct all the context we would like to create, then contact
    // the naming service to ensure they all exist.
    const char * ctx_names [] = {"CUTS", "TestManager"};

    CosNaming::Name ns_name (3);
    CosNaming::NamingContext_var ctx;

    for (int i = 0; i < 2; ++ i)
    {
      // Initialize the next id in the name.
      ns_name.length (i + 1);
      ns_name[i].id = CORBA::string_dup (ctx_names[i]);

      try
      {
        ctx = this->root_ctx_->bind_new_context (ns_name);
      }
      catch (const CosNaming::NamingContext::AlreadyBound &)
      {
        // do nothing
      }
    }

    // Update the length so that the test manager's name is visible
    // to the naming service.
    ns_name.length (3);
    ns_name[2].id = CORBA::string_dup (this->test_app ()->options ().name_.c_str ());

    // Bind the actual test manger to the naming service.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - binding testing manager to naming service as %s\n",
                this->test_app ()->options ().name_.c_str ()));

    CUTS::TestManager_var tm = this->test_manager_->_this ();
    this->root_ctx_->bind (ns_name, tm);
    return 0;
  }
  catch (const CosNaming::NamingContext::AlreadyBound & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s already registered with naming service (%s)\n",
                this->test_app ()->options ().name_.c_str (),
                ex._info ().c_str ()));
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// register_with_name_service
//
int CUTS_Testing_Server::unregister_with_name_service (void)
{
  if (CORBA::is_nil (this->root_ctx_))
    return 0;

  try
  {
    // Construct the fully qualified name of the test manger for
    // within the naming service.
    CosNaming::Name ns_name (3);
    ns_name.length (3);

    ns_name[0].id = CORBA::string_dup ("CUTS");
    ns_name[1].id = CORBA::string_dup ("TestManager");
    ns_name[2].id = CORBA::string_dup (this->test_app ()->options ().name_.c_str ());

    // Unregister the TestManger with the naming service.
    ACE_DEBUG ((LM_INFO,
                "%T - %M - unregistering test manager with naming service\n"));

    this->root_ctx_->unbind (ns_name);
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T - %M - %s\n",
                ex._info ().c_str ()));
  }

  return -1;
}

//
// print_help
//
void CUTS_Testing_Server::print_help (void)
{

}

//
// the_ORB
//
CORBA::ORB_ptr CUTS_Testing_Server::the_ORB (void)
{
  return CORBA::ORB::_duplicate (this->orb_.in ());
}

