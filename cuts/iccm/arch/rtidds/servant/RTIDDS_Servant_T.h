// -*- C++ -*-

//=============================================================================
/**
 *  @file         RTIDDS_Servant_T.h
 *
 *  $Id$
 *
 *  Code generated by iCCM skeleton project generator that is include
 *  in the CUTS (http://cuts.cs.iupui.edu) and developed by:
 *
 *      Software Engineering & Distributed System (SEDS) Group
 *      Indiana Univesity-Purdue University Indianapolis
 *      Indianapolis, IN 46202
 */
//=============================================================================

#ifndef _ICCM_RTIDDS_SERVANT_T_H_
#define _ICCM_RTIDDS_SERVANT_T_H_

#include "cuts/iccm/arch/dds/servant/DDS_Servant_T.h"

#include "RTIDDS_EventConsumer_T.h"
#include "RTIDDS_Publisher_Table_T.h"
#include "RTIDDS_Publisher_T.h"
#include "RTIDDS_Servant.h"

namespace iCCM
{

/**
 * @class RTIDDS_Servant_T
 *
 * Template implementation of RTIDDS servant. This implementation
 * is the base class for all servants.
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class RTIDDS_Servant_T :
  public DDS_Servant_T <RTIDDS, T, CONTEXT, EXECUTOR, POA_EXEC>
{
public:
  /// Initializing constructor.
  RTIDDS_Servant_T (T * _this,
                    const char * name,
                    ::PortableServer::POA_ptr port_poa,
                    typename EXECUTOR::_ptr_type impl);

  /// Destructor.
  virtual ~RTIDDS_Servant_T (void);
};

}

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Servant_T.inl"
#endif

#include "RTIDDS_Servant_T.cpp"

#endif  // !defined _ICCM_RTIDDS_SERVANT_T_H_
