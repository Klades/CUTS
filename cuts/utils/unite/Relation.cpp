// $Id$

#include "Relation.h"

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Relation_Causality

//
// CUTS_Relation_Causality
//
CUTS_Relation_Causality::CUTS_Relation_Causality (void)
{

}

//
// CUTS_Relation_Causality
//
CUTS_Relation_Causality::
CUTS_Relation_Causality (const ACE_CString & cause, const ACE_CString & effect)
: cause_ (cause),
  effect_ (effect)
{

}

//
// CUTS_Relation_Causality
//
CUTS_Relation_Causality::
CUTS_Relation_Causality (const CUTS_Relation_Causality & copy)
: cause_ (copy.cause_),
  effect_ (copy.effect_)
{

}

//
// operator =
//
const CUTS_Relation_Causality &
CUTS_Relation_Causality::operator = (const CUTS_Relation_Causality & copy)
{
  if (this == &copy)
    return *this;

  this->cause_ = copy.cause_;
  this->effect_ = copy.effect_;

  return *this;
}

//
// set
//
void CUTS_Relation_Causality::
set (const ACE_CString & cause, const ACE_CString & effect)
{
  this->cause_ = cause;
  this->effect_ = effect;
}

//
// cause
//
const ACE_CString & CUTS_Relation_Causality::cause (void) const
{
  return this->cause_;
}

//
// effect
//
const ACE_CString & CUTS_Relation_Causality::effect (void) const
{
  return this->effect_;
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Log_Format_Relation

//
// CUTS_Log_Format_Relation
//
CUTS_Log_Format_Relation::CUTS_Log_Format_Relation (void)
{

}

//
// CUTS_Log_Format_Relation
//
CUTS_Log_Format_Relation::
CUTS_Log_Format_Relation (const CUTS_Log_Format_Relation & copy)
: format_ (copy.format_),
  causality_ (copy.causality_)
{

}

//
// ~CUTS_Log_Format_Relation
//
CUTS_Log_Format_Relation::~CUTS_Log_Format_Relation (void)
{

}

//
// CUTS_Log_Format_Relation
//
const CUTS_Log_Format_Relation &
CUTS_Log_Format_Relation::operator = (const CUTS_Log_Format_Relation & copy)
{
  if (this == &copy)
    return *this;

  this->format_ = copy.format_;
  this->causality_ = copy.causality_;

  return *this;
}

//
// effect
//
void CUTS_Log_Format_Relation::effect (CUTS_Log_Format * format)
{
  this->format_ = format;
}

//
// effect
//
CUTS_Log_Format * CUTS_Log_Format_Relation::effect (void)
{
  return this->format_;
}

//
// effect
//
const CUTS_Log_Format * CUTS_Log_Format_Relation::effect (void) const
{
  return this->format_;
}

//
// causality
//
CUTS_Log_Format_Relation::causality_type &
CUTS_Log_Format_Relation::causality (void)
{
  return this->causality_;
}

//
// causality
//
const CUTS_Log_Format_Relation::causality_type &
CUTS_Log_Format_Relation::causality (void) const
{
  return this->causality_;
}