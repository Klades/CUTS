// -*- C++ -*-

#ifndef _PP_STATS_H_
#define _PP_STATS_H_

#include "ace/SString.h"
#include "ace/Time_Value.h"
#include <iosfwd>

class PP_Stats
{
public:
  PP_Stats (const char * name);

  const PP_Stats & operator += (const ACE_Time_Value & tv);

  void reset (void);

  static double tv_to_double (const ACE_Time_Value & tv);

  int count (void) const;

  double avg (void) const;

  double min_value (void) const;

  double max_value (void) const;

private:

  ACE_CString name_;

  int count_;

  double avg_;

  double min_;

  double max_;
};

std::ostream & operator << (std::ostream & out, const PP_Stats & s);

#endif
