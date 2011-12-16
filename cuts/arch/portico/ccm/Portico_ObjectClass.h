// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_ObjectClass.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_OBJECTCLASS_H_
#define _PORTICO_OBJECTCLASS_H_

#include "RTI.hh"
#include <memory>

#include "Portico_ObjectClass_Trait_T.h"
#include "Portico_CCM_stub_export.h"

/**
 * @class Portico_ObjectClass
 *
 * Base class for ObjectClass events. This base class does not
 * contain any content. Instead, it requires that all ObjectClass
 * element provide a mechanism for reading and writing attributes
 * to and from attribute sets, respectively.
 */
class Portico_CCM_STUB_Export Portico_ObjectClass
{
public:
  /// Default constructor.
  Portico_ObjectClass (RTI::ObjectClassHandle hla_type);

  /// Destructor.
  virtual ~Portico_ObjectClass (void);

  /**
   * Read attribute from the handle set.
   *
   * @param[in]       attrs         The attribute handle set
   */
  virtual void __hla_read_attributes (const RTI::AttributeHandleValuePairSet &) = 0;

  /**
   * Write attributes to the handle set.
   *
   * @param[in]       attrs         The attribute handle set
   */
  virtual void __hla_write_attributes (RTI::AttributeHandleValuePairSet &) const = 0;

  /// Get the object type.
  RTI::ObjectClassHandle __hla_type (void) const;

protected:
  /// Handle to this object class type.
  RTI::ObjectClassHandle hla_type_;
};

#endif  // !defined _PORTICO_OBJECTCLASS_H_
