// -*- C++ -*-

#ifndef _CUTS_RTIDDS_ENDPOINT_H_
#define _CUTS_RTIDDS_ENDPOINT_H_

#include "ndds/ndds_cpp.h"
#include "RTIDDS_export.h"

/**
 * @class CUTS_RTIDDS_Endpoint
 */
class CUTS_RTIDDS_Export CUTS_RTIDDS_Endpoint
{
 public:
  /// Default constructor.
  CUTS_RTIDDS_Endpoint (void);

  /// Destructor.
  virtual ~CUTS_RTIDDS_Endpoint (void);

  /// Get a reference to the DDS topic for the endpoint.
  ::DDSTopic * topic (void);

  /**
   * Open the endpoint by creating the topic.
   */
  virtual int open (::DDSDomainParticipant * participant,
                    const char * type_name,
                    const char * topic_name);

  /// Close the endpoint.
  virtual int close (void);

  /// Test if the endpoint is open. An endpoint is open if it
  /// container a topic.
  bool is_open (void) const;

 protected:
  /// Reference to the domain participant for the topic.
  ::DDSDomainParticipant * participant_;

  /// The DDS topic for the endpoint.
  ::DDSTopic * dds_topic_;
};

#if defined (__CUTS_INLINE__)
#include "RTIDDS_Endpoint.inl"
#endif

#endif
