// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Initialize_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Initialize_T <CONTEXT>::CUTS_BE_Initialize_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Initialize_T <CONTEXT>::~CUTS_BE_Initialize_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Initialize_T <CONTEXT>::generate (const PICML::RootFolder_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Finalize_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Finalize_T <CONTEXT>::CUTS_BE_Finalize_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Finalize_T <CONTEXT>::~CUTS_BE_Finalize_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Finalize_T <CONTEXT>::generate (const PICML::RootFolder_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Open_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_File_Open_T <CONTEXT>::CUTS_BE_File_Open_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_File_Open_T <CONTEXT>::~CUTS_BE_File_Open_T (void)
{

}

template <typename CONTEXT>
void CUTS_BE_File_Open_T <CONTEXT>::
generate (const PICML::ComponentImplementationContainer_in,
          const PICML::MonolithicImplementation_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_File_Close_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_File_Close_T <CONTEXT>::
CUTS_BE_File_Close_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_File_Close_T <CONTEXT>::~CUTS_BE_File_Close_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_File_Close_T <CONTEXT>::
generate (const PICML::ComponentImplementationContainer_in,
          const PICML::MonolithicImplementation_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Prologue_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Prologue_T <CONTEXT>::CUTS_BE_Prologue_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Prologue_T <CONTEXT>::~CUTS_BE_Prologue_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Prologue_T <CONTEXT>::
generate (const PICML::ComponentImplementationContainer_in,
          const PICML::MonolithicImplementation_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Epilogue_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Epilogue_T <CONTEXT>::CUTS_BE_Epilogue_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Epilogue_T <CONTEXT>::~CUTS_BE_Epilogue_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Epilogue_T <CONTEXT>::
generate (const PICML::ComponentImplementationContainer_in,
          const PICML::MonolithicImplementation_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Include_File_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Include_File_T <CONTEXT>::
CUTS_BE_Include_File_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Include_File_T <CONTEXT>::~CUTS_BE_Include_File_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Include_File_T <CONTEXT>::
generate (const std::string &)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Component_Impl_Begin_T <CONTEXT>::
CUTS_BE_Component_Impl_Begin_T (CONTEXT & )

{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Component_Impl_Begin_T <CONTEXT>::
~CUTS_BE_Component_Impl_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Component_Impl_Begin_T <CONTEXT>::
generate (const PICML::MonolithicImplementation_in,
          const PICML::Component_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Component_Impl_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Component_Impl_End_T <CONTEXT>::
CUTS_BE_Component_Impl_End_T (CONTEXT & )

{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Component_Impl_End_T <CONTEXT>::
~CUTS_BE_Component_Impl_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Component_Impl_End_T <CONTEXT>::
generate (const PICML::MonolithicImplementation_in,
          const PICML::Component_in)
{

}


///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Environment_Begin_T <CONTEXT>::
CUTS_BE_Environment_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Environment_Begin_T <CONTEXT>::
~CUTS_BE_Environment_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Environment_Begin_T <CONTEXT>::
generate (const PICML::Component_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Environment_Method_Begin_T <CONTEXT>::
CUTS_BE_Environment_Method_Begin_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Environment_Method_Begin_T <CONTEXT>::
~CUTS_BE_Environment_Method_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Environment_Method_Begin_T <CONTEXT>::
generate (const PICML::MultiInputAction_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_Method_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Environment_Method_End_T <CONTEXT>::
CUTS_BE_Environment_Method_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Environment_Method_End_T <CONTEXT>::
~CUTS_BE_Environment_Method_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Environment_Method_End_T <CONTEXT>::
generate (const PICML::MultiInputAction_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Environment_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Environment_End_T <CONTEXT>::
CUTS_BE_Environment_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Environment_End_T <CONTEXT>::~CUTS_BE_Environment_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Environment_End_T <CONTEXT>::generate (const PICML::Component_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Attribute_Begin_T <CONTEXT>::
CUTS_BE_Attribute_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Attribute_Begin_T <CONTEXT>::
~CUTS_BE_Attribute_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Attribute_Begin_T <CONTEXT>::
generate (const PICML::Attribute_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Attribute_End_T <CONTEXT>::
CUTS_BE_Attribute_End_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Attribute_End_T <CONTEXT>::
~CUTS_BE_Attribute_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Attribute_End_T <CONTEXT>::
generate (const PICML::Attribute_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ReadonlyAttribute_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ReadonlyAttribute_Begin_T <CONTEXT>::
CUTS_BE_ReadonlyAttribute_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ReadonlyAttribute_Begin_T <CONTEXT>::
~CUTS_BE_ReadonlyAttribute_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_ReadonlyAttribute_Begin_T <CONTEXT>::
generate (const PICML::ReadonlyAttribute_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ReadonlyAttribute_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ReadonlyAttribute_End_T <CONTEXT>::
CUTS_BE_ReadonlyAttribute_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ReadonlyAttribute_End_T <CONTEXT>::
~CUTS_BE_ReadonlyAttribute_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_ReadonlyAttribute_End_T <CONTEXT>::
generate (const PICML::ReadonlyAttribute_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variables_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Variables_Begin_T <CONTEXT>::
CUTS_BE_Variables_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Variables_Begin_T <CONTEXT>::
~CUTS_BE_Variables_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Variables_Begin_T <CONTEXT>::
generate (const PICML::Component_in )
{

}


///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variables_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Variables_End_T <CONTEXT>::
CUTS_BE_Variables_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Variables_End_T <CONTEXT>::~CUTS_BE_Variables_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Variables_End_T <CONTEXT>::
generate (const PICML::Component_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Variable_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Variable_T <CONTEXT>::
CUTS_BE_Variable_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Variable_T <CONTEXT>::~CUTS_BE_Variable_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Variable_T <CONTEXT>::generate (const PICML::Variable_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Variable_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_PeriodicEvent_Variable_T <CONTEXT>::
CUTS_BE_PeriodicEvent_Variable_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_PeriodicEvent_Variable_T <CONTEXT>::~CUTS_BE_PeriodicEvent_Variable_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_PeriodicEvent_Variable_T <CONTEXT>::
generate (const PICML::PeriodicEvent_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ApplicationTask_Variable_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ApplicationTask_Variable_T <CONTEXT>::
CUTS_BE_ApplicationTask_Variable_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ApplicationTask_Variable_T <CONTEXT>::~CUTS_BE_ApplicationTask_Variable_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_ApplicationTask_Variable_T <CONTEXT>::
generate (const PICML::ApplicationTask_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Attribute_Variable_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Attribute_Variable_T <CONTEXT>::
CUTS_BE_Attribute_Variable_T (CONTEXT & context)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Attribute_Variable_T <CONTEXT>::~CUTS_BE_Attribute_Variable_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Attribute_Variable_T <CONTEXT>::
generate (const PICML::ReadonlyAttribute_in attr)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Worker_Variable_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Worker_Variable_T <CONTEXT>::
CUTS_BE_Worker_Variable_T (CONTEXT & context)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Worker_Variable_T <CONTEXT>::~CUTS_BE_Worker_Variable_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Worker_Variable_T <CONTEXT>::
generate (const PICML::WorkerType_in, const PICML::Worker_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Component_Impl_Entrypoint_T <CONTEXT>::
CUTS_BE_Component_Impl_Entrypoint_T (CONTEXT & context)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Component_Impl_Entrypoint_T <CONTEXT>::~CUTS_BE_Component_Impl_Entrypoint_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Component_Impl_Entrypoint_T <CONTEXT>::
generate (const PICML::MonolithicImplementation_in ,
          const PICML::ComponentImplementationArtifact_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_InEventPort_Begin_T <CONTEXT>::
CUTS_BE_InEventPort_Begin_T (CONTEXT & context)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_InEventPort_Begin_T <CONTEXT>::~CUTS_BE_InEventPort_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_InEventPort_Begin_T <CONTEXT>::
generate (const PICML::InEventPort_in ,
          GAME::Mga::Collection_T <PICML::Property> & )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_InEventPort_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_InEventPort_End_T <CONTEXT>::
CUTS_BE_InEventPort_End_T (CONTEXT & context)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_InEventPort_End_T <CONTEXT>::~CUTS_BE_InEventPort_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_InEventPort_End_T <CONTEXT>::
generate (const PICML::InEventPort_in ,
          GAME::Mga::Collection_T <PICML::Property> & )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_PeriodicEvent_Begin_T <CONTEXT>::
CUTS_BE_PeriodicEvent_Begin_T (CONTEXT & context)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_PeriodicEvent_Begin_T <CONTEXT>::
~CUTS_BE_PeriodicEvent_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_PeriodicEvent_Begin_T <CONTEXT>::
generate (const PICML::PeriodicEvent_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_PeriodicEvent_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_PeriodicEvent_End_T <CONTEXT>::
CUTS_BE_PeriodicEvent_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_PeriodicEvent_End_T <CONTEXT>::
~CUTS_BE_PeriodicEvent_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_PeriodicEvent_End_T <CONTEXT>::
generate (const PICML::PeriodicEvent_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ApplicationTask_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ApplicationTask_Begin_T <CONTEXT>::
CUTS_BE_ApplicationTask_Begin_T (CONTEXT & context)
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ApplicationTask_Begin_T <CONTEXT>::
~CUTS_BE_ApplicationTask_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_ApplicationTask_Begin_T <CONTEXT>::
generate (const PICML::ApplicationTask_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ApplicationTask_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ApplicationTask_End_T <CONTEXT>::
CUTS_BE_ApplicationTask_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ApplicationTask_End_T <CONTEXT>::
~CUTS_BE_ApplicationTask_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_ApplicationTask_End_T <CONTEXT>::
generate (const PICML::ApplicationTask_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ProvidedRequestPort_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ProvidedRequestPort_Begin_T <CONTEXT>::
CUTS_BE_ProvidedRequestPort_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ProvidedRequestPort_Begin_T <CONTEXT>::
~CUTS_BE_ProvidedRequestPort_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_ProvidedRequestPort_Begin_T <CONTEXT>::
generate (const PICML::ProvidedRequestPort_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_ProvidedRequestPort_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ProvidedRequestPort_End_T <CONTEXT>::
CUTS_BE_ProvidedRequestPort_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_ProvidedRequestPort_End_T <CONTEXT>::
~CUTS_BE_ProvidedRequestPort_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_ProvidedRequestPort_End_T <CONTEXT>::
generate (const PICML::ProvidedRequestPort_in )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Postcondition_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Postcondition_T <CONTEXT>::
CUTS_BE_Postcondition_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Postcondition_T <CONTEXT>::~CUTS_BE_Postcondition_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Postcondition_T <CONTEXT>::generate (const std::string & )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Precondition_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Precondition_T <CONTEXT>::
CUTS_BE_Precondition_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Precondition_T <CONTEXT>::~CUTS_BE_Precondition_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Precondition_T <CONTEXT>::generate (const std::string & )
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branches_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branches_Begin_T <CONTEXT>::
CUTS_BE_Branches_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branches_Begin_T <CONTEXT>::~CUTS_BE_Branches_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Branches_Begin_T <CONTEXT>::generate (size_t)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_Begin_T <CONTEXT>::
CUTS_BE_Branch_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_Begin_T <CONTEXT>::~CUTS_BE_Branch_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Branch_Begin_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_End_T <CONTEXT>::
CUTS_BE_Branch_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_End_T <CONTEXT>::~CUTS_BE_Branch_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Branch_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_Condition_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_Condition_Begin_T <CONTEXT>::
CUTS_BE_Branch_Condition_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_Condition_Begin_T <CONTEXT>::~CUTS_BE_Branch_Condition_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Branch_Condition_Begin_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_Condition_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_Condition_End_T <CONTEXT>::
CUTS_BE_Branch_Condition_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_Condition_End_T <CONTEXT>::~CUTS_BE_Branch_Condition_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Branch_Condition_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branch_No_Condition_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_No_Condition_T <CONTEXT>::
CUTS_BE_Branch_No_Condition_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branch_No_Condition_T <CONTEXT>::~CUTS_BE_Branch_No_Condition_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Branch_No_Condition_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Branches_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branches_End_T <CONTEXT>::
CUTS_BE_Branches_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Branches_End_T <CONTEXT>::~CUTS_BE_Branches_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Branches_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Do_While_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Do_While_Begin_T <CONTEXT>::
CUTS_BE_Do_While_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Do_While_Begin_T <CONTEXT>::~CUTS_BE_Do_While_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Do_While_Begin_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Do_While_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Do_While_End_T <CONTEXT>::
CUTS_BE_Do_While_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Do_While_End_T <CONTEXT>::~CUTS_BE_Do_While_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Do_While_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Do_While_Condition_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Do_While_Condition_Begin_T <CONTEXT>::
CUTS_BE_Do_While_Condition_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Do_While_Condition_Begin_T <CONTEXT>::~CUTS_BE_Do_While_Condition_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Do_While_Condition_Begin_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Do_While_Condition_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Do_While_Condition_End_T <CONTEXT>::
CUTS_BE_Do_While_Condition_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Do_While_Condition_End_T <CONTEXT>::~CUTS_BE_Do_While_Condition_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Do_While_Condition_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_While_Condition_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_While_Condition_Begin_T <CONTEXT>::
CUTS_BE_While_Condition_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_While_Condition_Begin_T <CONTEXT>::~CUTS_BE_While_Condition_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_While_Condition_Begin_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_While_Condition_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_While_Condition_End_T <CONTEXT>::
CUTS_BE_While_Condition_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_While_Condition_End_T <CONTEXT>::~CUTS_BE_While_Condition_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_While_Condition_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_While_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_While_Begin_T <CONTEXT>::
CUTS_BE_While_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_While_Begin_T <CONTEXT>::~CUTS_BE_While_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_While_Begin_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_While_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_While_End_T <CONTEXT>::
CUTS_BE_While_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_While_End_T <CONTEXT>::~CUTS_BE_While_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_While_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_For_Condition_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_Condition_Begin_T <CONTEXT>::
CUTS_BE_For_Condition_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_Condition_Begin_T <CONTEXT>::~CUTS_BE_For_Condition_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_For_Condition_Begin_T <CONTEXT>::generate (void)
{

}

//////////////////////////////////////////////////////////////////////////////
// CUTS_BE_For_Condition_Delimiter_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_Condition_Delimiter_T <CONTEXT>::
CUTS_BE_For_Condition_Delimiter_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_Condition_Delimiter_T <CONTEXT>::~CUTS_BE_For_Condition_Delimiter_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_For_Condition_Delimiter_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_For_Condition_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_Condition_End_T <CONTEXT>::
CUTS_BE_For_Condition_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_Condition_End_T <CONTEXT>::~CUTS_BE_For_Condition_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_For_Condition_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_For_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_Begin_T <CONTEXT>::
CUTS_BE_For_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_Begin_T <CONTEXT>::~CUTS_BE_For_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_For_Begin_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_For_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_End_T <CONTEXT>::
CUTS_BE_For_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_For_End_T <CONTEXT>::~CUTS_BE_For_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_For_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Properties_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Action_Properties_Begin_T <CONTEXT>::
CUTS_BE_Action_Properties_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Action_Properties_Begin_T <CONTEXT>::~CUTS_BE_Action_Properties_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Action_Properties_Begin_T <CONTEXT>::generate (size_t count)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Property_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Action_Property_T <CONTEXT>::
CUTS_BE_Action_Property_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Action_Property_T <CONTEXT>::~CUTS_BE_Action_Property_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Action_Property_T <CONTEXT>::generate (const PICML::Property_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_Properties_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Action_Properties_End_T <CONTEXT>::
CUTS_BE_Action_Properties_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Action_Properties_End_T <CONTEXT>::~CUTS_BE_Action_Properties_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Action_Properties_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_WorkerAction_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_WorkerAction_Begin_T <CONTEXT>::
CUTS_BE_WorkerAction_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_WorkerAction_Begin_T <CONTEXT>::~CUTS_BE_WorkerAction_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_WorkerAction_Begin_T <CONTEXT>::generate (const PICML::Action_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_OutputAction_Begin_T <CONTEXT>::
CUTS_BE_OutputAction_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_OutputAction_Begin_T <CONTEXT>::~CUTS_BE_OutputAction_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_OutputAction_Begin_T <CONTEXT>::
generate (const PICML::OutputAction_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_Property_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_OutputAction_Property_T <CONTEXT>::
CUTS_BE_OutputAction_Property_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_OutputAction_Property_T <CONTEXT>::~CUTS_BE_OutputAction_Property_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_OutputAction_Property_T <CONTEXT>::
generate (const PICML::OutputAction_in, const PICML::Property_in property)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_OutputAction_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_OutputAction_End_T <CONTEXT>::
CUTS_BE_OutputAction_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_OutputAction_End_T <CONTEXT>::~CUTS_BE_OutputAction_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_OutputAction_End_T <CONTEXT>::
generate (const PICML::OutputAction_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_CallAction_Begin_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_CallAction_Begin_T <CONTEXT>::
CUTS_BE_CallAction_Begin_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_CallAction_Begin_T <CONTEXT>::~CUTS_BE_CallAction_Begin_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_CallAction_Begin_T <CONTEXT>::
generate (const PICML::CallAction_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_CallAction_Property_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_CallAction_Property_T <CONTEXT>::
CUTS_BE_CallAction_Property_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_CallAction_Property_T <CONTEXT>::~CUTS_BE_CallAction_Property_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_CallAction_Property_T <CONTEXT>::
generate (const PICML::CallAction_in, const PICML::Property_in property)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_CallAction_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_CallAction_End_T <CONTEXT>::
CUTS_BE_CallAction_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_CallAction_End_T <CONTEXT>::~CUTS_BE_CallAction_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_CallAction_End_T <CONTEXT>::
generate (const PICML::CallAction_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_RequestAction_Begin_T

template <typename CONTEXT>
CUTS_BE_RequestAction_Begin_T <CONTEXT>::
CUTS_BE_RequestAction_Begin_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_RequestAction_Begin_T <CONTEXT>::
generate (const PICML::RequestAction_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_RequestAction_End_T

template <typename CONTEXT>
CUTS_BE_RequestAction_End_T <CONTEXT>::
CUTS_BE_RequestAction_End_T (CONTEXT &)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_RequestAction_End_T <CONTEXT>::
generate (const PICML::RequestAction_in)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_Action_End_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Action_End_T <CONTEXT>::
CUTS_BE_Action_End_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_Action_End_T <CONTEXT>::~CUTS_BE_Action_End_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_Action_End_T <CONTEXT>::generate (void)
{

}

///////////////////////////////////////////////////////////////////////////////
// CUTS_BE_State_T

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_State_T <CONTEXT>::
CUTS_BE_State_T (CONTEXT & )
{

}

template <typename CONTEXT>
CUTS_INLINE
CUTS_BE_State_T <CONTEXT>::~CUTS_BE_State_T (void)
{

}

template <typename CONTEXT>
CUTS_INLINE
void CUTS_BE_State_T <CONTEXT>::generate (const PICML::State_in state)
{

}
