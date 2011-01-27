// -*- C++ -*-

//=============================================================================
/**
 * @file        Unique_Property_Bag.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CUTE_UNIQUE_PROPERTY_BAG_H_
#define _CUTS_CUTE_UNIQUE_PROPERTY_BAG_H_

#include "Property_Locator_Handler.h"

/**
 * @class CUTS_CUTE_Property_Locator_Handler
 *
 * Interface for handling located elements with properties.
 */
class CUTS_CUTE_Unique_Property_Bag :
  public CUTS_CUTE_Property_Locator_Handler
{
public:
  typedef ACE_Unbounded_Set <ACE_CString> items_type;
  typedef items_type::ITERATOR ITERATOR;
  typedef items_type::CONST_ITERATOR CONST_ITERATOR;

  /// Default constructor.
  CUTS_CUTE_Unique_Property_Bag (void);

  /// Destructor.
  virtual ~CUTS_CUTE_Unique_Property_Bag (void);

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

  const items_type & items (void) const;

private:
  void insert_parameters (const ACE_Unbounded_Set <ACE_CString> &);

  /// Collection of unique parameters.
  items_type items_;
};

#if defined (__CUTS_INLINE__)
#include "Unique_Property_Bag.inl"
#endif

#endif
