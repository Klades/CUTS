#include "ciao/Valuetype_Factories/Cookies.h"

#include "ModelDataConversion.h"

#include "PubAppContext.h"

namespace DSTO_AppSpace_Impl
{
  PubAppContext::PubAppContext (void)
  {
  }
  
  PubAppContext::~PubAppContext (void)
  {
  }
  
  void
  PubAppContext::push_app_op_send ( ::Outer::TestData * ev)
  {
    ::OBV_Outer::TestData_IDL * corba_ev = 0;
    ACE_NEW (corba_ev, ::OBV_Outer::TestData_IDL);
    ::Outer::TestData_IDL_var safe_corba_ev = corba_ev;
    ::ModelDataConversion::to_corba (*corba_ev, *ev);

    ACE_READ_GUARD (TAO_SYNCH_MUTEX,
                    mon,
                    this->app_op_send_lock_);

    for (APP_OP_SEND_TABLE::const_iterator iter =
           this->app_op_send_table_.begin ();
         iter != this->app_op_send_table_.end ();
         ++iter)
      {
        iter->second->push_TestData_IDL (corba_ev);
      }
  }
  
  ::Components::Cookie *
  PubAppContext::subscribe_app_op_send (
    ::Outer::TestData_IDLConsumer_ptr c)
  {
    if ( ::CORBA::is_nil (c))
      {
        throw ::CORBA::BAD_PARAM ();
      }
      
    std::pair<APP_OP_SEND_TABLE::iterator, bool> result;
    APP_OP_SEND_TABLE::value_type entry;
    entry.first = reinterpret_cast<ptrdiff_t> (c);
    entry.second = ::Outer::TestData_IDLConsumer::_duplicate (c);
    
    {
      ACE_WRITE_GUARD_RETURN (TAO_SYNCH_MUTEX,
                              mon,
                              app_op_send_lock_,
                              0);
                              
      result = app_op_send_table_.insert (entry);
    }

    if (! result.second)
      {
        ACE_ERROR_RETURN ((LM_ERROR,
                           "subscribe on %s failed\n",
                           "app_op_send"),
                          0);
      }

    ::Components::Cookie * retv = 0;
    ACE_NEW_THROW_EX (retv,
                      ::CIAO::Cookie_Impl (entry.first),
                      ::CORBA::NO_MEMORY ());

    return retv;
  }
  
  ::Outer::TestData_IDLConsumer_ptr
  PubAppContext::unsubscribe_app_op_send (
    ::Components::Cookie * ck)
  {
    ptrdiff_t key = 0UL;
    APP_OP_SEND_TABLE::size_type n = 0UL;

    if (ck == 0 || ! ::CIAO::Cookie_Impl::extract (ck, key))
      {
        throw ::Components::InvalidConnection ();
      }

    {
      ACE_WRITE_GUARD_RETURN (TAO_SYNCH_MUTEX,
                              mon,
                              app_op_send_lock_,
                              ::Outer::TestData_IDLConsumer::_nil ());

      APP_OP_SEND_TABLE::iterator iter =
        app_op_send_table_.find (key);

      if (iter != app_op_send_table_.end ())
        {
          ::Outer::TestData_IDLConsumer_var retv = iter->second;
          n = app_op_send_table_.erase (key);

          if (n == 1UL)
            {
              return retv._retn ();
            }
        }
    }

    throw ::Components::InvalidConnection ();
  }
  
  PubAppContext *
  PubAppContext::_narrow ( ::Components::SessionContext_ptr p)
  {
    return dynamic_cast<PubAppContext *> (p);
  }
}