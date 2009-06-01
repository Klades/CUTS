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
void CUTS_BE_Initialize_T <CONTEXT>::generate (const PICML::RootFolder & )
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
void CUTS_BE_Finalize_T <CONTEXT>::generate (const PICML::RootFolder & )
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
generate (const PICML::ComponentImplementationContainer &,
          const PICML::MonolithicImplementation &)
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
generate (const PICML::ComponentImplementationContainer &,
          const PICML::MonolithicImplementation &)
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
generate (const PICML::ComponentImplementationContainer &,
          const PICML::MonolithicImplementation &)
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
generate (const PICML::ComponentImplementationContainer &,
          const PICML::MonolithicImplementation &)
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
generate (const PICML::MonolithicImplementation & ,
          const PICML::Component & )
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
generate (const PICML::MonolithicImplementation & ,
          const PICML::Component & )
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
generate (const PICML::Component &)
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
generate (const PICML::MultiInputAction & )
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
generate (const PICML::MultiInputAction & )
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
void CUTS_BE_Environment_End_T <CONTEXT>::generate (const PICML::Component & )
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
generate (const PICML::Attribute & )
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
generate (const PICML::Attribute & )
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
generate (const PICML::ReadonlyAttribute & )
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
generate (const PICML::ReadonlyAttribute & )
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
generate (const PICML::Component & )
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
generate (const PICML::Component & )
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
void CUTS_BE_Variable_T <CONTEXT>::generate (const PICML::Variable & )
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
generate (const PICML::PeriodicEvent & )
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
generate (const PICML::ReadonlyAttribute & attr)
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
generate (const PICML::WorkerType &, const PICML::Worker &)
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
generate (const PICML::MonolithicImplementation & ,
          const PICML::ComponentImplementationArtifact & )
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
generate (const PICML::InEventPort & ,
          const std::vector <PICML::Property> & )
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
generate (const PICML::InEventPort & ,
          const std::vector <PICML::Property> & )
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
generate (const PICML::PeriodicEvent & )
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
generate (const PICML::PeriodicEvent & )
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
generate (const PICML::ProvidedRequestPort & )
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
generate (const PICML::ProvidedRequestPort & )
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
void CUTS_BE_Action_Property_T <CONTEXT>::generate (const PICML::Property &)
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
void CUTS_BE_WorkerAction_Begin_T <CONTEXT>::
generate (const PICML::Worker &, const PICML::Action &)
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
generate (const PICML::OutputAction &)
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
generate (const PICML::OutputAction &, const PICML::Property & property)
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
generate (const PICML::OutputAction &)
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
void CUTS_BE_State_T <CONTEXT>::generate (const PICML::State & state)
{

}
