// $Id$

#include "OpenSplice_EventConsumer.h"

CUTS_OpenSplice_CCM_EventConsumer::
CUTS_OpenSplice_CCM_EventConsumer (void)
{

}

CUTS_OpenSplice_CCM_EventConsumer::
~CUTS_OpenSplice_CCM_EventConsumer (void)
{

}

//
// topic
//
char * CUTS_OpenSplice_CCM_EventConsumer::topic (void)
{
  ::CORBA::String_var temp_str = ::CORBA::string_dup (this->topic_.c_str ());
  return temp_str._retn ();
}
