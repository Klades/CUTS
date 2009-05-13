#include "ccm/CCM_SessionComponentC.h"
#include "ciao/Logger/Log_Macros.h"

#include "DSTO_AdapterBase.h"

namespace CUTS_DSTO
{
  AdapterBase::AdapterBase (const char * instance_name,
                            ::CIAO::Container_ptr container)
    : ins_name_ (instance_name),
      container_ ( ::CIAO::Container::_duplicate (container))
  {
  }

  AdapterBase::~AdapterBase (void)
  {
  }

  ::CORBA::IRObject_ptr
  AdapterBase::get_component_def (void)
  {
    return ::CORBA::IRObject::_nil ();
  }

  ::Components::CCMHome_ptr
  AdapterBase::get_ccm_home (void)
  {
    return ::Components::CCMHome::_nil ();
  }

  ::Components::PrimaryKeyBase *
  AdapterBase::get_primary_key (void)
  {
    return 0;
  }
  
  ::Components::SessionComponent_ptr
  AdapterBase::get_executor (void)
  {
    ::Components::SessionComponent_var temp; // TODO
    return temp._retn ();
  }

  void
  AdapterBase::configuration_complete (void)
  {
  }

  void
  AdapterBase::remove (void)
  {
    try
      {
        ::Components::ConsumerDescriptions_var consumers =
          this->get_all_consumers ();

        ::CORBA::ULong const consumer_len = consumers->length ();

        for (CORBA::ULong j = 0; j < consumer_len; ++j)
          {
            ::PortableServer::ObjectId_var cons_id =
              this->container_->the_port_POA ()->reference_to_id (
                consumers[j]->consumer ());

            ::CIAO::Servant_Activator *sa =
              this->container_->ports_servant_activator ();
            sa->update_port_activator (cons_id.in ());

            this->container_->the_port_POA ()->deactivate_object (
              cons_id);
          }

//        ::Components::SessionComponent_var temp = this->get_executor ();
//        temp->ccm_remove ();

        ::CORBA::Object_var objref = this->container_->get_objref (this);

        ::Components::CCMObject_var ccmobjref =
          Components::CCMObject::_narrow (objref.in ());

        ::PortableServer::ObjectId_var oid;

        this->container_->uninstall_servant (
          this,
          ::CIAO::Container_Types::COMPONENT_t,
          oid.out ());
      }
    catch (const ::CORBA::Exception & ex)
      {
        ex._tao_print_exception ("CCMObject::remove: ");
      }
  }

  ::Components::ComponentPortDescription *
  AdapterBase::get_all_ports (void)
  {
    return 0;
  }

  ::Components::EventConsumerBase_ptr
  AdapterBase::get_consumer (const char * sink_name)
  {
    if (0 == sink_name)
      {
        throw Components::InvalidName ();
      }

    Components::EventConsumerBase_ptr retval =
      this->lookup_consumer (sink_name);

    if (CORBA::is_nil (retval))
      {
        throw Components::InvalidName ();
      }

    return retval;
  }

  ::Components::Cookie *
  AdapterBase::subscribe (
    const char * /* publisher_name */,
    ::Components::EventConsumerBase_ptr /* subscriber */)
  {
    return 0;
  }
    
  ::Components::EventConsumerBase_ptr
  AdapterBase::unsubscribe (const char * /* publisher_name */,
                            ::Components::Cookie * /* ck */)
  {
    return ::Components::EventConsumerBase::_nil ();
  }
                                 
  void
  AdapterBase::connect_consumer (
    const char * /* emitter_name */,
    ::Components::EventConsumerBase_ptr /* consumer */)
  {
  }
    
  ::Components::EventConsumerBase_ptr
  AdapterBase::disconnect_consumer (const char * /* source_name */)
  {
    return ::Components::EventConsumerBase::_nil ();
  }

  ::Components::ConsumerDescriptions *
  AdapterBase::get_all_consumers (void)
  {
    ::Components::ConsumerDescriptions *tmp = 0;
    ACE_NEW_THROW_EX (tmp,
                      ::Components::ConsumerDescriptions (
                      this->consumer_table_.size ()),
                      CORBA::NO_MEMORY ());

    ::Components::ConsumerDescriptions_var retval = tmp;

    retval->length (this->consumer_table_.size ());
    ::CORBA::ULong i = 0UL;

    for (ConsumerTable::const_iterator iter = this->consumer_table_.begin ();
         iter != this->consumer_table_.end ();
         ++iter, ++i)
      {
        retval[i] = iter->second;
      }

    return retval._retn ();
  }

  ::Components::ConsumerDescriptions *
  AdapterBase::get_named_consumers (
    const ::Components::NameList & /* names */)
  {
    return 0;
  }
    
  ::Components::EmitterDescriptions *
  AdapterBase::get_all_emitters (void)
  {
    return 0;
  }

  ::Components::EmitterDescriptions *
  AdapterBase::get_named_emitters (
    const ::Components::NameList & /* names */)
  {
    return 0;
  }
    
  ::Components::PublisherDescriptions *
  AdapterBase::get_all_publishers (void)
  {
    return 0;
  }

  ::Components::PublisherDescriptions *
  AdapterBase::get_named_publishers (
    const ::Components::NameList & /* names */)
  {
    return 0;
  }
    
  CORBA::Object_ptr
  AdapterBase::provide_facet (const char * /* name */)
  {
    return ::CORBA::Object::_nil ();
  }

  ::Components::FacetDescriptions *
  AdapterBase::get_all_facets (void)
  {
    return 0;
  }

  ::Components::FacetDescriptions *
  AdapterBase::get_named_facets (
    const ::Components::NameList & /* names */)
  {
    return 0;
  }
    
  ::CORBA::Boolean
  AdapterBase::same_component ( ::CORBA::Object_ptr /* object_ref */)
  {
    return false;
  }

  ::Components::Cookie *
  AdapterBase::connect (const char * /* name */,
                        ::CORBA::Object_ptr /* connection */)
  {
    return 0;
  }
                             
  ::CORBA::Object_ptr
  AdapterBase::disconnect (const char * /* name */,
                           ::Components::Cookie * /* ck */)
  {
    return ::CORBA::Object::_nil ();
  }
                                
  ::Components::ConnectionDescriptions *
  AdapterBase::get_connections (const char * /* name */)
  {
    return 0;
  }

  ::Components::ReceptacleDescriptions *
  AdapterBase::get_all_receptacles (void)
  {
    return 0;
  }

  ::Components::ReceptacleDescriptions *
  AdapterBase::get_named_receptacles (
    const ::Components::NameList & /* names */)
  {
    return 0;
  }

  ::CORBA::Object_ptr
  AdapterBase::get_facet_executor (const char * /* name */)
  {
    return ::CORBA::Object::_nil ();
  }

  void
  AdapterBase::add_consumer (const char * port_name,
                             ::Components::EventConsumerBase_ptr port_ref)
  {
    if (0 == port_name || ::CORBA::is_nil (port_ref))
      {
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("Servant_Impl_Base::add_consumer ")
                    ACE_TEXT ("- Bad port name [%C] or bad objref\n"),
                    port_name));
        throw ::CORBA::BAD_PARAM ();
        return;
      }

    ::Components::ConsumerDescription *cd = 0;
    ACE_NEW_THROW_EX (cd,
                      ::OBV_Components::ConsumerDescription,
                      CORBA::NO_MEMORY ());

    ::Components::ConsumerDescription_var safe = cd;

    cd->name (port_name);
    cd->type_id (port_ref->_interface_repository_id ());
    cd->consumer (port_ref);

    ConsumerTable::value_type entry;
    entry.first = port_name;
    entry.second = safe._retn ();

    ACE_WRITE_GUARD_THROW_EX (TAO_SYNCH_MUTEX,
                              mon,
                              this->lock_,
                              CORBA::NO_RESOURCES ());

    (void) this->consumer_table_.insert (entry);
  }

  ::Components::EventConsumerBase_ptr
  AdapterBase::lookup_consumer (const char * port_name)
  {
    if (0 == port_name)
      {
        return ::Components::EventConsumerBase::_nil ();
      }

    ACE_READ_GUARD_THROW_EX (TAO_SYNCH_MUTEX,
                             mon,
                             this->lock_,
                             CORBA::NO_RESOURCES ());

    ConsumerTable::const_iterator iter =
      this->consumer_table_.find (port_name);

    if (iter == this->consumer_table_.end ())
      {
        return ::Components::EventConsumerBase::_nil ();
      }

    return
      ::Components::EventConsumerBase::_duplicate (
        iter->second->consumer ());
  }

  ::Components::ConsumerDescription *
  AdapterBase::lookup_consumer_description (
    const char * port_name)
  {
    if (0 == port_name)
      {
        /// Calling function will throw InvalidName after getting this.
        return 0;
      }

    ::Components::ConsumerDescription_var cd;
    ConsumerTable::const_iterator iter;

    {
      ACE_READ_GUARD_THROW_EX (TAO_SYNCH_MUTEX,
                               mon,
                               this->lock_,
                               CORBA::NO_RESOURCES ());

      iter = this->consumer_table_.find (port_name);

      if (iter != this->consumer_table_.end ())
        {
          cd = iter->second;
        }
    }

    return cd._retn ();
  }
}
