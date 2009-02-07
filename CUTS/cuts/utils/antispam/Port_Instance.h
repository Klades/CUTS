// -*- C++ -*-

//=============================================================================
/**
 * @file        Port_Instance.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_PORT_INSTANCE_H_
#define _CUTS_PORT_INSTANCE_H_

#include "ace/Unbounded_Set.h"
#include "Port.h"

// Forward decl.
class CUTS_Component_Instance;

// Forward decl.
class CUTS_Input_Event_Port_Instance;

// Forward decl.
class CUTS_Output_Event_Port_Instance;

// Forward decl.
class CUTS_Antispam_Visitor;

/**
 * @class CUTS_Port_Instance
 */
class CUTS_ANTISPAM_Export CUTS_Port_Instance
{
public:
  /// Destructor.
  virtual ~CUTS_Port_Instance (void);

  /**
   * Get the port instance's type.
   *
   * @return        The port type.
   */
  const CUTS_Port & type (void) const;

  /**
   * Get the port instances parent.
   *
   * @return        Component instance that owns this port.
   */
  const CUTS_Component_Instance & parent (void) const;

  double service_time (void) const;

  void service_time (double t);

  /// Reset the port instance.
  virtual void reset (void);

protected:
  /// Default constructor.
  CUTS_Port_Instance (const CUTS_Component_Instance & parent,
                      const CUTS_Port & type);

  /// Parent of the port instance.
  const CUTS_Component_Instance & parent_;

  /// The port type for this instance.
  const CUTS_Port & type_;

  /// Service time for the port.
  double service_time_;

private:
  // prevent the following operations
  CUTS_Port_Instance (const CUTS_Port_Instance & instance);
  const CUTS_Port_Instance & operator = (const CUTS_Port_Instance &);
};

/**
 * @class CUTS_Input_Event_Port_Instance
 */
class CUTS_ANTISPAM_Export CUTS_Input_Event_Port_Instance :
  public CUTS_Port_Instance
{
public:
  typedef ACE_Unbounded_Set <CUTS_Output_Event_Port_Instance *> outputs_type;

  /// Default constructor.
  CUTS_Input_Event_Port_Instance (const CUTS_Component_Instance & parent,
                                  const CUTS_Input_Event_Port & type);

  /// Destructor.
  virtual ~CUTS_Input_Event_Port_Instance (void);

  double lambda (void) const;

  void lambda (double l);

  const outputs_type & outputs (void) const;

  CUTS_Output_Event_Port_Instance *
    new_output (const CUTS_Output_Event_Port * type);

  void accept (CUTS_Antispam_Visitor & visitor);

  /// Reset the output port instance.
  virtual void reset (void);

  /// Calculate the utilization of the port.
  double utilization (void) const;

  double response_time (void) const;

private:
  double lambda_;

  outputs_type outputs_;
};

/**
 * @class CUTS_Output_Event_Port_Instance
 */
class CUTS_ANTISPAM_Export CUTS_Output_Event_Port_Instance :
  public CUTS_Port_Instance
{
public:
  typedef ACE_Unbounded_Set <CUTS_Input_Event_Port_Instance *> connections_type;

  /// Default constructor.
  CUTS_Output_Event_Port_Instance (const CUTS_Component_Instance & parent,
                                   const CUTS_Output_Event_Port & type);

  /// Destructor.
  virtual ~CUTS_Output_Event_Port_Instance (void);

  /**
   * Make a new connection for this output port.
   *
   * @param[in]       input       Target input port.
   */
  int new_connection (CUTS_Input_Event_Port_Instance * input);

  void accept (CUTS_Antispam_Visitor & visitor);

  double service_time (void) const;

  void service_time (double t);

  const connections_type & connections (void) const;

private:
  /// Service time for this port.
  double service_time_;

  /// Collection of target inputs for this output.
  connections_type conns_;
};

#if defined (__CUTS_INLINE__)
#include "Port_Instance.inl"
#endif

#endif  // !defined _CUTS_PORT_INSTANCE_H_
