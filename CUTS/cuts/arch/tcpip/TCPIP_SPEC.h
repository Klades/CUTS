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

#include "ace/UUID.h"
#include "ace/CDR_Stream.h"
#include "TCPIP_export.h"

/**
 * @class CUTS_TCPIP_SPEC
 *
 * Implementation of the Simple Protocol for Event-based
 * Communication (SPEC).
 */
class CUTS_TCPIP_SPEC
{
public:
  /// Id of the target object/component.
  ACE_Utils::UUID uuid_;

  /// Target event of the object.
  ACE_CDR::ULong event_id_;

  /// Size of the event's data (or payload).
  ACE_CDR::ULong data_size_;
};

/**
 * Insert the SPEC into the input stream.
 *
 * @param[in]       input         Target input stream
 * @param[in]       spec          SPEC header
 */
ACE_CDR::Boolean operator << (ACE_OutputCDR & input, const CUTS_TCPIP_SPEC & spec);

/**
 * Extract the SPEC from the output stream.
 *
 * @param[in]       input         Target input stream
 * @param[in]       spec          SPEC header
 */
ACE_CDR::Boolean operator >> (ACE_InputCDR & output, CUTS_TCPIP_SPEC & spec);

#endif  // !defined _CUTS_TCPIP_SPEC_H_
