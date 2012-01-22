// -*- C++ -*-

//=============================================================================
/**
 * @file        Log_Format_Compiler.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_LOG_FORMAT_COMPILER_H_
#define _CUTS_UNITE_LOG_FORMAT_COMPILER_H_

#include <sstream>
#include "Variable_Table.h"

/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_Log_Format_Compiler
 */
class CUTS_Log_Format_Compiler
{
public:

  /// Constructor
  CUTS_Log_Format_Compiler (void);

  /// Destructor
  ~CUTS_Log_Format_Compiler (void);

  /**
   * Implementation for adding new relations
   * @param[in]     format    the log format string
   * @param[in]     expr      resulting pcre expression.
   * @param[in]     vars      set of log format variables.
   * @return        true if succeed false if fails.
   */
  bool compile (const char * format,
                std::ostringstream & expr,
                CUTS_Log_Format_Variable_Table & vars);
};

#endif  // !defined _CUTS_UNITE_LOG_FORMAT_COMPILER_H_