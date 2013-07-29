// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// FacetImpl_T
//
template <typename COMPONENT, typename OBJECT>
CUTS_INLINE
FacetImpl_T <COMPONENT, OBJECT>::FacetImpl_T (COMPONENT * parent)
 : parent_ (parent)
{

}

//
// ~FacetImpl_T
//
template <typename COMPONENT, typename OBJECT>
CUTS_INLINE
FacetImpl_T <COMPONENT, OBJECT>::~FacetImpl_T (void)
{

}

//
// getParent
//
template <typename COMPONENT, typename OBJECT>
CUTS_INLINE
COMPONENT &
FacetImpl_T <COMPONENT, OBJECT>::getParent (void)
{
  return *(this->parent_);
}

} // namespace iCCM
