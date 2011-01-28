// -*- C++ -*-

#ifndef _CUTS_RTIDDS_SERVANT_H_
#define _CUTS_RTIDDS_SERVANT_H_

#include "ndds/ndds_cpp.h"
#include "RTIDDS_export.h"

/**
 * @class CUTS_RTIDDS_Servant
 *
 * The base class for the RTI-DDS servant. Each servant can be either a
 * publisher, subscriber, or both. This is dependent on if the component
 * has event ports, and the type of event ports.
 */
class CUTS_RTIDDS_Export CUTS_RTIDDS_Servant
{
public:
  /// Destructor.
  virtual ~CUTS_RTIDDS_Servant (void) ;

  /**
   * Get the domain participant for the servant.
   *
   * @return     The current domain participant
   */
  virtual ::DDSDomainParticipant * participant (void);

  /**
   * Configure the servant using the provided domain participant.
   *
   * @param[in]        participant        New domain participant.
   */
  virtual void configure (::DDSDomainParticipant *);

  /// Remove the servant.
  virtual ::DDSDomainParticipant * remove_participant (void);

protected:
  /// Default constructor.
  CUTS_RTIDDS_Servant (void);

  /// The domain participant for the servant.
  ::DDSDomainParticipant * participant_;

  /// The publisher for this participant.
  ::DDSPublisher * publisher_;

  /// The subscriber for this participant.
  ::DDSSubscriber * subscriber_;
};

#include "RTIDDS_Servant.h"

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Servant.inl"
#endif

#endif

