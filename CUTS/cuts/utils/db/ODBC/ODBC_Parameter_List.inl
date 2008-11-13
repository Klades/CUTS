// $Id$

//
// size
//
CUTS_INLINE
size_t ODBC_Parameter_List::size (void) const
{
  return this->size ();
}

//
// operator []
//
CUTS_INLINE
const ODBC_Parameter & ODBC_Parameter_List::operator [] (size_t index) const
{
  return this->params_[index];
}

//
// operator []
//
CUTS_INLINE
ODBC_Parameter & ODBC_Parameter_List::operator [] (size_t index)
{
  return this->params_[index];
}
