#include "tao/ORB_Core.h"

#include "ciao/Servants/Port_Activator_T.h"
#include "ciao/Logger/Log_Macros.h"

#include "ModelDDSDataConversion.h"

#include "PubAppDDSAdapter.h"

namespace DSTO_AppSpace_Impl
{
  PubAppDDSAdapter::PubAppDDSAdapter ( ::AppSpace::PubAppDDS * exe,
                                      ::Components::CCMHome_ptr,
                                      const char * ins_name,
                                      ::CIAO::Home_Servant_Impl_Base *,
                                      ::CIAO::Container_ptr c)
    : ::DSTO::AdapterBase (ins_name, c),
      ::DSTO::Adapter< ::POA_Outer::PubAppDDSComponent> (ins_name, c),
      app_ (exe),
      context_ (0)
  {
    ACE_NEW (this->context_,
             PubAppDDSContext (this->dds_utility_));
    
    try
      {
        ::Components::SessionComponent_var scom =
          ::Components::SessionComponent::_narrow (exe);

        if (! ::CORBA::is_nil (scom.in ()))
          {
            scom->set_session_context (this->context_);
          }
          
        // TODO - generate a domain id.  
        if (! this->dds_utility_.init (0))
          {
            ACE_ERROR ((LM_EMERGENCY,
                        ACE_TEXT ("PubAppDDSAdapter: error ")
                        ACE_TEXT ("in DDS initialization\n")));
          }  
      }
    catch (const CORBA::Exception& ex)
      {
        ex._tao_print_exception (
          "Exception caught in PubAppDDSAdapter constructor");
      }
  }
  
  PubAppDDSAdapter::~PubAppDDSAdapter (void)
  {
    delete this->context_;
    delete this->app_;
  }
  
  ::Components::SessionComponent_ptr
  PubAppDDSAdapter::get_executor (void)
  {
    return ::Components::SessionComponent::_duplicate (app_);
  }

  ::Components::Cookie *
  PubAppDDSAdapter::subscribe (
    const char * publisher_name,
    ::Components::EventConsumerBase_ptr subscriber)
  {
    if (publisher_name == 0)
      {
        throw ::Components::InvalidName ();
      }
      
    if (ACE_OS::strcmp (publisher_name, "app_op_send") == 0)
      {
        ::DummyConsumer_var sub =
          ::DummyConsumer::_narrow (subscriber);
          
        if ( ::CORBA::is_nil (sub.in ()))
          {
            throw ::Components::InvalidConnection ();
          }
        else
          {
            return this->subscribe_app_op_send (sub.in ());
          }
      }
      
    return 0;
  }

  ::Components::EventConsumerBase_ptr
  PubAppDDSAdapter::unsubscribe (const char * publisher_name,
                                 ::Components::Cookie * ck)
  {
    if (publisher_name == 0)
      {
        throw ::Components::InvalidName ();
      }
      
    if (ACE_OS::strcmp (publisher_name, "app_op_send") == 0)
      {
        return this->unsubscribe_app_op_send (ck);
      }
      
    throw ::Components::InvalidName ();
  }
    
  ::Components::Cookie *
  PubAppDDSAdapter::subscribe_app_op_send (
    ::DummyConsumer_ptr c)
  {
    return this->context_->subscribe_app_op_send (c);
  }

  ::DummyConsumer_ptr
  PubAppDDSAdapter::unsubscribe_app_op_send ( ::Components::Cookie * ck)
  {
    return this->context_->unsubscribe_app_op_send (ck);
  }
  
  void
  PubAppDDSAdapter::configuration_complete (void)
  {
    ::Outer::TestData ev;
    ev.key = 5;
    ev.packet.name = "catastrophe";
    ev.packet.id = 12345;
    ev.packet.urgent = true;
    
    this->app_->app_op_send (&ev);
  }

  //=========================================================

  extern "C" PubAppDDSAdapter_Export ::PortableServer::Servant
  create_PubAppDDSAdapter_Servant (
    ::Components::EnterpriseComponent_ptr p,
    ::CIAO::Container_ptr c,
    const char *ins_name)
  {
    ::AppSpace::PubAppDDS * x =
      dynamic_cast< ::AppSpace::PubAppDDS *> (
        ::Components::EnterpriseComponent::_duplicate (p));

    if (x == 0)
      {
        return 0;
      }

    ::PortableServer::Servant retval = 0;
    
    ACE_NEW_RETURN (
      retval, 
      PubAppDDSAdapter (x,
                        ::Components::CCMHome::_nil (),
                        ins_name,
                        0,
                        c),
      0);

    return retval;
  }
}
