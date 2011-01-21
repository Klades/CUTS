// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_SERVANT_H_
#define _CUTS_OPENSPLICE_SERVANT_H_

#include "ccpp_dds_dcps.h"
#include "OpenSplice_export.h"

/**
 * @class CUTS_OpenSplice_Servant
 */
class CUTS_OPENSPLICE_Export CUTS_OpenSplice_Servant
{
 public:
  /// Destructor.
  virtual ~CUTS_OpenSplice_Servant (void) ;

  /**
   * Get the domain participant for the servant.
   *
   * @return     The current domain participant
   */
  virtual ::DDS::DomainParticipant_ptr participant (void);

  /**
   * Configure the servant using the provided domain participant.
   *
   * @param[in]        participant        New domain participant.
   */
  virtual void configure (::DDS::DomainParticipant_ptr);

  /// Remove the servant.
  virtual ::DDS::DomainParticipant_ptr remove_participant (void);

protected:
  /// Default constructor.
  CUTS_OpenSplice_Servant (void);

  /// The domain participant for the servant.
  ::DDS::DomainParticipant_var participant_;
};

#include "OpenSplice_Servant.h"

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Servant.inl"
#endif

#endif

