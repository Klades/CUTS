// $Id$

#include "cuts/Port_Agent.h"

#if !defined (__CUTS_INLINE__)
#include "cuts/Port_Agent.inl"
#endif

//#include "cuts/Activation_Record.h"
//#include "cuts/Activation_Record_Entry.h"
//#include "cuts/Port_Measurement.h"

////
//// update
////
//void CUTS_Port_Agent::
//consolidate (const CUTS_Activation_Record * record)
//{
//  // Locate the measurements for this owner. If we can not
//  // find the records then we need to create a new entry for it.
//  CUTS_Port_Measurement * pm = 0;
//  int retval = this->sender_map_.find (record->owner (), pm);
//
//  if (retval == 0 && pm != 0)
//  {
//    // Get the start time of the record's activity.
//    const ACE_Time_Value & start_time = record->start_time ();
//
//    // Get the duration of the record's activity.
//    ACE_Time_Value duration;
//    record->get_duration (duration);
//
//    // Store the process and queuing time.
//    pm->process_time () += duration;
//    pm->queuing_time () += record->queue_time ();
//
//    /// @todo Determine the correct method for cosolidating the
//    ///       endpoint records for the activation log.
//    //pm->record_endpoints (record->endpoints ());
//  }
//  else
//  {
//    if (retval != 0)
//    {
//      ACE_ERROR ((LM_ERROR,
//                  "*** error (CUTS_Port_Agent): failed to locate port "
//                  "measurements for sender %u\n",
//                  record->owner ()));
//    }
//    else
//    {
//      ACE_ERROR ((LM_ERROR,
//                  "*** error (CUTS_Port_Agent): port measurement for sender "
//                  "%u is NIL\n",
//                  record->owner ()));
//    }
//  }
//}
