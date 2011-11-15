// -*- C++ -*-

//=============================================================================
/**
 * @file        Gnuplot_Presentation_Service.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_GNUPLOT_PRESENTATION_SERVICE_H_
#define _CUTS_GNUPLOT_PRESENTATION_SERVICE_H_

#include "cuts/utils/unite/Presentation_Service.h"
#include "Gnuplot_Presentation_Service_export.h"
#include "ace/SString.h"

/**
 * @class CUTS_Console_Presentation_Service
 *
 * Implementation of a UNITE presentation service that writes the results
 * to the console window. This service is statically linked into the
 * the application.
 */
class CUTS_GNUPLOT_PRESENTATION_SERVICE_Export CUTS_Gnuplot_Presentation_Service :
  public CUTS_Unite_Presentation_Service
{
public:
  /// Default constructor.
  CUTS_Gnuplot_Presentation_Service (void);

  /// Destructor
  virtual ~CUTS_Gnuplot_Presentation_Service (void);

  virtual int init (int argc, char * argv []);

  virtual int handle_result (CUTS_Dataset_Result & result);

private:
  /// Target directory for gnuplot files.
  ACE_CString output_;

  /// Flag that determines to include group titles.
  bool has_group_titles_;
};

///////////////////////////////////////////////////////////////////////////////
//

// Declare the static service
ACE_STATIC_SVC_DECLARE_EXPORT (CUTS_GNUPLOT_PRESENTATION_SERVICE,
                               CUTS_Gnuplot_Presentation_Service)

ACE_FACTORY_DECLARE (CUTS_GNUPLOT_PRESENTATION_SERVICE,
                     CUTS_Gnuplot_Presentation_Service)

#if defined (__CUTS_INLINE__)
#include "Gnuplot_Presentation_Service.inl"
#endif

#endif  // !defined _CUTS_GNUPLOT_PRESENTATION_SERVICE_H_
