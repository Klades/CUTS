// $Id$

#include "Unit_Test_Result.h"

//
// CUTS_Unit_Test_Result
//
CUTS_Unit_Test_Result::CUTS_Unit_Test_Result (void)
{

}

//
// ~CUTS_Unit_Test_Result
//
CUTS_Unit_Test_Result::~CUTS_Unit_Test_Result (void)
{

}

//
// result
//
const ACE_CString & CUTS_Unit_Test_Result::result (void) const
{
  return this->result_;
}

//
// result
//
void CUTS_Unit_Test_Result::result (const ACE_CString & r)
{
  this->result_ = r;
}

//
// groups
//
CUTS_Unit_Test_Group_Result & CUTS_Unit_Test_Result::groups (void)
{
  return this->group_;
}

//
// groups
//
const CUTS_Unit_Test_Group_Result & CUTS_Unit_Test_Result::groups (void) const
{
  return this->group_;
}
