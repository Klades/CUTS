// -*- C++ -*-
// $Id$

//
// CUTS_Template_Config_List_Parser
//
CUTS_INLINE
CUTS_Template_Config_List_Parser::
CUTS_Template_Config_List_Parser (const ACE_CString & template_file,
                                  const CUTS_Property_Map & overrides)
: template_file_ (template_file),
  overrides_ (overrides)
{

}

//
// ~CUTS_Template_Config_List_Parser
//
CUTS_INLINE
CUTS_Template_Config_List_Parser::~CUTS_Template_Config_List_Parser (void)
{

}

