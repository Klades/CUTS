// -*- C++ -*-

//=============================================================================
/**
 * @file        Property_Locator.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CUTE_PROPERTY_LOCATOR_HANDLER_H_
#define _CUTS_CUTE_PROPERTY_LOCATOR_HANDLER_H_

#include "ace/SString.h"
#include "ace/Unbounded_Set.h"
#include "game/GME_fwd.h"

#include "cuts/config.h"

/**
 * @class CUTS_CUTE_Property_Locator_Handler
 *
 * Interface for handling located elements with properties.
 */
class CUTS_CUTE_Property_Locator_Handler
{
protected:
  /// Default constructor.
  CUTS_CUTE_Property_Locator_Handler (void);

  /// Destructor.
  virtual ~CUTS_CUTE_Property_Locator_Handler (void);

public:
  /**
   * The attribute has one or more parameters defined in its text.
   *
   * @param[in]         attr        The target attribute
   * @param[in]         params      The identified parameters
   */
  virtual int handle_attribute (GAME::Attribute_in attr,
                                const ACE_Unbounded_Set <ACE_CString> & params);

  /**
   * The name on the specified element has one or more parameters
   * defined in its text.
   *
   * @param[in]         folder      The object with parameters
   * @param[in]         params      The identified parameters
   */
  virtual int handle_name (GAME::Object_in obj,
                           const ACE_Unbounded_Set <ACE_CString> & params);
};

#if defined (__CUTS_INLINE__)
#include "Property_Locator_Handler.inl"
#endif

#endif
