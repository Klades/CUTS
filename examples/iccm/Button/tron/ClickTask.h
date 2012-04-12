//  $Id$

#ifndef _CLICKTASK_H_
#define _CLICKTASK_H_

#include "ace/Task.h"

namespace ButtonImpl
{
  // Forward decl
  class Button;
}

/**
 * @class ClickTask
 *
 * ACE_Task class for notifying the ButtonImpl to decide
 * what kind of click event to send to tron.
 */
class ClickTask : public ACE_Task_Base
{
public:
  // Initalizing ctor
  ClickTask (::ButtonImpl::Button * button);

  // dtor
  virtual ~ClickTask (void);

  // Activate the task
  int activate (const ACE_Time_Value & interval);

  // Deactivate the task
  int deactivate (void);

  // Service handler routine
  virtual int svc (void);

  // Handle the timeout notification
  virtual int handle_timeout (const ACE_Time_Value & current, const void * act);

private:
  // The ButtonImpl
  ::ButtonImpl::Button * button_;

  // Task active flag
  bool is_active_;

  // Timer id for the task
  long timer_id_;

  // Timeout counter
  size_t timeout_count_;
};

#endif  // !defined _CLICKTASK_H_

