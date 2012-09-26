// -*- C++ -*-

//==============================================================================
/**
 *  @file        Push_Event_Visitor.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_TCPIP_PUSH_EVENT_VISITOR_H_
#define _ICCM_TCPIP_PUSH_EVENT_VISITOR_H_

#include "cuts/config.h"
#include "cuts/iccm/compiler/Scope_Visitor.h"

#include <fstream>
#include "ace/SString.h"

namespace iCCM
{
namespace TCPIP
{

/**
 * @class Push_Event_Visitor
 *
 * Visitor for generating the TCPIP push_event method
 */
class Push_Event_Visitor : public Scope_Visitor
{
public:
  /// Initalizing constructor.
  Push_Event_Visitor (std::ofstream & hfile,
                      std::ofstream & sfile,
                      const ACE_CString & servant);

  /// Destructor.
  ~Push_Event_Visitor (void);

  virtual int visit_consumes (AST_Consumes * node);

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & servant_;
};

} // namespace iCCM
} // namespace TCPIP

#if defined (__CUTS_INLINE__)
#include "Push_Event_Visitor.inl"
#endif  // !defined __CUTS_INLINE__

#endif  // _ICCM_TCPIP_PUSH_EVENT_VISITOR_H_
