// -*- C++ -*-

//=============================================================================
/**
 *  @file       Upcall_Event.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_UPCALL_EVENT_H_
#define _ICCM_UPCALL_EVENT_H_

#include "Scope_Visitor.h"
#include "ace/SString.h"

#include <fstream>

namespace iCCM
{

/**
 * @class Upcall_Event
 *
 * Main visitor that converts a DDS type model into CCM event model.
 */
class Upcall_Event : public Scope_Visitor
{
public:
  /// Default constructor.
  Upcall_Event (std::ofstream & hfile, std::ofstream & sfile);

  /// Destructor.
  virtual ~Upcall_Event (void);

  // used methods
  virtual int visit_eventtype (AST_EventType * node);
  virtual int visit_field (AST_Field * node);

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString upcall_event_;
};

}

#endif  // !defined _ICCM_EXECUTOR_IDL_FILE_
