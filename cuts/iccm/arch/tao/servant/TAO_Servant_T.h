// -*- C++ -*-

//=============================================================================
/**
 *  @file         TAO_Servant_T.h
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

#ifndef _ICCM_TAO_SERVANT_T_H_
#define _ICCM_TAO_SERVANT_T_H_

#include "cuts/iccm/servant/Servant_T.h"

#include "TAO_Servant.h"
#include "TAO_EventConsumer_T.h"
#include "TAO_Publisher_T.h"
#include "TAO_Publisher_Table_T.h"

namespace iCCM
{

/**
 * @class TAO_Servant_T
 *
 * Template implementation of TAO servant. This implementation
 * is the base class for all servants.
 */
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
class TAO_Servant_T :
  public Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, TAO_Servant>
{
public:
  /// Type definition of the base type.
  typedef Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC, TAO_Servant> base_type;

  /// Type definition of the consumer map.
  typedef typename base_type::consumer_map_type consumer_map_type;

  /// Type definition of the publisher map.
  typedef typename base_type::emits_map_type emits_map_type;

  /// Type definition of the publisher table map.
  typedef typename base_type::publishes_map_type publishes_map_type;

  /// Initializing constructor.
  TAO_Servant_T (
    T * _this,
    const char * name,
    ::PortableServer::POA_ptr port_poa,
    typename EXECUTOR::_ptr_type impl);

  /// Destructor.
  virtual ~TAO_Servant_T (void);
};

}

#if defined (__CUTS_INLINE__)
#include "TAO_Servant_T.inl"
#endif

#include "TAO_Servant_T.cpp"

#endif  // !defined _ICCM_TAO_SERVANT_T_H_
