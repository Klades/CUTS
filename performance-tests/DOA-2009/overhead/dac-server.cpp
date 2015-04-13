// $Id$

#include "ace/Get_Opt.h"
#include "ace/Singleton.h"
#include "ace/Signal.h"
#include "ace/streams.h"
#include "EINode_Channel_i.h"

class Server
{
public:
  Server (void)
    : ior_filename_ ("datachannel.ior")
  {

  }

  int run_main (int argc, char * argv [])
  {
    try
    {
      this->orb_ = ::CORBA::ORB_init (argc, argv);
      this->parse_args (argc, argv);

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

      EINode_Channel_i channel;
      PortableServer::ObjectId_var oid = this->root_poa_->activate_object (&channel);

      // Write the object reference to an IOR file
      obj = this->root_poa_->id_to_reference (oid.in ());
      ::CORBA::String_var ior = this->orb_->object_to_string (obj.in ());

      std::ofstream iorfile;
      iorfile.open (this->ior_filename_.c_str ());

      if (iorfile.is_open ())
      {
        iorfile << ior.in ();
        iorfile.close ();
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "%T - %M - failed to open IOR file for writing; %s\n",
                    this->ior_filename_.c_str ()));
      }

      // Run the ORB's main event loop.
      this->orb_->run ();
    }
    catch (const ::CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - %s\n",
                  ex._info ().c_str ()));
    }

    return -1;
  }

  int parse_args (int argc, char * argv [])
  {
    const char * optstr = "o:";
    ACE_Get_Opt get_opt (argc, argv, optstr);

    int opt;

    while (EOF != (opt = get_opt ()))
    {
      switch (opt)
      {
      case 'o':
        this->ior_filename_ = get_opt.opt_arg ();
        break;
      }
    }

    return 0;
  }

  void shutdown (void)
  {
    try
    {
      this->orb_->shutdown ();
    }
    catch (const ::CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - %s\n",
                  ex._info ().c_str ()));
    }
    catch (...)
    {

    }
  }

  void destroy (void)
  {
    try
    {
      this->root_poa_->destroy (0, 0);
      this->orb_->destroy ();
    }
    catch (const ::CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - %s\n",
                  ex._info ().c_str ()));
    }
  }

private:
  ::CORBA::ORB_var orb_;

  ::PortableServer::POA_var root_poa_;

  ACE_CString ior_filename_;
};

#define SERVER \
  ACE_Singleton <Server, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  SERVER->shutdown ();
  ACE_UNUSED_ARG (sig);
}

//
// register_sighandler
//
static void register_sighandler (void)
{
  ACE_Sig_Action sa (&server_sighandler);

  sa.register_action (SIGINT);
  sa.register_action (SIGTERM);
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  SERVER->run_main (argc, argv);
  SERVER->destroy ();
  return 0;
}
