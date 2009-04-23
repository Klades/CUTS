// -*- C++ -*-

//=============================================================================
/**
 * @file        Property_Evaluator_List_Actor.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PROPERTY_EVALUATOR_LIST_ACTOR_H_
#define _CUTS_PROPERTY_EVALUATOR_LIST_ACTOR_H_

#include "Utils_export.h"
#include "ace/Unbounded_Set.h"
#include "ace/SString.h"

// Forward decl.
class CUTS_Property_Map;

// Forward decl.
class CUTS_Property_Evaluator_Config;

/**
 * @class CUTS_Property_Evaluator_List_Actor
 *
 * Set of actors for CUTS_Property_Evaluator_Grammar. These set of actors
 * will write contents to std::ostream.
 */
class CUTS_UTILS_Export CUTS_Property_Evaluator_List_Actor
{
public:
  /// Type definition of the list type.
  typedef ACE_Unbounded_Set <ACE_CString> list_type;

  /**
   * Initializing constructor.
   *
   * @param[in]       out         Target output stream.
   */
  CUTS_Property_Evaluator_List_Actor (void);

  /// Desturctor.
  ~CUTS_Property_Evaluator_List_Actor (void);

  /// Callback method for appending text.
  template <typename IteratorT>
  void append (IteratorT begin, IteratorT end) const;

  /// Callback method for expanding a property.
  template <typename IteratorT>
  void expand (IteratorT begin,
               IteratorT end,
               const CUTS_Property_Map & map,
               const CUTS_Property_Evaluator_Config & config) const;

  const list_type & list (void) const;

  /// Clear the contents of the list.
  void clear (void);

private:
  /// List of properties in template.
  mutable list_type list_;
};

#if defined (__CUTS_INLINE__)
#include "Property_Evaluator_List_Actor.inl"
#endif

#include "Property_Evaluator_List_Actor_T.cpp"

#endif  // !defined _CUTS_PROPERTY_EVALUATOR_LIST_ACTOR_H_
