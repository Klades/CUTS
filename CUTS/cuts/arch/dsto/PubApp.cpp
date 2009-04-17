// This include is not to be generated from the model, it's
// just for debugging.
#include "ace/Streams.h"

#include "PubApp.h"

namespace AppSpace
{
  PubApp::PubApp (void)
    : context_ (0)
  {
  }

  PubApp::~PubApp (void)
  {
  }

  void
  PubApp::app_op_send ( ::Outer::TestData * ev)
  {
    // For debugging, to compare with the native data values
    // on the other end.
    cout << endl
         << "\t DSTO pub data -" << endl
         << "key: " << ev->key << endl
         << "name: " << ev->packet.name << endl
         << "id: " << ev->packet.id << endl
         << "urgent: "
         << (ev->packet.urgent ? "true" : "false") << endl;
      
    this->context_->push_app_op_send (ev);
  }
  
  void
  PubApp::set_context ( ::DSTO_AppSpace_Impl::PubAppContext * ctx)
  {
    this->context_ = ctx;
  }
  
  void
  PubApp::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    // CIAO duplicates the context when it is passed from the
    // servant, but I don't see why we can't just expect the
    // servant's and exec's lifetime to coincide - if so we 
    // don't need a copy.
    this->context_ =
      dynamic_cast< ::DSTO_AppSpace_Impl::PubAppContext *> (ctx);
//    this->context_ =
//      dynamic_cast< ::DSTO_AppSpace_Impl::PubAppContext *> (
//        ::Components::SessionContext::_duplicate (ctx));

    if (CORBA::is_nil (this->context_))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  extern "C" PubApp_Export ::Components::EnterpriseComponent_ptr
  create_PubAppAdapter_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_RETURN (
      retval,
      ::AppSpace::PubApp,
      ::Components::EnterpriseComponent::_nil ());

    return retval;
  }
}

