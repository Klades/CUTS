// -*- C++ -*-

//=============================================================================
/**
 *  @file         DDS_Container.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _ICCM_DDS_CONTAINER_H_
#define _ICCM_DDS_CONTAINER_H_

#include "cuts/iccm/deployment/Container_T.h"

namespace iCCM
{

/**
 * @class DDS_Container
 */
template <typename T>
class DDS_Container :
  public Container_T <typename T::container_type,
                      typename T::component_instance_handler_type,
                      typename T::container_strategy_type,
                      typename T::servant_type>
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]           handler         Pointer to the parent handler
   * @param[in]           the_POA         POA to pass to base class
   */
  DDS_Container (typename T::component_instance_handler_type * handler,
                 ::PortableServer::POA_ptr the_POA);

  /// Destructor.
  virtual ~DDS_Container (void);

private:
  // prevent the following operations
  DDS_Container (void);
  DDS_Container (const DDS_Container &);
  const DDS_Container & operator = (const DDS_Container &);
};

}

#if defined (__CUTS_INLINE__)
#include "DDS_Container.inl"
#endif

#include "DDS_Container.cpp"

#endif  // !defined _ICCM_DDS_CONTAINER_H_
