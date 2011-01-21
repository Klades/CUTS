// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_SERVANT_H_
#define _CUTS_OPENSPLICE_SERVANT_H_

#include "ccpp_dds_dcps.h"
#include "OpenSplice_export.h"

/**
 * @class CUTS_OpenSplice_Servant
 *
 * Base class for all C++ bindings of OpenSplice. The servant is a
 * single participant in the domain. It also has a single publisher
 * and subscriber interface for sending and receiving events, respectively.
 * If the servant does neither sends nor receives events, then the
 * publisher or subscriber interface will not be active.
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

  /// Test if the servant is a publisher.
  bool is_publisher (void) const;

  /// Test is the servant is a subscriber.
  bool is_subscriber (void) const;

protected:
  /// Default constructor.
  CUTS_OpenSplice_Servant (void);

  /// The domain participant for the servant.
  ::DDS::DomainParticipant_var participant_;

  /// The publisher for the servant.
  ::DDS::Publisher_var publisher_;

  /// The subscriber for the servant.
  ::DDS::Subscriber_var subscriber_;
};

#include "OpenSplice_Servant.h"

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Servant.inl"
#endif

#endif

