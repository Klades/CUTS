// -*- C++ -*-

//=============================================================================
/**
 * @file      Port.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ANTISPAM_PORT_H_
#define _CUTS_ANTISPAM_PORT_H_

#include "ace/SString.h"
#include "Antispam_export.h"
#include "ace/Unbounded_Set.h"

// Forward decl.
class CUTS_Component;

/**
 * @class CUTS_Port
 *
 * Base type for all ports of a component.
 */
class CUTS_ANTISPAM_Export CUTS_Port
{
public:
  /// Constructor.
  CUTS_Port (CUTS_Component * parent);

  /// Destructor.
  virtual ~CUTS_Port (void);

  const ACE_CString & name (void) const;

  void name (const ACE_CString & name);

  double service_time (void) const;

  void service_time (double t);

  CUTS_Component & parent (void);

protected:
  /// Name of the port.
  ACE_CString name_;

  /// Service time for the port.
  double service_time_;

  /// Parent component of the port.
  CUTS_Component * parent_;

private:
  CUTS_Port (const CUTS_Port &);
  const CUTS_Port & operator = (const CUTS_Port &);
};

/**
 * @class CUTS_Output_Event_Port
 *
 * Output event port type.
 */
class CUTS_ANTISPAM_Export CUTS_Output_Event_Port : public CUTS_Port
{
public:
  /// Default constructor.
  CUTS_Output_Event_Port (CUTS_Component * parent);

  /// Destructor.
  virtual ~CUTS_Output_Event_Port (void);
};

/**
 * @class CUTS_Input_Event_Port
 *
 * Input event port type.
 */
class CUTS_ANTISPAM_Export CUTS_Input_Event_Port : public CUTS_Port
{
public:
  typedef ACE_Unbounded_Set <CUTS_Output_Event_Port *> outputs_type;

  /// Default constructor.
  CUTS_Input_Event_Port (CUTS_Component * parent);

  /// Destructor.
  virtual ~CUTS_Input_Event_Port (void);

  CUTS_Output_Event_Port * new_output_port (void);

  const outputs_type & outputs (void) const;

  outputs_type & outputs (void);

private:
  outputs_type outputs_;
};

#if defined (__CUTS_INLINE__)
#include "Port.inl"
#endif

#endif  // !defined _CUTS_ANTISPAM_PORT_H_
