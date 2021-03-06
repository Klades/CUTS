// $Id$

#include "DDS_Domain_File.h"

#if !defined (__CUTS_INLINE__)
#include "DDS_Domain_File.inl"
#endif

#include "ace/SString.h"

namespace iCCM
{

//
// configure
//
void DDS_Domain_File::configure (void)
{
  // Get the CUTS_ROOT environment variable.
  ACE_Env_Value <const char *> CUTS_ROOT ("CUTS_ROOT", "");

  // Locate the schemas directory
  ACE_CString schemas_dir (CUTS_ROOT);
  schemas_dir += "/etc/schemas/iccm/";

  // Configure the entity resolver.
  this->br_.path (schemas_dir.c_str ());
  this->parser_->setEntityResolver (&this->resolver_);

  // Configure the parser features.
  this->parser_->setCreateCommentNodes (false);
  this->parser_->setCreateEntityReferenceNodes (false);
  this->parser_->setDoNamespaces (true);
  this->parser_->setIncludeIgnorableWhitespace (false);
  this->parser_->setValidationScheme (AbstractDOMParser::Val_Auto);
  this->parser_->setDoSchema (true);
  this->parser_->setValidationSchemaFullChecking (true);
  this->parser_->setValidationConstraintFatal (true);
}
}
