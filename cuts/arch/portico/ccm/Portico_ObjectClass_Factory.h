// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_ObjectClass_Factory.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_OBJECTCLASS_FACTORY_H_
#define _PORTICO_OBJECTCLASS_FACTORY_H_

#include "RTI.hh"
#include "Portico_CCM_stub_export.h"

// Forward decl.
class Portico_ObjectClass;

/**
 * @class Message_ObjectClass_Factory
 *
 * The ObjectClass implementation for the ::Message event.
 */
class Portico_CCM_STUB_Export Portico_ObjectClass_Factory
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       handle          The object class handle
   */
  Portico_ObjectClass_Factory (RTI::ObjectClassHandle handle);

  /// Destructor.
  virtual ~Portico_ObjectClass_Factory (void);

  /// Create a new object class event.
  virtual Portico_ObjectClass * create (void) = 0;

  /**
   * Get the attribute handles for the object class.
   *
   * @param[out]      handles         The attribute handles
   */
  virtual void get_attributes (RTI::AttributeHandleSet & handles) const = 0;

  /// Get the object class handle.
  virtual RTI::ObjectClassHandle get_handle (void) const;

protected:
  /// Handle for the ObjectClass
  RTI::ObjectClassHandle handle_;
};

#endif  // !defined _PORTICO_OBJECTCLASS_FACTORY_H_
