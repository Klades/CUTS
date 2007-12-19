// -*- C++ -*-

//=============================================================================
/**
 * @file        Activation_Record_Endpoint.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ACTIVATION_RECORD_ENDPOINT_H_
#define _CUTS_ACTIVATION_RECORD_ENDPOINT_H_

#include "cuts/config.h"
#include "cuts/CUTS_export.h"
#include "ace/Time_Value.h"

//=============================================================================
/**
 * @class CUTS_Activation_Record_Endpoint
 *
 * Endpoint for an activation record. The endpoint is characterized
 * by sending information to another process, either local or remote.
 */
//=============================================================================

class CUTS_Export CUTS_Activation_Record_Endpoint
{
public:
  /// Default constructor.
  CUTS_Activation_Record_Endpoint (void);

  /**
   * Initializing constructor.
   *
   * @param[in]       toc           Time of completion.
   * @param[in]       datasize      Number of bytes sent.
   */
  CUTS_Activation_Record_Endpoint (const ACE_Time_Value & toc,
                                   size_t datasize = 0);

  /// Copy constructor.
  CUTS_Activation_Record_Endpoint (const CUTS_Activation_Record_Endpoint &);

  /// Destructor.
  ~CUTS_Activation_Record_Endpoint (void);

  /// Size of the data sent at this endpoint.
  size_t datasize (void) const;

  /// Unique id of the endpoint.
  const ACE_Time_Value & time_of_completion (void) const;

  /// Assignment operator.
  const CUTS_Activation_Record_Endpoint &
    operator = (const CUTS_Activation_Record_Endpoint & rhs);

private:
  /// Size of the data send at this endpoint.
  size_t datasize_;

  /// Time of completion for the endpoint.
  ACE_Time_Value toc_;
};

#if defined (__CUTS_INLINE__)
#include "cuts/Activation_Record_Endpoint.inl"
#endif

#endif  // !defined _CUTS_ACTIVATION_RECORD_ENDPOINT_H_
