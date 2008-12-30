// -*- C++ -*-

//=============================================================================
/**
 * @file        Barrier_i.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BARRIER_I_H_
#define _CUTS_BARRIER_I_H_

#include "../barrierS.h"
#include "ace/Unbounded_Set.h"

/**
 * @class ACE_Node
 *
 * Specialization of the ACE_Node for CORBA _var types.
 */
template <class C>
class ACE_Node <CUTS::BarrierCallback_var, C>
{
  friend class ACE_Unbounded_Set_Ex <CUTS::BarrierCallback_var, C>;
  friend class ACE_Unbounded_Set_Ex_Iterator <CUTS::BarrierCallback_var, C>;
  friend class ACE_Unbounded_Set_Ex_Const_Iterator <CUTS::BarrierCallback_var, C>;

public:
  /// This isn't necessary, but it keeps some compilers happy.
  ~ACE_Node (void);

private:
  ACE_Node (const CUTS::BarrierCallback_var &i, ACE_Node <CUTS::BarrierCallback_var, C> * n);
  ACE_Node (ACE_Node <CUTS::BarrierCallback_var, C> * n = 0, int = 0);
  ACE_Node (const ACE_Node <CUTS::BarrierCallback_var, C> &n);

  /// Not possible
  void operator = (const ACE_Node <CUTS::BarrierCallback_var, C> &);

  /// Pointer to next element in the list of ACE_Nodes.
  ACE_Node <CUTS::BarrierCallback_var, C> * next_;

  /// Current value of the item in this node.
  CUTS::BarrierCallback_var item_;
};

/**
 * @class CUTS_Barrier_i
 *
 * Basic implementation of the CUTS::Barrier interface.
 */
class CUTS_Barrier_i : public POA_CUTS::Barrier
{
public:
  /// Default constructor.
  CUTS_Barrier_i (size_t & count);

  /// Destructor.
  virtual ~CUTS_Barrier_i (void);

  /**
   * Wait for all clients to reach the barrier.
   */
  void register_client (CUTS::BarrierCallback_ptr node);

  void broadcast (void);

  int close (void);

private:
  /// Number of clients to listen.
  size_t & count_;

  typedef ACE_Unbounded_Set <CUTS::BarrierCallback_var> set_type;

  set_type nodes_;
};

#if defined (__CUTS_INLINE__)
#include "Barrier_i.inl"
#include "Barrier_T.inl"
#endif

#include "Barrier_T.cpp"

#endif  // !defined _CUTS_BARRIER_I_H_
