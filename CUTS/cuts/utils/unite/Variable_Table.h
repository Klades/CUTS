// -*- C++ -*-

//=============================================================================
/**
 * @file        Variable_Table.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_VARIABLE_TABLE_H_
#define _CUTS_UNITE_VARIABLE_TABLE_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/SString.h"
#include "ace/Vector_T.h"

// Forward decl.
class CUTS_Log_Format_Variable;


class CUTS_Log_Format_Variable_Table :
  public ACE_Hash_Map_Manager <ACE_CString,
                              CUTS_Log_Format_Variable *,
                              ACE_Null_Mutex>
{

public:
  CUTS_Log_Format_Variable_Table (){}

  ~CUTS_Log_Format_Variable_Table (){}

  CUTS_Log_Format_Variable * CUTS_Log_Format_Variable_Table::operator [] (const char * name)
  {
    ACE_CString key (name);
    for (CUTS_Log_Format_Variable_Table::CONST_ITERATOR iter (*this);
        !iter.done ();
        ++ iter)
    {
      if ((ACE_CString )iter->key () == key)
        return iter->item ();
    }

    return 0;
  }

};

#endif  // !defined _CUTS_UNITE_VARIABLE_TABLE_H_