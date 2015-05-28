// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_Servant.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _SERVANT_H_
#define _SERVANT_H_

#include "tao/PortableServer/Servant_Base.h"
#include "ccm/CCM_StandardConfiguratorC.h"

#include "ace/SString.h"

#include "Servant_export.h"

namespace iCCM
{

// Forward decls.
class EventConsumer;
class Publisher;
class Publisher_Table;

/**
 * @class Servant
 *
 * Base class for the CCM servant. This class defines the required
 * methods for interfacing with the Container object.
 */
class ICCM_SERVANT_Export Servant :
  public virtual ::PortableServer::ServantBase
{
protected:
  /**
   * Default constructor.
   */
  Servant (const char * name);

public:
  /// Destructor.
  virtual ~Servant (void);

  /// Method for activating a component.
  virtual void activate_component (void);

  /// Method for passivating a component.
  virtual void passivate_component (void);

  /// Method for removing a component.
  virtual void remove (void);

  /**
   * Get the instance's name.
   *
   * @return        Name of the instance.
   */
  virtual const ACE_CString & name (void) const;

  /**
   * Set the component's attributes. The attributes are extracted
   * from the configuration values, and passes to the correct
   * setter method on the component implementation.
   */
  virtual void set_attributes (const ::Components::ConfigValues &);

  virtual void add_eventconsumer (const char * name, EventConsumer *) = 0;
  virtual void add_publisher (const char * name, Publisher *) = 0;
  virtual void add_publisher_table (const char * name, Publisher_Table *) = 0;

protected:
  /// Name of the CCM servant.
  ACE_CString name_;

private:
  Servant (void);
};

}

#if defined (__CUTS_INLINE__)
#include "Servant.inl"
#endif

#endif  // !defined _CUTS_TCPIP_SERVANT_H_
