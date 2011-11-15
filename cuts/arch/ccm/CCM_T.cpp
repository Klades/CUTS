// $Id$

namespace CUTS
{
namespace CCM
{

//
// create_servant
//
template <typename EXECUTOR, typename SERVANT>
::PortableServer::Servant
create_servant (const char * name,
                ::PortableServer::POA_ptr port_POA,
                ::Components::EnterpriseComponent_ptr p)
{
  // First, convert the pointer to its concrete type.
  typename EXECUTOR::_var_type executor = EXECUTOR::_narrow (p);

  if (::CORBA::is_nil (executor.in ()))
    return 0;

  // Now, create the servant for the executor.
  SERVANT * servant = 0;

  ACE_NEW_RETURN (servant,
                  SERVANT (name, port_POA, executor.in ()),
                  0);

  return servant;
}

}
}
