// $Id$

//=============================================================================
/**
 * @file        Template_Engine.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEMPATE_ENGINE_H_
#define _CUTS_TEMPATE_ENGINE_H_

#include "cuts/config.h"
#include "cuts/utils/Text_Processor.h"

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_Template_Engine
 */
class CUTS_Template_Engine
{
public:
  /// Default constructor.
  CUTS_Template_Engine (const CUTS_Property_Map & map);

  /// Destructor.
  ~CUTS_Template_Engine (void);

  bool process (const char * file,
                std::ostream & out,
                bool use_env = false,
                bool ignore_variables = false,
                bool ignore_commands = false);

private:
  CUTS_Text_Processor tp_;
};

#if defined (__CUTS_INLINE__)
#include "Template_Engine.inl"
#endif

#endif  // !defined _CUTS_TEMPATE_ENGINE_H_
