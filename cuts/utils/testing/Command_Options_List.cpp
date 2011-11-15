#include "Command_Options_List.h"

#if !defined (__CUTS_INLINE__)
#include "Command_Options_List.inl"
#endif

//
// append
//
int CUTS_Command_Options_List::append (const CUTS_Command_Options & opts)
{
  node_type * node = 0;
  ACE_NEW_RETURN (node,
                  node_type (opts),
                  -1);

  // Insert the Command at the end of the list.
  this->insert_tail (node);
  return 0;
}
