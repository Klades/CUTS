// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Open_T

CUTS_INLINE
CUTS_BE_File_Open_T <CUTS_BE_CCM::Cpp::Context>::CUTS_BE_File_Open_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_File_Open_T <CUTS_BE_CCM::Cpp::Context>::~CUTS_BE_File_Open_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Close_T

CUTS_INLINE
CUTS_BE_File_Close_T <CUTS_BE_CCM::Cpp::Context>::CUTS_BE_File_Close_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_File_Close_T <CUTS_BE_CCM::Cpp::Context>::~CUTS_BE_File_Close_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Include_File_T

CUTS_INLINE
CUTS_BE_Include_File_T <CUTS_BE_CCM::Cpp::Context>::CUTS_BE_Include_File_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Include_File_T <CUTS_BE_CCM::Cpp::Context>::~CUTS_BE_Include_File_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Prologue_T

CUTS_INLINE
CUTS_BE_Prologue_T <CUTS_BE_CCM::Cpp::Context>::CUTS_BE_Prologue_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Prologue_T <CUTS_BE_CCM::Cpp::Context>::~CUTS_BE_Prologue_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Epilogue_T

CUTS_INLINE
CUTS_BE_Epilogue_T <CUTS_BE_CCM::Cpp::Context>::CUTS_BE_Epilogue_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Epilogue_T <CUTS_BE_CCM::Cpp::Context>::~CUTS_BE_Epilogue_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_Begin_T

CUTS_INLINE
CUTS_BE_Component_Impl_Begin_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_Component_Impl_Begin_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Component_Impl_Begin_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_Component_Impl_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_End_T

CUTS_INLINE
CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_Component_Impl_End_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Component_Impl_End_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_Component_Impl_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Begin_T

CUTS_INLINE
CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_PeriodicEvent_Begin_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_PeriodicEvent_Begin_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_PeriodicEvent_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_End_T

CUTS_INLINE
CUTS_BE_PeriodicEvent_End_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_PeriodicEvent_End_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_PeriodicEvent_End_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_PeriodicEvent_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_Begin_T

CUTS_INLINE
CUTS_BE_Environment_Method_Begin_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_Environment_Method_Begin_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Environment_Method_Begin_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_Environment_Method_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_End_T

CUTS_INLINE
CUTS_BE_Environment_Method_End_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_Environment_Method_End_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Environment_Method_End_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_Environment_Method_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_Entrypoint_T

CUTS_INLINE
CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_Component_Impl_Entrypoint_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Component_Impl_Entrypoint_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_Component_Impl_Entrypoint_T (void)
{

}


///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_Begin_T

CUTS_INLINE
CUTS_BE_Attribute_Begin_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_Attribute_Begin_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_Attribute_Begin_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_Attribute_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_End_T

CUTS_INLINE
CUTS_BE_Attribute_End_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_Attribute_End_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context),
  readonly_begin_ (context),
  readonly_end_ (context)
{

}

CUTS_INLINE
CUTS_BE_Attribute_End_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_Attribute_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ReadonlyAttribute_Begin_T

CUTS_INLINE
CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_ReadonlyAttribute_Begin_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_ReadonlyAttribute_Begin_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_ReadonlyAttribute_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ReadonlyAttribute_End_T

CUTS_INLINE
CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_ReadonlyAttribute_End_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_ReadonlyAttribute_End_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_ReadonlyAttribute_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_Begin_T

CUTS_INLINE
CUTS_BE_InEventPort_Begin_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_InEventPort_Begin_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_InEventPort_Begin_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_InEventPort_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_End_T

CUTS_INLINE
CUTS_BE_InEventPort_End_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_InEventPort_End_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_InEventPort_End_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_InEventPort_End_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ProvidedRequestPort_Begin_T

CUTS_INLINE
CUTS_BE_ProvidedRequestPort_Begin_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_ProvidedRequestPort_Begin_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_ProvidedRequestPort_Begin_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_ProvidedRequestPort_Begin_T (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ProvidedRequestPort_End_T

CUTS_INLINE
CUTS_BE_ProvidedRequestPort_End_T <CUTS_BE_CCM::Cpp::Context>::
CUTS_BE_ProvidedRequestPort_End_T (CUTS_BE_CCM::Cpp::Context & context)
: visitor_type (context)
{

}

CUTS_INLINE
CUTS_BE_ProvidedRequestPort_End_T <CUTS_BE_CCM::Cpp::Context>::
~CUTS_BE_ProvidedRequestPort_End_T (void)
{

}

namespace CUTS_BE_CCM
{
//
// ~Type_System
//
CUTS_INLINE
Type_System::~Type_System (void)
{
}
}   // namespace CUTS_BE_CCM
