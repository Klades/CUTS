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

#ifndef _CUTS_BE_CCM_CCP_TRAITS_H_
#define _CUTS_BE_CCM_CCP_TRAITS_H_

#include "CCM_export.h"
#include <iosfwd>

// Forward decl.
struct CUTS_BE_IDL_Node;

namespace CUTS_BE_CCM
{
namespace Cpp
{

/**
 * @class Traits
 *
 * Backend traits for integrating different distributed architectures
 * into CCM.
 */
class CUTS_BE_CCM_Export Traits
{
public:
  /// Destructor.
  virtual ~Traits (void);

  virtual bool generate_default_servant (void);

  virtual const char * stub_base_project (void);
  virtual const char * skel_base_project (void);
  virtual const char * svnt_base_project (void);

  virtual void write_top (std::ostream &, const CUTS_BE_IDL_Node & );

  virtual void write_stub_source_files (std::ostream &, const CUTS_BE_IDL_Node &);
  virtual void write_stub_after (std::ostream &, const CUTS_BE_IDL_Node &);
  virtual void write_stub_custom (std::ostream &, const CUTS_BE_IDL_Node &);

  virtual void write_idl_gen_files (std::ostream &, const CUTS_BE_IDL_Node &);
  virtual void write_exec_idl_files (std::ostream &, const CUTS_BE_IDL_Node &);
  virtual void write_exec_source_files (std::ostream &, const CUTS_BE_IDL_Node &);

  virtual const char * custom_stub_prefix (void);

  /// Get the name of the CCM context template object.
  virtual const char * ccm_context_template_type (void);
  virtual const char * ccm_context_template_type_header (void);

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

  // Feature: emulates asynchronous communication
  virtual bool emulates_async (void);
};

}
}

#if defined (__CUTS_INLINE__)
#include "Traits.inl"
#endif

#endif  // !defined _CUTS_BE_CCM_TRAITS_H_
