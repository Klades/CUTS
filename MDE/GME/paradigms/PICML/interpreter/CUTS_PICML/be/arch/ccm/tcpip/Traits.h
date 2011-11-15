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

  virtual const char * custom_stub_prefix (void);

  /// Get the name of the CCM context template object.
  virtual const char * ccm_servant_template_type (void);
  virtual const char * ccm_servant_template_type_header (void);

  /// Get the name of the CCM event consumer template object.
  virtual const char * ccm_eventconsumer_template_type (void);
  virtual const char * ccm_eventconsumer_template_type_header (void);

  /// Get the name of the CCM publisher template object.
  virtual const char * ccm_publisher_template_type (void);
  virtual const char * ccm_publisher_template_type_header (void);

  /// Get the name of the CCM publisher table template object.
  virtual const char * ccm_publisher_table_template_type (void);
  virtual const char * ccm_publisher_table_template_type_header (void);

private:
  /// The IDL file has events.
  bool has_events_;
};


#if defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_TRAITS_H_
