// $Id$

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
void CUTS_DB_SQLite_Parameter::bind (float * buffer)
{
  this->bind_double (static_cast <double> (*buffer));
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (double * buffer)
{
  this->bind_double (*buffer);
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (short * buffer)
{
  this->bind_int (static_cast <int> (*buffer));
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (u_short * buffer)
{
  this->bind_int (static_cast <int> (*buffer));
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (long * buffer)
{
  this->bind_int (static_cast <int> (*buffer));
}

//
// bind
//
CUTS_INLINE
void CUTS_DB_SQLite_Parameter::bind (u_long * buffer)
{
  this->bind_int (static_cast <int> (*buffer));
}
