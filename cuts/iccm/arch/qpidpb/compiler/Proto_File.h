// -*- C++ -*-

//=============================================================================
/**
 *  @file       Proto_File.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_PROTO_FILE_H_
#define _ICCM_PROTO_FILE_H_

#include "Scope_Visitor.h"
#include "ace/SString.h"
#include <fstream>

namespace iCCM
{

/**
 * @class Proto_File
 *
 * Main visitor that generates a Proto file which represents an IDL file
 */
class Proto_File : public Scope_Visitor
{
public:
  /// Default constructor.
  Proto_File (const ACE_CString & package);

  /// Destructor.
  virtual ~Proto_File (void);

  // used methods
  virtual int visit_root (AST_Root *node);
  virtual int visit_structure (AST_Structure * node);
  virtual int visit_field (AST_Field * node);
  virtual int visit_module (AST_Module * node);

  virtual int init (const ACE_CString & filename);

private:
  std::ofstream proto_file_;
  ACE_CString package_;
  size_t counter_;
};

}

#endif  // !defined _ICCM_PROTO_FILE_H_
