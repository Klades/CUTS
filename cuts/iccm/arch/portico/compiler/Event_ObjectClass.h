// $Id:

#ifndef _ICCM_EVENT_OBJECTCLASS_H_
#define _ICCM_EVENT_OBJECTCLASS_H_

#include "Scope_Visitor.h"
#include "ace/SString.h"

#include <fstream>

namespace iCCM
{

/**
 * @class Event_ObjectClass
 *
 * Visitor which generates Portico_ObjectClasses for events
 */
class Event_ObjectClass : public Scope_Visitor
{
public:
  /// Default constructor.
  Event_ObjectClass (std::ofstream & hfile, std::ofstream & sfile);

  /// Destructor.
  virtual ~Event_ObjectClass (void);

  // used methods
  virtual int visit_eventtype (AST_EventType * node);
  virtual int visit_field (AST_Field * node);
  virtual int visit_module (AST_Module * node);

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
  ACE_CString event_objectclass_;
  ACE_CString marshal_scope_;
};

}

#endif  // !defined _ICCM_EVENT_OBJECTCLASS_H_
