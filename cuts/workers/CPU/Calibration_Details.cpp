// $Id$

#include "Calibration_Details.h"

#if !defined (__CUTS_INLINE__)
#include "Calibration_Details.inl"
#endif

#include "ace/Auto_Ptr.h"
#include "ace/CORBA_macros.h"
#include <numeric>
#include <math.h>
#include <algorithm>

#include "boost/bind.hpp"
#include "boost/ref.hpp"
#include "boost/accumulators/accumulators.hpp"
#include "boost/accumulators/statistics/stats.hpp"
#include "boost/accumulators/statistics/mean.hpp"
#include "boost/accumulators/statistics/min.hpp"
#include "boost/accumulators/statistics/max.hpp"
#include "boost/accumulators/statistics/variance.hpp"
#include "boost/math/distributions/normal.hpp"

//
// ~CUTS_CPU_Calibration_Details
//
CUTS_CPU_Calibration_Details::
~CUTS_CPU_Calibration_Details (void)
{
  CUTS_CPU_Calibration_Details_Log::CONST_ITERATOR iter (this->log_);

  for (iter; !iter.done (); iter ++)
    delete iter->item ();
}

//
// process
//
int CUTS_CPU_Calibration_Details::
process (size_t msec,
         const CUTS_CPU_Calibration_Results & results,
         CUTS_CPU_Calibration_Details_Log_Entry * & entry)
{
  // First, let's try to find the entry in the log.
  int retval = this->log_.find (msec, entry);

  if (retval == -1)
  {
    // Create a new entry for the log
    ACE_NEW_THROW_EX (entry,
                      CUTS_CPU_Calibration_Details_Log_Entry,
                      ACE_bad_alloc ());

    // Try to add the entry to log. If we are not able to add the entry
    // to the log, then we need to release the allocated memory.
    ACE_Auto_Ptr <CUTS_CPU_Calibration_Details_Log_Entry> auto_clean (entry);
    retval = this->log_.bind (msec, entry);

    if (retval == 0)
      auto_clean.release ();
  }

  if (retval == 0)
  {
    typedef boost::accumulators::accumulator_set<CUTS_CPU_Calibration_Results::value_type,
      boost::accumulators::stats<boost::accumulators::tag::mean,
        boost::accumulators::tag::variance>
      > distribution_accumulator_type;

    typedef boost::accumulators::accumulator_set<CUTS_CPU_Calibration_Results::value_type,
      boost::accumulators::stats<boost::accumulators::tag::mean,
        boost::accumulators::tag::max, boost::accumulators::tag::min,
        boost::accumulators::tag::variance, boost::accumulators::tag::count>
      > result_accumulator_type;

    // Copy values into the distribution accumulator
    distribution_accumulator_type dist_acc;
    std::for_each (results.begin (), results.end (), boost::bind <void> (boost::ref (dist_acc), _1));

    // Allocate the result accumulator
    result_accumulator_type result_acc;

    // Create normal distribution and identify outer fences
    double std_dev = sqrt (boost::accumulators::variance (dist_acc));
    if (std_dev != 0)
    {
      // There is variance in the results, lets see if we can remove
      // any extreme outliers via normal distribution
      boost::math::normal dist (boost::accumulators::mean (dist_acc),
                                std_dev);
      double q1 = quantile (dist, 0.25);
      double q3 = quantile (complement (dist, 0.25));
      double qi = q3 - q1;
      double lower_fence = q1 - 1.5 * qi;
      double upper_fence = q3 + 1.5 * qi;

      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT("*** info (CUTS_CPU_Worker): outliers are between ")
                  ACE_TEXT("[%f] and [%f]\n"),lower_fence, upper_fence));

      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("*** info (CUTS_CPU_Worker): average execution ")
                  ACE_TEXT ("time before removing outliers: [%f]\n"),
                  boost::accumulators::mean (dist_acc)));
      size_t drop_count = 0;

      // Copy values which aren't outliers into the result accumulator
      for (CUTS_CPU_Calibration_Results::const_iterator iter = results.begin ();
           iter != results.end ();
           iter ++)
      {
        if ((*iter > lower_fence) && (*iter < upper_fence))
          result_acc (*iter);
        else
          ++drop_count;
      }
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("*** info (CUTS_CPU_Worker): dropped [%d] samples ")
                  ACE_TEXT ("as outliers\n"),
                  drop_count));
    }
    else
    {
      // No standard deviation, so looking for outliers isn't necessary.
      std::for_each (results.begin (),
                     results.end (),
                     boost::bind <void> (boost::ref (result_acc), _1));
    }

    // Calculate the average execution time and the average error
    // of the collected execution times.
    CUTS_CPU_Calibration_Results::
      value_type sum = std::accumulate (results.begin (), results.end (), 0);

    entry->average_time_  = boost::accumulators::mean (result_acc);
    entry->average_error_ = entry->average_time_ - (double) msec;
    entry->percent_error_ = entry->average_error_ / (double) msec;

    // Calculate basic statistics about the results.
    entry->variance_ = boost::accumulators::variance (result_acc);
    entry->stddev_ = sqrt (entry->variance_);
    entry->stderr_ = entry->stddev_ / sqrt (boost::accumulators::count (result_acc));

    // Update the min, max, and sum percentages.
    if (entry->average_error_ < this->min_error_)
      this->min_error_ = entry->average_error_;
    else if (entry->average_error_ > this->max_error_)
      this->max_error_ = entry->average_error_;

    this->percent_error_sum_ += entry->percent_error_;
    ++ this->count_;
  }

  return retval;
}

//
// reset
//
void CUTS_CPU_Calibration_Details::reset (void)
{
  // Reset the values.
  this->max_error_ = 0.0;
  this->min_error_ = 0.0;
  this->percent_error_sum_ = 0.0;
  this->count_ = 0;

  // Delete all the entries in the log.
  CUTS_CPU_Calibration_Details_Log::ITERATOR iter (this->log_);

  for (; !iter.done (); iter ++)
    delete iter->item ();

  this->log_.unbind_all ();
}

//
// calculate_stddev
//
double CUTS_CPU_Calibration_Details::
calculate_variance (size_t msec, const CUTS_CPU_Calibration_Results & results)
{
  double sum = 0.0;
  CUTS_CPU_Calibration_Results::const_iterator iter;

  for (iter = results.begin (); iter != results.end (); iter ++)
    sum += ((double)(*iter - msec) * (double)(*iter - msec));

  return (sum / (double) results.size ());
}
