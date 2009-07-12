// -*- C++ -*-

#ifndef _CUTS_RTIDDS_SERVANT_H_
#define _CUTS_RTIDDS_SERVANT_H_

#include "ndds/ndds_cpp.h"
#include "RTIDDS_export.h"

/**
 * @class CUTS_RTIDDS_Servant
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
};

#include "RTIDDS_Servant.h"

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Servant.inl"
#endif

#endif

