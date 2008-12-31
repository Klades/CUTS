// $Id$

#include "Node_File_Reader.h"

#if !defined (__CUTS_INLINE__)
#include "Node_File_Reader.inl"
#endif

#include "ace/SString.h"

//
// CUTS_Node_File_Reader
//
CUTS_Node_File_Reader::CUTS_Node_File_Reader (void)
: reader_type (&CUTS::reader::node),
  resolver_ (br_)
{
  // Get the CUTS_ROOT environment variable value.
  ACE_Env_Value <const char *> CUTS_ROOT ("CUTS_ROOT", "");

  std::ostringstream cuts_schema;
  cuts_schema << CUTS_ROOT << "/etc/schemas/";
  this->br_.path (cuts_schema.str ().c_str ());

  // Configure the entity resolver.
  this->parser_->setEntityResolver (&this->resolver_);
  this->parser_->setCreateCommentNodes (false);
  this->parser_->setCreateEntityReferenceNodes (false);
  this->parser_->setDoNamespaces (true);
  this->parser_->setIncludeIgnorableWhitespace (false);
  this->parser_->setValidationScheme (AbstractDOMParser::Val_Auto);
  this->parser_->setDoSchema (true);
  this->parser_->setValidationSchemaFullChecking (true);
  this->parser_->setValidationConstraintFatal (false);
}

//
// load
//
bool CUTS_Node_File_Reader::load (const ACE_CString & filename)
{
  // First, read the configuration file.
  if (!reader_type::read (filename.c_str ()))
    return false;

  // Convert the XML document into its object format.
  *this >>= this->config_;
  return true;
}
