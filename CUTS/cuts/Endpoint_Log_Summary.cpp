// $Id$

#include "Endpoint_Log_Summary.h"

#if !defined (__CUTS_INLINE__)
#include "Endpoint_Log_Summary.inl"
#endif  /* defined __CUTS_INLINE__ */

#include "cuts/Metrics_Visitor.h"

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
      CUTS_Endpoint_Data_Log::iterator
        iter = log->begin (), iter_end = log->end ();

      for ( ; iter != iter_end; iter ++)
        iter->reset ();

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
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error (CUTS_Endpoint_Log_Summary): failed to "
                       "prepare for processing endpoints\n"),
                       -1);

  // Initialize the iterators for the endpoints.
  CUTS_Activation_Record_Endpoints::const_iterator
    iter = endpoints.begin (),
    iter_end = endpoints.used_end ();

  CUTS_Endpoint_Data_Log * endpoint_log = 0;
  CUTS_Endpoint_Data_Log::iterator index_iter;
  CUTS_Endpoint_Data_Log::pointer data = 0;

  for ( ; iter != iter_end; iter ++)
  {
    // Locate the endpoint log for this endpoint.
    if (this->logs_.find (iter->id (), endpoint_log) == 0)
    {
      if (endpoint_log != 0)
      {
        // Find the location in the log for the next entry.
        if (this->iters_.find (iter->id (), index_iter) == 0)
        {
          if (index_iter != endpoint_log->used_end ())
            data = index_iter;
          else
            data = endpoint_log->next_free_record ();

          // Regardless, we still need to move the index iterator
          // to the next position.
          this->iters_.rebind (iter->id (), ++ index_iter);

          // Now that we have the correct data. We need to update it
          // with the latest endpoint data.
          if (data != 0)
            *data += *iter;
        }
        else
        {
          ACE_ERROR ((LM_ERROR,
                      "*** error (CUTS_Endpoint_Log_Summary): `%d' does not "
                      "have an indexer; ignoring endpoint entry\n",
                      iter->id ()));
        }

        // Reset the pointers for the next iteration.
        endpoint_log = 0;
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    "*** error (CUTS_Endpoint_Log_Summary): `%d' recovered "
                    "a NIL log\n",
                    iter->id ()));
      }
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error (CUTS_Endpoint_Log_Summary): endpoint log "
                  "does not exist for `%d'",
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
  CUTS_Activation_Record_Endpoints::const_iterator
    iter = endpoints.begin (),
    iter_end = endpoints.used_end ();

  CUTS_Endpoint_Data_Log * endpoint_log = 0;

  for ( ; iter != iter_end; iter ++)
  {
    if (this->logs_.find (iter->id (), endpoint_log) == -1)
    {
      // We are making the assumption there is only 1 endpoint
      // per log. This will eventually change. We are going to
      // also allow auto grown of the log, just in case we have
      // more endpoints than we expected :)
      ACE_NEW_RETURN (endpoint_log,
                      CUTS_Endpoint_Data_Log (1, true),
                      -1);

      // Save the endpoint log for future usage.
      this->logs_.bind (iter->id (), endpoint_log);
    }

    if (endpoint_log != 0)
    {
      // Reset the log regardless.
      endpoint_log->reset ();

      if (this->iters_.rebind (iter->id (), endpoint_log->begin ()) == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           "*** error (CUTS_Endpoint_Log_Summary): failed "
                           "to initialize iterator for `%d'",
                           iter->id ()),
                           -1);
    }

    // Reset the pointer(s) the next iteration.
    endpoint_log = 0;
  }

  return 0;
}

//
// accept
//
void CUTS_Endpoint_Log_Summary::
accept (CUTS_Metrics_Visitor & visitor) const
{
  visitor.visit_endpoint_log_summary (*this);
}
