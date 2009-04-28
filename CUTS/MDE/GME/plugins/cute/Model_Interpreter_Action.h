// -*- C++ -*-

//=============================================================================
/**
 * @file        Model_Interpreter_Action.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CUTE_MODEL_INTERPRETER_ACTION_H_
#define _CUTS_CUTE_MODEL_INTERPRETER_ACTION_H_

#include "game/Attribute.h"
#include "game/Object.h"
#include "cuts/utils/Property_Map.h"
#include "cuts/utils/Text_Processor.h"

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_CUTE_Model_Interpreter_Action
 */
class CUTS_CUTE_Model_Interpreter_Action
{
public:
  CUTS_CUTE_Model_Interpreter_Action (void);

  virtual ~CUTS_CUTE_Model_Interpreter_Action (void);

  virtual void replace (const CUTS_Property_Map & config) = 0;

  virtual void reset (void) = 0;

private:
  // prevent the following operations.
  CUTS_CUTE_Model_Interpreter_Action (const CUTS_CUTE_Model_Interpreter_Action &);
  const CUTS_CUTE_Model_Interpreter_Action & operator = (const CUTS_CUTE_Model_Interpreter_Action &);
};

/**
 * @class CUTS_CUTE_Replace_Model_Name_Action
 */
class CUTS_CUTE_Replace_Model_Name_Action :
  public CUTS_CUTE_Model_Interpreter_Action
{
public:
  CUTS_CUTE_Replace_Model_Name_Action (const GME::Object & object);

  virtual ~CUTS_CUTE_Replace_Model_Name_Action (void);

  virtual void replace (const CUTS_Property_Map & config);

  virtual void reset (void);

private:
  /// Target object to replace name.
  GME::Object object_;

  /// The old value of the name.
  ACE_CString old_value_;
};

/**
 * @class CUTS_CUTE_Replace_Model_Attribute_Action
 */
class CUTS_CUTE_Replace_Model_Attribute_Action :
  public CUTS_CUTE_Model_Interpreter_Action
{
public:
  /**
   * Initializing constructors.
   */
  CUTS_CUTE_Replace_Model_Attribute_Action (const GME::Attribute & attr);

  virtual ~CUTS_CUTE_Replace_Model_Attribute_Action (void);

  virtual void replace (const CUTS_Property_Map & config);

  virtual void reset (void);

private:
  GME::Attribute attr_;

  /// The old value of the attribute.
  ACE_CString old_value_;
};

#if defined (__CUTS_INLINE__)
#include "Model_Interpreter_Action.inl"
#endif

#endif  // !defined _CUTS_CUTE_MODEL_INTERPRETER_ACTION_H_
