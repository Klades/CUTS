// -*- C++ -*-

//=============================================================================
/**
 * @file      Model_Cache_Manager.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _MODEL_CACHE_MANAGER_H_
#define _MODEL_CACHE_MANAGER_H_

#include <set>
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

/// Forward decl.
class Model_Cache;

//=============================================================================
/**
 * @class Model_Cache_Manager
 *
 * Manager responsible for managing all the caches. When this object
 * is destroyed, it will ensure that all the caches it manages clear
 * their cache.
 */
//=============================================================================

class Model_Cache_Manager
{
public:
  /// Default constructor.
  Model_Cache_Manager (void);

  /// Destructor.
  ~Model_Cache_Manager (void);

  void insert (Model_Cache * cache);

  void remove (Model_Cache * cache);

  /// Clear all the caches.
  void clear_all (void);

private:
  /// Type definition of the set of cache objects.
  typedef std::set <Model_Cache *> cache_set_type;

  /// Collection of the registered caches.
  cache_set_type caches_;
};

#define MODEL_CACHE_MANAGER() \
  ACE_Singleton <Model_Cache_Manager, ACE_Null_Mutex>::instance ()

#endif  // !defined _MODEL_CACHE_MANAGER_H_
