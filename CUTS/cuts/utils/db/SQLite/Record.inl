// $Id$

//
// done
//
CUTS_INLINE
bool CUTS_DB_SQLite_Record::done (void) const
{
  return this->state_ == SQLITE_DONE;
}

//
// count
//
CUTS_INLINE
size_t CUTS_DB_SQLite_Record::count (void) const
{
  return -1;
}
