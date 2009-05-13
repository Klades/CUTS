#ifndef CUTS_DSTO_CONTEXTBASE_H
#define CUTS_DSTO_CONTEXTBASE_H

#include "ccm/CCM_SessionContextC.h"

#include "DSTO_Utilities_export.h"

namespace CUTS_DSTO
{
  class DSTO_Utilities_Export ContextBase
    : public virtual ::Components::SessionContext
  {
  public:
    ContextBase (void);
    virtual ~ContextBase (void);
    
    virtual ::Components::Principal_ptr
    get_caller_principal (void);
    
    virtual ::Components::CCMHome_ptr
    get_CCM_home (void);
    
    virtual ::CORBA::Boolean
    get_rollback_only (void);
    
    virtual ::Components::Transaction::UserTransaction_ptr
    get_user_transaction (void);
    
    virtual ::CORBA::Boolean
    is_caller_in_role (const char *);
    
    virtual void
    set_rollback_only (void);
    
    virtual ::CORBA::Object_ptr
    resolve_service_reference (const char *);
    
    virtual ::CORBA::Object_ptr
    get_CCM_object (void);
  };
}

#endif // CUTS_DSTO_CONTEXTBASE_H