#include "tao/ORB_Core.h"

#include "ciao/Valuetype_Factories/Cookies.h"

#include "ciao/Servants/Port_Activator_T.h"

#include "DummyConsumer.h"

#include "ModelDDSDataConversion.h"

#include "SubAppDDSAdapter.h"
#include "Listeners.h"

using namespace DDS;

namespace DSTO_AppSpace_Impl
{
  SubAppDDSAdapter::SubAppDDSAdapter ( ::AppSpace::SubAppDDS * executor,
                                      ::Components::CCMHome_ptr,
                                      const char * ins_name,
                                      ::CIAO::Home_Servant_Impl_Base *,
                                      ::CIAO::Container_ptr c)
    : ::DSTO::AdapterBase (ins_name, c),
      ::DSTO::Adapter< ::POA_Outer::SubAppDDSComponent> (ins_name, c),
      app_ (executor)
  {
    try
     {
       this->populate_consumer_table ();
     
       // TODO - generate a domain id.  
       if (! this->dds_utility_.init (0))
         {
           ACE_ERROR ((LM_EMERGENCY,
                       ACE_TEXT ("SubAppDDSAdapter: error ")
                       ACE_TEXT ("in DDS initialization\n")));
         }  

        ::Outer::TestData_DDSTypeSupport_var ts =
          new ::Outer::TestData_DDSTypeSupport;
          
        // For now, we're using a topic name constructed from
        // the publishes port name, so it has to be hard-coded.  
        Topic_var topic =
          this->dds_utility_.get_topic< ::Outer::TestData_DDSTypeSupportInterface> (
            ts.in (),
            "app_op_send_topic");
        this->dds_utility_.check_objref (
          topic.in (),
          "SubAppDDSAdapter: get_topic ()");
          
        this->app_op_recv_listener_ =
          new app_op_recv_Listener (this->app_, this->dds_utility_);
            
        this->app_op_recv_reader_ =
          this->dds_utility_.get_datareader< ::Outer::TestData_DDSDataReader> (
            topic.in (),
            this->app_op_recv_listener_.in ());
      }
    catch (const CORBA::Exception&)
      {
      }
  }
  
  ::Components::SessionComponent_ptr
  SubAppDDSAdapter::get_executor (void)
  {
    return ::Components::SessionComponent::_duplicate (app_);
  }
  
  ::Components::EventConsumerBase_ptr
  SubAppDDSAdapter::get_consumer (const char * sink_name)
  {
    if (sink_name == 0)
      {
        throw ::Components::InvalidName ();
      }
      
    // Generate one of these for each consumes port.
    if (ACE_OS::strcmp (sink_name, "app_op_recv") == 0)
      {
        return this->get_consumer_app_op_recv ();
      }
      
    throw ::Components::InvalidName ();
  }

  ::DummyConsumer_ptr
  SubAppDDSAdapter::get_consumer_app_op_recv (void)
  {
    if (! ::CORBA::is_nil (this->consumes_app_op_recv_.in ()))
      {
        return 
          ::DummyConsumer::_duplicate (
            this->consumes_app_op_recv_.in ());
      }

    ::Components::EventConsumerBase_var obj =
      this->get_consumer_app_op_recv_i ();

    ::DummyConsumer_var eco =
      ::DummyConsumer::_narrow (obj.in ());

    this->consumes_app_op_recv_ = eco;
    return
      ::DummyConsumer::_duplicate (
        this->consumes_app_op_recv_.in ());
  }
  
  void
  SubAppDDSAdapter::populate_consumer_table (void)
  {
    ::CORBA::Object_var obj_var;
    ::Components::EventConsumerBase_var ecb_var;

    ecb_var =
      this->get_consumer_app_op_recv_i ();
  }
  
  ::Components::EventConsumerBase_ptr
  SubAppDDSAdapter::get_consumer_app_op_recv_i (void)
  {
    typedef
    ::CIAO::Port_Activator_T<DummyConsumer_impl,
                             ::DSTO::ExecBase,
                             ::DSTO::ContextBase,
                             SubAppDDSAdapter>
      MACRO_MADNESS_TYPEDEF;
      
    MACRO_MADNESS_TYPEDEF * tmp = 0;
    ACE_CString obj_id (this->ins_name_);
    obj_id += "_app_op_recv";
    
    ACE_NEW_THROW_EX (
      tmp,
      MACRO_MADNESS_TYPEDEF (
        obj_id.c_str (),
        "app_op_recv",
        ::CIAO::Port_Activator_Types::SINK,
        app_,
        0,
        this),
      ::CORBA::NO_MEMORY ());
      
    ::CIAO::Port_Activator_var pa = tmp;
      
    ::CIAO::Servant_Activator_var sa =
      this->container_->ports_servant_activator ();
      
    if (!sa->register_port_activator (tmp))
      {
        return ::DummyConsumer::_nil ();
      }
      
    ::CORBA::Object_var obj =
      this->container_->generate_reference (
        obj_id.c_str (),
        "IDL:DummyConsumer:1.0",
        ::CIAO::Container_Types::FACET_CONSUMER_t);
        
    ::Components::EventConsumerBase_var ecb =
      ::Components::EventConsumerBase::_narrow (obj.in ());
      
    if (CORBA::is_nil (ecb.in ()))
      {
        ACE_ERROR ((LM_EMERGENCY,
                    ACE_TEXT ("DummyConsumer objref generation failed\n")));
      }

    return ecb._retn ();
  }

  extern "C" SubAppDDSAdapter_Export ::PortableServer::Servant
  create_SubAppDDSAdapter_Servant (
    ::Components::EnterpriseComponent_ptr p,
    ::CIAO::Container_ptr c,
    const char *ins_name)
  {
    ::AppSpace::SubAppDDS * x =
      dynamic_cast< ::AppSpace::SubAppDDS *> (p);

    if (x == 0)
      {
        return 0;
      }

    ::PortableServer::Servant retval = 0;
    
    ACE_NEW_RETURN (
      retval, 
      SubAppDDSAdapter (x,
                        ::Components::CCMHome::_nil (),
                        ins_name,
                        0,
                        c),
      0);

    return retval;
  }
}
