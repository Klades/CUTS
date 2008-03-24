// -*- C++ -*-

//=============================================================================
/**
 * @file       Log_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_LOG_T_H_
#define _CUTS_LOG_T_H_

#include "cuts/config.h"
#include "ace/Containers_T.h"

//=============================================================================
/**
 * @class CUTS_Log_T
 *
 * Efficient log class for storing entries. The log is built on top
 * of an array and is optimized for fast access to its entries. It
 * also grows automatically once all entries in the record are used.
 * The log is also thread-safe, depending on the type of LOCK used
 * to parameterize this class.
 */
//=============================================================================

template <typename T, typename LOCK>
class CUTS_Log_T : protected ACE_Array_Base <T>
{
public:
  /// Type definition of the lock type.
  typedef LOCK lock_type;

  /// Type definition of the iterator.
  typedef typename ACE_Array_Base <T>::iterator iterator;

  /// Type definition of the constant iterator.
  typedef typename ACE_Array_Base <T>::const_iterator const_iterator;

  /// Type definition of the size type.
  typedef typename ACE_Array_Base <T>::size_type size_type;

  /// Type definition of the pointer type.
  typedef typename ACE_Array_Base <T>::pointer pointer;

  /**
   * Initializing constructor.
   *
   * @param[in]         size        Initial size of the log.
   * @param[in]         grow        Allow the log to grow as needed.
   */
  CUTS_Log_T (typename size_type size = 0, 
              bool auto_grow = true);

  /**
   * Copy constructor.
   *
   * @param[in]         log         The source log.
   */
  CUTS_Log_T (const CUTS_Log_T & log);

  /// Destructor
  ~CUTS_Log_T (void);

  /**
   * Get the number of free records in the log. Free records are
   * considered those that have not been used for logging metrics.
   *
   * @return        The number of free records.
   */
  typename size_type free_size (void) const;

  /**
   * Get the number of used records in the log. Used records are
   * considered those that have been used for logging metrics.
   *
   * @return        The number of used records.
   */
  typename size_type used_size (void) const;

  /// Reset the log by converting all used records to free records.
  void reset (void);

  /**
   * Get the next free record in the log. This version of the
   * method is thread-safe. It will also resize the underlying
   * logging buffer if necessary.
   *
   * @return          Pointer to the next free record.
   */
  T * next_free_record (void);

  // @{ @name Batch Mode Operations

  /**
   * Get the underlying mutual exclusion object.
   *
   * @return            The locking mechanism.
   */
  LOCK & lock (void);

  /**
   * Get the next free record in the list. This version of the
   * method is not thread-safe, and will not resize the underlying
   * logging buffer.
   *
   * @return            Pointer to the next free record.
   */
  T * next_free_record_no_lock (void);

  // @}

  /**
   * Assignment operator.
   *
   * @param[in]       log       Right-hand side of the operator.
   * @return          Reference to self.
   */
  const CUTS_Log_T & operator = (const CUTS_Log_T & log);

  // @{ @name STL-based iterators

  /// Get iterator to beginning of log.
  using ACE_Array_Base <T>::begin;

  /// Get iterator to end of log.
  using ACE_Array_Base <T>::end;

  /**
   * Get an iterator to the end of the used log entries. The state
   * of this element may, or may not be valid. It is advised that
   * you do not try to dereference this iterator.
   *
   * @return          Iterator object.
   */
  typename iterator used_end (void);

  /**
   * @overload
   */
  typename const_iterator used_end (void) const;

  // @}

  /**
   * Get the auto grow state of the log.
   *
   * @retval        true        Auto grow is enabled.
   * @retval        false       Auto grow is not enabled.
   */
  bool auto_grow (void) const;
  
  /**
   * Set the auto grow state of the log.
   *
   * @param[in]     flag        The auto grow state.
   */
  void auto_grow (bool flag);

  /**
   * Get the size of the log. This include both used, and unused 
   * entries in the log.
   *
   * @return        Size of the log.
   */
  typename size_type size (void) const;

  /**
   * Set the new size of the log. This will perserve the existing 
   * entries in the log.
   *
   * @retval        0       Successfully set the new size.
   * @retval        -1      Failed to set the new size.
   */
  int size (typename size_type new_size);

private:
  /// Thread-safe helper method to copy a log.
  void copy_log (const CUTS_Log_T & log);

  /// Implementation of the copy_log () function.
  void copy_log_i (const CUTS_Log_T & log);

  /// Number of used records in the log.
  size_t used_;

  /// Flag that determines if the log can grow when needed.
  bool auto_grow_;

  /// Lock for the log.
  mutable LOCK lock_;
};

#if defined (__CUTS_INLINE__)
#include "cuts/Log_T.inl"
#endif

#include "cuts/Log_T.cpp"

#endif  // !defined _CUTS_LOG_T_H_
