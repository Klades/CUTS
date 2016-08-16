#ifndef EVENT_PACKAGE_H_
#define EVENT_PACKAGE_H_

template <typename EVENT_TRAITS, typename INFO>
class EventPackage
{
  public:
    typedef typename EVENT_TRAITS::dds_event_sequence_type event_seq;
    typedef typename EVENT_TRAITS::upcall_event_type upcall_event_type;
    typedef typename EVENT_TRAITS::reader_type READER;

    EventPackage (event_seq * event, INFO * info, READER * reader);
    ~EventPackage (void);

    event_seq * get (void);

  private:
    event_seq * event_;
    INFO * info_;
    READER * reader_;
};

#include "EventPackage.cpp"

#endif
