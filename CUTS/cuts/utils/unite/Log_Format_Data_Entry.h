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
#include "Log_Format_Adapter.h"

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
   * Construct the insert query
   * @param[in]     table    name of the table the data will be added
   * @param[in]     format   log format with which the messages are matched
   */
  void prepare (const ACE_CString & table,
                CUTS_Log_Format * format);

  /**
   * Construct the update query
   * @param[in]     table    name of the table the data will be added
   * @param[in]     format   log format with which the messages are matched
   * @param[in]     relation index of the relation
   */

  void prepare (const ACE_CString & table,
                CUTS_Log_Format * format,
                size_t relation);

   /**
   * Construct the update query
   * @param[in]     message   trace which has the values for the query
   * @param[in]     adapter   adapter to fill other values
   */
  void execute (const ACE_CString & message,
                CUTS_Log_Format_Adapter *adapter);

private:
  /// Underlying query for inserting data
  ADBC::SQLite::Query * query_;

  /// Name of the log format.
  CUTS_Log_Format * format_;

};

#endif // !defined _CUTS_UNITE_LOG_FORMAT_DATA_ENTRY_H_