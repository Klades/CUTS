// $Id$

//=============================================================================
/**
 * @file          Attribute_Tag.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _GME_ATTRIBUTE_TAG_H_
#define _GME_ATTRIBUTE_TAG_H_

#include "cuts/config.h"
#include "GNC_Base_export.h"
#include "game/GME.h"
#include <string>

/**
 * @struct GME_Attribute_Tag
 *
 * Information about a Naomi attribute tag in a GME model.
 */
class GNC_BASE_Export GME_Attribute_Tag
{
public:
  /// Default constructor
  GME_Attribute_Tag (void);

  /// Destructor.
  ~GME_Attribute_Tag (void);

  /// Target object that contains the attribute.
  GME::Object object_;

  /// Name of the GME attribute. This is applicable to only
  /// simple attribute types.
  std::string gme_attribute_;

  /// Direction of the attribute, i.e., input or output.
  std::string direction_;

  /// Module for the complex parser/generator.
  std::string complex_;
};

#if defined (__CUTS_INLINE__)
#include "Attribute_Tag.inl"
#endif

#endif  // !defined _GME_ATTRIBUTE_TAG_H_
