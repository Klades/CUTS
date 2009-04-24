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

#ifndef _CUTS_CUTE_PROPERTY_LOCATOR_H_
#define _CUTS_CUTE_PROPERTY_LOCATOR_H_

#include "ace/Hash_Multi_Map_Manager_T.h"
#include "ace/SString.h"
#include "ace/Null_Mutex.h"
#include "game/FCO.h"
#include "game/Visitor.h"
#include "cuts/utils/Property_Evaluator_T.h"
#include "cuts/utils/Property_Evaluator_List_Actor.h"

/**
 * @class CUTS_CUTE_Property_Locator
 */
class CUTS_CUTE_Property_Locator : public GME::Visitor
{
public:
  /// Type definition of the map type.
  typedef ACE_Hash_Multi_Map_Manager <ACE_CString,
                                      GME::FCO,
                                      ACE_Hash <ACE_CString>,
                                      ACE_Equal_To <ACE_CString>,
                                      ACE_Null_Mutex> map_type;

  /// Default constructor.
  CUTS_CUTE_Property_Locator (void);

  /// Destructor.
  virtual ~CUTS_CUTE_Property_Locator (void);

  /// Clear the locator.
  void clear (void);

  /// Get the items found by the locator.
  const map_type & items (void) const;

  size_t total_items (void);

  virtual void visit_Folder (GME::Folder & folder);

  virtual void visit_Model (GME::Model & model);

  virtual void visit_FCO (GME::FCO & fco);

private:
  void visit_Attribute (GME::Attribute & attr);

  /// Map that holds located items.
  map_type map_;

  CUTS_Property_Map prop_map_;

  CUTS_Property_Evaluator_List_Actor actor_;

  typedef CUTS_Property_Evaluator_List_Actor::list_type list_type;

  typedef
    CUTS_Property_Evaluator_T <CUTS_Property_Evaluator_List_Actor>
    evaluator_type;

  evaluator_type evaluator_;

  size_t total_size_;
};

#if defined (__CUTS_INLINE__)
#include "Property_Locator.inl"
#endif

#endif  // !defined _CUTS_CUTE_PROPERTY_LOCATOR_H_
