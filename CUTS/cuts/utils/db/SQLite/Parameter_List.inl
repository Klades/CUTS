// $Id$

//
// CUTS_DB_SQLite_Parameter_List
//
CUTS_INLINE
CUTS_DB_SQLite_Parameter_List::
CUTS_DB_SQLite_Parameter_List (const CUTS_DB_SQLite_Query & parent)
: parent_ (parent)
{

}

//
// CUTS_DB_SQLite_Parameter_List
//
CUTS_INLINE
CUTS_DB_SQLite_Parameter_List::~CUTS_DB_SQLite_Parameter_List (void)
{

}

//
// size
//
CUTS_INLINE
size_t CUTS_DB_SQLite_Parameter_List::size (void) const
{
  return this->params_.size ();
}

//
// operator []
//
CUTS_INLINE
CUTS_DB_SQLite_Parameter &
CUTS_DB_SQLite_Parameter_List::operator [] (size_t index)
{
  return this->params_[index];
}

//
// operator []
//
CUTS_INLINE
const CUTS_DB_SQLite_Parameter &
CUTS_DB_SQLite_Parameter_List::operator [] (size_t index) const
{
  return this->params_[index];
}

//
// parent
//
CUTS_INLINE
const CUTS_DB_SQLite_Query & CUTS_DB_SQLite_Parameter_List::owner (void) const
{
  return this->parent_;
}

