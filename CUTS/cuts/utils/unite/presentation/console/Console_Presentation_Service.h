// -*- C++ -*-

//=============================================================================
/**
 * @file        Console_Presentation_Service.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CONSOLE_PRESENTATION_SERVICE_H_
#define _CUTS_CONSOLE_PRESENTATION_SERVICE_H_

#include "cuts/utils/unite/Presentation_Service.h"
#include "Console_Presentation_Service_export.h"

/**
 * @class CUTS_Console_Presentation_Service
 *
 * Implementation of a UNITE presentation service that writes the results
 * to the console window. This service is statically linked into the
 * the application.
 */
class CUTS_CONSOLE_PRESENTATION_SERVICE_Export CUTS_Console_Presentation_Service :
  public CUTS_Unite_Presentation_Service
{
public:
  /// Default constructor.
  CUTS_Console_Presentation_Service (void);

  /// Destructor
  virtual ~CUTS_Console_Presentation_Service (void);

  virtual int handle_result (CUTS_Dataset_Result & result);
};

///////////////////////////////////////////////////////////////////////////////
//

ACE_FACTORY_DECLARE (CUTS_CONSOLE_PRESENTATION_SERVICE,
                     CUTS_Console_Presentation_Service)

// Declare the static service
ACE_STATIC_SVC_DECLARE_EXPORT (CUTS_CONSOLE_PRESENTATION_SERVICE,
                               CUTS_Console_Presentation_Service)

#if defined (__CUTS_INLINE__)
#include "Console_Presentation_Service.inl"
#endif

#endif  // !defined _CUTS_CONSOLE_PRESENTATION_SERVICE_H_
