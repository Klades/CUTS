// $Id$

//
// CUTS_DB_SQLite_Record
//
CUTS_INLINE
CUTS_DB_SQLite_Record::
CUTS_DB_SQLite_Record (const CUTS_DB_SQLite_Query & query, int state)
: query_ (query),
  state_ (state)
{

}

//
// ~CUTS_DB_SQLite_Record
//
CUTS_INLINE
CUTS_DB_SQLite_Record::~CUTS_DB_SQLite_Record (void)
{

}

//
// count
//
CUTS_INLINE
size_t CUTS_DB_SQLite_Record::count (void) const
{
  return -1;
}
