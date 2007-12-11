// -*- C++ -*-

//=============================================================================
/**
 * @file      DB_Parameter.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_PARAMETER_H_
#define _CUTS_DB_PARAMETER_H_

#include "DB_Exception.h"

// Forward decl.
class CUTS_DB_Date_Time_Impl;

//=============================================================================
/**
 * @class CUTS_DB_Parameter
 *
 * Base class for parameters of different database implementations.
 */
//=============================================================================

class CUTS_DB_UTILS_Export CUTS_DB_Parameter
{
public:
  /// The types of parameters supported.
  enum Parameter_Type
  {
    /// The parameter type is unknown.
    PT_UNKNOWN,
    /// The parameter is of boolean type.
    PT_BOOL,
    /// The parameter is of char type.
    PT_CHAR,
    /// The parameter is a short integer.
    PT_SHORT,
    /// The parameter is a unsigned short type.
    PT_USHORT,
    /// The parameter is a long type.
    PT_LONG,
    /// The parameter is a unsigned long type.
    PT_ULONG,
    /// The parameter is a float type.
    PT_FLOAT,
    /// The parameter is a double type.
    PT_DOUBLE,
    /// The parameter is a date type.
    PT_DATE,
    /// The parameter is a time type.
    PT_TIME,
    /// The parameter is a date/time type.
    PT_DATETIME
  };

  /// The direction of the parameter.
  enum Direction_Type
  {
    /// Parameter is an input type.
    DIRECTION_INPUT,

    /// Parameter is an output type.
    DIRECTION_OUTPUT,

    /// Parameter is an inout type.
    DIRECTION_INOUT
  };

  /**
   * Initializing contructor.
   *
   * @param[in]     type      The parameter type.
   * @param[in]     index     Index of the parameter.
   */
  CUTS_DB_Parameter (void);

  /// Destructor.
  virtual ~CUTS_DB_Parameter (void);

  /**
   * Get the type of the parameter.
   *
   * @return The parameter type.
   */
  Parameter_Type type (void) const;

  /**
   * Get the direction of the parameter. The direction will be
   * one of the values in the Direction_Type enumeration.
   *
   * @return      Direction of the parameter.
   */
  Direction_Type direction (void) const;

  /**
   * Get the index of the parameter.
   *
   * @return    The index of the parameter; 1-based.
   */
  size_t index (void) const;

  /**
   * Determine if the parameter is null.
   *
   * @retval      1       The parameter is null.
   * @retval      0       The parameter is not null.
   */
  int is_null (void) const;

  /// Make the parameter a NULL value.
  virtual void null (void) = 0;

  /**
   * Bind the parameter to a character buffer. If the size of
   * the buffer is 0, then it is buffer is NULL terminated.
   *
   * @param[in]       buffer    Source character buffer.
   * @param[in]       bufsize   Size of the buffer.
   */
  virtual void bind (char * buffer, size_t bufsize) = 0;

  /**
   * Bind the parameter to a short value.
   *
   * @param[in]       buffer    Source short value.
   */
  virtual void bind (short * buffer) = 0;
  /**
   * Bind the parameter to a unsigned short value.
   *
   * @param[in]       buffer    Source unsigned short value.
   */
  virtual void bind (u_short * buffer) = 0;

  /**
   * Bind the parameter to a signed long value.
   *
   * @param[in]       buffer    Source signed long value.
   */
  virtual void bind (long * buffer) = 0;

  /**
   * Bind the parameter to a unsigned long value.
   *
   * @param[in]       buffer    Source unsigned long value.
   */
  virtual void bind (u_long * buffer) = 0;

  /**
   * Bind the parameter to a float value.
   *
   * @param[in]       buffer    Source float value.
   */
  virtual void bind (float * buffer) = 0;

  /**
   * Bind the parameter to a double value.
   *
   * @param[in]       buffer    Source double value.
   */
  virtual void bind (double * buffer) = 0;

  /**
   * Bind the parameter to a data/time value.
   *
   * @param[in]       datetime    Source date/time value.
   */
  virtual void bind (CUTS_DB_Date_Time_Impl * datetime) = 0;

  /**
   * Set the length of the parameter. This is necessary of the
   * parameter is already bound to a buffer, and the length of the
   * input buffer has changed.
   *
   * @param[in]       len         Length of the buffer.
   */
  virtual void length (long len) = 0;

  /**
   * Get the current length/size of the parameter.
   *
   * @return          The length/size of the parameter.
   */
  virtual long length (void) = 0;

protected:
  /// The index of the parameter.
  int index_;

private:
  /// The parameter type.
  Parameter_Type type_;

  /// The direction of the parameter.
  Direction_Type direction_;

  /// Null flags for the parameter.
  int null_;
};

#if defined (__CUTS_INLINE__)
#include "DB_Parameter.inl"
#endif

#endif  // !defined _CUTS_DB_PARAMETER_H_