// $Id$

//
// log_file
//
CUTS_INLINE
const ACE_CString & Process_Log::log_file (void) const
{
  return this->log_file_;
}

//
// write_string
//
CUTS_INLINE
int Process_Log::
write_string (std::ofstream & file, const ACE_CString & str)
{
  return this->write_string (file, str.c_str (), str.length ());
}
