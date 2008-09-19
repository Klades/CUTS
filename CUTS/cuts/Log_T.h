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

#include "CUTS_export.h"
#include "ace/Guard_T.h"
#include "ace/Containers_T.h"

// Forward decl.
template <typename T, typename LOCK> class CUTS_Log_Iterator_T;

// Forward decl.
template <typename T, typename LOCK> class CUTS_Log_Const_Iterator_T;

/**
 * @class CUTS_Log_T
 *
 * Efficient log class for storing entries. The log is built on top
 * of an array and is optimized for fast access to its entries. It
 * also grows automatically once all entries in the record are used.
 * The log is also thread-safe, depending on the type of LOCK used
 * to parameterize this class.
 */
template <typename T, typename LOCK>
class CUTS_Log_T
{
public:
  // Friend decl.
  friend class CUTS_Log_Iterator_T <T, LOCK>;
  friend class CUTS_Log_Const_Iterator_T <T, LOCK>;

  /// Type definition of the lock type.
  typedef LOCK lock_type;

  /// Type definition of the iterator.
  typedef CUTS_Log_Iterator_T <T, LOCK> iterator;

  /// Type definition of the constant iterator.
  typedef CUTS_Log_Const_Iterator_T <T, LOCK> const_iterator;

  typedef T * pointer;

  /**
   * Initializing constructor.
   *
   * @param[in]         size        Initial size of the log.
   * @param[in]         grow        Allow the log to grow as needed.
   */
  CUTS_Log_T (size_t chuck_size);

  CUTS_Log_T (const CUTS_Log_T & log);

  /// Destructor
  ~CUTS_Log_T (void);

  /**
   * Get the number of free records in the log. Free records are
   * considered those that have not been used for logging metrics.
   *
   * @return        The number of free records.
   */
  size_t free_size (void) const;

  /**
   * Get the number of used records in the log. Used records are
   * considered those that have been used for logging metrics.
   *
   * @return        The number of used records.
   */
  size_t used_size (void) const;

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

  /**
   * Assignment operator
   */
  const CUTS_Log_T & operator = (const CUTS_Log_T & log);

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

  /// Reset the log without acquiring a lock.
  void reset_no_lock (void);

  // @}

  /**
   * Get the size of the log. This include both used, and unused
   * entries in the log.
   *
   * @return        Size of the log.
   */
  size_t size (void) const;

  /**
   * Set the new size of the log. This will perserve the existing
   * entries in the log.
   *
   * @retval        0       Successfully set the new size.
   * @retval        -1      Failed to set the new size.
   */
  int size (size_t new_size);

private:

  void copy_i (const CUTS_Log_T & log);

  int size_i (size_t new_size);

  /// Allocation size for a chuck of records.
  size_t chunk_size_;

  /// The current size of the log; used + free space.
  size_t curr_size_;

  /// Number of used records in the log.
  size_t used_size_;

  /// Lock for the log.
  mutable LOCK lock_;

  /// Type definition for a chuck of records.
  typedef ACE_Array <T> chunk_type;

  /// Type definition for the underlying record log.
  typedef ACE_Array <chunk_type *> record_log;

  /// Collection of records.
  record_log records_;
};

/**
 * @class CUTS_Log_Iterator_T
 */
template <typename T, typename LOCK>
class CUTS_Log_Iterator_T
{
public:
  CUTS_Log_Iterator_T (CUTS_Log_T <T, LOCK> & log);

  ~CUTS_Log_Iterator_T (void);

  int done (void) const;

  int advance (void);

  T * operator -> (void);

  T & operator * (void);

private:
  CUTS_Log_T <T, LOCK> & log_;

  size_t index_;

  size_t offset_;

  size_t location_;

  size_t used_size_;

  // prevent the following operations
  CUTS_Log_Iterator_T (CUTS_Log_Iterator_T &);
  CUTS_Log_Iterator_T & operator = (const CUTS_Log_Iterator_T &);
};

/**
 * @class CUTS_Log_Const_Iterator_T
 */
template <typename T, typename LOCK>
class CUTS_Log_Const_Iterator_T
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         log       Target log.
   */
  CUTS_Log_Const_Iterator_T (const CUTS_Log_T <T, LOCK> & log);

  /// Destructor.
  ~CUTS_Log_Const_Iterator_T (void);

  /**
   * Determine if the iterator is done.
   *
   * @retval        0         Iterator is not done
   * @retval        1         Iterator is done
   */
  int done (void) const;

  /**
   * Move the next element in the log.
   *
   * @retval        1         There are more elements
   * @retval        0         There are no more elements
   */
  int advance (void);

  /**
   * Get a pointer reference to the next element. This treats
   * the iterator like a pointer.
   *
   * @return        Address of the current element.
   */
  const T * operator -> (void) const;

  /**
   * Get a reference to the next element.
   *
   * @return        Reference to current element.
   */
  const T & operator * (void) const;

private:
  const CUTS_Log_T <T, LOCK> & log_;

  size_t index_;

  size_t offset_;

  size_t location_;

  size_t used_size_;

  // prevent the following operations
  CUTS_Log_Const_Iterator_T (const CUTS_Log_Const_Iterator_T &);
  const CUTS_Log_Const_Iterator_T & operator = (const CUTS_Log_Const_Iterator_T &);
};

#if defined (__CUTS_INLINE__)
#include "Log_T.inl"
#endif

#include "Log_T.cpp"

#endif  // !defined _CUTS_LOG_T_H_
