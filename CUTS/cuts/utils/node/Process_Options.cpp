// $Id$

#include "Process_Options.h"

#if !defined (__CUTS_INLINE__)
#include "Process_Options.inl"
#endif

//
// CUTS_Process_Options
//
const CUTS_Process_Options &
CUTS_Process_Options::operator = (const CUTS_Process_Options & rhs)
{
  this->name_ = rhs.name_;
  this->exec_ = rhs.exec_;
  this->args_ = rhs.args_;
  this->cwd_ = rhs.cwd_;
  this->delay_ = rhs.delay_;
  this->stderr_ = rhs.stderr_;
  this->stdout_ = rhs.stdout_;
  this->wait_for_completion_ = rhs.wait_for_completion_;

  return *this;
}
