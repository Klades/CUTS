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

#ifndef _CUTS_HOST_T_H_
#define _CUTS_HOST_T_H_

#include <set>
#include <string>
#include "cuts/config.h"

/**
 * @class CUTS_Host_T
 *
 * Template abstraction for storing objects on a host. The host
 * is not allowed to contain duplicates.
 */
template <typename T>
class CUTS_Host_T
{
public:
  /// Type definition of the item type.
  typedef T item_type;

  /// Type definition of the items type.
  typedef typename std::set <item_type> items_type;

  /// Type definition of the iterator.
  typedef typename items_type::iterator iterator;

  /// Type definition of the const iterator.
  typedef typename items_type::const_iterator const_iterator;

  /// Default constructor.
  CUTS_Host_T (void);

  CUTS_Host_T (const std::string & name);

  /**
   * Copy constructor.
   *
   * @param[in]       host        Source host
   */
  CUTS_Host_T (const CUTS_Host_T & host);

  /// Destructor.
  ~CUTS_Host_T (void);

  void name (const std::string & name);

  const std::string & name (void) const;

  /**
   * Assignment operator
   *
   * @param[in]       host        Source host
   */
  const CUTS_Host_T & operator = (const CUTS_Host_T & host);

  iterator begin (void);

  const_iterator begin (void) const;

  iterator end (void);

  const_iterator end (void) const;

  bool operator == (const CUTS_Host_T & rhs) const;

  bool operator < (const CUTS_Host_T & rhs) const;

  bool operator > (const CUTS_Host_T & rhs) const;

  size_t size (void) const;

  bool insert (const item_type & item);

private:
  /// The name of the host.
  std::string name_;

  /// Collection of items on host.
  std::set <T> items_;
};

#if defined (__CUTS_INLINE__)
#include "Host_T.inl"
#endif

#include "Host_T.cpp"

#endif  // !defined _CUTS_HOST_T_H_
