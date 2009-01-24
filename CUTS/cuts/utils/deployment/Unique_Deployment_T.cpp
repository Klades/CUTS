// $Id$

#if !defined (__CUTS_INLINE__)
#include "Unique_Deployment_T.inl"
#endif

#include "boost/bind.hpp"
#include <algorithm>

//
// init
//
template <typename T>
bool CUTS_Unique_Deployment_T <T>::init (const domain_type & domain)
{
  if (!this->deployments_.empty ())
    this->deployments_.empty ();

  deployment_type empty;

  std::for_each (domain.begin (),
                 domain.end (),
                 boost::bind (&deployment_type::insert,
                              boost::ref (empty),
                              _1));

  this->deployments_.push_back (empty);
  this->domain_ = domain;
  return true;
}

//
// calculate
//
template <typename T>
void CUTS_Unique_Deployment_T <T>::calculate (const item_type & item)
{
  size_t iterations = this->deployments_.size ();

  for (size_t i = 0; i < iterations; ++ i)
  {
    this->calculate_i (this->deployments_.front (), item);
    this->deployments_.pop_front ();
  }
}

//
// calculate_i
//
template <typename T>
void CUTS_Unique_Deployment_T <T>::
calculate_i (const deployment_type & deployment, const item_type & item)
{
  size_t count = this->domain_.size ();

  for (size_t i = 0; i < count; ++ i)
  {
    // Insert the item into the deployment.
    deployment_type updated (deployment);

    typename deployment_type::iterator iter = updated.begin ();
    std::advance (iter, i);

    iter->insert (item);

    // Save the updated deployment.
    this->deployments_.push_back (updated);
  }
}

//
// operator []
//
template <typename T>
const typename CUTS_Unique_Deployment_T <T>::deployment_type &
CUTS_Unique_Deployment_T <T>::operator [] (size_t index) const
{
  typename collection_type::const_iterator iter = this->deployments_.begin ();
  std::advance (iter, index);

  return *iter;
}
