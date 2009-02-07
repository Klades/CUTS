// -*- C++ -*-

//=============================================================================
/**
 * @file        Antispam_Visitor.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ANTISPAM_VISITOR_H_
#define _CUTS_ANTISPAM_VISITOR_H_

#include "Antispam_export.h"

// Forward decl.
class CUTS_Output_Event_Port_Instance;

// Forward decl.
class CUTS_Input_Event_Port_Instance;

// Forward decl.
class CUTS_Component_Instance;

// Forward decl.
class CUTS_Component_Assembly;

/**
 * @class CUTS_Antispam_Visitor
 */
class CUTS_ANTISPAM_Export CUTS_Antispam_Visitor
{
public:
  /// Destructor
  virtual ~CUTS_Antispam_Visitor (void);

  virtual void visit_CUTS_Component_Assembly (
    CUTS_Component_Assembly & assembly);

  virtual void visit_CUTS_Output_Event_Port_Instance (
    CUTS_Output_Event_Port_Instance & port);

  virtual void visit_CUTS_Input_Event_Port_Instance (
    CUTS_Input_Event_Port_Instance & port);

  virtual void visit_CUTS_Component_Instance (
    CUTS_Component_Instance & instance);

protected:
  /// Default constructor.
  CUTS_Antispam_Visitor (void);

private:
  // prevent the following operations
  CUTS_Antispam_Visitor (const CUTS_Antispam_Visitor &);
  const CUTS_Antispam_Visitor & operator = (const CUTS_Antispam_Visitor &);
};

#if defined (__CUTS_INLINE__)
#include "Antispam_Visitor.inl"
#endif

#endif
