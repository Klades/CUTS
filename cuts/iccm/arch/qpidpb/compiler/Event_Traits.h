// -*- C++ -*-

//=============================================================================
/**
 *  @file       Event_Traits.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _ICCM_EVENT_TRAITS_H_
#define _ICCM_EVENT_TRAITS_H_

#include "Scope_Visitor.h"
#include <fstream>
#include "ace/SString.h"

namespace iCCM
{

/**
 * @class Upcall_Event
 *
 * Main visitor that converts a DDS type model into CCM event model.
 */
class Event_Traits : public Scope_Visitor
{
public:
  /// Default constructor.
  Event_Traits (std::ofstream & hfile, std::ofstream & sfile);

  /// Destructor.
  virtual ~Event_Traits (void);

  // used methods
  virtual int visit_root (AST_Root * node);
  virtual int visit_module (AST_Module * node);
  virtual int visit_eventtype (AST_EventType * node);

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString scope_;
};

}

#endif  // !defined _ICCM_EXECUTOR_IDL_FILE_
