// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Object.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_OBJECT_T_H_
#define _CUTS_TCPIP_OBJECT_T_H_

#include "ace/Atomic_Op_T.h"
#include "ace/Null_Mutex.h"
#include "ace/Thread_Mutex.h"
#include "TCPIP_Object.h"

/**
 * @class CUTS_TCPIP_Object_T
 *
 * Base class for all dynamically created objects of the TCPIP architecture.
 */
template <typename MUTEX>
class CUTS_TCPIP_Object_T : public CUTS_TCPIP_Object
{
public:
  /// Type definition for the lock type.
  typedef MUTEX lock_type;

  /// Default constructor for the object.
  CUTS_TCPIP_Object_T (void);

  /// Increment the reference count.
  virtual void incr_refcount (void);

  /**
   * Decrement the reference count. Once the reference count reaches
   * zero, then the object is destroyed.
   */
  virtual void decr_refcount (void);

  /**
   * Get the current reference count.
   *
   * @return        The current reference count.
   */
  virtual size_t refcount (void) const;

protected:
  /// Destructor for the object.
  virtual ~CUTS_TCPIP_Object_T (void);

private:
  /// Reference count for the object.
  mutable ACE_Atomic_Op <MUTEX, size_t> refcount_;
};


/// Type definition of a single-threaded object. This object will be
/// accessed by only one thread of execution.
typedef CUTS_TCPIP_Object_T <ACE_Null_Mutex> CUTS_TCPIP_ST_Object;

/// Type definition of a multi-threaded object. This object will be
/// accessed by multiple threads of execution.
typedef CUTS_TCPIP_Object_T <ACE_RW_Thread_Mutex> CUTS_TCPIP_MT_Object;

#if defined (__CUTS_INLINE__)
#include "TCPIP_Object_T.inl"
#endif

#include "TCPIP_Object_T.cpp"

#endif  // !defined _CUTS_TCPIP_OBJECT_T_H_
