// This include is not to be generated from the model, it's
// just for debugging.
#include "ace/streams.h"

#include "PubAppDDS.h"

namespace AppSpace
{
  PubAppDDS::PubAppDDS (void)
    : context_ (0)
  {
  }

  PubAppDDS::~PubAppDDS (void)
  {
  }

  void
  PubAppDDS::app_op_send ( ::Outer::TestData * ev)
  {
    // For debugging, to compare with the native data values
    // on the other end.
    cout << endl
         << "\t DDS pub data -" << endl
         << "key: " << ev->key << endl
         << "name: " << ev->packet.name << endl
         << "id: " << ev->packet.id << endl
         << "urgent: "
         << (ev->packet.urgent ? "true" : "false") << endl;
      
    this->context_->push_app_op_send (ev);
  }
  
  void
  PubAppDDS::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    // CIAO duplicates the context when it is passed from the
    // servant, but I don't see why we can't just expect the
    // servant's and exec's lifetime to coincide - if so we 
    // don't need a copy.
    this->context_ =
      dynamic_cast< ::DSTO_AppSpace_Impl::PubAppDDSContext *> (ctx);

    if (CORBA::is_nil (this->context_))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  extern "C" PubAppDDS_Export ::Components::EnterpriseComponent_ptr
  create_PubAppDDSAdapter_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_RETURN (
      retval,
      ::AppSpace::PubAppDDS,
      ::Components::EnterpriseComponent::_nil ());

    return retval;
  }
}

