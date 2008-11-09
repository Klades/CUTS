// $Id$

#include "Testing_Service_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_Service_Manager.inl"
#endif

#include "Testing_Service.h"
#include "Testing_Service_DLL.h"
#include "ace/ARGV.h"
#include "ace/Guard_T.h"
#include "ace/CORBA_macros.h"

//
// load_service
//
int CUTS_Testing_Service_Manager::load_service (const char * name,
                                                const char * location,
                                                const char * entryPoint,
                                                const char * args)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_Manager::load_service (const char *, const char *, const char *, const char *)");

  // First, load the module into memory.
  CUTS_Testing_Service_DLL * dll = 0;

  ACE_NEW_THROW_EX (dll,
                    CUTS_Testing_Service_DLL (),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <CUTS_Testing_Service_DLL> auto_clean (dll);

  if (dll->open (location, entryPoint) != 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to loaded service '%s' into memory\n",
                       name),
                       -1);
  }

  // Get the service from the DLL.
  CUTS_Testing_Service * svc = dll->get_svc ();

  if (svc != 0)
  {
    // Initialize the contents of the service.
    svc->app_ = &this->test_app_;

    ACE_DEBUG ((LM_DEBUG,
                "%T (%t) - %M - initializing the service with arguments (%s)\n",
                args));

    ACE_ARGV_T <char> arg_list (args != 0 ? args : "");
    int retval = svc->init (arg_list.argc (), arg_list.argv ());

    if (retval == 0)
    {
      // Save the service in the service map.
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - storing testing service in map under id '%s'\n",
                  name));

      retval = this->svc_map_.bind (ACE_CString (name), dll);

      if (retval == 0)
        auto_clean.release ();
    }
    else
    {

    }

    return retval;
  }
  else
  {
    ACE_ERROR ((LM_ERROR,
                "%T (%t) - %M - failed to get service from DLL\n"));
  }

  return -1;
}

//
// handle_shutdown
//
int CUTS_Testing_Service_Manager::
handle_shutdown (const ACE_Time_Value & tv)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_Manager::handle_shutdown (const ACE_Time_Value &)");

  ACE_READ_GUARD_RETURN (map_type::lock_type,
                         guard,
                         this->svc_map_.mutex (),
                         -1);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - sending handle_shutdown () singal to all services\n"));

  CUTS_Testing_Service_DLL * dll = 0;
  map_type::CONST_ITERATOR iter (this->svc_map_);

  for ( ; !iter.done (); iter ++)
  {
    dll = iter->item ();

    if (dll != 0)
      dll->get_svc ()->handle_shutdown (tv);
  }

  return 0;
}

//
// handle_startup
//
int CUTS_Testing_Service_Manager::
handle_startup (const ACE_Time_Value & tv)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_Manager::handle_startup (const ACE_Time_Value &)");

  ACE_READ_GUARD_RETURN (map_type::lock_type,
                         guard,
                         this->svc_map_.mutex (),
                         -1);

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - sending handle_startup () singal to all services\n"));

  CUTS_Testing_Service_DLL * dll = 0;
  map_type::CONST_ITERATOR iter (this->svc_map_);

  for ( ; !iter.done (); iter ++)
  {
    dll = iter->item ();

    if (dll != 0)
      dll->get_svc ()->handle_startup (tv);
  }

  return 0;
}

//
// close
//
int CUTS_Testing_Service_Manager::close (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_Manager::close (void)");

  {
    ACE_READ_GUARD_RETURN (map_type::lock_type,
                          guard,
                          this->svc_map_.mutex (),
                          -1);

    CUTS_Testing_Service_DLL * dll = 0;
    map_type::CONST_ITERATOR iter (this->svc_map_);

    for ( ; !iter.done (); iter ++)
    {
      dll = iter->item ();

      if (dll != 0)
        dll->close ();
    }
  }

  // Remote all the entries from the mapping.
  this->svc_map_.unbind_all ();
  return 0;
}
