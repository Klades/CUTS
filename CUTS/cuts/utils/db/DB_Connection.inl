// $Id$

//
// disconnect
//
CUTS_INLINE
void CUTS_DB_Connection::disconnect (void)
{
  this->connected_ = false;
}

//
// connect
//
CUTS_INLINE
void CUTS_DB_Connection::connect (const ACE_CString & connstr)
{
  this->connected_ = true;
  this->connstr_ = connstr;
}
