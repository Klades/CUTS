// -*- C++ -*-

//=============================================================================
/**
 * @file          Static_Node_T.h
 *
 * Summary classes for the endpoint data.
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _CUTS_STATIC_NODE_T_H_
#define _CUTS_STATIC_NODE_T_H_

#include "config.h"

/**
 * @class CUTS_Static_Node_T
 */
template <typename T>
class CUTS_Static_Node_T
{
public:
  /// Value type for the node.
  typedef T value_type;

  /// Default constructor.
  CUTS_Static_Node_T (void);

  /**
   * Initializing constructor.
   *
   * @param[in]       item        Target item
   */
  CUTS_Static_Node_T (const T & item,
                     CUTS_Static_Node_T <T> * next = 0,
                     CUTS_Static_Node_T <T> * prev = 0);

  /// Destructor.
  ~CUTS_Static_Node_T (void);

  /// The item contained in the node.
  T item_;

  /// Pointer to the next node.
  CUTS_Static_Node_T <T> * next_;

  /// Pointer to the previous node.
  CUTS_Static_Node_T <T> * prev_;
};

#if defined (__CUTS_INLINE__)
#include "Static_Node_T.inl"
#endif

#include "Static_Node_T.cpp"

#endif  // !defined _CUTS_STATIC_NODE_T_H_
