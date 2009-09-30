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
 * @ingroup UNITE_Common
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
  /// Lower-bound of the viewpoint.
  int units_before_;

  /// Upper-bound of the viewpoint.
  int units_after_;

  /// The WHERE clause of the aspect.
  ACE_CString condition_;
};

#endif  // !defined _CUTS_UNITE_ASPECT_H_
