// $Id$

//
// CUTS_Activation_Record_Endpoint
//
CUTS_INLINE
CUTS_Activation_Record_Endpoint::
CUTS_Activation_Record_Endpoint (void)
: datasize_ (0),
  toc_ (ACE_Time_Value::zero)
{

}

//
// CUTS_Activation_Record_Endpoint
//
CUTS_INLINE
CUTS_Activation_Record_Endpoint::
CUTS_Activation_Record_Endpoint (const ACE_Time_Value & toc, size_t datasize)
: datasize_ (datasize),
  toc_ (toc)
{

}


//
// CUTS_Activation_Record_Endpoint
//
CUTS_INLINE
CUTS_Activation_Record_Endpoint::
CUTS_Activation_Record_Endpoint (const CUTS_Activation_Record_Endpoint & are)
: datasize_ (are.datasize_),
  toc_ (are.toc_)
{

}

//
// ~CUTS_Activation_Record_Endpoint
//
CUTS_INLINE
CUTS_Activation_Record_Endpoint::~CUTS_Activation_Record_Endpoint (void)
{

}

//
// operator =
//
CUTS_INLINE
const CUTS_Activation_Record_Endpoint &
CUTS_Activation_Record_Endpoint::
operator = (const CUTS_Activation_Record_Endpoint & rhs)
{
  this->datasize_ = rhs.datasize_;
  this->toc_ = rhs.toc_;
  return *this;
}

//
// time_of_completion
//
CUTS_INLINE
const ACE_Time_Value & CUTS_Activation_Record_Endpoint::
time_of_completion (void) const
{
  return this->toc_;
}

//
// time_of_completion
//
CUTS_INLINE
size_t CUTS_Activation_Record_Endpoint::datasize (void) const
{
  return this->datasize_;
}
