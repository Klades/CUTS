// -*- C++ -*- 

//=============================================================================
/**
 * @file        Model_Cache_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _MODEL_CACHE_T_H_
#define _MODEL_CACHE_T_H_

#include <string>
#include <map>
#include "Model_Cache.h"
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

//=============================================================================
/**
 * @class Model_Cache
 */
//=============================================================================

template <typename T>
class Model_Cache_T : public Model_Cache
{
public:
  /// Type definition of the item type.
  typedef T value_type;

  typedef std::map <std::string, T> cache_type;

  /// Default constructor.
  Model_Cache_T (void);

  /// Destructor.
  ~Model_Cache_T (void);

  /**
   * Get the cache for the specified type.
   *
   * @param[in]       type        The type of interest.
   */
  typename cache_type & operator [] (const std::string & type);

  /**
   * @overload
   */
  const typename cache_type & operator [] (const std::string & type) const;

  /// Clear the cache.
  virtual void clear (void);

private:
  /// The cache by types.
  std::map <std::string, typename cache_type> cache_;
};

#include "Model_Cache_T.cpp"

/// Singleton definition of the model cache.
#define MODEL_CACHE(T, name) \
  (*ACE_Singleton <Model_Cache_T <T>, ACE_Null_Mutex>::instance ())[name]

#endif  // !defined _MODEL_CACHE_T_H_
