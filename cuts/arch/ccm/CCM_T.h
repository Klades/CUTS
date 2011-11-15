// -*- C++ -*-

//=============================================================================
/**
 *  @file         CCM_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_T_H_
#define _CUTS_CCM_T_H_

namespace CUTS
{
namespace CCM
{

/**
 * Standard method for creating a CCM servant.
 *
 * @param[in]       name      Name of the servant
 * @param[in]       p         Pointer to the executor
 */
template <typename EXECUTOR, typename SERVANT>
::PortableServer::Servant
create_servant (const char * name,
                ::PortableServer::POA_ptr port_POA,
                ::Components::EnterpriseComponent_ptr p);

}
}

#include "CCM_T.cpp"

#endif

