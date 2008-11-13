// $Id$

#include "ace/SString.h"

//
// CUTS_DB_SQLite_Parameter
//
CUTS_INLINE
CUTS_DB_SQLite_Parameter::CUTS_DB_SQLite_Parameter (void)
: owner_ (0)
{

}

//
// CUTS_DB_SQLite_Parameter
//
CUTS_INLINE
CUTS_DB_SQLite_Parameter::
CUTS_DB_SQLite_Parameter (const CUTS_DB_SQLite_Parameter & p)
: CUTS_DB_Parameter (p),
  owner_ (p.owner_)
{

}

//
// ~CUTS_DB_SQLite_Parameter
//
CUTS_INLINE
CUTS_DB_SQLite_Parameter::~CUTS_DB_SQLite_Parameter (void)
{

}

//
// operator =
//
CUTS_INLINE
const CUTS_DB_SQLite_Parameter &
CUTS_DB_SQLite_Parameter::operator = (const CUTS_DB_SQLite_Parameter & rhs)
{
  this->owner_ = rhs.owner_;
  this->index_ = rhs.index_;

  return *this;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (float & value)
{
  this->bind_double (static_cast <double> (value));
  CUTS_DB_Parameter::bind (value);
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (double & value)
{
  this->bind_double (value);
  CUTS_DB_Parameter::bind (value);
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (ACE_INT16 & value)
{
  this->bind_int (static_cast <int> (value));
  CUTS_DB_Parameter::bind (value);
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (ACE_UINT16 & value)
{
  this->bind_int (static_cast <int> (value));
  CUTS_DB_Parameter::bind (value);
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (ACE_INT32 & value)
{
  this->bind_int (static_cast <int> (value));
  CUTS_DB_Parameter::bind (value);
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (ACE_UINT32 & value)
{
  this->bind_int (static_cast <int> (value));
  CUTS_DB_Parameter::bind (value);
}
