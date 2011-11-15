// -*- C++ -*-

//=============================================================================
/**
 * @file        Trace_Importer_Parser.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TRACE_IMPORTER_PARSER_H_
#define _CUTS_TRACE_IMPORTER_PARSER_H_

#include "ace/SString.h"
#include "cuts/config.h"

// Forward decl.
class CUTS_Test_Database;

/**
 * @class CUTS_Trace_Importer_Parser
 *
 * Parser class for importing a trace into a CUTS_Test_Database. This
 * class assumes the CUTS_Test_Database already has been properly
 * initialized, i.e., has a cuts_logging table.
 */
class CUTS_Trace_Importer_Parser
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       test_db         Target test database.
   */
  CUTS_Trace_Importer_Parser (CUTS_Test_Database & test_db);

  /// Destructor.
  ~CUTS_Trace_Importer_Parser (void);

  /**
   * Import the specified trace into the database.
   *
   * @param[in]       trace_file          Location of the trace file.
   * @param[in]       hostname            Host that generated \a trace_file.
   */
  bool import_trace (const ACE_CString & trace_file,
                     const ACE_CString & hostname);

private:
  /// Target test database for import.
  CUTS_Test_Database & test_db_;
};

#if defined (__CUTS_INLINE__)
#include "Trace_Importer_Parser.inl"
#endif

#endif  // !defined _CUTS_TRACE_PARSER_H_
