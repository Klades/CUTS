// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_Config_List_Parser_Grammar_T

//
// CUTS_Config_List_Parser_Grammar_T
//
template <typename ACTOR>
CUTS_INLINE
CUTS_Config_List_Parser_Grammar_T <ACTOR>::
CUTS_Config_List_Parser_Grammar_T (ACTOR & actor)
: actor_ (actor)
{

}

//
// ~CUTS_Config_List_Parser_Grammar_T
//
template <typename ACTOR>
CUTS_INLINE
CUTS_Config_List_Parser_Grammar_T <ACTOR>::~CUTS_Config_List_Parser_Grammar_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Config_List_Parser_T

//
// CUTS_Config_List_Parser_T
//
template <typename ACTOR>
CUTS_INLINE
CUTS_Config_List_Parser_T <ACTOR>::CUTS_Config_List_Parser_T (ACTOR & actor)
: grammar_ (actor)
{

}

//
// ~CUTS_Template_Config_List_Parser
//
template <typename ACTOR>
CUTS_INLINE
CUTS_Config_List_Parser_T <ACTOR>::~CUTS_Config_List_Parser_T (void)
{

}
