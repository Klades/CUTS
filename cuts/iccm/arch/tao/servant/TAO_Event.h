//  $Id$

#ifndef _TAO_EVENT_H_
#define _TAO_EVENT_H_

#include "cuts/config.h"
#include "TAO_stub_export.h"

namespace iCCM
{
/**
 * @struct TAO_Event_Traits
 *
 * Trait class for mapping TAO events to CORBA events, and visa
 * versa.
 */
template <typename EVENT>
struct TAO_Event_Traits;

/**
 * Base class for all TAO events.  Concrete events must read
 * and write attributes as desired.
 */
class ICCM_TAO_STUB_Export TAO_Event
{
public:
  // Default ctor.
  TAO_Event (void);

  // dtor.
  virtual ~TAO_Event (void);
};

}

#if defined (__CUTS_INLINE__)
#include "TAO_Event.inl"
#endif

#endif  // !defined _TAO_EVENT_H_

