// $Id$

#include "Variable.h"
#include "adbc/SQLite/Types.h"

#if !defined (__CUTS_INLINE__)
#include "Variable.inl"
#endif


///////////////////////////////////////////////////////////////////////////////
// class CUTS_Datetime_Log_Format_Variable

//
// CUTS_Datetime_Log_Format_Variable
//
CUTS_Datetime_Log_Format_Variable::
CUTS_Datetime_Log_Format_Variable (size_t index, const std::string format)
: CUTS_Log_Format_Variable (CUTS_Log_Format_Variable::VT_DATETIME, index),
  format_(format)
{

}

//
// Destructor
//
CUTS_Datetime_Log_Format_Variable::~CUTS_Datetime_Log_Format_Variable (void)
{

}

//
// CUTS_Datetime_Log_Format_Variable
//
void CUTS_Datetime_Log_Format_Variable::
value (const char * begin, const char * end)
{
  // Get the substrings of the Date_Time format and
  // set the cooresponding elements of a date time

  std::string temp (begin, end);
  std::string hour, min, sec, msec;

  hour = temp.substr (0, 2);
  min = temp.substr (3, 2);
  sec = temp.substr (6, 2);
  msec = temp.substr (9, 3);

  // set the ACE_Date_Time object

  this->date_time_.day (10);
  this->date_time_.month (5);
  this->date_time_.year (2010);
  this->date_time_.hour (ACE_OS::atoi (hour.c_str ()));
  this->date_time_.minute (ACE_OS::atoi (min.c_str ()));
  this->date_time_.second (ACE_OS::atoi (sec.c_str ()));
  this->date_time_.microsec (ACE_OS::atoi (msec.c_str ()));
}

//
// bind
//
void CUTS_Datetime_Log_Format_Variable::bind (ADBC::SQLite::Parameter & param)
{
  ADBC::SQLite::Date_Time timeoftrace (this->date_time_);
  param.bind (&timeoftrace);
}

//
// CUTS_Datetime_Log_Format_Variable
//

void CUTS_Datetime_Log_Format_Variable::value (char * val)
{

}

//
// CUTS_Datetime_Log_Format_Variable
//
void CUTS_Datetime_Log_Format_Variable::date_time (ACE_Date_Time & date_time)
{
  this->date_time_= date_time;
}

//
// CUTS_Datetime_Log_Format_Variable
//
ACE_Date_Time CUTS_Datetime_Log_Format_Variable::date_time ()
{
  return this->date_time_;
}

//
// CUTS_Datetime_Log_Format_Variable
//
const std::string CUTS_Datetime_Log_Format_Variable::format ()
{
  return this->format_;
}