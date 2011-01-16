// -*- C++ -*-

//=============================================================================
/**
 * @file            Traits.h
 *
 * $Id$
 *
 * @author          James H. Hill
 */
//=============================================================================

#ifndef _CUTS_BE_CCM_TCPIP_TRAITS_H_
#define _CUTS_BE_CCM_TCPIP_TRAITS_H_

#include "../Traits.h"
#include "BE_TCPIP_export.h"

/**
 * @class CUTS_BE_TCPIP_Traits
 *
 * The CCM traits for TCP/IP.
 */
class CUTS_BE_TCPIP_Export CUTS_BE_TCPIP_Traits :
  public CUTS_BE_CCM::Cpp::Traits
{
public:
  CUTS_BE_TCPIP_Traits (void);

  /// Destructor.
  virtual ~CUTS_BE_TCPIP_Traits (void);

  virtual bool generate_default_servant (void);

  virtual const char * stub_base_project (void);

  virtual const char * svnt_base_project (void);

  virtual void write_stub_source_files (std::ostream &, const CUTS_BE_IDL_Node &);

private:
  /// The IDL file has events.
  bool has_events_;
};


#if defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_TRAITS_H_
