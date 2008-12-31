// $Id$

#include "Barrier_Client.h"

#if !defined (__CUTS_INLINE__)
#include "Barrier_Client.inl"
#endif

#include "cuts/ORB_Server_Task.h"
#include "ace/Get_Opt.h"
#include "ace/INET_Addr.h"
#include "ace/streams.h"

const char * __HELP__ =
"CUTS distributed barrier client\n"
"\n"
"  Usage: cuts-barrier [OPTIONS]\n"
"\n"
"Informative Output:\n"
"  -h, --help                 display this help screen\n";

//
// run_main
//
int CUTS_Barrier_Client::run_main (int argc, char * argv [])
{
  CUTS_ORB_Server_Task task;

  try
  {
    if (this->parse_args (argc, argv) != 0)
      return -1;

    // Get a reference to the RootPOA
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - resolving reference to RootPOA\n"));
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    this->root_ = PortableServer::POA::_narrow (obj);

    // Activate the POA manager.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating RootPOA's manager\n"));
    PortableServer::POAManager_var mgr = this->root_->the_POAManager ();
    mgr->activate ();

    // Activate the callback servant.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating callback object\n"));
    PortableServer::ObjectId_var oid =
      this->root_->activate_object (&this->callback_);

    // Convert the servant into a reference.
    obj = this->root_->id_to_reference (oid.in ());
    CUTS::BarrierCallback_var callback = CUTS::BarrierCallback::_narrow (obj.in ());

    // Resolve the reference to the BarrierService. We need to enter a
    // reconnection loop just in case the barrier is not present when
    // we initially attempt to connect.
    CUTS::Barrier_var barrier = this->connect ();

    if (CORBA::is_nil (barrier.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t( - %M - failed to connect to barrier\n"),
                         -1);
    }

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating server's task\n"));

    task.reset (this->orb_.in ());

    if (task.activate () == 0)
    {
      // Register the callback with the barrier.
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - registering callback with barrier\n"));

      CORBA::String_var name = CORBA::string_dup (this->name_.c_str ());
      barrier->register_client (name.in (), callback.in ());

      // Wait for notification from the server.
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - waiting for all nodes to reach barrier\n"));

      if (this->callback_.wait () == -1)
        ACE_ERROR ((LM_ERROR,
                    "%T (%t) - %M - failed to wait for barrier\n"));

      // Shutdown the ORB and wait for the task to return.
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - shutting down the server\n"));

      this->shutdown ();
      task.wait ();
    }
    else
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to activate server's task\n"),
                         -1);
    }

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));

    // Make sure we shutdown the server.
    this->shutdown ();
    task.wait ();
  }

  return -1;
}

//
// parse_args
//
int CUTS_Barrier_Client::parse_args (int argc, char * argv [])
{
  this->orb_ = CORBA::ORB_init (argc, argv);

  const char * optstr = "h";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);

  char op;

  while ((op = get_opt ()) != EOF)
  {
    switch (op)
    {
    case 0:
      if (ACE_OS::strcmp ("help", get_opt.long_option ()) == 0)
      {
        this->print_help ();
      }
      break;

    case 'h':
      this->print_help ();
      break;
    }
  }

  // Set the default name of the client.
  ACE_INET_Addr inet_addr;
  this->name_ = inet_addr.get_host_name ();

  return 0;
}

//
// print_help
//
void CUTS_Barrier_Client::print_help (void)
{
  std::cout << __HELP__ << std::endl;
  ACE_OS::exit (0);
}

//
// connect
//
CUTS::Barrier_ptr CUTS_Barrier_Client::connect (void)
{
  // Resolve the reference to the BarrierService. We need to enter a
  // reconnection loop just in case the barrier is not present when
  // we initially attempt to connect.

  CUTS::Barrier_var barrier;
  CORBA::Object_var obj;

  do
  {
    try
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - resolving reference to BarrierService\n"));
      obj = this->orb_->resolve_initial_references ("BarrierService");

      if (CORBA::is_nil (obj.in ()))
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                           "%T (%t) - %M - failed to resolve initial reference"
                           " BarrierService\n"),
                           0);
      }

      barrier = CUTS::Barrier::_narrow (obj.in ());

      if (CORBA::is_nil (barrier.in ()))
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                           "%T (%t) - %M - object is not a CUTS::Barrier\n"),
                           0);
      }
    }
    catch (const CORBA::TRANSIENT & )
    {
    }
  } while (CORBA::is_nil (barrier.in ()));

  return barrier._retn ();
}

//
// destroy
//
void CUTS_Barrier_Client::destroy (void)
{
  try
  {
    this->root_->destroy (0, 0);
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
// shutdown
//
void CUTS_Barrier_Client::shutdown (void)
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
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - caught unknown exception (%N:%l)\n"));
  }
}
