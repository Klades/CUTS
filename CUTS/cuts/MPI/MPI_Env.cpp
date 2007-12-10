// $Id$

#include "MPI_Env.h"

#if !defined (__CUTS_INLINE__)
#include "MPI_Env.inl"
#endif

#include "cuts/Benchmark_Agent_i.h"
#include "cuts/BDC/Benchmark_Data_CollectorC.h"
#include "orbsvcs/CosNamingC.h"
#include "ace/OS_NS_unistd.h"
#include "ace/INET_Addr.h"
#include "ace/Thread_Manager.h"

//
// instance_
//
CUTS_MPI_Env * CUTS_MPI_Env::instance_ = 0;

//
// instance
//
CUTS_MPI_Env * CUTS_MPI_Env::instance (void)
{
  if (CUTS_MPI_Env::instance_ != 0)
    return CUTS_MPI_Env::instance_;

  ACE_NEW_RETURN (CUTS_MPI_Env::instance_,
                  CUTS_MPI_Env (),
                  CUTS_MPI_Env::instance_);

  return CUTS_MPI_Env::instance_;
}

//
// close_singleton
//
void CUTS_MPI_Env::close_singleton (void)
{
  if (CUTS_MPI_Env::instance_ == 0)
    return;

  // Delete the instance and reset its value.
  delete CUTS_MPI_Env::instance_;
  CUTS_MPI_Env::instance_ = 0;
}

//
// init
//
int CUTS_MPI_Env::init (int & argc, char * argv [])
{
  try
  {
    // Initialize the CORBA ORB for the environment.
    ACE_DEBUG ((LM_DEBUG,
                "*** info (cutsmpi): initializing the CORBA service\n"));

    this->orb_ = CORBA::ORB_init (argc, argv);

    if (CORBA::is_nil (this->orb_.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error (cutsmpi): failed to initialze ORB\n"),
                         -1);
    }

    // Get a reference to the RootPOA
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");

    if (CORBA::is_nil (obj.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error (cutsmpi): failed to get root POA\n"),
                         -1);
    }

    // Convert the object into a portable server.
    this->poa_ = ::PortableServer::POA::_narrow (obj.in ());

    if (CORBA::is_nil (this->poa_.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error (cutsmpi): object is not a POA\n"),
                         -1);
    }

    // Get the POA manager from the POA.
    PortableServer::POAManager_var mgr = this->poa_->the_POAManager ();

    if (CORBA::is_nil (mgr.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error (cutsmpi): failed to get POA manager\n"),
                         -1);
    }

    // Activate the POA manager.
    mgr->activate ();

    // Create the benchmark agent and activate it. We then need to
    // transfer ownership to a servant.
    ACE_DEBUG ((LM_DEBUG,
                "*** info (cutsmpi): activating the benchmark agent\n"));

    ACE_NEW_RETURN (this->agent_, Benchmark_Agent_i (), -1);
    CUTS::Benchmark_Agent_var agent = this->agent_->_this ();
    this->agent_servant_ = this->agent_;

    // Get the BDC so we can register the application, which we treat
    // as a component. The return value for the component should be
    // assigned to the benchmark agent for identification purposes.
    CUTS::Benchmark_Data_Collector_var the_BDC = this->get_BDC ();

    if (CORBA::is_nil (the_BDC.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error (cutsmpi): failed to get "
                         "BenchmarkDataCollector\n"),
                         -1);
    }

    // Get the testing service from the BDC. The testing service
    // is responsible for handling our registration needs.
    CUTS::Testing_Service_var tsvc = the_BDC->provide_testing_service ();

    if (CORBA::is_nil (tsvc.in ()))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "*** error (cutsmpi): failed to get "
                        "testing service from BenchmarkDataCollector\n"),
                        -1);
    }

    // Register this parallel application with the testing service. The
    // name of the 'component' is the name of the application, plus its
    // rank in the MPI_COMM_WORLD, i.e., MyApp-1
    this->reg_.name = CORBA::string_dup (argv[0]);
    this->reg_.agent = CUTS::Benchmark_Agent::_duplicate (this->agent_->_this ());

    // Get the hostname and ip-address for this 'component'.
    char hostname[1024];
    ACE_OS::hostname (hostname, sizeof (hostname));
    ACE_INET_Addr inet ((u_short)0, hostname, AF_ANY);

    this->reg_.host_info.ipaddr = ::CORBA::string_dup (inet.get_host_addr ());
    this->reg_.host_info.hostname = ::CORBA::string_dup (inet.get_host_name ());

    // We are now ready to register the application w/ the testing
    // service object in the BDC.
    this->agent_->parent (tsvc->register_component (this->reg_));

    // Finally, start a service thread that handles ORB request.
    this->grp_id_ =
      ACE_Thread_Manager::instance ()->spawn (&CUTS_MPI_Env::svc_thr, this);

    if (this->grp_id_ == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                        "*** error (cutsmpi): failed to spawn service thread\n"),
                        -1);
    }

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (cutsmpi): %s\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (cutsmpi): unknown exception occured\n"));
  }

  return -1;
}

//
// fini
//
int CUTS_MPI_Env::fini (void)
{
  ACE_DEBUG ((LM_TRACE,  "entering fini\n"));

  try
  {
    if (!CORBA::is_nil (this->orb_.in ()))
    {
      // We need to unregister ourselves with the BDC. This means, getting
      // a reference to the BDC and telling the testing service to unregister
      // ourselves from the database.
      CUTS::Benchmark_Data_Collector_var the_BDC = this->get_BDC ();

      if (CORBA::is_nil (the_BDC.in ()))
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                          "*** error (cutsmpi): the CUTS/BenchmarkDataCollector "
                          "is NIL\n"),
                          -1);
      }

      CUTS::Testing_Service_var tsvc = the_BDC->provide_testing_service ();

      if (CORBA::is_nil (tsvc.in ()))
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                          "*** error (cutsmpi): the testing service is NIL\n"),
                          -1);
      }

      tsvc->unregister_component (this->reg_);

      // Destroy the POA and then the ORB. This should cause the
      // service thread to exit.
      if (!CORBA::is_nil (this->poa_.in ()))
      {
        ACE_DEBUG ((LM_INFO,
                    "*** info (cutsmpi): destroying the POA\n"));

        this->poa_->destroy (1, 1);
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "*** error (cutsmpi): POA object is NIL"));
      }

      // Shutdown the ORB. This will stop the ORB event loop. Once
      // we have stopped the event loop, we can destroy the ORB.
      this->orb_->shutdown (true);
      this->orb_->destroy ();

      // Reset the ORB variable.
      this->orb_ = CORBA::ORB::_nil ();
    }

    // Wait for the service thread to exit. We need to reset the
    // group id if we are able to wait for all service threads to
    // exit.
    if (this->grp_id_ != -1)
    {
      ACE_DEBUG ((LM_INFO,
                  "*** info (cutsmpi): waiting for service thread to exit\n"));

      if (ACE_Thread_Manager::instance ()->wait_grp (this->grp_id_) == 0)
        this->grp_id_ = -1;
    }

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (cutsmpi): finalization failed [%s]\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (cutsmpi): unknown exception during finalization\n"));
  }

  return -1;
}

//
// svc_thr
//
ACE_THR_FUNC_RETURN CUTS_MPI_Env::svc_thr (void * param)
{
  try
  {
    // Extract the CUTS_MPI environment from the parameter.
    CUTS_MPI_Env * _this = reinterpret_cast <CUTS_MPI_Env *> (param);

    // Run the ORB event loop.
    ACE_DEBUG ((LM_INFO,
                "*** info (cutsmpi): starting ORB event loop\n"));

    _this->orb_->run ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_DEBUG ((LM_DEBUG,
                "*** error (cutsmpi): failure in service thread [%s]\n",
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_DEBUG ((LM_DEBUG,
                "*** error (cutsmpi): unknown exception in service thread\n"));
  }
  return 0;
}

//
// get_BDC
//
CUTS::Benchmark_Data_Collector * CUTS_MPI_Env::get_BDC (void)
{
  // Get the NameService initial reference from the command-line.
  CORBA::Object_var obj =
    this->orb_->resolve_initial_references ("NameService");

  if (CORBA::is_nil (obj.in ()))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error (cutsmpi): failed to locate naming "
                       "service; NameService reference not defined\n"),
                       0);
  }

  // Extract the naming context from the object.
  CosNaming::NamingContextExt_var naming_context =
    CosNaming::NamingContextExt::_narrow (obj.in ());

  if (CORBA::is_nil (naming_context.in ()))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error (cutsmpi): object is not a naming "
                       "service object\n"),
                       0);
  }

  ACE_DEBUG ((LM_DEBUG,
              "*** info (cutsmpi): locating CUTS/BenchmarkDataCollector in "
              "naming service\n"));

  // Get the BenchmarkDataCollector from the naming context.
  CORBA::String_var name = CORBA::string_dup ("CUTS/BenchmarkDataCollector");
  obj = naming_context->resolve_str (name.in ());

  // Extract the BDC from the object.
  return CUTS::Benchmark_Data_Collector::_narrow (obj.in ());
}
