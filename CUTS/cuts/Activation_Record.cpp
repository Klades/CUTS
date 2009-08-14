// $Id$

#include "cuts/Activation_Record.h"

#if !defined (__CUTS_INLINE__)
#include "cuts/Activation_Record.inl"
#endif

////
//// CUTS_Activation_Record
////
//CUTS_Activation_Record::
//CUTS_Activation_Record (const CUTS_Activation_Record & rec)
//: active_ (rec.active_),
//  owner_ (rec.owner_),
//  stopwatch_ (rec.stopwatch_),
//  queue_time_ (rec.queue_time_),
//  endpoints_ (rec.endpoints_),
//  entries_ (50)
//{
//
//}
//
////
//// operator =
////
//const CUTS_Activation_Record &
//CUTS_Activation_Record::operator = (const CUTS_Activation_Record & rec)
//{
//  this->active_ = rec.active_;
//  this->owner_ = rec.owner_;
//
//  this->stopwatch_ = rec.stopwatch_;
//  this->queue_time_ = rec.queue_time_;
//  this->entries_ = rec.entries_;
//
//  this->endpoints_ = rec.endpoints_;
//  return *this;
//}

//
// reset
//
void CUTS_Activation_Record::reset (void)
{
  this->owner_ = CUTS_UNKNOWN_IMPL;
  this->queue_time_ = ACE_Time_Value::zero;

  this->endpoints_.reset ();
  this->entries_.reset ();
}

//
// perform_action_i
//
void CUTS_Activation_Record::perform_action_i (size_t uid, size_t type)
{
  // Get the next entry in the log.
  CUTS_Activation_Record_Entry * entry = this->entries_.next_free_record ();

  // Store information about the current action in the entry.
  entry->uid_ = uid;
  entry->type_ = type;
  this->action_timer_.elapsed_time (entry->duration_);
}

//
// log_endpoint
//
void CUTS_Activation_Record::log_endpoint (size_t uid, size_t datasize)
{
  CUTS_Activation_Record_Endpoint *
    endpoint = this->endpoints_.next_free_record ();

  if (endpoint != 0)
  {
    endpoint->set (uid, ACE_OS::gettimeofday (), datasize);
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (record): failed to create new endpoint\n"));
  }
}
