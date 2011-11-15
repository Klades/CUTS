// -*- C++ -*-

//=============================================================================
/**
 * @file      mem_action_t.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_MEM_ACTION_T_H_
#define _CUTS_MEM_ACTION_T_H_

#include "type_t.h"
#include "value_of_t.h"

//=============================================================================
/**
 * @fn CUTS_invoke0_t
 */
//=============================================================================

template <typename R, typename M, typename T>
inline R CUTS_invoke0_t (M method, T t)
{
  return (CUTS_value_of (t).*method) ();
}

/**
 * @overload
 */
template <typename R, typename M, typename T>
inline R CUTS_invoke0_t (M method, T * t)
{
  return (t->*method) ();
}

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename R, typename M, typename T,
          typename A1>
inline R CUTS_invoke1_t (M method, T t, A1 a1)
{
  return (CUTS_value_of (t).*method) (a1);
}

template <typename R, typename M, typename T,
          typename A1>
inline R CUTS_invoke1_t (M method, T * t, A1 a1)
{
  return (t->*method) (a1);
}

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename R, typename M, typename T,
          typename A1, typename A2>
inline R CUTS_invoke2_t (M method, T t, A1 a1, A2 a2)
{
  return (CUTS_value_of (t).*method) (a1, a2);
}

template <typename R, typename M, typename T,
          typename A1, typename A2>
inline R CUTS_invoke2_t (M method, T * t, A1 a1, A2 a2)
{
  return (t->*method) (a1, a2);
}

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename R, typename M, typename T,
          typename A1, typename A2, typename A3>
inline R CUTS_invoke3_t (M method, T t, A1 a1, A2 a2, A3 a3)
{
  return (CUTS_value_of (t).*method) (a1, a2, a3);
}

template <typename R, typename M, typename T,
          typename A1, typename A2, typename A3>
inline R CUTS_invoke3_t (M method, T * t, A1 a1, A2 a2, A3 a3)
{
  return (t->*method) (a1, a2, a3);
}

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename R, typename M, typename T,
          typename A1, typename A2, typename A3, typename A4>
inline R CUTS_invoke4_t (M method, T t, A1 a1, A2 a2, A3 a3, A4 a4)
{
  return (CUTS_value_of (t).*method) (a1, a2, a3, a4);
}

template <typename R, typename M, typename T,
          typename A1, typename A2, typename A3, typename A4>
inline R CUTS_invoke4_t (M method, T * t, A1 a1, A2 a2, A3 a3, A4 a4)
{
  return (t->*method) (a1, a2, a3, a4);
}

//=============================================================================
/**
 *
 */
//=============================================================================

template <typename R, typename M, typename T,
          typename A1, typename A2, typename A3, typename A4, typename A5>
inline R CUTS_invoke5_t (M method, T t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
  return (CUTS_value_of (t).*method) (a1, a2, a3, a4, a5);
}

template <typename R, typename M, typename T,
          typename A1, typename A2, typename A3, typename A4, typename A5>
inline R CUTS_invoke5_t (M method, T * t, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
  return (t->*method) (a1, a2, a3, a4, a5);
}

//=============================================================================
/**
 * @struct CUTS_mem_action0_t
 */
//=============================================================================

template <typename R, typename M, typename T>
struct CUTS_mem_action0_t
{
  /// Type definition of the object type.
  typedef T type;

  /// Type definition of the return type.
  typedef R return_type;

  /// Type definition of the method type.
  typedef R (M::*method_type) (void);

  inline CUTS_mem_action0_t (method_type method, T object)
  : method_ (method),
    object_ (object)
  {
  }

  inline R operator () (void) const
  {
    return CUTS_invoke0_t <R> (this->method_, this->object_);
  }

private:
  /// Pointer to the method.
  method_type method_;

  /// Target object of method.
  T object_;
};

//=============================================================================
/**
 * CUTS_mem_action1_t
 */
//=============================================================================

template <typename R,  typename M, typename T,
          typename P1>
struct CUTS_mem_action1_t
{
  /// Type definition of the object type.
  typedef T type;

  /// Type definition of the return type.
  typedef R return_type;

  /// Type definition of the method type.
  typedef R (M::*method_type) (P1);

  inline CUTS_mem_action1_t (method_type method, T object)
  : method_ (method),
    object_ (object)
  {

  }

  template <typename A1>
  inline R operator () (A1 arg1) const
  {
    return CUTS_invoke1_t <R> (this->method_, this->object_, arg1);
  }

private:
  /// Target method of the object to invoke.
  method_type method_;

  /// The target object.
  T object_;
};

//=============================================================================
/**
 * CUTS_mem_action2_t
 */
//=============================================================================

template <typename R,  typename M, typename T,
          typename P1, typename P2>
struct CUTS_mem_action2_t
{
  typedef R (M::*method_type) (P1, P2);

  inline CUTS_mem_action2_t (method_type method, T object)
  : method_ (method),
    object_ (object)
  {

  }

  template <typename A1, typename A2>
  inline R operator () (A1 arg1, A2 arg2) const
  {
    return CUTS_invoke2_t <R> (this->method_, this->object_, arg1, arg2);
  }

private:
  method_type method_;

  T object_;
};


//=============================================================================
/**
 * CUTS_mem_action3_t
 */
//=============================================================================

template <typename R,  typename M, typename T,
          typename P1, typename P2, typename P3>
struct CUTS_mem_action3_t
{
  typedef R (M::*method_type) (P1, P2, P3);

  inline CUTS_mem_action3_t (method_type method, T object)
  : method_ (method),
    object_ (object)
  {

  }

  template <typename A1, typename A2, typename A3>
  inline R operator () (A1 arg1, A2 arg2, A3 arg3) const
  {
    return CUTS_invoke3_t <R> (this->method_, this->object_, arg1, arg2, arg3);
  }

private:
  method_type method_;

  T object_;
};


//=============================================================================
/**
 * CUTS_mem_action4_t
 */
//=============================================================================

template <typename R,  typename M, typename T,
          typename P1, typename P2, typename P3, typename P4>
struct CUTS_mem_action4_t
{
  typedef R (M::*method_type) (P1, P2, P3, P4);

  inline CUTS_mem_action4_t (method_type method, T object)
  : method_ (method),
    object_ (object)
  {

  }

  template <typename A1, typename A2, typename A3, typename A4>
  inline R operator () (A1 arg1, A2 arg2, A3 arg3, A4 arg4) const
  {
    return CUTS_invoke4_t <R> (this->method_, this->object_, arg1, arg2, arg3, arg4);
  }

private:
  method_type method_;

  T object_;
};

//=============================================================================
/**
 * CUTS_mem_action5_t
 */
//=============================================================================

template <typename R,  typename M, typename T,
          typename P1, typename P2, typename P3, typename P4, typename P5>
struct CUTS_mem_action5_t
{
  typedef R (M::*method_type) (P1, P2, P3, P4, P5);

  inline CUTS_mem_action5_t (method_type method, T object)
  : method_ (method),
    object_ (object)
  {

  }

  template <typename A1, typename A2, typename A3,
            typename A4, typename A5>
  inline R operator () (A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) const
  {
    return CUTS_invoke5_t <R> (this->method_, this->object_, arg1, arg2, arg3, arg4, arg5);
  }

private:
  method_type method_;

  T object_;
};

//=============================================================================
/**
 * CUTS_mem_action
 *
 * Factory operation(s) that create the appropriate member action functor
 * for object methods.
 */
//=============================================================================

template <typename R, typename M, typename T>
CUTS_mem_action0_t <R, M, T>
CUTS_action (R (M::*method) (void), T object)
{
  typedef CUTS_mem_action0_t <R, M, T> mem_action_t;
  return mem_action_t (method, object);
}

template <typename R,  typename M, typename T,
          typename P1>
CUTS_mem_action1_t <R, M, T, P1>
CUTS_action (R (M::*method) (P1), T object)
{
  typedef CUTS_mem_action1_t <R, M, T, P1> mem_action_t;
  return mem_action_t (method, object);
}

template <typename R,  typename M, typename T,
          typename P1, typename P2>
CUTS_mem_action2_t <R, M, T, P1, P2>
CUTS_action (R (M::*method) (P1, P2), T object)
{
  typedef CUTS_mem_action2_t <R, M, T, P1, P2> mem_action_t;
  return mem_action_t (method, object);
}

template <typename R,  typename M, typename T,
          typename P1, typename P2, typename P3>
CUTS_mem_action3_t <R, M, T, P1, P2, P3>
CUTS_action (R (M::*method) (P1, P2, P3), T object)
{
  typedef CUTS_mem_action3_t <R, M, T, P1, P2, P3> mem_action_t;
  return mem_action_t (method, object);
}

template <typename R,  typename M, typename T,
          typename P1, typename P2, typename P3, typename P4>
CUTS_mem_action4_t <R, M, T, P1, P2, P3, P4>
CUTS_action (R (M::*method) (P1, P2, P3, P4), T object)
{
  typedef CUTS_mem_action4_t <R, M, T, P1, P2, P3, P4> mem_action_t;
  return mem_action_t (method, object);
}

template <typename R, typename M, typename T,
          typename P1, typename P2, typename P3, typename P4, typename P5>
CUTS_mem_action5_t <R, M, T, P1, P2, P3, P4, P5>
CUTS_action (R (M::*method) (P1, P2, P3, P4, P5), T object)
{
  typedef CUTS_mem_action5_t <R, M, T, P1, P2, P3, P4, P5> mem_action_t;
  return mem_action_t (method, object);
}

#endif  // !defined _CUTS_MEM_ACTION_T_H_
