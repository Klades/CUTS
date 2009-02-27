// -*- C++ -*-

//=============================================================================
/**
 * @file        Unite_App.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_APP_H_
#define _CUTS_UNITE_APP_H_

#include "ace/SString.h"

/**
 * @class CUTS_Unite_App
 *
 * Main entry point for the application represented as an
 * object. This helps prevent pollution of the global namespace.
 */
class CUTS_Unite_App
{
public:
  /// Default constructor
  CUTS_Unite_App (void);

  /// Destructor
  ~CUTS_Unite_App (void);

  int run_main (int argc, char * argv []);

private:
  int parse_args (int argc, char * argv []);

  ACE_CString config_;

  ACE_CString datafile_;

  ACE_CString sandbox_;
};

#endif  // !defined _CUTS_UNITE_APP_H_
