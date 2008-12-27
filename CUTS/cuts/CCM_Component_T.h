// -*- C++ -*-

//=============================================================================
/**
 * @file          CCM_Component_T.h
 *
 * $Id$
 *
 * @author        James H. Hill <j dot hill at vanderbilt dot edu>
 */
//=============================================================================

#ifndef _CUTS_CCM_COMPONENT_T_H_
#define _CUTS_CCM_COMPONENT_T_H_

#include "config.h"

/**
 * @class CUTS_CCM_Component_T
 *
 * Template class for CCM components. This class defines the required
 * methods that must be implemented by every CCM session component. 
 * This prevents the compiler from complaining about undefined methods
 * on the executor class. If a derived class needs to implement one
 * of the required methods, then it needs to only overload the method.
 */
template <typename T, typename CTX>
class CUTS_CCM_Component_T : public T
{
public:
  /// Type definition for the executor type.
  typedef T exec_type;

  /// Type definition for the context type.
  typedef CTX context_type;

  /// Default constructor.
  CUTS_CCM_Component_T (void);

  /// Destructor.
  virtual ~CUTS_CCM_Component_T (void);

  /**
   * Set the session context for the component. This gives the
   * component access to the outside world, i.e., the components
   * that is is connected.
   *
   * @param[in]       ctx           The context for the component.
   */
  virtual void set_session_context (Components::SessionContext_ptr ctx);

  virtual void ccm_activate (void);

  virtual void ciao_preactivate (void);

  virtual void ciao_postactivate (void);

  virtual void ccm_passivate (void);

  virtual void ccm_remove (void);

protected:
  /// The context for the component.
  typename CTX::_var_type ctx_;
};

#if defined (__CUTS_INLINE__)
#include "CCM_Component_T.inl"
#endif

#include "CCM_Component_T.cpp"

#endif  // !defined _CUTS_CCM_COMPONENT_T_H_
