// -*- C++ -*-

//=============================================================================
/**
 * @file          Parameter.h
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_DB_SQLITE_PARAMETER_H_
#define _CUTS_DB_SQLITE_PARAMETER_H_

#include "DB_SQLite_export.h"
#include "cuts/utils/db/DB_Parameter.h"

// Forward decl.
class CUTS_DB_SQLite_Parameter_List;

/**
 * @class CUTS_DB_SQLite_Parameter
 */
class CUTS_DB_SQLITE_Export CUTS_DB_SQLite_Parameter :
  public CUTS_DB_Parameter
{
  // Friend decl.
  friend class CUTS_DB_SQLite_Parameter_List;

public:
  /// Default constructor.
  CUTS_DB_SQLite_Parameter (void);

  /**
   * Copy constructor
   *
   * @param[in]       p         Source parameter
   */
  CUTS_DB_SQLite_Parameter (const CUTS_DB_SQLite_Parameter & p);

  /// Destructor.
  virtual ~CUTS_DB_SQLite_Parameter (void);

  /// Make the parameter a NULL value.
  virtual void null (void);

  /**
   * Bind the parameter to a character buffer. If the size of
   * the buffer is 0, then it is buffer is NULL terminated.
   *
   * @param[in]       buffer    Source character buffer.
   * @param[in]       bufsize   Size of the buffer.
   */
  virtual void bind (char * buffer, size_t bufsize);

  virtual void bind (const char * buffer, size_t bufsize);

  /**
   * Bind the parameter to a short value.
   *
   * @param[in]       buffer    Source short value.
   */
  virtual void bind (ACE_INT16 & value);
  /**
   * Bind the parameter to a unsigned short value.
   *
   * @param[in]       buffer    Source unsigned short value.
   */
  virtual void bind (ACE_UINT16 & value);

  /**
   * Bind the parameter to a signed long value.
   *
   * @param[in]       buffer    Source signed long value.
   */
  virtual void bind (ACE_INT32 & buffer);

  /**
   * Bind the parameter to a unsigned long value.
   *
   * @param[in]       buffer    Source unsigned long value.
   */
  virtual void bind (ACE_UINT32 & buffer);

  virtual void bind (ACE_INT64 & buffer);

  virtual void bind (ACE_UINT64 & buffer);

  /**
   * Bind the parameter to a float value.
   *
   * @param[in]       buffer    Source float value.
   */
  virtual void bind (float & buffer);

  /**
   * Bind the parameter to a double value.
   *
   * @param[in]       buffer    Source double value.
   */
  virtual void bind (double & value);

  /**
   * Bind the parameter to a data/time value.
   *
   * @param[in]       datetime    Source date/time value.
   */
  virtual void bind (CUTS_DB_Date_Time & dt);

  /**
   * Set the length of the parameter. This is necessary of the
   * parameter is already bound to a buffer, and the length of the
   * input buffer has changed.
   *
   * @param[in]       len         Length of the buffer.
   */
  virtual void length (long len);

  /**
   * Get the current length/size of the parameter.
   *
   * @return          The length/size of the parameter.
   */
  virtual long length (void);

  /**
   * Assignment operator
   *
   * @param[in]       rhs       Right-hand side of operator
   * @param[in]       Reference to this object
   */
  const CUTS_DB_SQLite_Parameter & operator = (const CUTS_DB_SQLite_Parameter & rhs);

private:
  void bind_int (int val);

  void bind_double (double d);

  void reset (const CUTS_DB_SQLite_Parameter_List * owner, int index);

  /// List that owns the parameter.
  const CUTS_DB_SQLite_Parameter_List * owner_;
};

#if defined (__CUTS_INLINE__)
#include "Parameter.inl"
#endif

#endif  // !defined _CUTS_DB_SQLITE_PARAMETER_H_
