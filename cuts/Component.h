// -*-

//=============================================================================
/**
 * @file      Component.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_COMPONENT_H_
#define _CUTS_COMPONENT_H_

#include "CUTS_export.h"
#include "ace/Unbounded_Set.h"

// Forward decl.
class CUTS_Active_Object;

/**
 * @class CUTS_Component
 */
class CUTS_Export CUTS_Component
{
public:
  /// Destructor.
  virtual ~CUTS_Component (void);

  /**
   * Register an active object with the component.
   *
   * @param[in]       ao          The active object.
   */
  int register_object (CUTS_Active_Object * ao);

  int activate (void);

  int deactivate (void);

protected:
  /// Default constructor.
  CUTS_Component (void);

  /// Type definition of the active object list.
  typedef ACE_Unbounded_Set <CUTS_Active_Object *> ao_list_type;

  /// The active objects managed by this component.
  ao_list_type ao_list_;
};

#if defined (__CUTS_INLINE__)
#include "Component.inl"
#endif

#endif  // !defined _CUTS_COMPONENT_H_
