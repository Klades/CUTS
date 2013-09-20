// $Id:

#ifndef _ICCM_EVENT_TRAITS_H_
#define _ICCM_EVENT_TRAITS_H_

#include "Scope_Visitor.h"
#include "ace/SString.h"

#include <fstream>

namespace iCCM
{

/**
 * @class Event_Traits
 *
 * Visitor which generates Portico_ObjectClass_Traits for events
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
  virtual int visit_field (AST_Field * node);

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString scope_;
  size_t attribute_count_;
};

}

#endif  // !defined _ICCM_EVENT_TRAITS_H_