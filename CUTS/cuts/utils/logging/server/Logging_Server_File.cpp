// $Id$

#include "Logging_Server_File.h"

#if !defined (__CUTS_INLINE__)
#include "Logging_Server_File.inl"
#endif

#include "ace/Env_Value_T.h"

//
// configure
//
void CUTS_Logging_Server_File::configure (void)
{
  ACE_Env_Value <char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream schemas_dir;
  schemas_dir << CUTS_ROOT << "/etc/schemas/";
  this->br_.path (schemas_dir.str ().c_str ());

  // Configure the entity resolver.
  (*this)->setEntityResolver (&this->resolver_);

  // Set the default features.
  (*this)->setCreateCommentNodes (false);
  (*this)->setCreateEntityReferenceNodes (false);
  (*this)->setDoNamespaces (true);
  (*this)->setIncludeIgnorableWhitespace (false);
  (*this)->setValidationScheme (AbstractDOMParser::ValSchemes::Val_Auto);
  (*this)->setDoSchema (true);
  (*this)->setValidationSchemaFullChecking (true);
  (*this)->setValidationConstraintFatal (false);
}
