// -*- C++ -*-

#ifndef _CUTS_OPENSPLICE_ENDPOINT_H_
#define _CUTS_OPENSPLICE_ENDPOINT_H_

#include "ccpp_dds_dcps.h"
#include "OpenSplice_export.h"

/**
 * @class CUTS_OpenSplice_Endpoint
 */
class CUTS_OPENSPLICE_Export CUTS_OpenSplice_Endpoint
{
 public:
  /// Default constructor.
  CUTS_OpenSplice_Endpoint (void);

  /// Destructor.
  virtual ~CUTS_OpenSplice_Endpoint (void);

  /// Get a reference to the DDS topic for the endpoint.
  ::DDS::Topic_ptr topic (void);

  /**
   * Open the endpoint by creating the topic.
   */
  virtual int open (::DDS::DomainParticipant_ptr participant,
                    ::DDS::TypeSupport_ptr type_support,
                    const char * topic_name);

  virtual int open (::DDS::DomainParticipant_ptr participant,
                    ::DDS::TypeSupport_ptr type_support,
                    const char * type_name,
                    const char * topic_name);

  /// Close the endpoint.
  virtual int close (void);

  /// Determine if the endpoint is open.
  bool is_open (void) const;

 protected:
  /// Reference to the domain participant for the topic.
  ::DDS::DomainParticipant_var participant_;

  /// The DDS topic for the endpoint.
  ::DDS::Topic_var dds_topic_;
};

#if defined (__CUTS_INLINE__)
#include "OpenSplice_Endpoint.inl"
#endif

#endif
