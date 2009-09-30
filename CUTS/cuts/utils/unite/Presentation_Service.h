// -*- C++ -*-

//=============================================================================
/**
 * @file        Presentation_Service.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_PRESENTATION_SERVICE_H_
#define _CUTS_UNITE_PRESENTATION_SERVICE_H_

#include "ace/Service_Object.h"
#include "Unite_export.h"

// Forward decl.
class CUTS_Dataset_Result;

/**
 * @ingroup UNITE_Common
 *
 * @class CUTS_Unite_Presentation_Service
 */
class CUTS_UNITE_Export CUTS_Unite_Presentation_Service :
  public ACE_Service_Object
{
public:
  /// Default constructor.
  CUTS_Unite_Presentation_Service (void);

  /// Destructor.
  virtual ~CUTS_Unite_Presentation_Service (void);

  /**
   * Handle the evaluation of a unit test. The service is safe to
   * assume the result is at the first entry.
   *
   * @param[in]           result        Result to process
   * @retval              0             Success
   * @retval              -1            Failure
   */
  virtual int handle_result (CUTS_Dataset_Result & result);
};

#if defined (__CUTS_INLINE__)
#include "Presentation_Service.inl"
#endif

#endif  // !defined _CUTS_UNITE_PRESENTATION_SERVICE_H_
