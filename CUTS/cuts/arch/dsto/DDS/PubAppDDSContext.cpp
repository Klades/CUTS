#include "ciao/Valuetype_Factories/Cookies.h"

#include "ModelDDSDataConversion.h"

#include "PubAppDDSContext.h"

namespace DSTO_AppSpace_Impl
{
  PubAppDDSContext::PubAppDDSContext (DDS_Utility & dds_utility)
    : dds_utility_ (dds_utility)
  {
  }
  
  PubAppDDSContext::~PubAppDDSContext (void)
  {
  }
  
  void
  PubAppDDSContext::push_app_op_send ( ::Outer::TestData * ev)
  {
    ::Outer::TestData_DDS dds_ev;
    ::ModelDDSDataConversion::to_corba (dds_ev, *ev);
    
    ReturnCode_t status =
      this->app_op_send_writer_->write (dds_ev, HANDLE_NIL);
    this->dds_utility_.check_status (
      status, 
      "push_app_op_send: write()");
  }
  
  ::Components::Cookie *
  PubAppDDSContext::subscribe_app_op_send (
    ::CUTS_DDS::DummyConsumer_ptr c)
  {
    if (CORBA::is_nil (this->app_op_send_writer_.in ()))
      {
        ::Outer::TestData_DDSTypeSupport_var ts =
          new ::Outer::TestData_DDSTypeSupport;
          
        Topic_var topic =
          this->dds_utility_.get_topic< ::Outer::TestData_DDSTypeSupportInterface> (
            ts.in (),
            "app_op_send_topic");
        this->dds_utility_.check_objref (
          topic.in (),
          "push_app_op_send: get_topic ()");
            
        this->app_op_send_writer_ =
          this->dds_utility_.get_datawriter< ::Outer::TestData_DDSDataWriter> (
            topic.in ());
        this->dds_utility_.check_objref (
          app_op_send_writer_.in (),
          "push_app_op_send: get_datawriter()");
      }

    if ( ::CORBA::is_nil (c))
      {
        throw ::CORBA::BAD_PARAM ();
      }
      
    ::Components::Cookie * retv = 0;
    ACE_NEW_THROW_EX (retv,
                      ::CIAO::Cookie_Impl (
                        reinterpret_cast<ptrdiff_t> (c)),
                      ::CORBA::NO_MEMORY ());

    return retv;
  }
  
  ::CUTS_DDS::DummyConsumer_ptr
  PubAppDDSContext::unsubscribe_app_op_send (
    ::Components::Cookie * ck)
  {
    // We may have to keep the whole consumer table mechanism
    // if returning 0 here messes things up.
    return ::CUTS_DDS::DummyConsumer::_nil ();
  }
  
  PubAppDDSContext *
  PubAppDDSContext::_narrow ( ::Components::SessionContext_ptr p)
  {
    return dynamic_cast<PubAppDDSContext *> (p);
  }
}