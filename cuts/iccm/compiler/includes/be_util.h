/* -*- c++ -*- */

//=============================================================================
/**
 * @file    $File$
 *
 * $Id$

 * @author  James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ICCM_COMPILER_BE_UTIL_H_
#define _CUTS_ICCM_COMPILER_BE_UTIL_H_

#include "Compiler_export.h"

// Forward decl
class AST_Generator;

class ICCM_COMPILER_Export be_util
{
public:
  /// Special BE arg call factored out of DRV_args.
  static void prep_be_arg (char *s);

  /// Checks made after parsing args.
  static void arg_post_proc (void);

  /// Display usage of BE-specific options.
  static void usage (void);

  /// Create an AST node generator.
  static AST_Generator * generator_init (void);
};

#endif // if !defined

