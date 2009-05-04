// This include is not to be generated from the model, it's
// just for debugging.
#include "ace/Streams.h"

#include "SubAppDDS.h"

namespace AppSpace
{
  SubAppDDS::SubAppDDS (void)
  {
  }

  SubAppDDS::~SubAppDDS (void)
  {
  }

  void
  SubAppDDS::app_op_recv ( ::Outer::TestData * ev)
  {
    // For debugging, to compare with the native data values
    // on the other end.
    cout << endl
         << "\t DDS sub data -" << endl
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

extern "C" SubAppDDS_Export ::Components::EnterpriseComponent_ptr
create_SubAppDDSAdapter_Impl (void)
{
  ::Components::EnterpriseComponent_ptr retval =
    ::Components::EnterpriseComponent::_nil ();

  ACE_NEW_RETURN (
    retval,
    ::AppSpace::SubAppDDS,
    ::Components::EnterpriseComponent::_nil ());

  return retval;
}

