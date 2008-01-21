#ifndef _CUTS_PORT_METRIC_H_
#define _CUTS_PORT_METRIC_H_

#include "cuts/Activation_Record_Log.h"
#include "cuts/Port_Measurement_Map.h"
#include "cuts/Timestamp_Metric.h"
#include "cuts/Port_Summary.h"

class CUTS_Metrics_Visitor;

//=============================================================================
/**
 * @class CUTS_Port_Metric
 *
 * Performance metrics for a port in a component. The metrics are
 * stored in a map by the component that sent the input event. If
 * metrics are not stored by sender, then all under the CUTS_UKNOWN_IMPL
 * id.
 */
//=============================================================================

class CUTS_Export CUTS_Port_Metric : public CUTS_Timestamp_Metric
{
public:
  /// Constructor.
  CUTS_Port_Metric (void);

  /// Destructor.
  ~CUTS_Port_Metric (void);

  /**
   * Get the log of performance data for the component.
   *
   * @return        Reference to the performance log.
   */
  CUTS_Activation_Record_Log & log (void);

  /**
   * @overload
   */
  const CUTS_Activation_Record_Log & log (void) const;

  /**
   * Get the summary of the port metrics.
   *
   * @return        Summary of the port metrics.
   */
  CUTS_Port_Summary & summary (void);

  /**
   * @overload
   */
  const CUTS_Port_Summary & summary (void) const;

  /**
   * Accept the system metric visitor.
   *
   * @param[in]       visitor       Target visitor object.
   */
  void accept (CUTS_Metrics_Visitor & visitor) const;

private:
  /// Latest time metric was updated.
  ACE_Time_Value timestamp_;

  /// Log of all the records collected on this port.
  CUTS_Activation_Record_Log log_;

  /// Summary of the port metrics.
  CUTS_Port_Summary summary_;

  // prevent the following operations
  CUTS_Port_Metric (const CUTS_Port_Metric &);
  const CUTS_Port_Metric & operator = (const CUTS_Port_Metric &);
};

#if defined (__CUTS_INLINE__)
#include "cuts/Port_Metric.inl"
#endif

#endif  // !defined _CUTS_PORT_METRIC_H_
