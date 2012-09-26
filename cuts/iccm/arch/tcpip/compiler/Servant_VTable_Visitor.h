// -*- C++ -*-

//==============================================================================
/**
 *  @file        Servant_VTable_Visitor.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_TCPIP_SERVANT_VTABLE_VISITOR_H_
#define _ICCM_TCPIP_SERVANT_VTABLE_VISITOR_H_

#include "cuts/config.h"
#include "cuts/iccm/compiler/Scope_Visitor.h"

#include <fstream>
#include "ace/SString.h"

namespace iCCM
{
namespace TCPIP
{

/**
 * @class Servant_VTable_Visitor
 *
 * Visitor for generating the servant vtable in the servant constructor
 */
class Servant_VTable_Visitor : public Scope_Visitor
{
public:
  /// Initalizing constructor.
  Servant_VTable_Visitor (std::ofstream & sfile);

  /// Destructor.
  ~Servant_VTable_Visitor (void);

  virtual int visit_consumes (AST_Consumes * node);

private:
  std::ofstream & sfile_;
  int port_counter_;
};

} // namespace iCCM
} // namespace TCPIP

#if defined (__CUTS_INLINE__)
#include "Servant_VTable_Visitor.inl"
#endif  // !defined __CUTS_INLINE__

#endif  // _ICCM_TCPIP_SERVANT_VTABLE_VISITOR_H_
