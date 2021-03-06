// $Id$

#ifndef _CUTS_BE_CIAO_FACTORY_MANAGER_H_
#define _CUTS_BE_CIAO_FACTORY_MANAGER_H_

#include "../../../BE_Manager_Factory.h"
#include "BE_CIAO_export.h"

/**
 * @class CUTS_BE_CIAO_Manager_Factory
 */
class CUTS_BE_CIAO_Manager_Factory : public CUTS_BE_Manager_Factory
{
public:
  /// Default constructor.
  CUTS_BE_CIAO_Manager_Factory (void);

  /// Destructor.
  virtual ~CUTS_BE_CIAO_Manager_Factory (void);

  CUTS_BE_Manager * create_manager (void);

  const char * name (void) const;

  const char * description (void) const;
};

CUTS_BE_CREATE_MANAGER_FACTORY_DECLARE (CUTS_BE_CIAO_Export);

#endif  // !defined _CUTS_BE_CIAO_FACTORY_MANAGER_H_
