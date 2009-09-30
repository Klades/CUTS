// -*- C++ -*-

//=============================================================================
/**
 * @file        Presentation_Service_Manager.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_PRESENTATION_SERVICE_MANAGER_H_
#define _CUTS_UNITE_PRESENTATION_SERVICE_MANAGER_H_

#include "ace/Service_Gestalt.h"
#include "Unite_export.h"

// Forward decl.
class CUTS_Dataset_Result;

/**
 * @ingroup UNITE_Common
 *
 * @class CUTS_Unite_Presentation_Service_Manager
 */
class CUTS_UNITE_Export CUTS_Unite_Presentation_Service_Manager :
  public ACE_Service_Gestalt
{
public:
  /// Default constructor
  CUTS_Unite_Presentation_Service_Manager (void);

  /// Destructor
  virtual ~CUTS_Unite_Presentation_Service_Manager (void);

  int load_service (const char * id,
                    const char * location,
                    const char * classname,
                    const char * params);

  int handle_result (CUTS_Dataset_Result & result);
};

#if defined (__CUTS_INLINE__)
#include "Presentation_Service_Manager.inl"
#endif

#endif  // !defined _CUTS_UNITE_PRESENTATION_SERVICE_MANAGER_H_
