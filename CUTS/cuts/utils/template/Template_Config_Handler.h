// -*- C++ -*-

//=============================================================================
/**
 * @file        Template_Config_List_Parser.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TEMPLATE_CONFIG_HANDLER_H_
#define _CUTS_TEMPLATE_CONFIG_HANDLER_H_

#include "Template_Common_export.h"

// Forward decl.
class CUTS_Property_Map;

/**
 * @class CUTS_Template_Config_Handler
 *
 * Base class for all template configuration handlers.
 */
class CUTS_TEMPLATE_COMMON_Export CUTS_Template_Config_Handler
{
public:
  /// Destructor.
  virtual ~CUTS_Template_Config_Handler (void);

  /**
   * Callback for handling a configuration
   *
   * @param[in]         config          Configuration to handle
   */
  virtual int handle_config (const CUTS_Property_Map & config) = 0;

protected:
  CUTS_Template_Config_Handler (void);
};

#if defined (__CUTS_INLINE__)
#include "Template_Config_Handler.inl"
#endif

#endif  // !defined _CUTS_TEMPLATE_CONFIG_HANDLER_H_
