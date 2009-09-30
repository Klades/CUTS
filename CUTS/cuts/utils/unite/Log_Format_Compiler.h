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
 * @ingroup UNITE_Common
 *
 * @class CUTS_Log_Format_Compiler
 */
class CUTS_Log_Format_Compiler
{
public:
  CUTS_Log_Format_Compiler (void);

  ~CUTS_Log_Format_Compiler (void);

  bool compile (const char * format,
                std::ostringstream & expr,
                CUTS_Log_Format_Variable_Table & vars);
};

#endif  // !defined _CUTS_UNITE_LOG_FORMAT_COMPILER_H_
