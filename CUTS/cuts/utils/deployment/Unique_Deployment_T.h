// -*- C++ -*-

//=============================================================================
/**
 * @file            Host_T.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNIQUE_DEPLOYMENT_T_H_
#define _CUTS_UNIQUE_DEPLOYMENT_T_H_

#include "Deployment_T.h"
#include "Domain_T.h"

/**
 * @class CUTS_Unique_Deployment_T
 *
 * Utility class for calculating unique deployments.
 */
template <typename T>
class CUTS_Unique_Deployment_T
{
public:
  typedef T host_type;

  typedef typename host_type::item_type item_type;

  typedef CUTS_Deployment_T <host_type> deployment_type;

  typedef CUTS_Domain_T <host_type> domain_type;

  typedef std::list <deployment_type> collection_type;

  /// Initializing constructor.
  CUTS_Unique_Deployment_T (void);

  /// Destructor.
  ~CUTS_Unique_Deployment_T (void);

  bool init (domain_type domain);

  void calculate (item_type item);

  const deployment_type & operator [] (size_t index) const;

  size_t size (void) const;

private:
  void calculate_i (deployment_type deployment, item_type item);

  /// Let of unique deployments.
  collection_type deployments_;

  domain_type domain_;
};

#if defined (__CUTS_INLINE__)
#include "Unique_Deployment_T.inl"
#endif

#include "Unique_Deployment_T.cpp"

#endif  // !defined _CUTS_UNIQUE_DEPLOYMENT_T_H_
