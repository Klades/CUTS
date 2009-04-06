// -*- C++ -*-
// $Id$

//
// CUTS_DB_Parameter
//
CUTS_INLINE
CUTS_DB_Parameter::CUTS_DB_Parameter (void)
: index_ (-1),
  type_ (PT_UNKNOWN),
  is_null_ (true)
{

}

//
// CUTS_DB_Parameter
//
CUTS_INLINE
CUTS_DB_Parameter::CUTS_DB_Parameter (const CUTS_DB_Parameter & p)
: index_ (p.index_),
  type_ (p.type_),
  is_null_ (p.is_null_)
{

}

//
// CUTS_DB_Parameter
//
CUTS_INLINE
CUTS_DB_Parameter::~CUTS_DB_Parameter (void)
{

}

//
// type
//
CUTS_INLINE
CUTS_DB_Parameter::Parameter_Type
CUTS_DB_Parameter::type (void) const
{
  return this->type_;
}

//
// index
//
CUTS_INLINE
size_t CUTS_DB_Parameter::index (void) const
{
  return this->index_;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (char *, size_t)
{
  this->type_ = CUTS_DB_Parameter::PT_CHAR;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (const char *, size_t)
{
  this->type_ = CUTS_DB_Parameter::PT_CHAR;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (ACE_INT16 &)
{
  this->type_ = CUTS_DB_Parameter::PT_SHORT;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (ACE_UINT16 &)
{
  this->type_ = CUTS_DB_Parameter::PT_USHORT;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (ACE_INT32 &)
{
  this->type_ = CUTS_DB_Parameter::PT_LONG;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (ACE_UINT32 &)
{
  this->type_ = CUTS_DB_Parameter::PT_ULONG;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (ACE_INT64 &)
{
  this->type_ = CUTS_DB_Parameter::PT_LONGLONG;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (ACE_UINT64 &)
{
  this->type_ = CUTS_DB_Parameter::PT_ULONGLONG;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (double &)
{
  this->type_ = CUTS_DB_Parameter::PT_DOUBLE;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (float &)
{
  this->type_ = CUTS_DB_Parameter::PT_FLOAT;
  this->is_null_ = false;
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_Parameter::bind (CUTS_DB_Date_Time &)
{
  this->type_ = CUTS_DB_Parameter::PT_DATETIME;
  this->is_null_ = false;
}

//
// is_null
//
CUTS_INLINE
bool CUTS_DB_Parameter::is_null (void) const
{
  return this->is_null_;
}

//
// null
//
CUTS_INLINE
void CUTS_DB_Parameter::null (void)
{
  this->is_null_ = true;
}

//
// direction
//
CUTS_INLINE
CUTS_DB_Parameter::Direction_Type
CUTS_DB_Parameter::direction (void) const
{
  return this->direction_;
}
