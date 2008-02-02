// -*- C++ -*-

//=============================================================================
/**
 * @file        Port_Summary.h
 *
 * Defines class for summarizing and presenting port-related metrics
 *
 * $Id$
 *
 * @author      James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_PORT_SUMMARY_H_
#define _CUTS_PORT_SUMMARY_H_

#include "cuts/Activation_Record_Log.h"
#include "cuts/Endpoint_Log_Summary.h"
#include "cuts/Time_Measurement.h"

// Forward decl.
class CUTS_Metrics_Visitor;

//=============================================================================
/**
 * @class CUTS_Port_Summary_Base
 */
//=============================================================================

class CUTS_Export CUTS_Port_Summary_Base
{
public:
  /// Default constructor.
  CUTS_Port_Summary_Base (void);

  /**
   * Copy constructor.
   *
   * @param[in]     copy        Source object.
   */
  CUTS_Port_Summary_Base (const CUTS_Port_Summary_Base & copy);

  /// Destructor.
  virtual ~CUTS_Port_Summary_Base (void);

  /**
   * Process the record.
   *
   * @param[in]       record        The source activation record.
   * @retval          0             Successfully process record.
   * @retval          -1            Failed to process record.
   */
  virtual int process (const CUTS_Activation_Record & record);

  /// Reset the summary.
  virtual void reset (void);

  /**
   * Get the queuing time for the port.
   *
   * @return          The queuing time measurements.
   */
  const CUTS_Time_Measurement & queuing_time (void) const;

  /**
   * Get the service time for the port.
   *
   * @return          The queuing time measurements.
   */
  const CUTS_Time_Measurement & service_time (void) const;

  /**
   * Get the endpoint data for the port.
   *
   * @retunr          The endpoint data.
   */
  const CUTS_Endpoint_Log_Summary & endpoints (void) const;

  /// Accept the visitor.
  virtual void accept (CUTS_Metrics_Visitor & visitor) const;

  /**
   * Assignment operator.
   *
   * @param[in]     rhs     Right-hand side of operator.
   * @return        Reference to self.
   */
  const CUTS_Port_Summary_Base & operator = (const CUTS_Port_Summary_Base & rhs);

  /**
   * Addition assignment operator.
   *
   * @param[in]     rhs     Right-hand side of operator.
   * @return        Reference to self.
   */
  const CUTS_Port_Summary_Base & operator += (const CUTS_Port_Summary_Base & rhs);

protected:
  /// The queuing time of the port.
  CUTS_Time_Measurement queuing_time_;

  /// The service time of the port.
  CUTS_Time_Measurement service_time_;

  /// Map of endpoints by id in chronologicial order.
  CUTS_Endpoint_Log_Summary endpoints_;
};

/// Type definition of map that stores CUTS_Port_Summary_Base objects by sender.
typedef ACE_Hash_Map_Manager <
  int, CUTS_Port_Summary_Base *, ACE_RW_Thread_Mutex>
  CUTS_Sender_Port_Summary;

//=============================================================================
/**
 * @class CUTS_Port_Summary
 */
//=============================================================================

class CUTS_Export CUTS_Port_Summary : public CUTS_Port_Summary_Base
{
public:
  /// Default constructor.
  CUTS_Port_Summary (void);

  /// Destructor.
  virtual ~CUTS_Port_Summary (void);

  /**
   * Process a log of activation records. This will accumulate the
   * records in the log with the current summary.
   *
   * @param[in]       log         The log of activation record.
   * @retval          0           Successfully process the log.
   * @retval          -1          Failed to process the log.
   */
  int process (const CUTS_Activation_Record_Log & log);

  /**
   * Process an activation record. This will accumulate the
   * record with the current summary of the port.
   *
   * @param[in]       record      The activation record.
   * @retval          0           Successfully process the record.
   * @retval          -1          Failed to process the record.
   */
  virtual int process (const CUTS_Activation_Record & record);

  /// Reset the summary.
  virtual void reset (void);

  /// Accept the visitor.
  virtual void accept (CUTS_Metrics_Visitor & visitor) const;

  /**
   * Get the port summary for each of the senders.
   *
   * @return          Summary of the senders.
   */
  const CUTS_Sender_Port_Summary & senders (void) const;

private:
  /// The sender for summary for the port.
  CUTS_Sender_Port_Summary ssp_;

  // prevent the following operations
  CUTS_Port_Summary (const CUTS_Port_Summary &);
  const CUTS_Port_Summary & operator = (const CUTS_Port_Summary &);
};

#if defined (__CUTS_INLINE__)
#include "cuts/Port_Summary.inl"
#endif

#endif  // !defined _CUTS_PORT_SUMMARY_H_
