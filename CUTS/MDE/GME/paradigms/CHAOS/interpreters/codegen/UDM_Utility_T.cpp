// $Id$

#if !defined (__CUTS_INLINE__)
#include "UDM_Utility_T.inl"
#endif

#include <algorithm>
#include "Uml.h"

//
// Sorted_By_Name <T>::operator ()
//
template <typename T>
bool Sorted_By_Name <T>::operator () (const T & lhs, const T & rhs)
{
  std::string name = lhs.name ();
  return name.compare (rhs.name ()) < 0;
}

//
// create_element_if_not_exist
//
template <typename COLLECTION, typename COMPARE, typename PARENT>
bool create_element_if_not_exist (const COLLECTION & coll,
                                  COMPARE & comp,
                                  const PARENT & parent,
                                  const Uml::CompositionChildRole & role,
                                  typename COLLECTION::value_type & element)
{
  COLLECTION::const_iterator iter =
    std::find_if (coll.begin (), coll.end (), comp);

  if (iter == coll.end ())
  {
    element = COLLECTION::value_type::Create (parent, role);
    return true;
  }
  else
  {
    element = *iter;
    return false;
  }
}
