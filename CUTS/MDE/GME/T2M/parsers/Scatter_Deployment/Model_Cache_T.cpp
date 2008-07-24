// $Id$

//
// Model_Cache_T
//
template <typename T>
Model_Cache_T <T>::Model_Cache_T (void)
{

}

//
// ~Model_Cache_T 
//
template <typename T>
Model_Cache_T <T>::~Model_Cache_T (void)
{

}

//
// operator []
//
template <typename T>
std::map <std::string, T> & Model_Cache_T <T>::
operator [] (const std::string & type)
{
  return this->cache_[type];
}

//
// operator []
//
template <typename T>
const std::map <std::string, T> & Model_Cache_T <T>::
operator [] (const std::string & type) const
{
  return this->cache_[type];
}

//
// operator []
//
template <typename T>
void Model_Cache_T <T>::clear (void)
{
  std::map <std::string, typename cache_type>::iterator 
    iter = this->cache_.begin (), iter_end = this->cache_.end ();

  for ( ; iter != iter_end; iter ++)
    iter->second.clear ();
}
