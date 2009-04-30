#include "tao/ORB_Core.h"

#include "ciao/Valuetype_Factories/Cookies.h"

#include "ciao/Servants/Port_Activator_T.h"

#include "ModelDataConversion.h"

#include "SubAppAdapter.h"

namespace DSTO_AppSpace_Impl
{
  SubAppAdapter::SubAppAdapter ( ::AppSpace::SubApp * executor,
                                ::Components::CCMHome_ptr,
                                const char * ins_name,
                                ::CIAO::Home_Servant_Impl_Base *,
                                ::CIAO::Container_ptr c)
    : ::DSTO::AdapterBase (ins_name, c),
      ::DSTO::Adapter< ::POA_Outer::SubAppComponent> (ins_name, c),
      app_ (executor),
      context_ (0)
  {
    ACE_NEW (this->context_, ::DSTO::ContextBase);
    
    TAO_OBV_REGISTER_FACTORY ( ::Outer::TestData_IDL_init,
                              ::OBV_Outer::TestData_IDL);
                              
    try
      {
        this->populate_consumer_table ();
      }
    catch (const CORBA::Exception&)
      {
      }
  }
  
  ::Components::SessionComponent_ptr
  SubAppAdapter::get_executor (void)
  {
    return ::Components::SessionComponent::_duplicate (app_);
  }

  ::Outer::TestData_IDLConsumer_ptr
  SubAppAdapter::get_consumer_app_op_recv (void)
  {
    if (! ::CORBA::is_nil (this->consumes_app_op_recv_.in ()))
      {
        return 
          ::Outer::TestData_IDLConsumer::_duplicate (
            this->consumes_app_op_recv_.in ());
      }

    ::Components::EventConsumerBase_var obj =
      this->get_consumer_app_op_recv_i ();

    ::Outer::TestData_IDLConsumer_var eco =
      ::Outer::TestData_IDLConsumer::_narrow (obj.in ());

    this->consumes_app_op_recv_ = eco;
    return
      ::Outer::TestData_IDLConsumer::_duplicate (
        this->consumes_app_op_recv_.in ());
  }
  
  void
  SubAppAdapter::populate_consumer_table (void)
  {
    ::CORBA::Object_var obj_var;
    ::Components::EventConsumerBase_var ecb_var;

    ecb_var =
      this->get_consumer_app_op_recv_i ();
  }
  
  ::Components::EventConsumerBase_ptr
  SubAppAdapter::get_consumer_app_op_recv_i (void)
  {
    ::Components::EventConsumerBase_ptr ret =
      this->lookup_consumer ("app_op_recv");

    if (! ::CORBA::is_nil (ret))
      {
        return ret;
      }

    typedef
    ::CIAO::Port_Activator_T<app_op_recv_Consumer,
                             ::DSTO::ExecBase,
                             ::DSTO::ContextBase,
                             SubAppAdapter>
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
        context_,
        this),
      ::CORBA::NO_MEMORY ());
      
    ::CIAO::Port_Activator_var pa = tmp;
      
    ::CIAO::Servant_Activator_var sa =
      this->container_->ports_servant_activator ();
      
    if (!sa->register_port_activator (tmp))
      {
        return ::Outer::TestData_IDLConsumer::_nil ();
      }
      
    ::CORBA::Object_var obj =
      this->container_->generate_reference (
        obj_id.c_str (),
        "IDL:Outer/TestData_IDLConsumer:1.0",
        ::CIAO::Container_Types::FACET_CONSUMER_t);
        
    ::Components::EventConsumerBase_var ecb =
      ::Components::EventConsumerBase::_narrow (obj.in ());

    this->add_consumer ("app_op_recv",
                        ecb.in ());

    return ecb._retn ();
  }

  //=========================================================

  app_op_recv_Consumer::app_op_recv_Consumer ( ::DSTO::ExecBase * executor,
                                              ::DSTO::ContextBase *)
    : executor_ (dynamic_cast< ::AppSpace::SubApp *> (executor))
  {
  }

  void
  app_op_recv_Consumer::push_TestData_IDL (
    ::Outer::TestData_IDL * corba_ev)
  {
    ::Outer::TestData * app_ev = 0;
    ACE_NEW (app_ev, ::Outer::TestData);
    ACE_Auto_Ptr< ::Outer::TestData> safe_ev (app_ev);
    ::ModelDataConversion::from_corba (*app_ev, *corba_ev);
    executor_->app_op_recv (safe_ev.release ());
    // Note that the app must manage the event's allocated memory,
    // but this rule can be easily changed.
  }

  //=========================================================

  extern "C" SubAppAdapter_Export ::PortableServer::Servant
  create_SubAppAdapter_Servant (
    ::Components::EnterpriseComponent_ptr p,
    ::CIAO::Container_ptr c,
    const char *ins_name)
  {
    ::AppSpace::SubApp * x =
      dynamic_cast< ::AppSpace::SubApp *> (p);

    if (x == 0)
      {
        return 0;
      }

    ::PortableServer::Servant retval = 0;
    
    ACE_NEW_RETURN (
      retval, 
      SubAppAdapter (x,
                     ::Components::CCMHome::_nil (),
                     ins_name,
                     0,
                     c),
      0);

    return retval;
  }
}
