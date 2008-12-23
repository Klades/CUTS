// $Id$

#include "Test_Configuration_File.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Configuration_File.inl"
#endif

#include "Test_export.h"
#include "ace/Env_Value_T.h"

//
// configure
//
void CUTS_Test_Configuration_File::configure (void)
{
  CUTS_TEST_TRACE ("CUTS_Test_Configuration_File::configure (void)");

  ACE_Env_Value <char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream schemas_dir;
  schemas_dir << CUTS_ROOT << "/etc/schemas/";
  this->br_.path (schemas_dir.str ().c_str ());

  // Configure the entity resolver.
  (*this)->setEntityResolver (&this->resolver_);
  (*this)->setCreateCommentNodes (false);
  (*this)->setCreateEntityReferenceNodes (false);
  (*this)->setDoNamespaces (true);
  (*this)->setIncludeIgnorableWhitespace (false);
  (*this)->setValidationScheme (AbstractDOMParser::Val_Auto);
  (*this)->setDoSchema (true);
  (*this)->setValidationSchemaFullChecking (true);
  (*this)->setValidationConstraintFatal (false);
}
