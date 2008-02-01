// $Id$

#include "Endpoint_Log_Summary.h"

#if !defined (__CUTS_INLINE__)
#include "Endpoint_Log_Summary.inl"
#endif  /* defined __CUTS_INLINE__ */

#include "cuts/Metrics_Visitor.h"
#include "ace/Auto_Ptr.h"

//
// CUTS_Endpoint_Log_Summary
//
CUTS_Endpoint_Log_Summary::
CUTS_Endpoint_Log_Summary (const CUTS_Endpoint_Log_Summary & copy)
{
  this->copy (copy.logs_);
}

//
// copy
//
void CUTS_Endpoint_Log_Summary::copy (const CUTS_Endpoint_Data_Logs & logs)
{
  if (this->logs_.current_size () > 0)
    this->clean_reset ();

  CUTS_Endpoint_Data_Logs::CONST_ITERATOR iter (logs);
  CUTS_Endpoint_Data_Logs::data_type data = 0;

  for (; !iter.done (); iter ++)
  {
    if (iter->item () != 0)
    {
      // Create a new value for the entry.
      ACE_NEW (data, CUTS_Endpoint_Data_Log ());
      ACE_Auto_Ptr <CUTS_Endpoint_Data_Log> auto_clean (data);

      // Copy the item.
      *data = *iter->item ();

      // Store the item in the table.
      if (this->logs_.bind (iter->key (), data) == 0)
        auto_clean.release ();
    }
  }
}

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
// operator =
//
const CUTS_Endpoint_Log_Summary &
CUTS_Endpoint_Log_Summary::operator = (const CUTS_Endpoint_Log_Summary & rhs)
{
  this->copy (rhs.logs_);
  return *this;
}

//
// operator +=
//
const CUTS_Endpoint_Log_Summary &
CUTS_Endpoint_Log_Summary::operator += (const CUTS_Endpoint_Log_Summary & rhs)
{
  CUTS_Endpoint_Data_Logs::CONST_ITERATOR iter (rhs.logs_);
  CUTS_Endpoint_Data_Logs::data_type log = 0;

  for (; !iter.done (); iter ++)
  {
    // Locate a matching log in myself.
    if (this->logs_.find (iter->key (), log) == -1)
    {
      ACE_NEW_RETURN (log, CUTS_Endpoint_Data_Log (), *this);
      ACE_Auto_Ptr <CUTS_Endpoint_Data_Log> auto_clean (log);

      if (this->logs_.bind (iter->key (), log) == 0)
        auto_clean.release ();
    }

    if (iter->item () != 0)
    {
      // Get iterators to the endpoints of the source log.
      CUTS_Endpoint_Data_Log::const_iterator
        log_iter = iter->item ()->begin (),
        log_iter_end = iter->item ()->used_end ();

      // Initialize the sequence iterator for the log.
      CUTS_Endpoint_Data_Log::pointer data = 0;
      CUTS_Endpoint_Data_Log::iterator index_iter = log->begin ();
      this->iters_.rebind (iter->key (), index_iter);

      for ( ; log_iter != log_iter_end; log_iter ++)
      {
        if (index_iter != log->used_end ())
          data = index_iter;
        else
          data = log->next_free_record ();

        // Sum the current value with the data.
        if (data != 0)
          *data += *log_iter;

        // Regardless, we still need to move the index iterator
        // to the next position.
        this->iters_.rebind (iter->key (), ++ index_iter);
      }
    }
  }

  return *this;
}

//
// accept
//
void CUTS_Endpoint_Log_Summary::
accept (CUTS_Metrics_Visitor & visitor) const
{
  visitor.visit_endpoint_log_summary (*this);
}
