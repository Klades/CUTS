// $Id$

template <typename PORTTYPE>
CUTS_INLINE
size_t CUTS_EISA_Port_Manager_T <PORTTYPE>::size (void) const
{
  return this->ports_.empty ();
}

template <typename PORTTYPE>
CUTS_INLINE
bool CUTS_EISA_Port_Manager_T <PORTTYPE>::empty (void) const
{
  return this->ports_.empty ();
}

template <typename PORTTYPE>
CUTS_INLINE
void CUTS_EISA_Port_Manager_T <PORTTYPE>::clear (void)
{
  this->ports_.clear ();
}
