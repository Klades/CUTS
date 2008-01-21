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

#include "cuts/Endpoint_Data.h"

//=============================================================================
/**
 * @class CUTS_Activation_Record_Endpoint
 *
 * Endpoint for an activation record. The endpoint is characterized
 * by sending information to another process, either local or remote.
 */
//=============================================================================

class CUTS_Export CUTS_Activation_Record_Endpoint :
  public CUTS_Endpoint_Data
{
public:
  /// Default constructor.
  CUTS_Activation_Record_Endpoint (void);

  /**
   * Initializing constructor.
   *
   * @param[in]       id            Id of the endpoint.
   * @param[in]       toc           Time of completion.
   * @param[in]       datasize      Number of bytes sent.
   */
  CUTS_Activation_Record_Endpoint (int id,
                                   const ACE_Time_Value & toc,
                                   size_t datasize);

  /**
   * Copy constructor.
   *
   * @param[in]       are           Source object.
   */
  CUTS_Activation_Record_Endpoint (const CUTS_Activation_Record_Endpoint & are);

  /// Destructor.
  ~CUTS_Activation_Record_Endpoint (void);

  /// Assignment operator.
  const CUTS_Activation_Record_Endpoint &
    operator = (const CUTS_Activation_Record_Endpoint & rhs);

  /// Get the id of the record.
  int id (void) const;

  /**
   * Set the values of the endpoint entry.
   *
   * @param[in]       id              The id of the endpoint.
   * @param[in]       toc             Time of completion.
   * @param[in]       datasize        The datasize of the endpoint.
   */
  void set (int id, const ACE_Time_Value & toc, size_t data_size);

private:
  /// Id of the endpoint entry.
  int id_;
};

#if defined (__CUTS_INLINE__)
#include "cuts/Activation_Record_Endpoint.inl"
#endif

#endif  // !defined _CUTS_ACTIVATION_RECORD_ENDPOINT_H_
