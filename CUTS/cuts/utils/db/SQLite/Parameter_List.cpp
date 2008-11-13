// $Id$

#include "Parameter_List.h"

#if !defined (__CUTS_INLINE__)
#include "Parameter_List.inl"
#endif

#include "Query.h"
#include "sqlite3.h"

//
// reset
//
void CUTS_DB_SQLite_Parameter_List::reset (void)
{
  // Get the number of parameters in the statement.
  int new_size = ::sqlite3_bind_parameter_count (this->parent_.stmt_);

  // Resize the statement.
  int old_size = this->params_.size ();
  this->params_.size (new_size);

  if (new_size > old_size)
  {
    for (int i = old_size; i < new_size; ++ i)
      this->params_[i].reset (this, i + 1);
  }
}
