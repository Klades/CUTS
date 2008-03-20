// -*- C++ -*-

//=============================================================================
/**
 * @file      Model_Cache.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _MODEL_CACHE_H_
#define _MODEL_CACHE_H_

//=============================================================================
/**
 * @class Model_Cache
 */
//=============================================================================

class Model_Cache
{
public:
  /// Destructor.
  virtual ~Model_Cache (void);

  /// Clear the cache.
  virtual void clear (void) = 0;

protected:
  /// Default constructor.
  Model_Cache (void);
};

#endif  // !defined _MODEL_CACHE_H_
