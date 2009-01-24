// -*- C++ -*-

//=============================================================================
/**
 * @file        Executor_App.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _GME_T2M_EXECUTOR_APP_H_
#define _GME_T2M_EXECUTOR_APP_H_

#include "game/Project.h"
#include "Executor_App_Options.h"

/**
 * @class CUTS_T2M_Executor_App
 */
class CUTS_T2M_Executor_App
{
public:
  /// Default constructor.
  CUTS_T2M_Executor_App (void);

  /// Destructor.
  ~CUTS_T2M_Executor_App (void);

  int run_main (int argc, char * argv []);

private:
  int run_parser (void);

  int run (const std::string & progid);

  int parse_args (int argc, char * argv []);

  int open_gme_project (void);

  int save_gme_project (void);

  /// Print the help screen for the application.
  void print_help (void);

  /// The GME project managed by this application.
  GME::Project project_;

  CUTS_T2M_Executor_App_Options opts_;
};

#if defined (__CUTS_INLINE__)
#include "Executor_App.inl"
#endif

#endif  // !defined _GME_T2M_EXECUTOR_APP_H_
