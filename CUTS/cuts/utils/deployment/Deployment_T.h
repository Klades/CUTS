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

#ifndef _CUTS_DEPLOYMENT_T_H_
#define _CUTS_DEPLOYMENT_T_H_

#include "cuts/config.h"

/**
 * @class CUTS_Deployment_T
 */
template <typename T>
class CUTS_Deployment_T
{
public:
  typedef T item_type;

  typedef std::set <item_type> collection_type;

  typedef typename collection_type::iterator iterator;

  typedef typename collection_type::const_iterator const_iterator;

    /// Default constructor.
  CUTS_Deployment_T (void);

  CUTS_Deployment_T (const CUTS_Deployment_T & src);

  /// Destructor.
  ~CUTS_Deployment_T (void);

  bool insert (item_type item);

  const CUTS_Deployment_T & operator = (const CUTS_Deployment_T & rhs);

  iterator begin (void);

  const_iterator begin (void) const;

  iterator end (void);

  const_iterator end (void) const;

private:
  collection_type hosts_;
};

#if defined (__CUTS_INLINE__)
#include "Deployment_T.inl"
#endif

#include "Deployment_T.cpp"

#endif  // !defined _CUTS_DEPLOYMENT_T_H_
