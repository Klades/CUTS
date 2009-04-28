// -*- C++ -*-

//=============================================================================
/**
 * @file        RawComponent.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef RAWCOMPONENT_H
#define RAWCOMPONENT_H

#include "ComponentLib.h"
#include "game/be/Plugin_T.h"
#include "game/be/Plugin_Impl.h"
#include "ace/SString.h"
#include "ace/Unbounded_Set.h"
#include "Interpreter_List.h"

/**
 * @class CUTS_CUTE
 *
 * Implementation of the CUTE plugin.
 */
class CUTS_CUTE :
  public GME::Plugin_Impl
{
public:
  /// Default constructor.
  CUTS_CUTE (void);

  /// Destructor.
  virtual ~CUTS_CUTE (void);

  /**
   * Handle the InvokeEx method.
   */
  int invoke_ex (GME::Project & project,
                 GME::FCO & fco,
                 GME::Collection_T <GME::FCO> & selected,
                 long flags);

private:
  void get_interpreters (const char * paradigm,
                         CUTS_CUTE_Interpreter_List & list);
};

GME_RAWCOMPONENT_DECL (GME::Plugin_T, CUTS_CUTE);

#endif  // !defined RAWCOMPONENT_H
