// $Id$

#if !defined (__CUTS_INLINE__)
#include "CHAOS_Servant_T.inl"
#endif

namespace iCCM
{

//
// set_attributes
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void
CHAOS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::set_attributes (const ::Components::ConfigValues & props)
{
  base_type::set_attributes (props);
}

//
// handle_config
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void
CHAOS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::handle_config (const ::Components::ConfigValues & props)
{
  // Call the base implementation, which calls back into load_port
  base_type::handle_config (props);

  // Now that we have all the endpoints and subservants loaded, let the
  // subservants configure the concrete endpoints appropriately.
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Configuring subservant(s)\n")));
  servant_map_type::ITERATOR iter (this->servants_);

  for (; !iter.done (); ++ iter)
    iter->item ()->handle_config (props);
}

//
// test
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void CHAOS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::test (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - SERVANT_T TEST\n")));
}

//
// load_port
//
template <typename T, typename CONTEXT, typename EXECUTOR, typename POA_EXEC>
void CHAOS_Servant_T <T, CONTEXT, EXECUTOR, POA_EXEC>::
load_port (const char * port, const char * location, const char * entrypt)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - loading port [%s] from library [%s:%s]\n"),
              port, location, entrypt));

  ACE_DLL module;

  if (0 != module.open (location, ACE_DEFAULT_SHLIB_MODE, false))
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - error loading opening %s; %m\n"),
                location));

    //throw ::Components::Deployment::InstallationFailure ();
  }

  // If we haven't loaded this DLL already, then we need to allocate a new subservant
  iCCM::Servant * svnt = 0;
  if (0 != this->servants_.find (location, svnt))
  {
    // First time seeing this servant.  Let's load it
    void * symbol = module.symbol ("create_servant");

    //if (0 == symbol)
      //throw ::Components::Deployment::ImplEntryPointNotFound ();

    typedef iCCM::Servant * (*ServantFactoryMethod) (const char *);
    ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (symbol);
    ServantFactoryMethod factory_method = reinterpret_cast <ServantFactoryMethod> (tmp_ptr);

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - new subservant identified, calling [create_servant] on library\n")));

    svnt = (*factory_method) (this->name_.c_str ());

    this->servants_.bind (location, svnt);
  }

  // Identify the type of endpoint and load it
  void * symbol = module.symbol (entrypt);
  ptrdiff_t tmp_ptr = reinterpret_cast <ptrdiff_t> (symbol);

  iCCM::CHAOS_EventConsumer * consumer;
  iCCM::CHAOS_Publisher * emits;
  iCCM::CHAOS_Publisher_Table * publishes;

  if (0 == this->consumers_.find (port, consumer))
  {
    // The consumer callback to the servant is model-specific, so we can't
    // handle it in a generic manner at this location.  Instead, we defer
    // the call to the factory method to the eventconsumer.
    consumer->allocate (tmp_ptr);
    svnt->add_eventconsumer (port, consumer->impl ());
  }
  else if (0 == this->emits_.find (port, emits))
  {
    typedef iCCM::Publisher * (*PublisherFactoryMethod) (void);
    PublisherFactoryMethod factory_method = reinterpret_cast <PublisherFactoryMethod> (tmp_ptr);

    iCCM::Publisher * p = (*factory_method) ();
    emits->impl (p);
    svnt->add_publisher (port, p);
  }
  else if (0 == this->publishes_.find (port, publishes))
  {
    typedef iCCM::Publisher_Table * (*PublisherTableFactoryMethod) (void);
    PublisherTableFactoryMethod factory_method = reinterpret_cast <PublisherTableFactoryMethod> (tmp_ptr);

    iCCM::Publisher_Table * p = (*factory_method) ();
    publishes->impl (p);
    svnt->add_publisher_table (port, p);
  }
}

}
