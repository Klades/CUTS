// $Id$

#include "CHAOS_Servant.h"

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Servant.inl"
#endif

namespace iCCM
{

const char * CHAOS_Servant::PORT_TYPE_PREFIX = "CHAOSPortType:";

//
// handle_config
//
void
CHAOS_Servant::handle_config (const ::Components::ConfigValues & values)
{
  size_t len = values.length ();
  size_t prefix_len = ACE_OS::strlen (this->PORT_TYPE_PREFIX);
  size_t tok = 0;

  for (size_t i = 0; i < len; ++i)
  {
    std::string name (values[i]->name ());
    tok = name.find (this->PORT_TYPE_PREFIX);
    if (tok == std::string::npos)
      continue;

    std::string dll_entry;
    values[i]->value () >>= dll_entry;

    tok = dll_entry.find (':');
    if (tok == std::string::npos)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - invalid dll/entry point for property [%s]; %m\n"),
                  values[i]->name ()));
      continue;
    }

    std::string port_name = name.substr (prefix_len);
    std::string dll = dll_entry.substr (0, tok);
    std::string entrypt = dll_entry.substr (tok+1);

    this->load_port (port_name.c_str (), dll.c_str (), entrypt.c_str ());
  }
}

//
// load_port
//
void
CHAOS_Servant::load_port (const char * port, const char * dll, const char * entrypt)
{

}

}
