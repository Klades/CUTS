// -*- C++ -*-

//=============================================================================
/**
 *  @file         Portico_AttributeHandle.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _PORTICO_ATTRIBUTEHANDLE_H_
#define _PORTICO_ATTRIBUTEHANDLE_H_

#include "ace/SString.h"
#include "RTI.hh"

#include "Portico_CCM_stub_export.h"

/**
 * @class Portico_AttributeHandle
 */
class Portico_CCM_STUB_Export Portico_AttributeHandle
{
public:
  /// Get the attribute's handle.
  RTI::AttributeHandle handle (void);

  /// Covert the object to an RTI::AttributeHandle.
  operator RTI::AttributeHandle ();

  /// Destructor.
  virtual ~Portico_AttributeHandle (void);

  /**
   * Read an attribute from the handle value set.
   *
   * @param[in]         attrs       Source handle value set
   * @param[in]         i           Index of attribute value
   */
  virtual void read (const RTI::AttributeHandleValuePairSet & attrs, RTI::ULong i) = 0;

  /**
   * Write the attribute to the handle value set.
   *
   * @param[in]         attrs       Target handle value set
   */
  virtual void write (RTI::AttributeHandleValuePairSet & attrs) const = 0;

protected:
  /**
   * Initializing constuctor.
   *
   * @param[in]         handle        Handle to object class
   */
  Portico_AttributeHandle (RTI::AttributeHandle handle);

  /// Handle for the ObjectClass
  RTI::AttributeHandle handle_;
};

/**
 * @class Portico_AttributeHandle_T
 *
 * Parameterized wrapper class for the RTI AttributeHandle. This
 * reading/writing an attribute values.
 */
template <typename T>
class Portico_AttributeHandle_T : public Portico_AttributeHandle
{
public:
  /**
   * Initializing constuctor.
   *
   * @param[in]         handle        Handle to object class
   */
  Portico_AttributeHandle_T (RTI::AttributeHandle handle)
    : Portico_AttributeHandle (handle)
  {

  }

  /// Destructor
  virtual ~Portico_AttributeHandle_T (void)
  {

  }

  /**
   * Read the attribute's value from the provided handle set. The
   * value is store locally in the value object.
   */
  void read (const RTI::AttributeHandleValuePairSet & attrs, RTI::ULong i)
  {
    ACE_ASSERT (attrs.getValueLength (i) == sizeof (T));

    RTI::ULong length;
    attrs.getValue (i, (char *)&this->value_, length);
  }

  void write (RTI::AttributeHandleValuePairSet & attrs) const
  {
    attrs.add (this->handle_, (char *)&this->value_, sizeof (T));
  }

  void value (const T & val)
  {
    this->value_ = val;
  }

  T & value (void)
  {
    return this->value_;
  }

  const T & value (void) const
  {
    return this->value_;
  }

private:
  /// The attribute's value stored in object format.
  T value_;
};

/**
 * @class Portico_AttributeHandle_T
 *
 * Parameterized wrapper class for the RTI AttributeHandle. This
 * reading/writing an attribute values.
 */
template < >
class Portico_CCM_STUB_Export Portico_AttributeHandle_T <ACE_CString> :
  public Portico_AttributeHandle
{
public:
  /**
   * Initializing constuctor.
   *
   * @param[in]         handle        Handle to object class
   */
  Portico_AttributeHandle_T (RTI::AttributeHandle handle);

  /// Destuctor.
  virtual ~Portico_AttributeHandle_T (void);

  /**
   * Read the attribute's value from the provided handle set. The
   * value is store locally in the value object.
   */
  void read (const RTI::AttributeHandleValuePairSet & attrs, RTI::ULong i);
  void write (RTI::AttributeHandleValuePairSet & attrs) const;

  void value (const ACE_CString & val);
  const ACE_CString & value (void) const;

private:
  /// The attribute's value stored in object format.
  ACE_CString value_;
};

#endif  // !defined _PORTICO_ATTRIBUTEHANDLE_H_
