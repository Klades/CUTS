// -*- C++ -*-

#include "ccpp_dds_dcps.h"

class Sender_App
{
public:
  /// Default constructor.
  Sender_App (void);

  /// Destructor.
  ~Sender_App (void);

  int run_main (int argc, char * argv []);

  void shutdown (void);

private:
  template <typename T>
  void register_type (void)
  {
    T * type_support = 0;

    ACE_NEW_THROW_EX (type_support,
                      T (),
                      ACE_bad_alloc ());

    ACE_Auto_Ptr <T> auto_clean (type_support);
    this->type_name_ = type_support->get_type_name ();
    type_support->register_type (this->participant_.in (), this->type_name_);
  }

  ::DDS::DomainParticipant_var participant_;
  ::DDS::Topic_var topic_;
  ::DDS::Publisher_var publisher_;
  ::DDS::DataWriter_var writer_;

  bool is_active_;

  const char * type_name_;
};
