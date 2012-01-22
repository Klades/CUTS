// $Id$

#include "Variable_Table.h"
#include "Variable.h"

//
// CUTS_Log_Format_Variable_Table
//
CUTS_Log_Format_Variable_Table::CUTS_Log_Format_Variable_Table (void)
{

}

//
// ~CUTS_Log_Format_Variable_Table
//
CUTS_Log_Format_Variable_Table::~CUTS_Log_Format_Variable_Table (void)
{
  for (map_type::ITERATOR iter (this->vars_); !iter.done (); ++ iter)
    delete iter->item ();
}

//
// insert
//
int CUTS_Log_Format_Variable_Table::
insert (const ACE_CString & type, const ACE_CString & name)
{

  return 0;
}

//
// operator []
//
CUTS_Log_Format_Variable *
CUTS_Log_Format_Variable_Table::operator [] (const ACE_CString & name) const
{
  CUTS_Log_Format_Variable * var = 0;
  this->vars_.find (name, var);

  return var;
}

//
// operator []
//
CUTS_Log_Format_Variable *
CUTS_Log_Format_Variable_Table::operator [] (size_t index) const
{
  return this->index_[index];
}


//
// clear
//
void CUTS_Log_Format_Variable_Table::clear (void)
{
  for (map_type::ITERATOR iter (this->vars_); !iter.done (); ++ iter)
    delete iter->item ();

  this->vars_.unbind_all ();
  this->index_.clear ();
}

//
// size
//
size_t CUTS_Log_Format_Variable_Table::size (void)
{
  return this->vars_.current_size ();
}
