// $Id$

#include "cuts/performance_i.h"

#if !defined (__CUTS_INLINE__)
#include "cuts/performance_i.inl"
#endif

#include "cuts/Port_Agent.h"
#include "cuts/Port_Metric.h"
#include "tao/corba.h"
#include "ace/Guard_T.h"

///////////////////////////////////////////////////////////////////////////////
// @@ extraction operators

namespace CUTS
{
  namespace global
  {
    /// Temporary placeholder for the time value.
    static ACE_Time_Value tv_placeholder_;

    /// The current activation record under processing.
    static CUTS_Activation_Record * curr_record_ = 0;
  }
}

//
// operator >>=
//
static inline
void operator >>= (const CUTS::Time_Stamp & ts, ACE_Time_Value & tm)
{
  tm.set (ts.sec, ts.usec);
}

//
// operator >>=
//
void operator >>= (const CUTS::Action_Time & time,
                   CUTS_Activation_Record_Entry & entry)
{
  entry.uid_ = time.unique_id;
  entry.type_ = time.type;

  time.duration >>= entry.duration_;
}

//
// operator >>=
//
template <typename S, typename T, typename LOCK>
static void operator >>= (const S & sequence, CUTS_Log_T <T, LOCK> & log)
{
  // Get the size of the sequence.
  CORBA::ULong curr_size = sequence.length ();

  // Get a pointer to the buffer w/ the activation records.
  typename S::const_value_type * buf = sequence.get_buffer ();
  typename S::const_value_type * buf_stop = buf + curr_size;

  // Since we are having problems w/ using the lock_type directly in
  // the macro, we are going to explicitly declare it. Then, we are
  // going to get a write lock to the log for batch processing.
  typedef typename CUTS_Log_T <T, LOCK>::lock_type lock_type;
  ACE_WRITE_GUARD (typename lock_type, guard, log.lock ());

  // Set the size of the log and reset its state.
  log.reset ();
  log.size (curr_size);

  // Update the size of the log. This will prevent us from having to
  // rely on next_free_record () to increase the log size. In some
  // cases that would be feasible, but it would cause to many
  // lock/unlock request. This is more like a batch operation job.

  typename CUTS_Log_T <T, LOCK>::pointer ptr = 0;

  for (; buf != buf_stop; buf ++)
  {
    ptr = log.next_free_record_no_lock ();

    if (ptr != 0)
      *buf >>= *ptr;
  }
}

//
// operator >>=
//
void operator >>= (const CUTS::Action_Times & times,
                   CUTS_Activation_Record_Entry_Log & entries)
{
  // Get the current size of the buffer and resize the log.
  CORBA::ULong curr_size = times.length ();
  entries.size (curr_size);

  // Get a pointer/iterator to the buffer/log.
  CUTS::Action_Times::const_value_type * buf = times.get_buffer ();
  CUTS::Action_Times::const_value_type * buf_stop = buf + curr_size;

  for (; buf != buf_stop; buf ++)
    *buf >>= *entries.next_free_record ();
}

//
// operator >>=
//
static
void operator >>= (const CUTS::Endpoint_Time & ep_time,
                   CUTS_Activation_Record_Endpoint & endpoint)
{
  // Get the time value for the endpoint.
  ACE_Time_Value tv;
  ep_time.exittime >>= tv;

  // Calculate how long it took to reach this endpoint.
  tv -= CUTS::global::curr_record_->start_time ();

  // Set the endpoints properties.
  endpoint.set (ep_time.unique_id, tv, ep_time.datasize);
}

//
// operator >>=
//
static void
operator >>= (const CUTS::Metric_Record & mr, CUTS_Activation_Record & ar)
{
  // Extract the owner of the <mr>.
  ar.owner (mr.sender);

  // Extract the open/close time for the record.
  mr.open_time  >>= ar.start_time ();
  mr.close_time >>= ar.stop_time ();

  // Extract the queueing and endpoint times from the record.
  ACE_Time_Value tv_temp;
  mr.queue_time >>= tv_temp;
  ar.queue_time (tv_temp);

  // Save the current record for future usage.
  CUTS::global::curr_record_ = &ar;

  // Extract the endpoints and entries from the metrics.
  mr.ep_times >>= ar.endpoints ();
  mr.action_log >>= ar.entries ();
}

//
// operator >>=
//
static
void operator >>= (const CUTS::Port_Metric & pm, CUTS_Port_Metric & port)
{
  // Update the time for the port metric.
  port.timestamp (CUTS::global::tv_placeholder_);

  // Extract the activation record log.
  CUTS_Activation_Record_Log & log = port.log ();
  pm.record_log >>= log;

  // Get a reference to the log and lock it for reading.
  ACE_READ_GUARD (CUTS_Activation_Record_Log::lock_type,
                  guard,
                  log.lock ());

  // Summarize the extracted activation record log.
  port.summary ().reset ();
  port.summary ().process (log);
}

//
// operator >>=
//
void operator >>= (const CUTS::Component_Metric & src,
                   CUTS_Component_Metric & dst)
{
  // Save the collection time for this component.
  CUTS::global::tv_placeholder_ = dst.timestamp ();

  // Get an pointer to the front and back of source buffer.
  CORBA::ULong curr_size = src.ports.length ();
  CUTS::Port_Metrics::const_value_type * iter = src.ports.get_buffer ();
  CUTS::Port_Metrics::const_value_type * iter_stop = iter + curr_size;

  // Get the collection time for the metric. This will be need to all
  // the port agents.

  CUTS_Port_Metric * port_metric = 0;

  while (iter < iter_stop)
  {
    // Try to locate the port metrics for <unique_id>. If we can't find
    // it then we need to create a new one.
    if (dst.port_metrics ().find (iter->unique_id, port_metric) == -1)
    {
      ACE_NEW_THROW_EX (port_metric,
                        CUTS_Port_Metric,
                        ACE_bad_alloc ());

      // Insert it into the mapping for next time.
      dst.port_metrics ().bind (iter->unique_id, port_metric);
    }

    // Update the collection time for the component.
    port_metric->timestamp (CUTS::global::tv_placeholder_);

    // Extract the metrics for the port.
    *iter ++ >>= *port_metric;
  }
}

///////////////////////////////////////////////////////////////////////////////
// @@ insertion operators

//
// operator <<=
//
inline
void operator <<= (CUTS::Time_Stamp & ts, const ACE_Time_Value & tv)
{
  ts.sec = tv.sec ();
  ts.usec = tv.usec ();
}

//
// operator <<=
//
static
void operator <<= (CUTS::Action_Time & act,
                   const CUTS_Activation_Record_Entry & entry)
{
  act.unique_id = entry.uid_;
  act.type = entry.type_;
  act.duration <<= entry.duration_;
}

//
// operetor <<=
//
static
void operator <<= (CUTS::Action_Times & times,
                   const CUTS_Activation_Record_Entry_Log & entries)
{
  // Get the current size of the log and resize the sequence.
  size_t curr_size = entries.used_size ();
  times.length (curr_size);

  // Get iterators to the source and destination buffer.
  CUTS::Action_Times::value_type * buf = times.get_buffer ();
  CUTS_Activation_Record_Entry_Log::const_iterator iter = entries.begin ();
  CUTS_Activation_Record_Entry_Log::const_iterator iter_stop = iter + curr_size;

  for (; iter != iter_stop; iter ++)
    *buf ++ <<= *iter;
}

//
// operator <<=
//
static
void operator <<= (CUTS::Endpoint_Times & ep_times,
                   const CUTS_Activation_Record_Endpoints & endpoints)
{
  // Set the correct size of the target buffer.
  CORBA::ULong curr_size = endpoints.used_size ();
  ep_times.length (curr_size);

  // Get an iterator to the endpoint times and a pointer to the
  // buffer that will store the endpoint times.
  CUTS_Activation_Record_Endpoints::const_iterator iter = endpoints.begin ();
  CUTS::Endpoint_Times::value_type * buf = ep_times.get_buffer ();

  for (CORBA::ULong i = 0; i < curr_size; i ++)
  {
    // Store the information in the buffer. This is the unique
    // id of the endpoint and the time it was encountered.
    buf->unique_id = iter->id ();
    buf->datasize  = iter->data_size ();
    buf->exittime <<= iter->time_of_completion ();

    // Move the next location in the map and the next slot
    // in the target buffer.
    iter ++;
    buf ++;
  }
}

//
// operator <<=
//
static
void operator <<= (CUTS::Metric_Record & dest,
                   const CUTS_Activation_Record & src)
{
  // Insert the owner of the record (i.e., event that caused the
  // creation of this record).
  dest.sender = src.owner ();

  // Insert the open/close time for the record.
  dest.open_time  <<= src.start_time ();
  dest.close_time <<= src.stop_time ();

  // Insert the queueing and endpoint times into the record.
  dest.queue_time <<= src.queue_time ();
  dest.ep_times   <<= src.endpoints ();
  dest.action_log <<= src.entries ();
}

//
// operator <<=
//
static
void operator <<= (CUTS::Metric_Records & mlog,
                   const CUTS_Activation_Record_Log & log)
{
  CORBA::ULong actual_size = 0;
  CORBA::ULong curr_size;

  do
  {
    ACE_READ_GUARD (CUTS_Activation_Record_Log::lock_type,
                    guard,
                    const_cast <CUTS_Activation_Record_Log &> (log).lock ());

    // Set the size of the <mlog> sequence.
    curr_size = log.used_size ();
    mlog.length (curr_size);

    // Get a iterator to the logs and a pointer to the head
    // of the target buffer.
    CUTS_Activation_Record_Log::const_iterator iter = log.begin ();
    CUTS::Metric_Records::value_type * buf = mlog.get_buffer ();

    // Get a read lock to the log. This will allow use to do a batch
    // processing operation and prevent other threads from trying to
    // increase the size of the record log.
    for (CORBA::ULong i = 0; i < curr_size; i ++)
    {
      // Only copy records that are not open (i.e., have be used). Since we
      // are only looking at used records, we do not have to worry about a
      // record in the middle of the pack being unused.
      if (!iter->is_open ())
      {
        // Store the record in the buffer.
        *buf ++ <<= *iter ++;

        // Keep track of the actual size.
        ++ actual_size;
      }
    }
  } while (0);

  // Make sure the size of the buffer reflects the number of
  // used records that we copied.
  if (actual_size != curr_size)
    mlog.length (actual_size);
}

//
// operator <<=
//
inline
void operator <<= (CUTS::Port_Metric & pm, const CUTS_Port_Agent & agent)
{
  pm.record_log <<= agent.log ();
}

//
// operator <<=
//
static void
operator <<= (CUTS::Port_Metrics & ports, const CUTS_Port_Agent_Set & agents)
{
  // Get the number of agents and update the size of the
  // port metrics.
  CORBA::ULong size = agents.current_size ();
  ports.length (size);


  // Get a pointer to both the source and destination buffer.
  CUTS::Port_Metrics::value_type * buf = ports.get_buffer ();
  CUTS_Port_Agent_Set::CONST_ITERATOR iter (agents);
  CORBA::ULong actual_size = 0;

  // Copy all the elements from the set to the sequence.
  for (; !iter.done (); iter.advance ())
  {
    CUTS_Port_Agent * agent = iter->key ();

    if (agent != 0)
    {
      buf->unique_id = iter->item ();

      // Insert the port agent and reset it.
      *buf ++ <<= *agent;
      agent->reset ();

      // Increment the actual size of the sequence.
      ++ actual_size;
    }
  }

  // Make sure the sequence is of the correct size.
  if (size != actual_size)
    ports.length (actual_size);
}

//
// operator <<=
//
void operator <<= (CUTS::Component_Metric & cm,
                   const CUTS_Benchmark_Agent & agent)
{
  // Set the parent id and the collection time.
  cm.unique_id = agent.parent ();
  cm.collection_time <<= ACE_OS::gettimeofday ();

  // Insert all the port metrics.
  cm.ports <<= agent.port_agents ();
}
