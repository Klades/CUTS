// $Id$

#include "cuts/Port_Summary.h"

#if !defined (__CUTS_INLINE__)
#include "cuts/Port_Summary.inl"
#endif

#include "cuts/Metrics_Visitor.h"
#include "ace/Auto_Ptr.h"

///////////////////////////////////////////////////////////////////////////////
// @@ CUTS_Port_Summary_Base

//
// reset
//
void CUTS_Port_Summary_Base::reset (void)
{
  this->queuing_time_.reset ();
  this->service_time_.reset ();
  this->endpoints_.reset ();
}

//
// process
//
int CUTS_Port_Summary_Base::
process (const CUTS_Activation_Record & record)
{
  // Store the queuing and service time of the record.
  this->queuing_time_ += record.queue_time ();

  ACE_Time_Value tmp_tv;
  record.get_duration (tmp_tv);

  this->service_time_ += tmp_tv;

  if (this->endpoints_.process (record.endpoints ()) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error (CUTS_Port_Summary_Base): failed to process "
                       "endpoints\n"),
                       -1);

  return 0;
}

//
// operator =
//
const CUTS_Port_Summary_Base &
CUTS_Port_Summary_Base::operator = (const CUTS_Port_Summary_Base & rhs)
{
  this->queuing_time_ = rhs.queuing_time_;
  this->service_time_ = rhs.service_time_;
  this->endpoints_ = rhs.endpoints_;

  return *this;
}

//
// operator +=
//
const CUTS_Port_Summary_Base &
CUTS_Port_Summary_Base::operator += (const CUTS_Port_Summary_Base & rhs)
{
  this->queuing_time_ += rhs.queuing_time_;
  this->service_time_ += rhs.service_time_;
  this->endpoints_  += rhs.endpoints_;

  return *this;
}

//
// accept
//
void CUTS_Port_Summary_Base::accept (CUTS_Metrics_Visitor & visitor) const
{
  visitor.visit_port_summary_base (*this);
}

///////////////////////////////////////////////////////////////////////////////
// @@ CUTS_Port_Summary

//
// ~CUTS_Port_Summary
//
CUTS_Port_Summary::~CUTS_Port_Summary (void)
{
  CUTS_Sender_Port_Summary::iterator iter = this->ssp_.begin ();
  CUTS_Sender_Port_Summary::iterator iter_end = this->ssp_.end ();

  for (; iter != iter_end; iter ++)
    delete iter->item ();
}

//
// process
//
int CUTS_Port_Summary::
process (const CUTS_Activation_Record_Log & log)
{
  CUTS_Activation_Record_Log::const_iterator p_record = log.begin ();
  CUTS_Activation_Record_Log::const_iterator p_record_end = log.used_end ();

  for ( ; p_record != p_record_end; p_record ++)
  {
    if (p_record != 0)
    {
      if (this->process (*p_record) == -1)
        ACE_ERROR ((LM_ERROR,
                    "*** error (CUTS_Port_Summary): failed to process "
                    "record\n"));
    }
  }

  return 0;
}

//
// process
//
int CUTS_Port_Summary::
process (const CUTS_Activation_Record & record)
{
  // Update the overall summary of the port.
  this->CUTS_Port_Summary_Base::process (record);

  // Find the sender port for this metric.
  CUTS_Port_Summary_Base * summary = 0;

  if (this->ssp_.find (record.owner (), summary) == -1)
  {
    // Create a new port summary and insert it into the map.
    ACE_NEW_RETURN (summary, CUTS_Port_Summary_Base (), -1);
    ACE_Auto_Ptr <CUTS_Port_Summary_Base> auto_clean (summary);

    int retval = this->ssp_.bind (record.owner (), summary);

    if (retval == 0)
    {
      auto_clean.release ();
    }
    else
    {
      if (retval == 1)
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                           "*** error (CUTS_Port_Summary): duplicate port\n"),
                           -1);
      }
      else
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                           "*** error (CUTS_Port_Summary): internal error\n"),
                           -1);
      }
    }
  }

  // Let the summary for the port process the record.
  if (summary != 0)
  {
    summary->process (record);
  }
  else
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error (CUTS_Port_Summary): invalid port "
                       "summary\n"),
                       -1);
  }

  return 0;
}

//
// reset
//
void CUTS_Port_Summary::reset (void)
{
  // Reset the base class.
  this->CUTS_Port_Summary_Base::reset ();

  // Reset the port summaries for each sender.
  CUTS_Sender_Port_Summary::ITERATOR iter (this->ssp_);

  for ( ; !iter.done (); iter ++)
  {
    if (iter->item ())
      iter->item ()->reset ();
  }
}

//
// accept
//
void CUTS_Port_Summary::accept (CUTS_Metrics_Visitor & visitor) const
{
  visitor.visit_port_summary (*this);
}
