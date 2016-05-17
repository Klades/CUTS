#ifndef _CUTS_ICCM_CONTAINER_H_
#define _CUTS_ICCM_CONTAINER_H_

#include "cuts/config.h"

#include "Deployment_Handlers_export.h"

namespace iCCM
{

// Forward decl.
class Container_Strategy;

class ICCM_DEPLOYENT_HANDLERS_Export Container
{
public:
  Container (void);
  virtual ~Container (void);

  virtual Container_Strategy * get_strategy (void) const = 0;
};

}

#endif
