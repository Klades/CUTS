#include "tao/ORB_Core.h"

#include "ciao/Servants/Port_Activator_T.h"
#include "ciao/Logger/Log_Macros.h"

#include "ModelDataConversion.h"

#include "PubAppAdapter.h"

namespace DSTO_AppSpace_Impl
{
  PubAppAdapter::PubAppAdapter ( ::AppSpace::PubApp * exe,
                                ::Components::CCMHome_ptr,
                                const char * ins_name,
                                ::CIAO::Home_Servant_Impl_Base *,
                                ::CIAO::Container_ptr c)
    : ::DSTO::AdapterBase (ins_name, c),
      ::DSTO::Adapter< ::POA_Outer::PubAppComponent> (ins_name, c),
      app_ (exe),
      context_ (0)
  {
    ACE_NEW (this->context_, PubAppContext);
    
    TAO_OBV_REGISTER_FACTORY ( ::Outer::TestData_IDL_init,
                              ::OBV_Outer::TestData_IDL);

    ::Components::SessionComponent_var scom =
      ::Components::SessionComponent::_narrow (exe);

    if (! ::CORBA::is_nil (scom.in ()))
      {
        scom->set_session_context (this->context_);
      }
  }
  
  ::Components::SessionComponent_ptr
  PubAppAdapter::get_executor (void)
  {
    return ::Components::SessionComponent::_duplicate (app_);
  }

  ::Components::Cookie *
  PubAppAdapter::subscribe (
    const char * publisher_name,
    ::Components::EventConsumerBase_ptr subscriber)
  {
    if (publisher_name == 0)
      {
        throw ::Components::InvalidName ();
      }
      
    if (ACE_OS::strcmp (publisher_name, "app_op_send") == 0)
      {
        ::Outer::TestData_IDLConsumer_var sub =
          ::Outer::TestData_IDLConsumer::_narrow (subscriber);
          
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
  PubAppAdapter::unsubscribe (const char * publisher_name,
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
  PubAppAdapter::subscribe_app_op_send (
    ::Outer::TestData_IDLConsumer_ptr c)
  {
    return this->context_->subscribe_app_op_send (c);
  }

  ::Outer::TestData_IDLConsumer_ptr
  PubAppAdapter::unsubscribe_app_op_send ( ::Components::Cookie * ck)
  {
    return this->context_->unsubscribe_app_op_send (ck);
  }
  
  void
  PubAppAdapter::configuration_complete (void)
  {
    ::Outer::TestData ev;
    ev.key = 5;
    ev.packet.name = "catastrophe";
    ev.packet.id = 12345;
    ev.packet.urgent = true;
    
    // @@@@ (JP) Added this non-virtual method because there is
    // something wrong with the vf table at this point. The context
    // set call is repeated here because the app's context pointer
    // member has been corrupted sometime since it was passed in by
    // the constructor above.
    this->app_->set_context (this->context_);
//    this->app_->set_session_context (this->context_);

    this->app_->app_op_send (&ev);
  }

  //=========================================================

  extern "C" PubAppAdapter_Export ::PortableServer::Servant
  create_PubAppAdapter_Servant (
    ::Components::EnterpriseComponent_ptr p,
    ::CIAO::Container_ptr c,
    const char *ins_name)
  {
    ::AppSpace::PubApp * x =
      dynamic_cast< ::AppSpace::PubApp *> (p);

    if (x == 0)
      {
        return 0;
      }

    ::PortableServer::Servant retval = 0;
    
    ACE_NEW_RETURN (
      retval, 
      PubAppAdapter (x,
                     ::Components::CCMHome::_nil (),
                     ins_name,
                     0,
                     c),
      0);

    return retval;
  }
}
