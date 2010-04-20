// -*- C++ -*-

//=============================================================================
/**
 * @file        Log_Format_Data_Entry.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_LOG_FORMAT_DATA_ENTRY_H_
#define _CUTS_UNITE_LOG_FORMAT_DATA_ENTRY_H_

#include "Variable_Table.h"

namespace ADBC
{
namespace SQLite
{
// Forward decl.
class Connection;

// Forward decl.
class Query;
}
}

// Forward decl.
class CUTS_Log_Format;

/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_Log_Format_Data_Entry
 */
class CUTS_Log_Format_Data_Entry
{
public:
  /**
   * Initializing contructor
   */
  CUTS_Log_Format_Data_Entry (ADBC::SQLite::Connection & conn);

  /// Destructor
  ~CUTS_Log_Format_Data_Entry (void);

  /**
   *
   */
  void prepare (const ACE_CString & table,
                const CUTS_Log_Format * format);

  void prepare (const ACE_CString & table,
                const CUTS_Log_Format * format,
                size_t relation);

  /**
   *
   */
  void execute (const ACE_CString & message);

private:
  /// Underlying query for inserting data
  ADBC::SQLite::Query * query_;

  /// Name of the log format.
  const CUTS_Log_Format * format_;
};

#endif // !defined _CUTS_UNITE_LOG_FORMAT_DATA_ENTRY_H_
