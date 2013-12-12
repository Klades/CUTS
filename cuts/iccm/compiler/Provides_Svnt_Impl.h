// -*- C++ -*-

//==============================================================================
/**
 *  @file        Provides_Svnt_Impl.h
 *
 *  $Id$
 *
 *  @author      Dennis Feiock
 */
//==============================================================================

#ifndef _ICCM_PROVIDES_SVNT_IMPL_H_
#define _ICCM_PROVIDES_SVNT_IMPL_H_

#include "Scope_Visitor.h"
#include <fstream>
#include "be_extern.h"
#include "be_global.h"

namespace iCCM
{

/**
 * @class Provides_Svnt_Impl
 *
 * Visitor for generating facet servants for 'provides' idl keyword
 */
class Provides_Svnt_Impl : public Scope_Visitor
{
public:
  /// Default constructor.
  Provides_Svnt_Impl (std::ofstream & hfile,
                      std::ofstream & sfile,
                      ACE_CString context);

  /// Destructor.
  ~Provides_Svnt_Impl (void);

  // Overload visit_scope
  virtual int visit_scope (UTL_Scope * node);

  // used methods
  virtual int visit_provides (AST_Provides * node);
  virtual int visit_interface (AST_Interface * node);
  virtual int visit_operation (AST_Operation * node);

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString context_;
  ACE_CString servant_name_;
};

} // namespace iCCM

#endif  // _ICCM_PROVIDES_SVNT_IMPL_H_
