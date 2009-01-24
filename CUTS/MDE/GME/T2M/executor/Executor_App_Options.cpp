// $Id$

#include "Executor_App_Options.h"

#if !defined (__CUTS_INLINE__)
#include "Executor_App_Options.inl"
#endif

#include "ace/Log_Msg.h"

//
// validate
//
bool CUTS_T2M_Executor_App_Options::validate (void)
{
  //if (this->project_.empty ())
  //  ACE_ERROR_RETURN ((LM_ERROR,
  //                     "%T (%t) - %M - missing project file\n"),
  //                     false);

  //if (this->filename_.empty ())
  //  ACE_ERROR_RETURN ((LM_ERROR,
  //                     "%T (%t) - %M - missing input file\n"),
  //                     false);

  // Determine if the file is a .mga file.
  this->is_mga_file_ = this->project_.rfind (".mga") != std::string::npos;
  return true;
}
