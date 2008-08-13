// -*- C++ -*-

//=============================================================================
/**
 * @file        XML_Manager_Factory.h
 *
 * Defines the manager factory for XML
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_XML_MANAGER_FACTORY_H_
#define _CUTS_BE_XML_MANAGER_FACTORY_H_

#include "CAPI_export.h"
#include "../BE_Manager_Factory.h"

//=============================================================================
/**
 * @class CUTS_BE_CAPI_Manager_Factory
 */
//=============================================================================

class CUTS_BE_CAPI_Manager_Factory :
  public CUTS_BE_Manager_Factory
{
public:
  CUTS_BE_CAPI_Manager_Factory (void);

  virtual ~CUTS_BE_CAPI_Manager_Factory (void);

  CUTS_BE_Manager * create_manager (void);

  const char * name (void) const;

  const char * description (void) const;
};

CUTS_BE_CREATE_MANAGER_FACTORY_DECLARE (CUTS_BE_CAPI_Export);

#endif  // !defined _CUTS_BE_XML_MANAGER_FACTORY_H_
