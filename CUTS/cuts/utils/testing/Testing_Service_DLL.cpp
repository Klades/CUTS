// $Id$

#include "Testing_Service_DLL.h"

#if !defined (__CUTS_INLINE__)
#include "Testing_Service_DLL.inl"
#endif

#include "Testing_Service.h"
#include "ace/Log_Msg.h"

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

  // Reset the pointer to the factory function.
  if (this->factory_ != 0)
    this->factory_ = 0;

  // Pass control to the contained DLL.
  return this->dll_.close ();
}


//
// open
//
int CUTS_Testing_Service_DLL::
open (const char * module, const char * factory)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::open (const char *, const char *)");

  if (this->factory_ != 0)
    this->close ();

  // First, load the module into memory.
  ACE_DEBUG ((LM_DEBUG,
              "%T (%t) - %M - loading %s module into memory\n",
              module));

  if (this->dll_.open (module) != 0)
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

  this->factory_ = reinterpret_cast <factory_type> (symbol);
  return 0;
}

//
// get_svc
//
CUTS_Testing_Service * CUTS_Testing_Service_DLL::get_svc (void)
{
  CUTS_TEST_TRACE ("CUTS_Testing_Service_DLL::get_svc (void)");

  if (this->svc_ == 0)
    this->svc_ = (*this->factory_) ();

  return this->svc_;
}
