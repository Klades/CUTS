// $Id$

#include "Testing_Service_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_Service_Manager.inl"
#endif

#include "Testing_Service.h"
#include "Testing_Service_DLL.h"
#include "ace/ARGV.h"
#include "ace/Argv_Type_Converter.h"
#include "ace/Guard_T.h"
#include "ace/CORBA_macros.h"
#include "ace/Service_Config.h"

//
// load_service
//
int CUTS_Testing_Service_Manager::load_service (const char * name,
                                                const char * location,
                                                const char * entryPoint,
                                                const char * args)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_Manager::load_service (const char *, const char *, const char *, const char *)");

  if (!this->is_open_)
    return -1;

  // First, load the module into memory.
  CUTS_Testing_Service_DLL * dll = 0;

  ACE_NEW_THROW_EX (dll,
                    CUTS_Testing_Service_DLL (),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <CUTS_Testing_Service_DLL> auto_clean (dll);

  // Make sure this service configuration is current.
  CUTS_Testing_Service_DLL_Guard guard (*dll);

  // Open the DLL for usage.
  if (dll->open (location, entryPoint) != 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - %M - failed to loaded service '%s' into memory\n",
                       name),
                       -1);
  }

  // Initialize the contents of the service.
  (*dll)->app_ = this->test_app_;

  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - initializing the service with arguments (%s)\n",
              args));

  // Make sure the name of the service if the first argument.
  ACE_ARGV_T <char> args_list;
  args_list.add (name);

  // Copy the remaining arguments.
  ACE_ARGV_T <char> args_copy (args);

  if (args_copy.argc ())
    args_list.add (args_copy.argv ());

  // Let's not corrupt the original command-line.
  int argc = args_list.argc ();
  ACE_Argv_Type_Converter command_line (argc, args_list.argv ());

  // Initialize the service.
  int retval = (*dll)->init (command_line.get_argc (),
                             command_line.get_ASCII_argv ());

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
    ACE_ERROR ((LM_ERROR,
                "% T (%t) - %M - failed to initialize testing service\n"));
  }

  return retval;
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
              "%T (%t) - %M - sending handle_shutdown () singal to all "
              "%d service(s)\n",
              this->svc_map_.current_size ()));

  CUTS_Testing_Service_DLL * dll = 0;
  map_type::CONST_ITERATOR iter (this->svc_map_);

  for ( ; !iter.done (); iter ++)
  {
    dll = iter->item ();

    if (dll != 0)
    {
      // Make sure this service configuration is current.
      CUTS_Testing_Service_DLL_Guard guard (*dll);

      // Send the shutdown signal to the DLL.
      (*dll)->handle_shutdown (tv);
    }
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
              "%T (%t) - %M - sending handle_startup () singal to "
              "all %d service(s)\n",
              this->svc_map_.current_size ()));

  CUTS_Testing_Service_DLL * dll = 0;
  map_type::CONST_ITERATOR iter (this->svc_map_);

  for ( ; !iter.done (); iter ++)
  {
    dll = iter->item ();

    if (dll != 0)
    {
      // Make sure this service configuration is current.
      CUTS_Testing_Service_DLL_Guard guard (*dll);

      // Send the startup signal to the DLL.
      (*dll)->handle_startup (tv);
    }
  }

  return 0;
}

//
// close
//
int CUTS_Testing_Service_Manager::close (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_Manager::close (void)");

  if (this->is_open_)
  {
    this->is_open_ = false;

    do
    {
      ACE_DEBUG ((LM_DEBUG,
                  "%T (%t) - %M - removing %d testing service(s)\n",
                  this->svc_map_.current_size ()));

      ACE_WRITE_GUARD_RETURN (map_type::lock_type,
                              guard,
                              this->svc_map_.mutex (),
                              -1);

      CUTS_Testing_Service_DLL * dll = 0;
      map_type::CONST_ITERATOR iter (this->svc_map_);

      for ( ; !iter.done (); iter ++)
      {
        dll = iter->item ();

        if (dll != 0)
        {
          // Make sure this service configuration is current.
          CUTS_Testing_Service_DLL_Guard guard (*dll);

          // Delete the loaded DLL.
          delete dll;
        }
      }
    } while (0);

    // Remote all the entries from the mapping.
    this->svc_map_.unbind_all ();
  }

  return 0;
}
