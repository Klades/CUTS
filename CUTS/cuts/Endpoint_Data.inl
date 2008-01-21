// $Id$

//
// CUTS_Endpoint_Data
//
CUTS_INLINE
CUTS_Endpoint_Data::CUTS_Endpoint_Data (void)
: data_size_ (0)
{

}

//
// CUTS_Endpoint_Data
//
CUTS_INLINE
CUTS_Endpoint_Data::
CUTS_Endpoint_Data (const ACE_Time_Value & toc, size_t datasize)
: data_size_ (datasize),
  toc_ (toc)
{

}

//
// CUTS_Endpoint_Data
//
CUTS_INLINE
CUTS_Endpoint_Data::
CUTS_Endpoint_Data (const CUTS_Endpoint_Data & data)
: data_size_ (data.data_size_),
  toc_ (data.toc_)
{

}

//
// ~CUTS_Endpoint_Data
//
CUTS_INLINE
CUTS_Endpoint_Data::~CUTS_Endpoint_Data (void)
{

}

//
// time_of_completion
//
CUTS_INLINE
const ACE_Time_Value & CUTS_Endpoint_Data::time_of_completion (void) const
{
  return this->toc_;
}

//
// data_size
//
CUTS_INLINE
size_t CUTS_Endpoint_Data::data_size (void) const
{
  return this->data_size_;
}

//
// set
//
CUTS_INLINE
void CUTS_Endpoint_Data::set (const ACE_Time_Value & toc, size_t data_size)
{
  this->data_size_ = data_size;
  this->toc_ = toc;
}

//
// operator >
//
CUTS_INLINE
bool CUTS_Endpoint_Data::
operator > (const CUTS_Endpoint_Data & rhs) const
{
  return this->toc_ > rhs.toc_;
}

//
// operator >=
//
CUTS_INLINE
bool CUTS_Endpoint_Data::
operator >= (const CUTS_Endpoint_Data & rhs) const
{
  return this->toc_ >= rhs.toc_;
}

//
// operator <
//
CUTS_INLINE
bool CUTS_Endpoint_Data::
operator < (const CUTS_Endpoint_Data & rhs) const
{
  return this->toc_ < rhs.toc_;
}

//
// operator <=
//
CUTS_INLINE
bool CUTS_Endpoint_Data::
operator <= (const CUTS_Endpoint_Data & rhs) const
{
  return this->toc_ <= rhs.toc_;
}

//
// operator ==
//
CUTS_INLINE
bool CUTS_Endpoint_Data::
operator == (const CUTS_Endpoint_Data & rhs) const
{
  return this->toc_ == rhs.toc_;
}
