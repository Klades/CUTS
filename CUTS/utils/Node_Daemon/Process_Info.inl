// $Id$

//
// operator ==
//
CUTS_INLINE
bool CUTS_Process_Info::
operator == (const CUTS_Process_Info & rhs)
{
  return this->name_ == rhs.name_;
}
