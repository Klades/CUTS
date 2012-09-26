/* -*- c++ -*- */
// $Id$

// ============================================================================
//
// = LIBRARY
//    IDL_TO_PICML_BE_DLL
//
// = FILENAME
//    be_global.h
//
// = DESCRIPTION
//    Header file for class containing compiler back end global data.
//
// = AUTHOR
//    Jeff Parsons <parsons@cs.wustl.edu>
//
// ============================================================================

#ifndef _CUTS_ICCM_TCPIP_CONTEXT_H_
#define _CUTS_ICCM_TCPIP_CONTEXT_H_

#include "ast_type.h"
#include "ast_eventtype.h"

#include "be_global.h"

#include "ace/Unbounded_Set.h"

// Forward decl.
class AST_Generator;

namespace iCCM
{
namespace TCPIP
{

/**
 * @class BE_GlobalData
 *
 * Defines a class containing all back end global data.
 */
class Context : public ::BE_GlobalData
{
public:
  // Constructor.
  Context (void);

  // Destructor.
  virtual ~Context (void);

  virtual void post_produce (void);

  // BEGIN: ARCHITECTURE SPECIFIC VALUES.
  virtual const ACE_CString & get_stub_file_prefix (void) const;
  virtual const ACE_CString & get_context_template_header_filename (void) const;
  virtual const ACE_CString & get_servant_template_header_filename (void) const;

  virtual const ACE_CString & get_servant_template_typename (void) const;
  virtual const ACE_CString & get_context_typename (void) const;

  virtual const ACE_CString & get_consumer_template_typename (void) const;
  virtual const ACE_CString & get_publisher_typename (void) const;
  virtual const ACE_CString & get_publisher_template_typename (void) const;
  virtual const ACE_CString & get_publisher_table_typename (void) const;
  virtual const ACE_CString & get_publisher_table_template_typename (void) const;

  // BEGIN: OPTIONAL ARCHITECTURE OVERLOADS
  virtual bool uses_default_bmi (AST_Component * node) const;
  virtual void generate_custom_bmi (AST_Component * node, std::ofstream & sfile) const;

  virtual bool uses_default_push_method (AST_Component * node) const;
  virtual void generate_custom_push_method (AST_Component * node,
                                            std::ofstream & hfile,
                                            std::ofstream & sfile,
                                            const ACE_CString & servant) const;

  virtual void generate_constructor_postamble (AST_Component * node, std::ofstream & sfile) const;
};

}
}

#endif /* IDL_TO_PICML_BE_GLOBAL_H */
