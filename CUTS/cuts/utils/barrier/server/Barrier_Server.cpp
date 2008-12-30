// $Id$

#include "Barrier_Server.h"

#if !defined (__CUTS_INLINE__)
#include "Barrier_Server.inl"
#endif

#include "cuts/ORB_Server_Task.h"
#include "tao/IORTable/IORTable.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"
#include <sstream>

const char * __HELP__ =
"CUTS distributed barrier daemon\n"
"\n"
"  Usage: cuts-barrier_d [OPTIONS]\n"
"\n"
"Main options:\n"
"  -n COUNT                   synchronize with COUNT clients\n"
"\n"
"Informative output:\n"
"  -h, --help                 display this help screen\n";

//
// run_main
//
int CUTS_Barrier_Server::run_main (int argc, char * argv [])
{
  try
  {
    // First, parse the command-line arguments.
    if (this->parse_args (argc, argv) != 0)
      return -1;

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - getting the RootPOA\n"));
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");

    if (CORBA::is_nil (obj.in ()))
      return -1;

    this->root_ = PortableServer::POA::_narrow (obj.in ());

    if (CORBA::is_nil (this->root_.in ()))
      return -1;

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - activating the POA manager\n"));
    PortableServer::POAManager_var mgr = this->root_->the_POAManager ();
    mgr->activate ();

    // Activate the servant.
    PortableServer::ObjectId_var oid =
      this->root_->activate_object (&this->barrier_);

    // Get a reference to the servant.
    obj = this->root_->id_to_reference (oid.in ());

    // Register the object with the IORTable.
    if (this->register_with_iortable ("CUTS/Barrier", obj.in ()) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%T (%t) - %M - failed to register servant with IORTable\n"),
                         -1);
    }

    // We are going to manually run the event loop. We need to only
    // process a selected number of messages, i.e., until all nodes
    // have registered with this barrier.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - processing the server's messages\n"));

    while (this->count_ > 0)
      this->orb_->perform_work ();

    // We can signal all the nodes to continue work now.
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - notifying all nodes to continue work\n"));
    this->barrier_.broadcast ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }

  // Close the servant, which will abort all the nodes.
  if (this->barrier_.close () == -1)
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to close the barrier\n"));

  return -1;
}

//
// parse_args
//
int CUTS_Barrier_Server::parse_args (int argc, char * argv [])
{
  this->orb_ = CORBA::ORB_init (argc, argv, "cuts.barrier.server");

  const char * optstr = "n:h";
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

    case 'n':
      {
        std::istringstream istr (get_opt.opt_arg ());
        istr >> this->count_;
      }
      break;
    }
  }

  return 0;
}

//
// print_help
//
void CUTS_Barrier_Server::print_help (void)
{
  std::cout << __HELP__ << std::endl;
  ACE_OS::exit (0);
}

//
// shutdown
//
void CUTS_Barrier_Server::shutdown (void)
{
  try
  {
    // Shutdown the ORB.
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

//
// register_with_iortable
//
int CUTS_Barrier_Server::
register_with_iortable (const char * name, CORBA::Object_ptr svnt_ref)
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

    CORBA::String_var objstr = this->orb_->object_to_string (svnt_ref);
    ior_table->bind (name, objstr.in ());
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - %s\n",
                ex._info ().c_str ()));
  }
}

//
// destroy
//
void CUTS_Barrier_Server::destroy (void)
{
  try
  {
    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destroying the RootPOA\n"));

    // Destroy the RootPOA.
    this->root_->destroy (0, 0);

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - destroying the server's ORB\n"));

    // Destroy the ORB.
    this->orb_->destroy ();
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
