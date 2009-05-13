#ifndef DDS_UTILITY_H
#define DDS_UTILITY_H

#include "ccpp_dds_dcps.h"

#include "DDS_Utilities_export.h"

using namespace DDS;

class DDS_Utilities_Export DDS_Utility
{
public:
  DDS_Utility (void);
  ~DDS_Utility (void);
  
  bool init (DomainId_t domain);
  
  template<typename T>
  Topic_ptr get_topic (T * type_support,
                       const char * topic_name)
  {
    // Can't have scoping in register_type() arg
    // Permanent fix later.
    char * type_name = CORBA::string_dup ("Outer_TestData_DDS");//type_support->get_type_name ();
    ReturnCode_t status =
      type_support->register_type (participant_.in (),
                                   type_name);
                                   
    this->check_status (status, "register_type()");
    
    Topic_var topic =
      participant_->create_topic (topic_name,
                                  type_name,
                                  TOPIC_QOS_DEFAULT,
                                  TopicListener::_nil(),
                                  ANY_STATUS);
                                         
    this->check_objref (topic, "create_topic()");
    CORBA::string_free (type_name);
    
    return topic._retn ();
  }
  
  template<typename T>
  T * get_datawriter (Topic_ptr topic)
  {
    if (CORBA::is_nil (publisher_.in ()))
      {
        publisher_ = 
          participant_->create_publisher (PUBLISHER_QOS_DEFAULT,
                                          PublisherListener::_nil (),
                                          ANY_STATUS);                                          
        this->check_objref (publisher_.in (),
                            "create_publisher()");
      }
      
    DataWriter_var dw =
      publisher_->create_datawriter (topic,
                                     DATAWRITER_QOS_DEFAULT,
                                     0,
                                     ANY_STATUS);                                
    this->check_objref (dw.in (), "create_datawriter()");
    
    T * w = T::_narrow (dw.in ());
    this->check_objref (w, "narrow()");
    
    return w;
  }
  
  template<typename T>
  T * get_datareader (Topic_ptr topic,
                      DataReaderListener_ptr listener)
  {
    if (CORBA::is_nil (subscriber_.in ()))
      {
        subscriber_ =
          participant_->create_subscriber (SUBSCRIBER_QOS_DEFAULT,
                                           SubscriberListener::_nil (),
                                           ANY_STATUS);                                  
        this->check_objref (subscriber_.in (),
                            "create_subscriber()");
      }
      
    DataReader_var dr =
      subscriber_->create_datareader (topic,
                                      DATAREADER_QOS_DEFAULT,
                                      listener,
                                      ANY_STATUS);                                
    this->check_objref (dr.in (), "create_datareader()");
    
    T * r = T::_narrow (dr.in ());
    this->check_objref (r, "narrow()");
    
    return r;
  }
  
  void check_status (ReturnCode_t status, const char * info);
  void check_objref (CORBA::Object_ptr obj, const char * info);

private:
  char * get_error_name (ReturnCode_t status);
  
private:
  DomainParticipantFactory_var factory_;
  DomainId_t domain_;
  DomainParticipant_var participant_;
  Publisher_var publisher_;
  Subscriber_var subscriber_;
};

#endif // DDS_UTILITY_H

