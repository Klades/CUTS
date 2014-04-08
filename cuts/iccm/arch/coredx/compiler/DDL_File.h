// -*- C++ -*-

//=============================================================================
/**
 *  @file       DDL_File.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDL_FILE_H_
#define _ICCM_DDL_FILE_H_

#include "Scope_Visitor.h"
#include <fstream>

namespace iCCM
{

/**
 * @class DDL_File
 *
 * Main visitor that generates a DDL file which wraps an IDL file
 */
class DDL_File : public Scope_Visitor
{
public:
  /// Default constructor.
  DDL_File (void);

  /// Destructor.
  virtual ~DDL_File (void);

  // used methods
  virtual int visit_root (AST_Root *node);

private:
  std::ofstream ddl_file_;
};

}

#endif  // !defined _ICCM_DDL_FILE_H_
