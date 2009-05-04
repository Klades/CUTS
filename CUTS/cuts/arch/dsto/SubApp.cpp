// This include is not to be generated from the model, it's
// just for debugging.
#include "ace/streams.h"

#include "SubApp.h"

namespace AppSpace
{
  SubApp::SubApp (void)
  {
  }

  SubApp::~SubApp (void)
  {
  }

  void
  SubApp::app_op_recv ( ::Outer::TestData * ev)
  {
    // For debugging, to compare with the native data values
    // on the other end.
    cout << endl
         << "\t DSTO sub data -" << endl
         << "key: " << ev->key << endl
         << "name: " << ev->packet.name << endl
         << "id: " << ev->packet.id << endl
         << "urgent: "
         << (ev->packet.urgent ? "true" : "false")
         << endl << endl;
      
    delete [] ev->packet.name;     
    ev->packet.name = 0;     

    delete ev;
    ev = 0;
  }
}

extern "C" SubApp_Export ::Components::EnterpriseComponent_ptr
create_SubAppAdapter_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (
    retval,
    ::AppSpace::SubApp,
    ::Components::EnterpriseComponent::_nil ());

  return retval;
}

