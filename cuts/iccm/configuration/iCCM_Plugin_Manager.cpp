#include "iCCM_Plugin_Manager.h"
#include "dance\Logger\Log_Macros.h"
#include "dance\Deployment\Deployment_PlanErrorC.h"
#include "dance\DAnCE_LocalityManagerC.h"
#include <fstream>
#include <algorithm>
#include <sstream>

namespace iCCM
{
  // Load a plugin from a shared library
  template <typename PLUGIN>
  typename PLUGIN::_ptr_type
    load_plugin (const char * artifact, const char * entrypoint)
  {
    ACE_DLL plugin_dll;

    if (plugin_dll.open (artifact, ACE_DEFAULT_SHLIB_MODE, false))
    {
      const char * error = plugin_dll.error ();

      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM_Plugin_Manager::load_plugin - ")
        ACE_TEXT ("Error while loading artifact <%s>: %s\n"),
        artifact,
        error));

      throw ::Deployment::PlanError (ACE_TEXT_ALWAYS_CHAR (artifact), ACE_TEXT_ALWAYS_CHAR (error));
    }

    DANCE_DEBUG (DANCE_LOG_EVENT_TRACE,
      (LM_TRACE, DLINFO
      ACE_TEXT ("iCCM_Plugin_Manager::load_plugin - ")
      ACE_TEXT ("Loading artifact <%s> successfully loaded.\n"),
      artifact));

    void * void_ptr = plugin_dll.symbol (entrypoint);
    ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (void_ptr);

    typedef typename PLUGIN::_ptr_type (*PluginFactory) (void);
    PluginFactory pcreator = reinterpret_cast<PluginFactory> (tmp_ptr);

    if (!pcreator)
    {
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM_Plugin_Manager::load_plugin - ")
        ACE_TEXT ("Unable to load plugin <%s>:<%s>\n"),
        artifact,
        entrypoint));
      throw ::Deployment::PlanError (ACE_TEXT_ALWAYS_CHAR (artifact), "Invalid entrypoint");
    }

    typename PLUGIN::_var_type plugin = pcreator ();

    if (CORBA::is_nil (plugin))
    {
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM_Plugin_Manager::load_plugin - ")
        ACE_TEXT ("Unable to load plugin <%s>:<%s>, nil result from factory\n"),
        artifact,
        entrypoint));
      throw ::Deployment::PlanError (ACE_TEXT_ALWAYS_CHAR (artifact), "Nil result from factory");
    }

    DANCE_DEBUG (DANCE_LOG_MINOR_EVENT,
      (LM_TRACE, DLINFO
      ACE_TEXT ("iCCM_Plugin_Manager::load_plugin - ")
      ACE_TEXT ("Successfully created plugin from <%s>:<%s>\n"),
      artifact,
      entrypoint));

    return plugin._retn ();
  }

  iCCM_Plugin_Manager::iCCM_Plugin_Manager (void)
  {
    std::ifstream plugin_list ("bin/plugins.config");
    std::string artifact;
    std::string entrypoint;

    while (plugin_list >> artifact >> entrypoint)
    {
      register_plugin (artifact.c_str (), entrypoint.c_str ());
    }
  }
  template<typename T>
  struct PluginCloser
  {
    void operator() () (T& item)
    {
      item.second->close ();
    }
  };

  iCCM_Plugin_Manager::~iCCM_Plugin_Manager (void)
  {
    std::for_each (plugins_.begin (), plugins_.end (), PluginCloser<PLUGIN_MAP::value_type> ());
  }

  void iCCM_Plugin_Manager::register_plugin (const char * artifact, const char * entrypoint)
  {
    DAnCE::LocalityConfiguration_var plugin = load_plugin< DAnCE::LocalityConfiguration > (artifact, entrypoint);

    try
    {
      CORBA::String_var id = plugin->type ();

      this->plugins_[id.in ()] = plugin._retn ();
    }
    catch (const CORBA::Exception & ex)
    {
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM_Plugin_Manager::register_plugin - ")
        ACE_TEXT ("CORBA exception caught while loading artifact <%s>:<%s> - %C\n"),
        artifact,
        entrypoint,
        ex._info ().c_str ()));
      throw ::Deployment::PlanError (ACE_TEXT_ALWAYS_CHAR (artifact), ex._info ().c_str ());
    }
    catch (...)
    {
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
        (LM_ERROR, DLINFO
        ACE_TEXT ("iCCM_Plugin_Manager::register_plugin - ")
        ACE_TEXT ("Unknown C++ exception while configuring plugin from <%s>:<%s>\n"),
        artifact,
        entrypoint));
      throw ::Deployment::PlanError (ACE_TEXT_ALWAYS_CHAR (artifact), "Unknown C++ exception during plugin configuration\n");
    }
  }

  void iCCM_Plugin_Manager::handle_properties (Deployment::Properties & props)
  {
    unsigned int num_properties = props.length ();

    // Attempt to run each property through a plugin
    for (unsigned int i = 0; i < num_properties; ++i)
    {
      Deployment::Property p = props[i];
      std::stringstream name;
      name << p.name;

      if (plugins_.count (name.str ()))
      {
        // Use plugin
        std::cout << "Using plugin " << name.str () << std::endl;
        plugins_[name.str ()]->configure (p);
      }
      else
      {
        // No plugin was found for property
        std::cout << "Plugin " << name.str () << " not found, skipping" << std::endl;
      }
    }
  }
}
