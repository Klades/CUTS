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

#ifndef _CUTS_BE_CCM_OPENSPLICE_TRAITS_H_
#define _CUTS_BE_CCM_OPENSPLICE_TRAITS_H_

#include "../Traits.h"
#include "BE_OpenSplice_export.h"

namespace CUTS_BE_OpenSplice
{

/**
 * @class Traits
 *
 * The CCM traits for OpenSplice.
 */
class CUTS_BE_OPENSPLICE_Export Traits :
  public CUTS_BE_CCM::Cpp::Traits
{
public:
  Traits (void);

  /// Destructor.
  virtual ~Traits (void);

  virtual bool generate_default_servant (void);

  virtual const char * stub_base_project (void);

  virtual const char * svnt_base_project (void);

  virtual void write_top (std::ostream &, const CUTS_BE_IDL_Node & );

  virtual void write_stub_source_files (std::ostream &, const CUTS_BE_IDL_Node &);

  virtual void write_stub_after (std::ostream &, const CUTS_BE_IDL_Node &);

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
};

}

#if defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_TRAITS_H_
