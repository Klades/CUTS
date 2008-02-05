// $Id$

#include "Baseline_Archiver_DB.h"
#include "cuts/Component_Registry.h"
#include "cuts/Component_Info.h"
#include "cuts/Component_Type.h"
#include "cuts/Host_Table_Entry.h"
#include "cuts/System_Metric.h"
#include "cuts/Component_Metric.h"
#include "cuts/Port_Metric.h"
#include "cuts/utils/DB_Connection.h"
#include "cuts/utils/DB_Query.h"
#include "cuts/utils/DB_Parameter.h"
#include "cuts/utils/DB_Exception.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_string.h"

//
// CUTS_Baseline_Archiver_DB
//
CUTS_Baseline_Archiver_DB::
CUTS_Baseline_Archiver_DB (const CUTS_Component_Registry & registry)
: registry_ (registry),
  info_ (0),
  perf_query_ (0, &CUTS_DB_Query::destroy),
  perf_endpoint_query_ (0, &CUTS_DB_Query::destroy)
{

}

//
// ~CUTS_Baseline_Archiver_DB
//
CUTS_Baseline_Archiver_DB::~CUTS_Baseline_Archiver_DB (void)
{

}

//
// init
//
bool
CUTS_Baseline_Archiver_DB::
execute (const CUTS_System_Metric & metrics,
         CUTS_DB_Connection & conn,
         bool is_default)
{
  if (!conn.is_connected ())
    ACE_ERROR_RETURN ((LM_ERROR,
                      "*** error [baseline]: not connected to database\n"),
                      false);

  try
  {
    this->is_default_ = is_default;

    // Create a query that will be used to insert the metrics
    // into the database.
    this->perf_query_.reset (conn.create_query ());
    this->perf_endpoint_query_.reset (conn.create_query ());

    if (this->perf_query_.get () == 0)
      return false;

    if (!this->is_default_)
    {
      const char * perf_stmt =
        "CALL cuts."
        "insert_component_instance_baseline_by_hostname (?,?,?,?,?,?,?,?)";

      // Prepare the insertion SQL statement.
      this->perf_query_->prepare (perf_stmt);
      this->perf_query_->parameter (0)->bind (this->hostname_, 0);
      this->perf_query_->parameter (1)->bind (this->instance_, 0);
      this->perf_query_->parameter (2)->bind (this->inport_, 0);
      this->perf_query_->parameter (3)->bind (this->perf_type_, 0);
      this->perf_query_->parameter (4)->bind (&this->perf_count_);
      this->perf_query_->parameter (5)->bind (&this->best_time_);
      this->perf_query_->parameter (6)->bind (&this->worst_time_);
      this->perf_query_->parameter (7)->bind (&this->total_time_);

      const char * perf_endpoint_stmt =
        "CALL cuts."
        "insert_component_instance_endpoint_baseline_by_hostname (?,?,?,?,?,?,?,?,?)";

      // Prepare the SQL statement.
      this->perf_endpoint_query_->prepare (perf_endpoint_stmt);
      this->perf_endpoint_query_->parameter (0)->bind (this->hostname_, 0);
      this->perf_endpoint_query_->parameter (1)->bind (this->instance_, 0);
      this->perf_endpoint_query_->parameter (2)->bind (this->inport_, 0);
      this->perf_endpoint_query_->parameter (3)->bind (&this->outport_index_);
      this->perf_endpoint_query_->parameter (4)->bind (this->outport_, 0);
      this->perf_endpoint_query_->parameter (5)->bind (&this->perf_count_);
      this->perf_endpoint_query_->parameter (6)->bind (&this->best_time_);
      this->perf_endpoint_query_->parameter (7)->bind (&this->worst_time_);
      this->perf_endpoint_query_->parameter (8)->bind (&this->total_time_);
    }
    else
    {
      const char * perf_stmt =
        "CALL cuts."
        "insert_component_instance_baseline_default (?,?,?,?,?,?,?)";

      // Prepare the insertion SQL statement.
      this->perf_query_->prepare (perf_stmt);

      // Setup the parameters for the query.
      this->perf_query_->parameter (0)->bind (this->instance_, 0);
      this->perf_query_->parameter (1)->bind (this->inport_, 0);
      this->perf_query_->parameter (2)->bind (this->perf_type_, 0);
      this->perf_query_->parameter (3)->bind (&this->perf_count_);
      this->perf_query_->parameter (4)->bind (&this->best_time_);
      this->perf_query_->parameter (5)->bind (&this->worst_time_);
      this->perf_query_->parameter (6)->bind (&this->total_time_);

      const char * perf_endpoint_stmt =
        "CALL cuts."
        "insert_component_instance_endpoint_baseline_default (?,?,?,?,?,?,?,?)";
      this->perf_endpoint_query_->prepare (perf_endpoint_stmt);
      this->perf_endpoint_query_->parameter (0)->bind (this->instance_, 0);
      this->perf_endpoint_query_->parameter (1)->bind (this->inport_, 0);
      this->perf_endpoint_query_->parameter (2)->bind (&this->outport_index_);
      this->perf_endpoint_query_->parameter (3)->bind (this->outport_, 0);
      this->perf_endpoint_query_->parameter (4)->bind (&this->perf_count_);
      this->perf_endpoint_query_->parameter (5)->bind (&this->best_time_);
      this->perf_endpoint_query_->parameter (6)->bind (&this->worst_time_);
      this->perf_endpoint_query_->parameter (7)->bind (&this->total_time_);
    }

    // Visit the system metrics.
    metrics.accept (*this);

    // Reset the query since it's not need anymore.
    this->perf_query_.reset ();
    return true;
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [baseline]: %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [baseline]: caught unknown exception (%l)\n"));
  }

  // Reset the query since we do not own the connection. We, therefore,
  // do not know when the query will become invalid.
  if (this->perf_query_.get () != 0)
    this->perf_query_.reset ();

  return false;
}

//
// visit_system_metric
//
void CUTS_Baseline_Archiver_DB::
visit_system_metric (const CUTS_System_Metric & sm)
{
  CUTS_Component_Metric_Map::CONST_ITERATOR iter (sm.component_metrics ());

  for (; !iter.done (); iter.advance ())
  {
    // Locate the component's registration info.
    if (this->registry_.get_component_info (iter->key (), &this->info_) == 0)
    {
      if (this->info_ != 0)
      {
        // Copy name of component into query buffer.
        ACE_OS::strncpy (this->instance_,
                         this->info_->inst_.c_str (),
                         sizeof (this->instance_));

        // Set the hostname if not default baseline metric.
        if (!this->is_default_)
        {
          if (this->info_->host_info_ != 0)
          {
            ACE_OS::strncpy (this->hostname_,
                             this->info_->host_info_->hostname_.c_str (),
                             sizeof (this->hostname_));
          }
          else
          {
            ACE_ERROR ((LM_ERROR,
                        "*** error (baseline): `%d' does not have host "
                        "information in its registration\n",
                        iter->key ()));

            // Force moving to the next component.
            continue;
          }
        }

        // Visit the current port metrics.
        if (iter->item ())
          iter->item ()->accept (*this);
      }
      else
      {
        ACE_ERROR ((LM_WARNING,
                    "*** warning (baseline): key `%d' does not have "
                    "registration information\n",
                    iter->key ()));
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error (baseline): failed to locate component "
                  "registration for `%d'\n",
                  iter->key ()));
    }
  }
}

//
// visit_component_metric
//
void CUTS_Baseline_Archiver_DB::
visit_component_metric (const CUTS_Component_Metric & cm)
{
  ACE_CString inport;
  CUTS_Port_Metric_Map::CONST_ITERATOR iter (cm.port_metrics ());

  for ( ; !iter.done (); iter.advance ())
  {
    if (this->info_->type_ != 0)
    {
      // Locate the name of this input port.
      if (this->info_->type_->sinks_.find (iter->key (), inport) == 0)
      {
        ACE_OS::strncpy (this->inport_,
                         inport.c_str (),
                         sizeof (this->inport_));

        // Visit the port metric.
        if (iter->item ())
          iter->item ()->accept (*this);
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "*** error (baseline): failed to locate input port name\n"));
      }
    }
  }
}

//
// visit_port_metric
//
void CUTS_Baseline_Archiver_DB::
visit_port_metric (const CUTS_Port_Metric & pm)
{
  pm.summary ().accept (*this);
}

//
// visit_port_measurement
//
void CUTS_Baseline_Archiver_DB::
visit_port_summary (const CUTS_Port_Summary & summary)
{
  // Process the overall queueing time for the port.
  ACE_OS::strncpy (this->perf_type_, "queue", sizeof (this->perf_type_));
  summary.queuing_time ().accept (*this);

  try
  {
    if (this->perf_count_ > 0)
      this->perf_query_->execute_no_record ();
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [baseline]: %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [baseline]: caught unknown exception (%l)\n"));
  }

  // Process the overall service time for the port.
  ACE_OS::strncpy (this->perf_type_, "process", sizeof (this->perf_type_));
  summary.service_time ().accept (*this);

  try
  {
    if (this->perf_count_ > 0)
      this->perf_query_->execute_no_record ();
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [baseline]: %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [baseline]: caught unknown exception (%l)\n"));
  }

  // Visit the endpoint logs of the summary.
  summary.endpoints ().accept (*this);
}

//
// visit_endpoint_log_summary
//
void CUTS_Baseline_Archiver_DB::
visit_endpoint_log_summary (const CUTS_Endpoint_Log_Summary & summary)
{
  ACE_CString outport;

  for (CUTS_Endpoint_Data_Logs::CONST_ITERATOR logs_iter (summary.logs ());
       !logs_iter.done ();
       logs_iter ++)
  {
    // Locate the name of this input port.
    if (this->info_->type_->sources_.find (logs_iter->key (), outport) == 0)
    {
      ACE_OS::strncpy (this->outport_,
                       outport.c_str (),
                       sizeof (this->outport_));

      // Visit the port metric.
      CUTS_Endpoint_Data_Log::const_iterator
        endpoint_iter = logs_iter->item ()->begin (),
        endpoint_iter_end = logs_iter->item ()->used_end ();

      this->outport_index_ = 0;

      for (; endpoint_iter != endpoint_iter_end; endpoint_iter ++)
      {
        this->perf_count_ = endpoint_iter->count ();

        if (this->perf_count_ > 0)
        {
          // Set the values of the parameters.
          this->best_time_  = endpoint_iter->min_value ().time_of_completion ().msec ();
          this->worst_time_ = endpoint_iter->max_value ().time_of_completion ().msec ();
          this->total_time_ = endpoint_iter->summation ().time_of_completion ().msec ();

          // Execute the endpoint query.
          this->perf_endpoint_query_->execute_no_record ();

          // Move to the next index.
          ++ this->outport_index_;
        }
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error (baseline): failed to locate input port name\n"));
    }
  }
}

//
// visit_time_measurement
//
void CUTS_Baseline_Archiver_DB::
visit_time_measurement (const CUTS_Time_Measurement & tm)
{
  // Store the timing metrics in the query buffers.
  this->perf_count_ = tm.count ();
  this->best_time_  = tm.min_value ().msec ();
  this->worst_time_ = tm.max_value ().msec ();
  this->total_time_ = tm.summation ().msec ();
}
