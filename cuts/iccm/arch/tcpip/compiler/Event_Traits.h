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

namespace iCCM
{

/**
 * @class Event_Traits
 *
 * Main visitor that converts a TCPIP type model into CCM event model.
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
};

}

#endif  // !defined _ICCM_EVENT_TRAITS_H_
