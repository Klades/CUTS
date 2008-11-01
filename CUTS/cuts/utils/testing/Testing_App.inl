// $Id$

//
// CUTS_Testing_App
//
CUTS_INLINE
CUTS_Testing_App::~CUTS_Testing_App (void)
{
  this->svc_config_.close ();
}

//
// options
//
CUTS_INLINE
const CUTS_Testing_Options & CUTS_Testing_App::options (void) const
{
  return this->opts_;
}
