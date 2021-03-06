// $Id$

//=============================================================================
/**
 * @file      Manager_Factory.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CIAO_FACTORY_MANAGER_H_
#define _CUTS_BE_CIAO_FACTORY_MANAGER_H_

#include "BE_EISA_export.h"
#include "../BE_Manager_Factory.h"

/**
 * @class CUTS_BE_EISA_Manager_Factory
 */
class CUTS_BE_EISA_Manager_Factory : public CUTS_BE_Manager_Factory
{
public:
  /// Default constructor.
  CUTS_BE_EISA_Manager_Factory (void);

  /// Destructor.
  virtual ~CUTS_BE_EISA_Manager_Factory (void);

  CUTS_BE_Manager * create_manager (void);

  const char * name (void) const;

  const char * description (void) const;
};

CUTS_BE_CREATE_MANAGER_FACTORY_DECLARE (CUTS_BE_EISA_Export);

#endif  // !defined _CUTS_BE_CIAO_FACTORY_MANAGER_H_
