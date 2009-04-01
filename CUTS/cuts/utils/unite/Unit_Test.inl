// $Id$

//
// CUTS_Unit_Test
//
CUTS_INLINE
CUTS_Unit_Test::CUTS_Unit_Test (void)
: name_ ("noname")
{

}

//
// CUTS_Unit_Test
//
CUTS_INLINE
CUTS_Unit_Test::CUTS_Unit_Test (const ACE_CString & name)
: name_ (name)
{

}

//
// ~CUTS_Unit_Test
//
CUTS_INLINE
CUTS_Unit_Test::~CUTS_Unit_Test (void)
{

}

//
// name
//
CUTS_INLINE
const ACE_CString & CUTS_Unit_Test::name (void) const
{
  return this->name_;
}

//
// name
//
CUTS_INLINE
void CUTS_Unit_Test::name (const ACE_CString & n)
{
  this->name_ = n;
}

//
// aggregation
//
CUTS_INLINE
const ACE_CString & CUTS_Unit_Test::aggregation (void) const
{
  return this->aggr_;
}

//
// aggregation
//
CUTS_INLINE
void CUTS_Unit_Test::aggregation (const ACE_CString & aggr)
{
  this->aggr_ = aggr;
}

//
// evaluation
//
CUTS_INLINE
const ACE_CString & CUTS_Unit_Test::evaluation (void) const
{
  return this->evaluation_;
}

//
// evaluation
//
CUTS_INLINE
void CUTS_Unit_Test::evaluation (const ACE_CString & eval)
{
  this->evaluation_ = eval;
}

//
// groupings
//
CUTS_INLINE
const CUTS_Unit_Test::grouping_type & CUTS_Unit_Test::groupings (void) const
{
  return this->grouping_;
}

//
// groupings
//
CUTS_INLINE
CUTS_Unit_Test::grouping_type & CUTS_Unit_Test::groupings (void)
{
  return this->grouping_;
}
