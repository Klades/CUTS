// -*- C++ -*-

//=============================================================================
/**
 * @file        Baseline_Archiver_DB.h
 *
 * Database archiver for the baseline metrics.
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BASELINE_ARCHIVER_DB_H_
#define _CUTS_BASELINE_ARCHIVER_DB_H_

#include "cuts/Metrics_Visitor.h"
#include "cuts/Auto_Functor_T.h"
#include "ace/Basic_Types.h"

// Forward decl.
class CUTS_Component_Registry;

// Forward decl.
struct CUTS_Component_Info;

// Forward decl.
class CUTS_DB_Connection;

// Forward decl.
class CUTS_DB_Query;

//=============================================================================
/**
 * @class CUTS_Baseline_Archiver_DB
 */
//=============================================================================

class CUTS_Baseline_Archiver_DB : public CUTS_Metrics_Visitor
{
public:
  /**
   * Initializing constructor. The \a conn passed into the consturctor
   * must be open. If the connection is not open, then the baseline
   * metrics will not be logged to the database.
   *
   * @param[in]     registry      Registry of known components.
   * @param[in]     conn          The target connection.
   * @param[in]     is_default    Metrics are the default baseline.
   */
  CUTS_Baseline_Archiver_DB (const CUTS_Component_Registry & registry);

  /// Destructor.
  virtual ~CUTS_Baseline_Archiver_DB (void);

  /**
   * Execute the database archiver.
   *
   * @param[in]     metrics       Target system metrics.
   * @param[in]     conn          The target connection.
   * @param[in]     is_default    Metrics are the default baseline.
   */
  bool execute (const CUTS_System_Metric & sm,
                CUTS_DB_Connection & conn,
                bool is_default = false);

protected:
  void visit_system_metric (const CUTS_System_Metric & system);

  void visit_component_metric (const CUTS_Component_Metric & component);

  void visit_port_metric (const CUTS_Port_Metric & port);

  void visit_port_summary (const CUTS_Port_Summary & summary);

  void visit_endpoint_log_summary (const CUTS_Endpoint_Log_Summary & summary);

  void visit_time_measurement (const CUTS_Time_Measurement & tm);

private:
  /// Registration information for all the components.
  const CUTS_Component_Registry & registry_;

  /// The metrics are the default.
  bool is_default_;

  /// The information about the component.
  const CUTS_Component_Info * info_;

  /// The query for inserting metrics.
  CUTS_Auto_Functor_T <CUTS_DB_Query> perf_query_;

  CUTS_Auto_Functor_T <CUTS_DB_Query> perf_endpoint_query_;

  /// Name of the instance being archived.
  char instance_[256];

  /// The input port for the baseline metric.
  char inport_[256];

  /// The output port for the baseline metric.
  char outport_[256];

  /// Name of the instance being archived.
  char perf_type_[10];

  /// Hostname for the baseline metric.
  char hostname_[256];

  /// The event count for the baseline metrics.
  ACE_INT32 perf_count_;

  /// The event count for the baseline metrics.
  ACE_INT32 outport_index_;

  /// The best execution time for the baseline.
  ACE_INT32 best_time_;

  /// The worst execution time for the baseline.
  ACE_INT32 worst_time_;

  /// The total time for the execution time.
  ACE_INT32 total_time_;
};
#endif  // !defined _CUTS_BASELINE_ARCHIVER_H_
