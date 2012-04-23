//  $Id$

#ifndef _TRON_CONSUMER_LIST_H_
#define _TRON_CONSUMER_LIST_H_

#include "cuts/config.h"
#include "tron/adapter.h"
#include <list>

namespace iCCM
{
  // Forward decl
  class Tron_EventConsumer;
}

/**
 * @class Tron_Consumer_List
 *
 * Object for managing the construction of Tron_Events from perform_impl
 * and sending the events to the proper consumers.
 */
class Tron_Consumer_List
{
public:
  // Default ctor
  Tron_Consumer_List (void){ };

  // Dtor
  virtual ~Tron_Consumer_List (void){ };

  // Add a consumer
  virtual void add (::iCCM::Tron_EventConsumer * consumer) = 0;

  // Push the event to the consumers
  virtual void push_event (uint16_t size, const int32_t data[]) = 0;
};

#endif  // !defined _TRON_CONSUMER_LIST_H_
