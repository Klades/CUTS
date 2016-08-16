#include "CPUAffinity.h"

#include "dance/DAnCE_PropertiesC.h"
#include "dance/Logger/Log_Macros.h"
#include "ace/Tokenizer_T.h"
#include <sstream>
#include <iostream>

namespace iCCM
{
  CPU_Affinity::CPU_Affinity (void) : Plugin ("edu.vanderbilt.dre.DAnCE.LocalityManager.CPUAffinity")
  {
  }

  CPU_Affinity::~CPU_Affinity (void)
  {
  }
  
  void CPU_Affinity::configure (const ::Deployment::Property & prop)
  {
#if defined (ACE_HAS_PTHREADS) || defined (ACE_WIN32)
    const char * extracted_affinity = 0;

    if (!(prop.value >>= extracted_affinity)) {
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM_CPU_Affinity::configure - ")
        ACE_TEXT ("Unable to extract CPU Affinity string")));
      throw ::Deployment::StartError (prop.name.in (), "Unable to extract CPU Affinity string");
    }

    CPU_Mask mask (extracted_affinity);
    // I strongly dislike this and need to fix it later.
    // sched_setaffinity returns 0 on success
    // SetProcessAffinityMask returns 0 on failure
    if (set_affinity (&mask))
    {
      std::stringstream str;
      std::string safe_error (ACE_OS::strerror (ACE_OS::last_error ()));
      
      str << "Unable to set CPU Affinity to <" << extracted_affinity << ">: " << safe_error;

      const char * msg = str.str ().c_str ();
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM::CPU_Affinity::configure - %C\n"),
        msg));
      throw ::Deployment::StartError (prop.name.in (), msg);
    }
#else
    throw ::Deployment::StartError (prop.name.in (), "CPU Affinity not supported on this platform");
#endif
  }

  int CPU_Affinity::set_affinity (CPU_Mask * mask)
  {
#ifdef ACE_HAS_PTHREADS
    int retval = pthread_setaffinity_np (pthread_self (), sizeof (cpu_set_t), mask->get ());
#endif
#ifdef ACE_WIN32
    int retval = SetProcessAffinityMask (GetCurrentProcess (), *(mask->get ()));
#endif
    if (retval) {
      retval = 0;
    }
    return retval;
  }
}

iCCM::Plugin * create_CPUAffinity_plugin (void)
{
  iCCM::Plugin * retval (0);

  ACE_NEW_RETURN (retval, iCCM::CPU_Affinity (), 0);

  return retval;
}
