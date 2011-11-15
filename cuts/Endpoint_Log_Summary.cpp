// $Id$

#include "Endpoint_Log_Summary.h"

#if !defined (__CUTS_INLINE__)
#include "Endpoint_Log_Summary.inl"
#endif  /* defined __CUTS_INLINE__ */

#include "Metrics_Visitor.h"
#include "ace/Auto_Ptr.h"
#include "ace/Trace.h"

//
// clean_reset
//
void CUTS_Endpoint_Log_Summary::clean_reset (void)
{
  CUTS_Endpoint_Data_Logs::ITERATOR log_iter (this->logs_);

  for ( ; !log_iter.done (); log_iter ++)
    delete log_iter->item ();

  this->logs_.unbind_all ();
}

//
// reset
//
void CUTS_Endpoint_Log_Summary::reset (void)
{
  // Reset all the endpoint data logs.
  CUTS_Endpoint_Data_Logs::ITERATOR log_iter (this->logs_);
  CUTS_Endpoint_Data_Logs::data_type log;

  for (; !log_iter.done (); log_iter ++)
  {
    log = log_iter->item ();

    if (log != 0)
    {
      // Reset all the elements of the log.
      CUTS_Endpoint_Data_Log::iterator log_iter (*log);

      for (; !log_iter.done (); log_iter.advance ())
        log_iter->reset ();

      // Reset the log's state.
      log->reset ();
    }
  }
}

//
// process
//
int CUTS_Endpoint_Log_Summary::
process (const CUTS_Activation_Record_Endpoints & endpoints)
{
  if (this->prepare (endpoints) == -1)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error (CUTS_Endpoint_Log_Summary): failed to "
                       "prepare for processing endpoints\n"),
                       -1);
  }

  // Initialize the iterators for the endpoints.
  CUTS_Activation_Record_Endpoints::const_iterator iter (endpoints);

  CUTS_Endpoint_Data_Log * endpoint_log = 0;
  CUTS_Endpoint_Data_Log::pointer data = 0;

  for ( ; !iter.done (); iter.advance ())
  {
    // Locate the endpoint log for this endpoint.
    if (this->logs_.find (iter->id (), endpoint_log) == 0)
    {
      data = endpoint_log->next_free_record ();

      if (data != 0)
        *data += *iter;
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M endpoint log does not exist for %d",
                  iter->id ()));
    }
  }

  return 0;
}

//
// prepare
//
int CUTS_Endpoint_Log_Summary::
prepare (const CUTS_Activation_Record_Endpoints & endpoints)
{
  CUTS_Activation_Record_Endpoints::
    const_iterator endpoints_iter (endpoints);

  CUTS_Endpoint_Data_Log * endpoint_log = 0;

  while (!endpoints_iter.done ())
  {
    if (this->logs_.find (endpoints_iter->id (), endpoint_log) == -1)
    {
      // We are making the assumption there is only 1 endpoint
      // per log. This will eventually change. We are going to
      // also allow auto grown of the log, just in case we have
      // more endpoints than we expected :)
      ACE_NEW_RETURN (endpoint_log,
                      CUTS_Endpoint_Data_Log (10),
                      -1);

      ACE_Auto_Ptr <CUTS_Endpoint_Data_Log> auto_clean (endpoint_log);

      // Save the endpoint log for future usage.
      if (this->logs_.bind (endpoints_iter->id (), endpoint_log) == 0)
        auto_clean.release ();
      else
        endpoint_log = 0;
    }

    // Reset the log regardless. This will make sure we insert endpoints
    // at the beginning of the log.
    if (endpoint_log != 0)
      endpoint_log->reset ();

    // Move to the next endpoint.
    endpoints_iter.advance ();
  }

  return 0;
}

////
//// operator +=
////
//const CUTS_Endpoint_Log_Summary &
//CUTS_Endpoint_Log_Summary::operator += (const CUTS_Endpoint_Log_Summary & rhs)
//{
//  CUTS_Endpoint_Data_Logs::CONST_ITERATOR iter (rhs.logs_);
//  CUTS_Endpoint_Data_Logs::data_type log = 0, srclog = 0;
//  CUTS_Endpoint_Data_Logs::key_type logid;
//
//  for (; !iter.done (); iter.advance ())
//  {
//    srclog = iter->item ();
//
//    if (srclog != 0)
//    {
//      logid = iter->key ();
//
//      // Locate a matching log in myself.
//      if (this->logs_.find (logid, log) == -1)
//      {
//        ACE_NEW_RETURN (log, CUTS_Endpoint_Data_Log (*srclog), *this);
//        ACE_Auto_Ptr <CUTS_Endpoint_Data_Log> auto_clean (log);
//
//        if (this->logs_.bind (logid, log) == 0)
//          auto_clean.release ();
//      }
//      else
//      {
//        // Get iterators to the endpoints of the source log.
//        CUTS_Endpoint_Data_Log::const_iterator
//          srclog_iter = srclog->begin (),
//          srclog_iter_end = srclog->used_end ();
//
//        // Initialize the sequence iterator for the log.
//        CUTS_Endpoint_Data_Log::pointer data = 0;
//        CUTS_Endpoint_Data_Log::iterator index_iter = log->begin ();
//
//        // Save the current indexer.
//        this->iters_.rebind (logid, index_iter);
//
//        for ( ; srclog_iter != srclog_iter_end; srclog_iter ++)
//        {
//          if (index_iter != log->used_end ())
//            data = index_iter;
//          else
//            data = log->next_free_record ();
//
//          // Sum the current value with the data.
//          if (data != 0)
//            *data += *srclog_iter;
//
//          // Regardless, we still need to move the index iterator
//          // to the next position.
//          this->iters_.rebind (logid, ++ index_iter);
//        }
//      }
//    }
//  }
//  return *this;
//}
//
//
// accept
//
void CUTS_Endpoint_Log_Summary::
accept (CUTS_Metrics_Visitor & visitor) const
{
  visitor.visit_endpoint_log_summary (*this);
}
