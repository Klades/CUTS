// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Template_Config_List_Parser_Grammar

//
// CUTS_Template_Config_List_Parser_Grammar
//
CUTS_INLINE
CUTS_Template_Config_List_Parser_Grammar::
CUTS_Template_Config_List_Parser_Grammar (CUTS_Template_Config_Handler * handler,
                                          const CUTS_Property_Map & overrides)
: handler_ (handler),
  overrides_ (overrides)
{

}

//
// ~CUTS_Template_Config_List_Parser_Grammar
//
CUTS_INLINE
CUTS_Template_Config_List_Parser_Grammar::
~CUTS_Template_Config_List_Parser_Grammar (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Template_Config_List_Parser

//
// CUTS_Template_Config_List_Parser
//
CUTS_INLINE
CUTS_Template_Config_List_Parser::
CUTS_Template_Config_List_Parser (CUTS_Template_Config_Handler * handler,
                                  const CUTS_Property_Map & overrides)
: grammar_ (handler, overrides)
{

}

//
// ~CUTS_Template_Config_List_Parser
//
CUTS_INLINE
CUTS_Template_Config_List_Parser::~CUTS_Template_Config_List_Parser (void)
{

}
