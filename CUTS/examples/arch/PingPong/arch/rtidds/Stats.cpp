// $Id$

#include "Stats.h"
#include <ostream>
#include <iomanip>

//
// PP_Stats
//
PP_Stats::PP_Stats (const char * name)
: name_ (name),
  count_ (0),
  avg_ (0.0),
  min_ (0.0),
  max_ (0.0)
{

}

//
// reset
//
void PP_Stats::reset (void)
{
  this->count_ = 0;
  this->avg_ = 0.0;
  this->min_ = 0.0;
  this->max_ = 0.0;
}

//
// operator +=
//
const PP_Stats & PP_Stats::operator += (const ACE_Time_Value & tv)
{
  double data = 1E6 * this->tv_to_double (tv);

  this->avg_ = (this->count_ * this->avg_ + data) / (this->count_ + 1);
  this->min_ = (this->count_ == 0 || data < this->min_) ? data : this->min_;
  this->max_ = (this->count_ == 0 || data > this->max_) ? data : this->max_;

  this->count_ ++;

  return *this;
}

//
// tv_to_double
//
double PP_Stats::tv_to_double (const ACE_Time_Value & tv)
{
  double tr;
  tr = (double)tv.sec () + (double)tv.usec () / (double)1000000.0;

  return tr;
}

//
// count
//
int PP_Stats::count (void) const
{
  return this->count_;
}

//
// avg
//
double PP_Stats::avg (void) const
{
  return this->avg_;
}

//
// min
//
double PP_Stats::min_value (void) const
{
  return this->min_;
}

//
// max
//
double PP_Stats::max_value (void) const
{
  return this->max_;
}

//
// operator <<
//
std::ostream & operator << (std::ostream & out, const PP_Stats & s)
{
  out
    << std::setw (10) << s.count () << " "
    << std::setw (6) << std::setprecision (0) << s.avg () << " "
    << std::setw (6) << std::setprecision (0) << s.min_value () << " "
    << std::setw (6) << std::setprecision (0) << s.max_value ();

  return out;
}
