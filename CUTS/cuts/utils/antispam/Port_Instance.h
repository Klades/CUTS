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

protected:
  /// Default constructor.
  CUTS_Port_Instance (const CUTS_Component_Instance & parent,
                      const CUTS_Port & type);

  /// Parent of the port instance.
  const CUTS_Component_Instance & parent_;

  /// The port type for this instance.
  const CUTS_Port & type_;

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
  typedef ACE_Unbounded_Set <CUTS_Output_Event_Port_Instance *> output_set_type;

  /// Default constructor.
  CUTS_Input_Event_Port_Instance (const CUTS_Component_Instance & parent,
                                  const CUTS_Input_Event_Port & type);

  /// Destructor.
  virtual ~CUTS_Input_Event_Port_Instance (void);

  double lambda (void) const;

  void lambda (double l);

  const output_set_type & outputs (void) const;

  CUTS_Output_Event_Port_Instance *
    new_output (const CUTS_Output_Event_Port * type);

  void accept (CUTS_Antispam_Visitor & visitor);

private:
  double lambda_;

  output_set_type outputs_;
};

/**
 * @class CUTS_Output_Event_Port_Instance
 */
class CUTS_ANTISPAM_Export CUTS_Output_Event_Port_Instance :
  public CUTS_Port_Instance
{
public:
  typedef ACE_Unbounded_Set <const CUTS_Input_Event_Port_Instance *> connection_set_type;

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
  int new_connection (const CUTS_Input_Event_Port_Instance * input);

  void accept (CUTS_Antispam_Visitor & visitor);

private:
  /// Collection of target inputs for this output.
  connection_set_type conns_;
};

#if defined (__CUTS_INLINE__)
#include "Port_Instance.inl"
#endif

#endif  // !defined _CUTS_PORT_INSTANCE_H_
