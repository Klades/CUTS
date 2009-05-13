// $Id$

namespace CUTS_TCPIP
{
namespace CCM
{
  template <typename EXEC, typename SVNT>
  ::PortableServer::Servant
  create_servant (const char * name,
                  CUTS_TCPIP_Servant_Manager * svnt_mgr,
                  ::Components::EnterpriseComponent_ptr p)
  {
    // First, convert the pointer to its concrete type.
    typename EXEC::_var_type executor = EXEC::_narrow (p);

    if (::CORBA::is_nil (executor.in ()))
      return 0;

    // Now, create the servant for the executor.
    SVNT * servant = 0;

    ACE_NEW_RETURN (servant,
                    SVNT (name, *svnt_mgr, executor.in ()),
                    0);

    return servant;
  }
}
}
