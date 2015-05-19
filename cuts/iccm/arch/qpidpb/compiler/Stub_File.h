// -*- C++ -*-

//==============================================================================
/**
 *  @file        Stub_File.h
 *
 *  $Id: generate_cpp_class.py 3685 2012-09-26 14:45:04Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_STUB_FILE_H_
#define _ICCM_STUB_FILE_H_

#include "Scope_Visitor.h"
#include <fstream>

namespace iCCM
{

/**
 * @class Stub_File
 *
 * Main visitor that generates CCM wrapper events
 */
class Stub_File : public Scope_Visitor
{
public:
  /// Default constructor.
  Stub_File (void);

  /// Destructor.
  virtual ~Stub_File (void);

  virtual int visit_root (AST_Root *node);
  virtual int visit_module (AST_Module * node);
  virtual int visit_eventtype (AST_EventType * node);

private:
  std::ofstream hfile_;
  std::ofstream sfile_;
};

} // namespace iCCM

#if defined (__CUTS_INLINE__)
#include "Stub_File.inl"
#endif  // !defined __CUTS_INLINE__

#endif  // _ICCM_STUB_FILE_H_
