// $Id:

#ifndef _ICCM_EVENT_OBJECTCLASS_FACTORY_H_
#define _ICCM_EVENT_OBJECTCLASS_FACTORY_H_

#include "Scope_Visitor.h"
#include "ace/SString.h"

#include <fstream>

namespace iCCM
{

/**
 * @class Event_ObjectClass_Factory
 *
 * Visitor which generates Portico_ObjectClass_Factories for events
 */
class Event_ObjectClass_Factory : public Scope_Visitor
{
public:
  /// Default constructor.
  Event_ObjectClass_Factory (std::ofstream & hfile, std::ofstream & sfile);

  /// Destructor.
  virtual ~Event_ObjectClass_Factory (void);

  // used methods
  virtual int visit_module (AST_Module * node);
  virtual int visit_eventtype (AST_EventType * node);
  virtual int visit_field (AST_Field * node);

private:
  std::ofstream & hfile_;
  std::ofstream & sfile_;
};

}

#endif  // !defined _ICCM_EVENT_OBJECTCLASS_FACTORY_H_
