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
// CUTS_Datetime_Log_Format_Variable
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
  std::string temp(begin, end);
  std::string hour, min, sec, msec;
  
  hour = temp.substr(0, 2);
  min = temp.substr(3, 2);
  sec = temp.substr(6, 2);
  msec = temp.substr(9, 3);

  this->date_time_.day(10);
  this->date_time_.month(5);
  this->date_time_.year(2010);
  this->date_time_.hour(atoi(hour.c_str()));
  this->date_time_.minute(atoi(min.c_str()));
  this->date_time_.second(atoi(sec.c_str()));
  this->date_time_.microsec(atoi(msec.c_str()));
  //this->value_.set (begin, end - begin, true);
}

//
// bind
//
void CUTS_Datetime_Log_Format_Variable::bind (ADBC::SQLite::Parameter & param)
{
	ADBC::SQLite::Date_Time timeoftrace(this->date_time_);
	param.bind(&timeoftrace);
}

void CUTS_Datetime_Log_Format_Variable::
set_value (char * val)
{
  //this->value_.set(val);
}

void CUTS_Datetime_Log_Format_Variable::date_time(char *val)
{
  //this->value_.set(val);
}

void CUTS_Datetime_Log_Format_Variable::date_time(ACE_Date_Time &date_time)
{
  this->date_time_= date_time;
}

ACE_Date_Time CUTS_Datetime_Log_Format_Variable::date_time()
{
  return this->date_time_;
}

const std::string CUTS_Datetime_Log_Format_Variable::format()
{
  return this->format_;
}