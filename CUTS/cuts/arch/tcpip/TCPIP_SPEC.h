// -*- C++ -*-

//=============================================================================
/**
 *  @file         TCPIP_SPEC.h
 *
 *  $Id$
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _CUTS_TCPIP_SPEC_H_
#define _CUTS_TCPIP_SPEC_H_

#include "ace/CDR_Base.h"
#include "ace/UUID.h"
#include "TCPIP_export.h"

// Forward decl.
class CUTS_TCPIP_InputCDR;

// Forward decl.
class CUTS_TCPIP_OutputCDR;

/**
 * @class CUTS_TCPIP_SPEC
 *
 * Implementation of the Simple Protocol for Event-based
 * Communication (SPEC).
 */
class CUTS_TCPIP_Export CUTS_TCPIP_SPEC
{
public:
  enum { BINARY_SIZE = 36 };

  /// Id of the target object/component.
  ACE_Utils::UUID uuid_;

  /// Target event of the object.
  ACE_CDR::ULong event_id_;
};

/**
 * Insert the SPEC into the input stream.
 *
 * @param[in]       output        Target input stream
 * @param[in]       spec          SPEC header
 */
CUTS_TCPIP_Export
ACE_CDR::Boolean operator << (CUTS_TCPIP_OutputCDR & output, const CUTS_TCPIP_SPEC & spec);

/**
 * Extract the SPEC from the output stream.
 *
 * @param[in]       input         Target input stream
 * @param[in]       spec          SPEC header
 */
CUTS_TCPIP_Export
ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & output, CUTS_TCPIP_SPEC & spec);

#endif  // !defined _CUTS_TCPIP_SPEC_H_
