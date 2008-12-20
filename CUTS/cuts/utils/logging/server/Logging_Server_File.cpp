// $Id$

#include "Logging_Server_File.h"

#if !defined (__CUTS_INLINE__)
#include "Logging_Server_File.inl"
#endif

#include "XSC/utils/XML_Schema_Resolver.h"
#include "ace/Env_Value_T.h"

//
// configure
//
void CUTS_Logging_Server_File::configure (void)
{
  ACE_Env_Value <char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream schemas_dir;
  schemas_dir << CUTS_ROOT << "/etc/schemas/";

  // Configure the entity resolver.
  XSC::XML::XML_Schema_Resolver <XSC::XML::Basic_Resolver>
    resolver (XSC::XML::Basic_Resolver (schemas_dir.str ().c_str ()));

  (*this)->setEntityResolver (&resolver);

  // Discard comment nodes in the document.
  (*this)->setCreateCommentNodes (false);

  // Disable datatype normalization. The XML 1.0 attribute value
  // normalization always occurs though.
  //if ((*this).parser ()->canSetFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true))
  //  (*this).parser ()->setFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true);

  // Do not create EntityReference nodes in the DOM tree. No
  // EntityReference nodes will be created, only the nodes
  // corresponding to their fully expanded substitution text will be
  // created.
  (*this)->setCreateEntityReferenceNodes (false);

  // Perform Namespace processing.
  (*this)->setDoNamespaces (true);

  // Do not include ignorable whitespace in the DOM tree.
  (*this)->setIncludeIgnorableWhitespace (false);

  // Perform Validation
  (*this)->setValidationScheme (AbstractDOMParser::ValSchemes::Val_Auto);

  // Enable the GetParser()'s schema support.
  (*this)->setDoSchema (true);

  // Enable full schema constraint checking, including checking which
  // may be time-consuming or memory intensive. Currently, particle
  // unique attribution constraint checking and particle derivation
  // restriction checking are controlled by this option.
  (*this)->setValidationSchemaFullChecking (true);

  // The GetParser() will treat validation error as fatal and will exit.
  (*this)->setValidationConstraintFatal (false);
}
