// -*- C++ -*-

//=============================================================================
/**
 * @file    Time_Measurement.h
 *
 * Mechanisms for observing and collecting statistics on time values.
 *
 * $Id$
 *
 * @author  James H. Hill <hillj@isis.vanderbilt.edu>
 */
//=============================================================================

#ifndef _CUTS_TIME_MEASUREMENT_H_
#define _CUTS_TIME_MEASUREMENT_H_

#include "cuts/Timestamp_Metric.h"
#include "cuts/Statistics_T.h"

// Forward decl.
class CUTS_Metrics_Visitor;

//=============================================================================
/**
 * @ingroup benchmarking
 * @class CUTS_Time_Measurement
 *
 * Timing operations using collecting timing information. This class
 * contains operations that assist with collecting timing measurements such
 * as the maximum and minimum timing values. Also, this class will accumulate
 * timing values and keep track of the number of timing samples.
 *
 * @todo Create an init () method that allows the time values to be
 *       initialized in a single call, instead of in a piecemeal fashion.
 */
//=============================================================================

class CUTS_Export CUTS_Time_Measurement :
  public CUTS_Statistics_T <ACE_Time_Value>,
  public CUTS_Timestamp_Metric
{
public:
  /// Constructor.
  CUTS_Time_Measurement (void);

  /// Destructor.
  ~CUTS_Time_Measurement (void);

  /**
   * Accept the visitor object.
   *
   * @param[in]     visitor       The target visitor object.
   */
   void accept (CUTS_Metrics_Visitor & visitor) const;
};

CUTS_Export
ACE_Time_Value operator / (const ACE_Time_Value & tv, double factor);

#if defined (__CUTS_INLINE__)
#include "cuts/Time_Measurement.inl"
#endif

#endif  // !defined _CUTS_TIME_MEASUREMENT_H_
