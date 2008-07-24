// $Id$

#include "stdafx.h"
#include "Model_Cache_Manager.h"
#include "Model_Cache.h"

//
// Model_Cache_Manager
//
Model_Cache_Manager::Model_Cache_Manager (void)
{

}

//
// ~Model_Cache_Manager
//
Model_Cache_Manager::~Model_Cache_Manager (void)
{
  this->clear_all ();
}

//
// insert
//
void Model_Cache_Manager::insert (Model_Cache * cache)
{
  this->caches_.insert (cache);
}

//
// remove
//
void Model_Cache_Manager::remove (Model_Cache * cache)
{
  this->caches_.erase (cache);
}

//
// insert
//
void Model_Cache_Manager::clear_all (void)
{
  cache_set_type::iterator 
    iter = this->caches_.begin (), iter_end = this->caches_.end ();

  for ( ; iter != iter_end; iter ++)
    (*iter)->clear ();
}

