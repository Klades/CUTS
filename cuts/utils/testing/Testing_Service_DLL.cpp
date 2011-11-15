// $Id$

#include "Testing_Service_DLL.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_Service_DLL.inl"
#endif

#include "Testing_Service.h"
#include "ace/CORBA_macros.h"

//
// close
//
int CUTS_Testing_Service_DLL::close (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::close (void)");

  if (this->svc_ != 0)
  {
    // First, finialize the service.
    this->svc_->fini ();

    // Now, we can remove it from memory.
    this->svc_->destroy ();
    this->svc_ = 0;
  }

  // Close the service configurator for this DLL.
  if (this->svc_config_->close () != 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T (%t) - failed to close service configurator\n"),
                       -1);
  }

  // Pass control to the contained DLL.
  //ACE_Service_Config_Guard gaurd (ACE_Service_Config::global ());
  return this->dll_.close ();
}


//
// open
//
int CUTS_Testing_Service_DLL::
open (const char * module, const char * factory)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::open (const char *, const char *)");

  if (this->svc_ != 0 || this->svc_config_->is_opened ())
    this->close ();

  // First, load the module into memory. Make sure we do not close the
  // handle on destruction. This way, we make sure we unload all the
  // static services before unloading the module. Also, there is a
  // good chance the same module is used to load mulitple servies. We
  // want to make sure the handle stays open until the very end.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - loading %s module into memory\n",
              module));

  if (this->dll_.open (module, ACE_DEFAULT_SHLIB_MODE, false) != 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - %m [%s]\n",
                       module),
                       -1);
  }

  // Next, extract the entry point symbol for instanstiating the
  // service from its module.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - extracting %s from module\n",
              factory));

  void * symbol = this->dll_.symbol (factory);

  if (symbol == 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%T - %M - failed to extract entry point %s\n",
                       factory),
                       -1);
  }

  // Convert the symbol into a valid factory function.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - converting symbol into factory object\n"));

  factory_type f = reinterpret_cast <factory_type> (symbol);

  // Use the factory to create a new service object. We need to switch
  // to the current service gestalt just in case creating the service
  // loads services.
  ACE_Service_Config_Guard guard (this->svc_config_.get ());
  this->svc_ = (*f) ();

  return this->svc_ != 0 ? 0 : -1;
}

//
// init
//
int CUTS_Testing_Service_DLL::init (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::init (void)");

  ACE_Service_Gestalt * gestalt = 0;

  ACE_NEW_THROW_EX (gestalt,
                    ACE_Service_Gestalt (),
                    ACE_bad_alloc ());

  this->svc_config_.reset (gestalt);
  return 0;
}
