// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Open_T

CUTS_INLINE
CUTS_BE_File_Open_T <CUTS_BE_Ciao>::CUTS_BE_File_Open_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_File_Open_T <CUTS_BE_Ciao>::~CUTS_BE_File_Open_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Close_T

CUTS_INLINE
CUTS_BE_File_Close_T <CUTS_BE_Ciao>::CUTS_BE_File_Close_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_File_Close_T <CUTS_BE_Ciao>::~CUTS_BE_File_Close_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Include_File_T

CUTS_INLINE
CUTS_BE_Include_File_T <CUTS_BE_Ciao>::CUTS_BE_Include_File_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Include_File_T <CUTS_BE_Ciao>::~CUTS_BE_Include_File_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Prologue_T

CUTS_INLINE
CUTS_BE_Prologue_T <CUTS_BE_Ciao>::CUTS_BE_Prologue_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Prologue_T <CUTS_BE_Ciao>::~CUTS_BE_Prologue_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Epilogue_T

CUTS_INLINE
CUTS_BE_Epilogue_T <CUTS_BE_Ciao>::CUTS_BE_Epilogue_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Epilogue_T <CUTS_BE_Ciao>::~CUTS_BE_Epilogue_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_Begin_T

CUTS_INLINE
CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Ciao>::
CUTS_BE_Component_Impl_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Component_Impl_Begin_T <CUTS_BE_Ciao>::
~CUTS_BE_Component_Impl_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_End_T

CUTS_INLINE
CUTS_BE_Component_Impl_End_T <CUTS_BE_Ciao>::
CUTS_BE_Component_Impl_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Component_Impl_End_T <CUTS_BE_Ciao>::
~CUTS_BE_Component_Impl_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Begin_T

CUTS_INLINE
CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Ciao>::
CUTS_BE_PeriodicEvent_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_Ciao>::
~CUTS_BE_PeriodicEvent_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_End_T

CUTS_INLINE
CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Ciao>::
CUTS_BE_PeriodicEvent_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_PeriodicEvent_End_T <CUTS_BE_Ciao>::
~CUTS_BE_PeriodicEvent_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_Begin_T

CUTS_INLINE
CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Ciao>::
CUTS_BE_Environment_Method_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Environment_Method_Begin_T <CUTS_BE_Ciao>::
~CUTS_BE_Environment_Method_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_End_T

CUTS_INLINE
CUTS_BE_Environment_Method_End_T <CUTS_BE_Ciao>::
CUTS_BE_Environment_Method_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Environment_Method_End_T <CUTS_BE_Ciao>::
~CUTS_BE_Environment_Method_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_Entrypoint_T

CUTS_INLINE
CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_Ciao>::
CUTS_BE_Component_Impl_Entrypoint_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_Ciao>::
~CUTS_BE_Component_Impl_Entrypoint_T (void)
{

}


///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_Begin_T

CUTS_INLINE
CUTS_BE_Attribute_Begin_T <CUTS_BE_Ciao>::
CUTS_BE_Attribute_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Attribute_Begin_T <CUTS_BE_Ciao>::
~CUTS_BE_Attribute_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_End_T

CUTS_INLINE
CUTS_BE_Attribute_End_T <CUTS_BE_Ciao>::
CUTS_BE_Attribute_End_T (CUTS_BE_Ciao & context)
: visitor_type (context),
  readonly_begin_ (context),
  readonly_end_ (context)
{

}

CUTS_INLINE
CUTS_BE_Attribute_End_T <CUTS_BE_Ciao>::
~CUTS_BE_Attribute_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ReadonlyAttribute_Begin_T

CUTS_INLINE
CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Ciao>::
CUTS_BE_ReadonlyAttribute_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_Ciao>::
~CUTS_BE_ReadonlyAttribute_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ReadonlyAttribute_End_T

CUTS_INLINE
CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Ciao>::
CUTS_BE_ReadonlyAttribute_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_Ciao>::
~CUTS_BE_ReadonlyAttribute_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_Begin_T

CUTS_INLINE
CUTS_BE_InEventPort_Begin_T <CUTS_BE_Ciao>::
CUTS_BE_InEventPort_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_InEventPort_Begin_T <CUTS_BE_Ciao>::
~CUTS_BE_InEventPort_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_End_T

CUTS_INLINE
CUTS_BE_InEventPort_End_T <CUTS_BE_Ciao>::
CUTS_BE_InEventPort_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_InEventPort_End_T <CUTS_BE_Ciao>::
~CUTS_BE_InEventPort_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ProvidedRequestPort_Begin_T

CUTS_INLINE
CUTS_BE_ProvidedRequestPort_Begin_T <CUTS_BE_Ciao>::
CUTS_BE_ProvidedRequestPort_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_ProvidedRequestPort_Begin_T <CUTS_BE_Ciao>::
~CUTS_BE_ProvidedRequestPort_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ProvidedRequestPort_End_T

CUTS_INLINE
CUTS_BE_ProvidedRequestPort_End_T <CUTS_BE_Ciao>::
CUTS_BE_ProvidedRequestPort_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_ProvidedRequestPort_End_T <CUTS_BE_Ciao>::
~CUTS_BE_ProvidedRequestPort_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// workspace generators

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Workspace_File_Open_T

CUTS_INLINE
CUTS_BE_Workspace_File_Open_T <CUTS_BE_Ciao>::
CUTS_BE_Workspace_File_Open_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Workspace_File_Open_T <CUTS_BE_Ciao>::
~CUTS_BE_Workspace_File_Open_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Workspace_Begin_T

CUTS_INLINE
CUTS_BE_Workspace_Begin_T <CUTS_BE_Ciao>::
CUTS_BE_Workspace_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Workspace_Begin_T <CUTS_BE_Ciao>::
~CUTS_BE_Workspace_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Workspace_Project_Include_T <CUTS_BE_IDL_Node>

CUTS_INLINE
CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
CUTS_BE_Workspace_Project_Include_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
~CUTS_BE_Workspace_Project_Include_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Impl_Node>

CUTS_INLINE
CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
CUTS_BE_Workspace_Project_Include_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Workspace_Project_Include_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
~CUTS_BE_Workspace_Project_Include_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Workspace_End_T

CUTS_INLINE
CUTS_BE_Workspace_End_T <CUTS_BE_Ciao>::
CUTS_BE_Workspace_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Workspace_End_T <CUTS_BE_Ciao>::
~CUTS_BE_Workspace_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Workspace_File_Close_T

CUTS_INLINE
CUTS_BE_Workspace_File_Close_T <CUTS_BE_Ciao>::
CUTS_BE_Workspace_File_Close_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Workspace_File_Close_T <CUTS_BE_Ciao>::
~CUTS_BE_Workspace_File_Close_T (void)
{

}


///////////////////////////////////////////////////////////////////////////////
// project generators [CUTS_BE_Impl_Node]

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Open_T

CUTS_INLINE
CUTS_BE_Project_File_Open_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
CUTS_BE_Project_File_Open_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_File_Open_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
~CUTS_BE_Project_File_Open_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Begin_T

CUTS_INLINE
CUTS_BE_Project_File_Begin_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
CUTS_BE_Project_File_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_File_Begin_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
~CUTS_BE_Project_File_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_Write_T

CUTS_INLINE
CUTS_BE_Project_Write_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
CUTS_BE_Project_Write_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_Write_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
~CUTS_BE_Project_Write_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_End_T

CUTS_INLINE
CUTS_BE_Project_File_End_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
CUTS_BE_Project_File_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_File_End_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
~CUTS_BE_Project_File_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Close_T

CUTS_INLINE
CUTS_BE_Project_File_Close_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
CUTS_BE_Project_File_Close_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_File_Close_T <CUTS_BE_Ciao, CUTS_BE_Impl_Node>::
~CUTS_BE_Project_File_Close_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// project generators [CUTS_BE_IDL_Node]

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Open_T

CUTS_INLINE
CUTS_BE_Project_File_Open_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
CUTS_BE_Project_File_Open_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_File_Open_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
~CUTS_BE_Project_File_Open_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Begin_T

CUTS_INLINE
CUTS_BE_Project_File_Begin_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
CUTS_BE_Project_File_Begin_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_File_Begin_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
~CUTS_BE_Project_File_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_Write_T

CUTS_INLINE
CUTS_BE_Project_Write_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
CUTS_BE_Project_Write_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_Write_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
~CUTS_BE_Project_Write_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_End_T

CUTS_INLINE
CUTS_BE_Project_File_End_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
CUTS_BE_Project_File_End_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_File_End_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
~CUTS_BE_Project_File_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Project_File_Close_T

CUTS_INLINE
CUTS_BE_Project_File_Close_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
CUTS_BE_Project_File_Close_T (CUTS_BE_Ciao & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Project_File_Close_T <CUTS_BE_Ciao, CUTS_BE_IDL_Node>::
~CUTS_BE_Project_File_Close_T (void)
{

}
