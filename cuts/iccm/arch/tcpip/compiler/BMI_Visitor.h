// -*- C++ -*-

//==============================================================================
/**
 *  @file        BMI_Visitor.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_TCPIP_BMI_VISITOR_H_
#define _ICCM_TCPIP_BMI_VISITOR_H_

#include "cuts/config.h"
#include "cuts/iccm/compiler/Scope_Visitor.h"

#include <fstream>
#include "ace/SString.h"

namespace iCCM
{
namespace TCPIP
{

/**
 * @class BMI_Visitor
 *
 * Class for generating the TCPIP Base Member Initalization code for servants
 */
class BMI_Visitor : public Scope_Visitor
{
public:
  /// Initalizing constructor.
  BMI_Visitor (std::ofstream & sfile);

  /// Destructor.
  ~BMI_Visitor (void);

  virtual int visit_consumes (AST_Consumes * node);

private:
  std::ofstream & sfile_;
  int port_counter_;
};

} // namespace iCCM
} // namespace TCPIP

#if defined (__CUTS_INLINE__)
#include "BMI_Visitor.inl"
#endif  // !defined __CUTS_INLINE__

#endif  // _ICCM_TCPIP_BMI_VISITOR_H_
