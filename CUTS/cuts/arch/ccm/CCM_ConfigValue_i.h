// -*- C++ -*-

//=============================================================================
/**
 *  @file       CCM_ConfigValue_i.h
 *
 *  $Id$
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CUTS_CCM_CONFIGVALUE_I_H_
#define _CUTS_CCM_CONFIGVALUE_I_H_

#include "ccm/CCM_StandardConfiguratorC.h"
#include "CCM_export.h"

/**
 * @class CUTS_CCM_ConfigValue_i
 */
class CUTS_CCM_Export CUTS_CCM_ConfigValue_i :
  public virtual ::OBV_Components::ConfigValue,
  public virtual ::CORBA::DefaultValueRefCountBase
{
public:
  CUTS_CCM_ConfigValue_i (void);

  CUTS_CCM_ConfigValue_i (const char* name, const CORBA::Any & value);

  virtual ~CUTS_CCM_ConfigValue_i (void);
};

/**
 * @class CUTS_CCM_ConfigValue_Factory
 */
class CUTS_CCM_Export CUTS_CCM_ConfigValue_Factory :
  public ::Components::ConfigValue_init
{
public:
  /// Default constructor.
  CUTS_CCM_ConfigValue_Factory (void);

  /// Destructor.
  virtual ~CUTS_CCM_ConfigValue_Factory (void);

  virtual ::CORBA::ValueBase * create_for_unmarshal (void);
};

#endif
