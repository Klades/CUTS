// -*- C++ -*-

//=============================================================================
/**
 * @file            Domain_T.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DOMAIN_T_H_
#define _CUTS_DOMAIN_T_H_

#include "cuts/config.h"

/**
 * @class CUTS_Domain_T
 */
template <typename T>
class CUTS_Domain_T
{
public:
  typedef T item_type;

  typedef std::set <item_type> collection_type;

  typedef typename collection_type::iterator iterator;

  typedef typename collection_type::const_iterator const_iterator;

  /// Default constructor.
  CUTS_Domain_T (void);

  CUTS_Domain_T (const CUTS_Domain_T & domain);

  /// Destructor.
  ~CUTS_Domain_T (void);

  bool insert (T item);

  const CUTS_Domain_T & operator = (const CUTS_Domain_T & rhs);

  iterator begin (void);

  const_iterator begin (void) const;

  iterator end (void);

  const_iterator end (void) const;

  size_t size (void) const;

private:
  /// List of items in the domain.
  std::set <item_type> items_;
};

#if defined (__CUTS_INLINE__)
#include "Domain_T.inl"
#endif

#include "Domain_T.cpp"

#endif  // !defined _CUTS_DOMAIN_T_H_
