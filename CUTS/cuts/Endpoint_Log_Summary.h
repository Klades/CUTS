/* -*- C++ -*- */

//=============================================================================
/**
 * @file          Endpoint_Log_Summary.h
 *
 * Summary classes for the endpoint data.
 *
 * $Id$
 *
 * @author        James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_ENDPOINT_LOG_SUMMARY_H_
#define _CUTS_ENDPOINT_LOG_SUMMARY_H_

#include "cuts/Activation_Record.h"
#include "cuts/Statistics_T.h"

typedef CUTS_Log_T <
  CUTS_Statistics_T <CUTS_Endpoint_Data>, ACE_Null_Mutex>
  CUTS_Endpoint_Data_Log;

typedef ACE_Hash_Map_Manager <
  int, CUTS_Endpoint_Data_Log *, ACE_Null_Mutex>
  CUTS_Endpoint_Data_Logs;

// Forward decl.
class CUTS_Metrics_Visitor;

//=============================================================================
/**
 * @class CUTS_Endpoint_Log_Summary
 *
 * INSERT CLASS DESCRIPTION HERE
 */
//=============================================================================

class CUTS_Export CUTS_Endpoint_Log_Summary
{
public:
  /// Default constructor.
  CUTS_Endpoint_Log_Summary (void);

  /// Destructor.
  ~CUTS_Endpoint_Log_Summary (void);

  /**
   * Process the endpoints from the activation record.
   *
   * @param[in]       endpoints     Endpoints from the activation record.
   */
  int process (const CUTS_Activation_Record_Endpoints & endpoints);

  /// Reset the endpoint summary.
  void reset (void);

  /**
   * Get the endpoint data logs. The logs are stored by endpoint
   * id and in chronological order. There is no correlation between
   * the order of occurence for different endpoint ids. If you want
   * the chronological order of endpoints across all the endpoints,
   * then you have to compute it yourself.
   *
   * @return      Summary logs for all endpoints.
   */
  const CUTS_Endpoint_Data_Logs & logs (void) const;

  /// Accept the visitor object.
  void accept (CUTS_Metrics_Visitor & visitor) const;

private:
  /// Prepare the summary for the endpoints.
  int prepare (const CUTS_Activation_Record_Endpoints & endpoints);

  /// The logs of the endpoint data.
  CUTS_Endpoint_Data_Logs logs_;

  /// Type defintion for the indexer of the logs.
  typedef ACE_Hash_Map_Manager <
    int, CUTS_Endpoint_Data_Log::iterator, ACE_Null_Mutex>
    CUTS_Endpoint_Data_Log_Iterators;

  /// The current offset into the log for the next record.
  CUTS_Endpoint_Data_Log_Iterators iters_;
};

#if defined (__CUTS_INLINE__)
#include "Endpoint_Log_Summary.inl"
#endif  /* defined __CUTS_INLINE__ */

#endif  /* !defined _CUTS_ENDPOINT_LOG_SUMMARY_H_ */
