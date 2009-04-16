// -*-

//=============================================================================
/**
 * @file      Calibrate_App.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CALIBRATE_APP_H_
#define _CUTS_CALIBRATE_APP_H_

#include "cuts/config.h"
#include "Calibrate_Options.h"

/**
 * @class CUTS_Calibrate_App
 *
 * Application object for the calibration executable.
 */
class CUTS_Calibrate_App
{
public:
  /// Default constructor.
  CUTS_Calibrate_App (void);

  /// Destructor.
  virtual ~CUTS_Calibrate_App (void);

  int run_main (int argc, char * argv []);

private:
  /// Helper method to parse command-line options.
  int parse_args (int argc, char * argv []);

  /// Options for the calibration application
  CUTS_Calibrate_Options opts_;
};

#if defined (__CUTS_INLINE__)
#include "Calibrate_App.inl"
#endif

#endif  // !defined _CUTS_CALIBRATE_APP_H_
