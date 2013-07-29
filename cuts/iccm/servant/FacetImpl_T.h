// -*- C++ -*-

//==============================================================================
/**
 *  @file        FacetImpl_T.h
 *
 *  $Id$
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _ICCM_FACETIMPL_T_H_
#define _ICCM_FACETIMPL_T_H_

#include "cuts/config.h"
#include "ccm/CCM_ObjectS.h"
#include "tao/LocalObject.h"

namespace iCCM
{

/**
 * @class FacetImpl_T
 *
 * Base class for facet implementations
 */
template <typename COMPONENT, typename OBJECT>
class FacetImpl_T
  : public virtual OBJECT,
    public virtual ::CORBA::LocalObject
{
public:
  /// Default constructor.
  FacetImpl_T (COMPONENT * parent);

  /// Destructor.
  virtual ~FacetImpl_T (void);

  /// Parent getter
  COMPONENT & getParent (void);

protected:
  COMPONENT * parent_;
};

} // namespace iCCM

#if defined (__CUTS_INLINE__)
#include "FacetImpl_T.inl"
#endif  // !defined __CUTS_INLINE__

#include "FacetImpl_T.cpp"

#endif  // _ICCM_FACETIMPL_T_H_
