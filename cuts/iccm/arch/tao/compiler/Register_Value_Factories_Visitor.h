// -*- C++ -*-

//==============================================================================
/**
 *  @file        Register_Value_Factories_Visitor.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_TAO_REGISTER_VALUE_FACTORIES_VISITOR_H_
#define _ICCM_TAO_REGISTER_VALUE_FACTORIES_VISITOR_H_

#include "cuts/config.h"
#include "cuts/iccm/compiler/Scope_Visitor.h"

#include <fstream>
#include "ace/SString.h"

namespace iCCM
{
namespace TAO
{

/**
 * @class Register_Value_Factories_Visitor
 *
 * Visitor for generating the TAO push_event method
 */
class Register_Value_Factories_Visitor : public Scope_Visitor
{
public:
  /// Initalizing constructor.
  Register_Value_Factories_Visitor (std::ofstream & hfile,
                                    std::ofstream & sfile,
                                    const ACE_CString & servant);

  /// Destructor.
  ~Register_Value_Factories_Visitor (void);

  virtual int visit_component (AST_Component * node);
  virtual int visit_eventtype (AST_EventType * node);

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  const ACE_CString & servant_;
};

} // namespace iCCM
} // namespace TAO

#if defined (__CUTS_INLINE__)
#include "Register_Value_Factories_Visitor.inl"
#endif  // !defined __CUTS_INLINE__

#endif  // _ICCM_TAO_REGISTER_VALUE_FACTORIES_VISITOR_H_
