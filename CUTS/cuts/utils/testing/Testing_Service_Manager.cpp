// $Id$

#include "Testing_Service_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_Service_Manager.inl"
#endif

#include "Testing_Service.h"
#include "ace/ARGV.h"
#include "ace/DLL.h"
#include "ace/Guard_T.h"

//
// load_service
//
int CUTS_Testing_Service_Manager::load_service (const char * name,
                                                const char * location,
                                                const char * entryPoint,
                                                const char * args)
{
  ACE_DLL module;

  // First, load the module into memory.
  if (module.open (location) != 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - %m [%s]\n",
                       name),
                       -1);
  }

  // Next, extract the entry point symbol for instanstiating the
  // service from its module.
  void * symbol = module.symbol (entryPoint);

  if (symbol == 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to extract entry point %s\n",
                       entryPoint),
                       -1);
  }

  // Convert the symbol into a valid factory function.
  typedef CUTS_Testing_Service * (*FUNC_PTR) (void);
  FUNC_PTR factory = reinterpret_cast <FUNC_PTR> (symbol);

  // Finally, create the service using the factory.
  CUTS_Testing_Service * svc = factory ();

  if (svc == 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to create service using provided entry point\n"),
                       -1);
  }

  // Initialize the contents of the service.
  svc->app_ = &this->test_app_;

  if (this->svc_map_.bind (ACE_CString (name), svc) != 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to store service\n"),
                       -1);
  }

  ACE_ARGV_T <char> arg_list (args);
  svc->init (arg_list.argc (), arg_list.argv ());

  return 0;
}

//
// handle_shutdown
//
int CUTS_Testing_Service_Manager::
handle_shutdown (const ACE_Time_Value & tv)
{
  ACE_READ_GUARD_RETURN (map_type::lock_type,
                         guard,
                         this->svc_map_.mutex (),
                         -1);

  map_type::CONST_ITERATOR iter (this->svc_map_);

  for ( ; !iter.done (); iter ++)
    iter->item ()->handle_shutdown (tv);

  return 0;
}

//
// handle_startup
//
int CUTS_Testing_Service_Manager::
handle_startup (const ACE_Time_Value & tv)
{
  ACE_READ_GUARD_RETURN (map_type::lock_type,
                         guard,
                         this->svc_map_.mutex (),
                         -1);

  map_type::CONST_ITERATOR iter (this->svc_map_);

  for ( ; !iter.done (); iter ++)
    iter->item ()->handle_startup (tv);

  return 0;
}

//
// close
//
int CUTS_Testing_Service_Manager::close (void)
{
  {
    ACE_READ_GUARD_RETURN (map_type::lock_type,
                          guard,
                          this->svc_map_.mutex (),
                          -1);

    map_type::CONST_ITERATOR iter (this->svc_map_);

    for ( ; !iter.done (); iter ++)
    {
      iter->item ()->fini ();
      iter->item ()->destroy ();
    }
  }

  // Remote all the entries from the mapping.
  this->svc_map_.unbind_all ();
  return 0;
}
