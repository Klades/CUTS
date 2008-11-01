// $Id$

#include "Test_Configuration_File.h"

#if !defined (__CUTS_INLINE__)
#include "Test_Configuration_File.inl"
#endif

#include "XSCRT/utils/Buffer_Writer_T.h"
#include "XSCRT/utils/Xml_Schema_Resolver_T.h"
#include "ace/Env_Value_T.h"

//
// configure
//
void CUTS_Test_Configuration_File::configure (void)
{
  ACE_Env_Value <char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream schemas_dir;
  schemas_dir << CUTS_ROOT << "/etc/schemas/";

  // Configure the entity resolver.
  this->parser ()->setEntityResolver (
    XSCRT::utils::xml_schema_resolver (
    XSCRT::utils::Basic_Resolver_T <char> (schemas_dir.str ().c_str ())));

  // Discard comment nodes in the document.
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgDOMComments, false))
    this->parser ()->setFeature (xercesc::XMLUni::fgDOMComments, false);

  // Disable datatype normalization. The XML 1.0 attribute value
  // normalization always occurs though.
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true))
    this->parser ()->setFeature (xercesc::XMLUni::fgDOMDatatypeNormalization, true);

  // Do not create EntityReference nodes in the DOM tree. No
  // EntityReference nodes will be created, only the nodes
  // corresponding to their fully expanded substitution text will be
  // created.
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgDOMEntities, false))
    this->parser ()->setFeature (xercesc::XMLUni::fgDOMEntities, false);

  // Perform Namespace processing.
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgDOMNamespaces, true))
    this->parser ()->setFeature (xercesc::XMLUni::fgDOMNamespaces, true);

  // Do not include ignorable whitespace in the DOM tree.
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false))
    this->parser ()->setFeature (xercesc::XMLUni::fgDOMWhitespaceInElementContent, false);

  // Perform Validation
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgDOMValidation, true))
    this->parser ()->setFeature (xercesc::XMLUni::fgDOMValidation, true);

  // Enable the GetParser()'s schema support.
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchema, true))
    this->parser ()->setFeature (xercesc::XMLUni::fgXercesSchema, true);

  // Enable full schema constraint checking, including checking which
  // may be time-consuming or memory intensive. Currently, particle
  // unique attribution constraint checking and particle derivation
  // restriction checking are controlled by this option.
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true))
    this->parser ()->setFeature (xercesc::XMLUni::fgXercesSchemaFullChecking, true);

  // The GetParser() will treat validation error as fatal and will exit.
  if (this->parser ()->canSetFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, true))
    this->parser ()->setFeature (xercesc::XMLUni::fgXercesValidationErrorAsFatal, true);
}
