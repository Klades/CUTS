// $Id$

//=============================================================================
/**
 * @file        Executor_App_Options.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_T2M_EXECUTOR_APP_OPTIONS_H_
#define _CUTS_T2M_EXECUTOR_APP_OPTIONS_H_

#include <string>
#include "cuts/config.h"

/**
 * @class CUTS_T2M_Executor_App_Options
 */
class CUTS_T2M_Executor_App_Options
{
public:
  /// Default constructor.
  CUTS_T2M_Executor_App_Options (void);

  /// Destructor.
  ~CUTS_T2M_Executor_App_Options (void);

  bool validate (void);

  std::string project_;

  std::string filename_;

  std::string parser_;

  std::string target_;

  bool is_mga_file_;

  bool enable_auto_addons_;

  std::string run_;

  std::string run_output_;

  std::string run_focus_;
};

#if defined (__CUTS_INLINE__)
#include "Executor_App_Options.inl"
#endif

#endif