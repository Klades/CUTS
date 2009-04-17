#include "DSTO_ExecBase.h"

namespace DSTO
{
  ExecBase::ExecBase (void)
    : ::Components::SessionComponent (),
      ::CORBA::LocalObject ()
  {
  }

  ExecBase::~ExecBase (void)
  {
  }

  void
  ExecBase::set_session_context (
    ::Components::SessionContext_ptr)
  {
  }

  void
  ExecBase::configuration_complete (void)
  {
  }

  void
  ExecBase::ccm_activate (void)
  {
  }

  void
  ExecBase::ccm_passivate (void)
  {
  }

  void
  ExecBase::ccm_remove (void)
  {
  }
  
  ExecBase *
  ExecBase::_narrow ( ::CORBA::Object_ptr)
  {
    return 0;
  }
}

