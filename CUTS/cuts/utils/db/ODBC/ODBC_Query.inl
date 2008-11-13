// $Id$

//
// parameter
//
CUTS_INLINE
ODBC_Parameter_List & ODBC_Query::parameters (void)
{
  return this->params_;
}

CUTS_INLINE
const ODBC_Parameter_List & ODBC_Query::parameters (void) const
{
  return this->params_;
}
