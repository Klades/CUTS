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

#ifndef _CUTS_ANTISPAM_HOST_H_
#define _CUTS_ANTISPAM_HOST_H_

#include "ace/Unbounded_Set.h"
#include "Antispam_export.h"

// Forward decl.
class CUTS_Component_Instance;

/**
 * @class CUTS_Host
 */
class CUTS_Host
{
public:
  /// Type definition of the container type.
  typedef ACE_Unbounded_Set <CUTS_Component_Instance *> container_type;

  /// Default constructor.
  CUTS_Host (void);

  /// Destructor
  ~CUTS_Host (void);

  container_type & instances (void);

  const container_type & instances (void) const;

  double utilization (void) const;

private:
  /// Collection of instances on this host.
  container_type instances_;
};

#if defined (__CUTS_INLINE__)
#include "Host.inl"
#endif

#endif  // !defined _CUTS_ANTISPAM_HOST_H_
