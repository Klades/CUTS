// -*- C++ -*-

//==============================================================================
/**
 *  @file       QpidPB_Servant.h
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
//==============================================================================

#ifndef _ICCM_QPIDPB_SERVANT_H_
#define _ICCM_QPIDPB_SERVANT_H_

#include "cuts/iccm/servant/Servant.h"

#include "QpidPB_EventConsumer.h"
#include "QpidPB_Publisher.h"
#include "QpidPB_Publisher_Table.h"

namespace iCCM
{

/**
 * @class QpidPB_Servant
 *
 * Base class for all QpidPB servant objects. This class enables
 * the container to send commands to the servant, such as
 * domain-specific configuration information.
 */
class ICCM_QPIDPB_SVNT_Export QpidPB_Servant :
  public Servant
{
public:
  /// Trait definitions for iCCM::Servant_T object.
  typedef QpidPB_EventConsumer eventconsumer_type;
  typedef QpidPB_Publisher publisher_type;
  typedef QpidPB_Publisher_Table publisher_table_type;

  /// Default constructor.
  QpidPB_Servant (const char * name);

  /// Destructor.
  virtual ~QpidPB_Servant (void);
};

}

#if defined (__CUTS_INLINE__)
#include "QpidPB_Servant.inl"
#endif

#endif  // !defined _ICCM_QpidPB_SERVANT_H_
