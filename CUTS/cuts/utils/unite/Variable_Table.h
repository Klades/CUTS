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

/// Type definition for the log format's variable table.
typedef ACE_Hash_Map_Manager <ACE_CString,
                              CUTS_Log_Format_Variable *,
                              ACE_Null_Mutex> CUTS_Log_Format_Variable_Table;

#endif  // !defined _CUTS_UNITE_VARIABLE_TABLE_H_
