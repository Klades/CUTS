#include "ace/Get_Opt.h"

#include "tao/ORB_Core.h"

#include "ciao/ComponentServer/CIAO_CS_ClientS.h"
#include "ciao/ComponentServer/CIAO_ComponentServerC.h"
#include "ciao/ComponentServer/CIAO_ServerActivator_Impl.h"
#include "ciao/ComponentServer/CIAO_ComponentInstallation_Impl.h"
#include "ciao/ComponentServer/CIAO_PropertiesC.h"
#include "ciao/Valuetype_Factories/ConfigValue.h"
#include "ciao/Logger/Logger_Service.h"

#include "SubAppDDSAdapter.h"
#include "PubAppDDSAdapter.h"

const char *cs_path = "ciao_componentserver";
CORBA::ULong spawn_delay = 5;

int
parse_args (int argc, ACE_TCHAR *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("s:d:"));
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 's':
        cs_path = get_opts.opt_arg ();
        break;

      case 'd':
        spawn_delay = ACE_OS::atoi (get_opts.opt_arg ());
        break;

      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-s <path> "
                           "-d <uint> "
                           "\n",
                           argv [0]),
                          -1);
      }
  // Indicates sucessful parsing of the command line
  return 0;
}

int
main (int argc, ACE_TCHAR *argv[])
{
  using namespace CIAO::Deployment;

  CIAO::Logger_Service logger;

  logger.init (argc, argv);

  try
    {
      CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);
      
      if (parse_args (argc, argv) != 0)
        {
          return 1;
        }

      CORBA::Object_var object =
        orb->resolve_initial_references ("RootPOA");

      PortableServer::POA_var root_poa =
        PortableServer::POA::_narrow (object.in ());

      PortableServer::POAManager_var poa_manager =
        root_poa->the_POAManager ();

      poa_manager->activate ();
      
      CIAO::Deployment::ComponentInstallation_Impl *tmp_ci = 0;

      ACE_NEW_THROW_EX (tmp_ci,
                        CIAO::Deployment::ComponentInstallation_Impl (),
                        CORBA::NO_MEMORY ());

      PortableServer::ServantBase_var safe_servant = tmp_ci;

      root_poa->activate_object (tmp_ci);

      CIAO_ServerActivator_i *sa_tmp =
        new CIAO_ServerActivator_i (spawn_delay,
                                    cs_path,
                                    0,
                                    false,
                                    tmp_ci->_this (),
                                    orb.in (),
                                    root_poa.in ());

      PortableServer::ServantBase_var safe = sa_tmp;

      ServerActivator_var sa = sa_tmp->_this ();
      
      ::Components::Deployment::ComponentServer_ptr h =
        sa->create_component_server (0);

      ComponentServer_var server = ComponentServer::_narrow (h);

      if (CORBA::is_nil (server.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Nil componentserver reference")),
                            -1);
        }

      Components::Deployment::Container_var tmp =
        server->create_container (0);
      Container_var sub_cont = Container::_narrow (tmp.in ());

      if (CORBA::is_nil (sub_cont.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Error: Got nil sub container\n")),
                            -1);
        }

      CORBA::Any val;
      ::Components::ConfigValues configs (3);
      configs.length (3);

      val <<= "create_SubAppDDSAdapter_Servant";
      configs[0] = new CIAO::ConfigValue_impl (CIAO::Deployment::SVNT_ENTRYPT,
                                               val);
      val <<= "SubAppDDSAdapter";
      configs[1] = new CIAO::ConfigValue_impl (CIAO::Deployment::SVNT_ARTIFACT,
                                               val);
      tmp_ci->install ("SubAppDDSAdapter", "SubAppDDSAdapter");

      val <<= "SubAppDDS";
      configs[2] = new CIAO::ConfigValue_impl (CIAO::Deployment::EXEC_ARTIFACT,
                                               val);
      tmp_ci->install ("SubAppDDS", "SubAppDDS");

      Components::CCMObject_var sub_obj =
        sub_cont->install_component ("theSubAppDDS",
                                     "create_SubAppDDSAdapter_Impl",
                                     configs);

      if (CORBA::is_nil (sub_obj. in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Got back a nil sub component ")
                             ACE_TEXT ("ref from install_component\n")),
                            -1);
        }
        
      ::Outer::SubAppDDSComponent_var sub_comp =
        ::Outer::SubAppDDSComponent::_narrow (sub_obj.in ());
        
      if (CORBA::is_nil (sub_comp.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Sub component narrow failed\n")),
                            -1);
        }
        
      tmp = server->create_container (0);
      Container_var pub_cont = Container::_narrow (tmp.in ());

      if (CORBA::is_nil (pub_cont.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Error: Got nil pub container\n")),
                            -1);
        }

      val <<= "create_PubAppDDSAdapter_Servant";
      configs[0] = new CIAO::ConfigValue_impl (CIAO::Deployment::SVNT_ENTRYPT,
                                               val);
      val <<= "PubAppDDSAdapter";
      configs[1] = new CIAO::ConfigValue_impl (CIAO::Deployment::SVNT_ARTIFACT,
                                               val);
      tmp_ci->install ("PubAppDDSAdapter", "PubAppDDSAdapter");

      val <<= "PubAppDDS";
      configs[2] = new CIAO::ConfigValue_impl (CIAO::Deployment::EXEC_ARTIFACT,
                                               val);
      tmp_ci->install ("PubAppDDS", "PubAppDDS");

      Components::CCMObject_var pub_obj =
        pub_cont->install_component ("thePubAppDDS",
                                     "create_PubAppDDSAdapter_Impl",
                                     configs);

      if (CORBA::is_nil (pub_obj. in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Got back a nil pub component ")
                             ACE_TEXT ("ref from install_component\n")),
                            -1);
        }
        
      ::Outer::PubAppDDSComponent_var pub_comp =
        ::Outer::PubAppDDSComponent::_narrow (pub_obj.in ());
        
      if (CORBA::is_nil (pub_comp.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Pub component narrow failed\n")),
                            -1);
        }
        
      ::Components::EventConsumerBase_var ec =
        sub_comp->get_consumer ("app_op_recv");
        
      if (CORBA::is_nil (ec.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("get_consumer() failed\n")),
                            -1);
        }
        
      ::DummyConsumer_var td_ec =
        ::DummyConsumer::_narrow (ec.in ());
      
       if (CORBA::is_nil (td_ec.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Consumer narrow failed\n")),
                            -1);
        }
            
      CORBA::ValueFactory_var vf = new ::Components::Cookie_init ();
      vf =
        orb->register_value_factory (
          "IDL:omg.org/Components/Cookie:1.0",
          vf.in ());

      ::Components::Cookie_var ck =
        pub_comp->subscribe ("app_op_send", td_ec.in ());
        
      if (ck.in () == 0)
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Subscribe returned null cookie\n")),
                            -1);
        }

      // This method is overridden to trigger a message send. 
      pub_comp->configuration_complete ();

/*       
      // These throw CORBA::UNIMPLEMENTED, leading to warnings
      // for the subsequent cleanup calls.    
      pub_cont->remove_component (pub_comp.in ());     
      sub_cont->remove_component (sub_comp.in ());  
         
      server->remove_container (sub_cont.in ());
      server->remove_container (pub_cont.in ());
      sa->remove_component_server (server.in ());
*/
      root_poa->destroy (true, true);
      orb->destroy ();
    }
  catch ( ::Components::CreateFailure &)
    {
      ACE_ERROR ((LM_ERROR, "Error: Caught CreateFailure exception.\n"));
    }
  catch ( ::Components::RemoveFailure &)
    {
      ACE_ERROR ((LM_ERROR, "Error: Caught RemoveFailure exception.\n"));
    }
  catch ( const ::CORBA::Exception &ex)
    {
      ex._tao_print_exception ("Error: Caught CORBA exception.\n");
    }
  catch (...)
    {
      ACE_ERROR ((LM_ERROR, "Error: Caught unknown exception\n"));
    }
  
  return 0;
}