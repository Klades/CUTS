// -*- C++ -*-

//=============================================================================
/**
 * @file          Type_System.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_TYPE_SYSTEM_H_
#define _CUTS_BE_CCM_TYPE_SYSTEM_H_

#include <ostream>
#include "PICML/PICML.h"
#include "PICML/Visitor.h"
#include "cuts/config.h"

#include "CCM_export.h"

namespace CUTS_BE_CCM
{

/**
 * @class Type_System
 *
 * Base class for all the type generators.
 */
class CUTS_BE_CCM_Export Type_System : public PICML::Visitor
{
public:
  /// Destructor.
  virtual ~Type_System (void);

  /**
   * Generate the type information for the member type.
   *
   * @param[in]       mt        Member type of interest.
   */
  virtual void generate (const PICML::MemberType_in mt);

protected:
  /// Default constructor.
  Type_System (std::ostream & out);

  /// Target output stream.
  std::ostream & out_;
};

}

#if defined (__CUTS_INLINE__)
#include "Type_System.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_TYPE_SYSTEM_H_
