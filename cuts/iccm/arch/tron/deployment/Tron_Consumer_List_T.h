//  $Id$

#ifndef _TRON_CONSUMER_LIST_T_H_
#define _TRON_CONSUMER_LIST_T_H_

#include "Tron_Consumer_List.h"

/**
 * @class Tron_Consumer_List_T
 *
 * Concrete Tron_Consumer_List which creates the appropriate
 * Tron_Event type
 */
template <typename T>
class Tron_Consumer_List_T : public Tron_Consumer_List
{
public:
  // Default ctor
  Tron_Consumer_List_T (void);

  // Dtor
  virtual ~Tron_Consumer_List_T (void);

  // Create and push event T to the consumers
  virtual void push_event (uint16_t size, const int32_t data[]);

  // Add a consumer
  virtual void add (::iCCM::Tron_EventConsumer * consumer);

private:
  // The consumers
  std::list < ::iCCM::Tron_EventConsumer * > consumers_;
};

#include "Tron_Consumer_List_T.cpp"

#endif  // !defined _TRON_CONSUMER_LIST_T_H_
