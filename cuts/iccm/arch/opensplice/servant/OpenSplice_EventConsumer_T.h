// -*- C++ -*-

//=============================================================================
/**
 *  @file         OpenSplice_EventConsumer_T.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_OPENSPLICE_EVENTCONSUMER_T_H_
#define _ICCM_OPENSPLICE_EVENTCONSUMER_T_H_

#include "cuts/iccm/arch/dds/servant/DDS_EventConsumer_T.h"
#include "OpenSplice.h"

namespace iCCM
{

/**
 * @class OpenSplice_EventConsumer_T
 */
template <typename SERVANT, typename EVENT>
class OpenSplice_EventConsumer_T :
  public DDS_EventConsumer_T <OpenSplice, SERVANT, EVENT>
{
public:
  // Type definition of the DESERIALIZE_METHOD from the base class.
  typedef typename DDS_EventConsumer_T <OpenSplice, SERVANT, EVENT>::DESERIALIZE_METHOD DESERIALIZE_METHOD;

  /**
   * Initializing constructor.
   *
   * @param[in]         servant         The parent servant.
   * @param[in]         callback        Deserialized method on servant.
   */
  OpenSplice_EventConsumer_T (SERVANT * servant, DESERIALIZE_METHOD callback);

  /// Destructor.
  virtual ~OpenSplice_EventConsumer_T (void);
};

}

#include "OpenSplice_EventConsumer_T.cpp"

#endif  // !definef _ICCM_OPENSPLICE_EVENTCONSUMER_T_H_
