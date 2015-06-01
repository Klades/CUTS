// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_Servant_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_OPENSPLICE_SERVANT_T_H_
#define _ICCM_OPENSPLICE_SERVANT_T_H_

#include "cuts/iccm/arch/dds/servant/DDS_Servant_T.h"

#include "OpenSplice_EventConsumer_T.h"
#include "OpenSplice_Publisher_Table_T.h"
#include "OpenSplice_Publisher_T.h"
#include "OpenSplice_Servant.h"

namespace iCCM
{

/**
 * @class OpenSplice_Servant_T
 *
 * Typed version of the OpenSplice servant base class.
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class OpenSplice_Servant_T :
  public DDS_Servant_T <OpenSplice, T, CONTEXT, EXECUTOR, POA_EXEC>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       _this           This servant object
   * @param[in]       name            Name of the servant
   * @param[in]       port_poa        The POA for ports
   * @param[in]       impl            The servant implementation
   */
  OpenSplice_Servant_T (T * _this,
                        const char * name,
                        ::PortableServer::POA_ptr port_poa,
                        typename EXECUTOR::_ptr_type impl);

  /**
   * Inactive constructor.  This constructor will not activate the object
   * but simply provides a mechanism to configure underlying EventConsumers,
   * Publishers, and Publisher_Tables
   */
  DDS_Servant_T (const char * name);

  /// Destructor.
  virtual ~OpenSplice_Servant_T (void);
};

}

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Servant_T.inl"
#endif

#include "OpenSplice_Servant_T.cpp"

#endif  // !defined _CUTS_OPENSPLICE_CCM_SERVANT_T_H_
