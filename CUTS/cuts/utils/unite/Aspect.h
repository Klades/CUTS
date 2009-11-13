// -*- C++ -*-

//=============================================================================
/**
 * @file        Aspect.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_UNITE_ASPECT_H_
#define _CUTS_UNITE_ASPECT_H_

#include "Unite_export.h"
#include "ace/SString.h"

/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_UNITE_Viewpoint
 *
 * The viewpoint of a given aspect. The viewpoint captures how many points
 * before and after (or the lower and upper bounds) each point of interest
 * that should be visible.
 */
class CUTS_UNITE_Export CUTS_UNITE_Viewpoint
{
public:
  CUTS_UNITE_Viewpoint (void)
    : lower_ (0),
      upper_ (0)
  {

  }

  CUTS_UNITE_Viewpoint (ACE_INT32 lower, ACE_INT32 upper)
    : lower_ (lower),
      upper_ (upper)
  {

  }

  /// Lower bound of the viewpoint.
  ACE_UINT32 lower_;

  /// Upper bound of the viewpoint.
  ACE_UINT32 upper_;
};

/**
 * @ingroup UNITE_Core
 *
 * @class CUTS_UNITE_Aspect
 *
 * Structure that defines the apsect within UNITE evaluation. An aspect
 * in UNITE is designed to focus on point(s)-of-interest that meet a
 * specific state, or criteria. Since this will result in a single point, it
 * can be hard to get meaningful understanding from the points-of-interest.
 * The aspects therefore require a viewpoint (i.e., lower/upper bound)
 * that helps place point(s)-of-interest into a meaningful context.
 */
class CUTS_UNITE_Export CUTS_UNITE_Aspect
{
public:
  /// The viewpoint for the aspect.
  CUTS_UNITE_Viewpoint viewpoint_;

  /// The WHERE clause of the aspect.
  ACE_CString condition_;
};

#endif  // !defined _CUTS_UNITE_ASPECT_H_
