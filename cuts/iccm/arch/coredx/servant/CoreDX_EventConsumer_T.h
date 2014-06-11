// -*- C++ -*-

//=============================================================================
/**
 *  @file         CoreDX_EventConsumer_T.h
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

#ifndef _ICCM_COREDX_EVENTCONSUMER_T_H_
#define _ICCM_COREDX_EVENTCONSUMER_T_H_

#include "cuts/iccm/arch/dds/servant/DDS_EventConsumer_T.h"
#include "CoreDX.h"

namespace iCCM
{

/**
 * @class CoreDX_EventConsumer_T
 */
template <typename SERVANT, typename EVENT>
class CoreDX_EventConsumer_T :
  public DDS_EventConsumer_T <CoreDX, SERVANT, EVENT>
{
public:
  /// Type definition of the servant type.
  typedef SERVANT servant_type;

  /// Type definition of the event type.
  typedef EVENT event_type;

  /// Type definition of the servant callback method.
  typedef void (SERVANT::*CALLBACK_METHOD) (EVENT *);

  /**
   * Initializing constructor.
   *
   * @param[in]         servant         The parent servant.
   * @param[in]         callback        Deserialized method on servant.
   */
  CoreDX_EventConsumer_T (SERVANT * servant, CALLBACK_METHOD callback);

  /// Destructor.
  virtual ~CoreDX_EventConsumer_T (void);

private:
  /// Servant to pass event.
  SERVANT * servant_;

  /// Method for deserializing an event.
  CALLBACK_METHOD callback_;
};

}

#include "CoreDX_EventConsumer_T.cpp"

#endif  // !definef _CUTS_COREDX_EVENTCONSUMER_T_H_