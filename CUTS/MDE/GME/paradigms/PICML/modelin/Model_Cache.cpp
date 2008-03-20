// $Id$

#include "stdafx.h"
#include "Model_Cache.h"
#include "Model_Cache_Manager.h"

//
// Model_Cache
//
Model_Cache::Model_Cache (void)
{
  MODEL_CACHE_MANAGER ()->insert (this);
}

//
// Model_Cache
//
Model_Cache::~Model_Cache (void)
{
  MODEL_CACHE_MANAGER ()->remove (this);
}
