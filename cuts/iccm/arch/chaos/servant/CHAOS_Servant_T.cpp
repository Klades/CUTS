// $Id$

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Servant_T.inl"
#endif

#include "CHAOS_Servant_Configuration.h"
#include "ace/DLL.h"

namespace iCCM
{
static const std::string PROPERTY_SERVANT_CONFIG ("CHAOSServantConfig");

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
CHAOS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
CHAOS_Servant_T (T * _this, const char * name, ::PortableServer::POA_ptr poa, typename EXECUTOR::_ptr_type executor)
: base_type (_this, name, poa, executor),
  the_POA_ (::PortableServer::POA::_duplicate (poa)),
  impl_ (EXECUTOR::_duplicate (executor))
{

}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void
CHAOS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::set_attributes (const ::Components::ConfigValues & props)
{
  base_type::set_attributes (props);
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void
CHAOS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
handle_config (const ::Components::ConfigValues & props)
{
  // Call the base implementation, which calls back into load_port
  base_type::handle_config (props);

  // Find the configuration property so we can load the servants, and
  // configure servant.
  for (CORBA::ULong i = 0, length = props.length (); i < length; ++ i)
  {
    const ::Components::ConfigValue * config = props[i];

    if (PROPERTY_SERVANT_CONFIG == config->name ())
    {
      std::string value;
      config->value () >>= value;
    
      this->load_servant_configuration (value);
    }
  }
}

template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
bool CHAOS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
load_servant_configuration (const std::string & filename)
{
  CHAOS_Servant_Configuration file (filename);
  Servant_Configuration config;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading servant configuration [file=%s]\n"),
              filename.c_str ()));

  if (!(file >>= config))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to load servant configuration [file=%s]\n"),
                filename.c_str ()));

    throw ::Components::CreateFailure ();
  }

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading %d delegate servant(s)\n"),
              config.servants.size ()));

  for (Servant_Definition definition : config.servants)
  {
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - loading concrete servant [%s:%s]\n"),
                definition.module.c_str (),
                definition.symbol.c_str ()));

    // Load the servant module into memory, and get a pointer to the 
    // symbol that represents the entry point for the servant.
    ACE_DLL dll;
    
    if (0 != dll.open (definition.module.c_str (), ACE_DEFAULT_SHLIB_MODE, false))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to load module [%s]\n"),
                         definition.module.c_str ()),
                         false);

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - loading symbol from module [%s]\n"),
                definition.symbol.c_str ()));

    void * tmp = dll.symbol (definition.symbol.c_str ());

    if (0 == tmp)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - symbol does not exists in module [%s]\n"),
                         definition.symbol.c_str ()),
                         false);

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - creating servant using loaded symbol\n")));

    // Create the servant from the factory.
    typedef ::PortableServer::Servant (*SERVANT_FACTORY_METHOD)
      (const char *,
       ::PortableServer::POA_ptr,
       ::Components::EnterpriseComponent_ptr p);

    SERVANT_FACTORY_METHOD factory_method =
      reinterpret_cast <SERVANT_FACTORY_METHOD> (tmp);

    // We need to create a child POA for this servant. Otherwise, we run the
    // risk of duplicate POAs existing on this POA.
    PortableServer::POA_var servant_poa = 
      this->create_servant_POA (definition.alias.c_str (), 
                                this->the_POA_.in ());

    ::PortableServer::Servant servant =
      factory_method (this->name_.c_str (), 
                      servant_poa.in (),
                      EXECUTOR::_nil ());

    Servant * iccm_servant = dynamic_cast <iCCM::Servant *> (servant);

    if (0 == iccm_servant)
    {
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - servant is not an iCCM servant\n"),
                  definition.alias.c_str ()));

      throw Components::CreateFailure ();
    }

    if (0 != this->servants_.bind (definition.alias, iccm_servant))
    {
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - failed to cache servant %s\n"),
                  definition.alias.c_str ()));

      throw Components::CreateFailure ();
    }
  }

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading %d delegate ports(s)\n"),
              config.ports.size ()));

  // Iterate over each port definition. For each port, find the port in
  // the target iCCM::Servant, and add it to this servant.
  for (Port_Definition port : config.ports)
  {
    Servant * servant = 0;

    if (0 != this->servants_.find (port.servant, servant))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - servant does not exist [%s]\n"),
                         port.servant.c_str ()),
                         false);

      throw ::Components::CreateFailure ();
    }

    if (port.type == "publishes")
    {
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - searching for publishes port <%s> in <%s>\n"),
                  port.destination.c_str (),
                  port.servant.c_str ()));

      // Get the publisher table from the target servant, and use it to set the 
      // implementation of the CHAOS publisher table.
      Publisher_Table * pt = 0;
      
      if (0 != servant->get_publisher_table (port.destination.c_str (), pt))
      {
        ACE_ERROR ((LM_DEBUG,
                    ACE_TEXT ("%T (%t) - %M - publishes port <%s> does not exist in <%s>\n"),
                    port.destination.c_str (),
                    port.servant.c_str ()));

        throw ::Components::CreateFailure ();
      }

      CHAOS_Publisher_Table * chaos_publisher_table = 0;

      if (0 != this->publishes_.find (port.source.c_str (), chaos_publisher_table))
        throw ::Components::CreateFailure ();

      chaos_publisher_table->impl (pt);
    }
    else if (port.type == "emits")
    {
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - searching for emits port <%s> in <%s>\n"),
                  port.destination.c_str (),
                  port.servant.c_str ()));

      // Get the publisher from the target servant, and use it to set the 
      // implementation of the CHAOS publisher.
      Publisher * publisher = 0;
      
      if (0 != servant->get_publisher (port.destination.c_str (), publisher))
      {
        ACE_ERROR ((LM_DEBUG,
                    ACE_TEXT ("%T (%t) - %M - emits port <%s> does not exist in <%s>\n"),
                    port.destination.c_str (),
                    port.servant.c_str ()));

        throw ::Components::CreateFailure ();
      }

      CHAOS_Publisher * chaos_publisher = 0;

      if (0 != this->emits_.find (port.source.c_str (), chaos_publisher))
        throw ::Components::CreateFailure ();

      chaos_publisher->impl (publisher);
    }
    else if (port.type == "consumes")
    {
      ACE_ERROR ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - searching for consumer port <%s> in <%s>\n"),
                  port.destination.c_str (),
                  port.servant.c_str ()));

      // Get the consumer from the target servant, and use it to set the 
      // implementation of the CHAOS consumer.
      EventConsumer * consumer = 0;
      
      if (0 != servant->get_event_consumer (port.destination.c_str (), consumer))
      {
        ACE_ERROR ((LM_DEBUG,
                    ACE_TEXT ("%T (%t) - %M - consumer port <%s> does not exist in <%s>\n"),
                    port.destination.c_str (),
                    port.servant.c_str ()));

        throw ::Components::CreateFailure ();
      }

      CHAOS_EventConsumer * chaos_consumer = 0;

      if (0 != this->consumers_.find (port.source.c_str (), chaos_consumer))
        throw ::Components::CreateFailure ();

      ::Components::EventConsumerBase_var obj = 
        servant->get_consumer (port.destination.c_str ());

      chaos_consumer->impl (consumer, obj.in ());
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - invalid port type [type=%s]\n"),
                  port.type.c_str ()));

      throw ::Components::CreateFailure ();
    }
  }

  ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("%T (%t) - %M - servant configuration complete\n"),
            filename.c_str ()));

  return true;
}

}
