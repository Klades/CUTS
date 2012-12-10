// -*- C++ -*-

//==============================================================================
/**
 *  @file       RTIDDS_Servant.h
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

#ifndef _ICCM_RTIDDS_SERVANT_H_
#define _ICCM_RTIDDS_SERVANT_H_

#include "cuts/iccm/servant/Servant.h"
#include "RTIDDS.h"

namespace iccm
{
  // Forward decl.
  class TopicQos;

  // Forward decl.
  class PublisherQos;

  // Forward decl.
  class SubscriberQos;

  // Forward decl.
  class DataReaderQos;

  // Forward decl.
  class DataWriterQos;
}

namespace iCCM
{

/**
 * @class RTIDDS_Servant
 *
 * Base class for all RTIDDS servant objects. This class enables
 * the container to send commands to the servant, such as
 * domain-specific configuration information.
 */
class ICCM_RTIDDS_SVNT_Export RTIDDS_Servant :
  public DDS_Servant <RTIDDS>
{
public:
  /// Base class typedef
  typedef DDS_Servant <RTIDDS> base_class;

  /// Default constructor.
  RTIDDS_Servant (const char * name);

  /// Destructor.
  virtual ~RTIDDS_Servant (void);

  /// Default configuration.
  virtual void configure (void);

  /// Initialize Qos configuration.
  virtual void configure (const ::iccm::DomainParticipantQos & qos);
};

}

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Servant.inl"
#endif

#endif  // !defined _ICCM_RTIDDS_SERVANT_H_
