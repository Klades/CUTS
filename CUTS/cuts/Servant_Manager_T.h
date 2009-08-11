// -*- C++ -*-

//=============================================================================
/**
 * @file        Servant_Manager_T.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_SERVANT_MANAGER_T_H_
#define _CUTS_SERVANT_MANAGER_T_H_

#include "config.h"
#include "tao/PortableServer/PortableServer.h"

/**
 * @class CUTS_Servant_Manager_T
 *
 * Helper class for managing the lifecycle of a servant. This object
 * behaves like the std::auto_ptr class.
 */
template <typename T>
class CUTS_Servant_Manager_T
{
public:
  /// Type definition of the servant type.
  typedef T type;

  /**
   * Initializing constructor.
   *
   * @param[in]       servant         Servant to host
   * @param[in]       manage          This object manages \a servant
   */
  CUTS_Servant_Manager_T (T * servant = 0, bool manage = true);

  /// Desturctor
  ~CUTS_Servant_Manager_T (void);

  /// Determine of the servant is managed.
  bool is_managed (void) const;

  /**
   * Reset the manager with a new servant.
   *
   * @param[in]       servant         Servant to host
   * @param[in]       manage          This object manages \a servant
   */
  int reset (T * servant = 0, bool manage = true);

  /**
   * Get a pointer to the actual servant.
   *
   * @return      The contained servant.
   */
  T * get (void);

  /**
   * Treat the servant manage as a pointer to the servant.
   *
   * @return      The contained servant.
   */
  T * operator -> (void);

  /**
   * Activate the servant under the specified POA.
   *
   * @param[in]   poa         Target POA for activation.
   */
  void activate (::PortableServer::POA_ptr poa);

  /// Deactivate the servant.
  void deactivate (void);

protected:
  /// Pointer to the servant.
  T * servant_;

  /// POA under which the servant is activated.
  ::PortableServer::POA_var poa_;

private:
  /// The servant is managed by this object.
  bool is_managed_;
};

/**
 * @class CUTS_Servant_Manager_T
 */
template <typename T, typename TRAITS>
class CUTS_Servant_Manager_Ex_T :
  public CUTS_Servant_Manager_T <T>
{
public:
  /// Type definition of the servant type.
  typedef typename CUTS_Servant_Manager_T <T>::type type;

  /// Type definition of the servant's traits.
  typedef TRAITS traits_type;

  /**
   * Initializing constructor.
   *
   * @param[in]       servant         Servant to host
   * @param[in]       manage          This object manages \a servant
   */
  CUTS_Servant_Manager_Ex_T (T * servant = 0, bool manage = true);

  /// Desturctor
  ~CUTS_Servant_Manager_Ex_T (void);

  /**
   * Activate the servant under the specified POA.
   *
   * @param[in]   poa         Target POA for activation.
   */
  void activate (::PortableServer::POA_ptr poa);

  /// Deactivate the servant.
  void deactivate (void);

  template <typename TRAIT>
  int set_trait_value (TRAIT trait, const ACE_CString & value);

  template <typename TRAIT>
  int get_trait_value (TRAIT trait, ACE_CString & value);

private:
  /// Traits of the servant manager.
  TRAITS traits_;
};

#if defined (__CUTS_INLINE__)
#include "Servant_Manager_T.inl"
#endif

#include "Servant_Manager_T.cpp"

#endif  // !defined _CUTS_SERVANT_MANAGER_T_H_
