// $Id:

#ifndef _CUTS_ICCM_PORTICO_CONTEXT_H_
#define _CUTS_ICCM_PORTICO_CONTEXT_H_

#include "ast_type.h"
#include "ast_eventtype.h"

#include "be_global.h"

#include "ace/Unbounded_Set.h"

// Forward decl.
class AST_Generator;

namespace iCCM
{
namespace Portico
{

/**
 * @class BE_GlobalData
 *
 * Defines a class containing all back end global data.
 */
class Context : public ::BE_GlobalData
{
public:
  // Default constructor
  Context (void);

  // Destructor
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
};

}
}
#endif
