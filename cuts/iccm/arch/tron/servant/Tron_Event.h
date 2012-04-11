//  $Id$

#ifndef _TRON_EVENT_H_
#define _TRON_EVENT_H_

#include "tron/adapter.h"
#include "cuts/config.h"

namespace iCCM
{
/**
 * @struct Tron_Event_Traits
 *
 * Trait class for mapping Tron events to CORBA events, and visa
 * versa.
 */
template <typename EVENT>
struct Tron_Event_Traits;

/**
 * Base class for all Tron events.  Concrete events must read
 * and write attributes as desired.
 */
class Tron_Event
{
public:
  // Default ctor.
  Tron_Event (void);

  // Initalizing ctor.
  Tron_Event (const uint16_t size, const int32_t data[]);

  // dtor.
  virtual ~Tron_Event (void);

  // Read attributes from tron
  virtual void __tron_read_attributes (const uint16_t size, const int32_t data[]) = 0;

  // Write attributes from tron
  virtual void __tron_write_attributes (Reporter * reporter, const int32_t channel) = 0;
};

}

#if defined (__CUTS_INLINE__)
#include "Tron_Event.inl"
#endif

#endif  // !defined _TRON_EVENT_H_

