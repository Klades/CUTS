// $Id$

#include "Sender_App.h"
#include "opensplice/Performance_TestDcps_impl.h"
#include "ace/High_Res_Timer.h"

//
// Sender_App
//
Sender_App::Sender_App (void)
: is_active_ (false)
{

}

//
// ~Sender_App
//
Sender_App::~Sender_App (void)
{

}

//
// run_main
//
int Sender_App::run_main (int argc, char * argv [])
{
  // Create the participant for this application.
  ::DDS::DomainParticipantFactory_var factory = ::DDS::DomainParticipantFactory::get_instance ();
  this->participant_ =
    factory->create_participant (0,
                                 PARTICIPANT_QOS_DEFAULT,
                                 0,
                                 DDS::STATUS_MASK_NONE);

  if (CORBA::is_nil (this->participant_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to create participant\n")),
                       1);

  // Register the event type with the sender. We can then register
  // a new topic for this application.
  this->register_type <Size8DataTypeSupport> ();

  this->topic_ =
    this->participant_->create_topic (this->type_name_,
                                      this->type_name_,
                                      TOPIC_QOS_DEFAULT,
                                      0,
                                      DDS::STATUS_MASK_NONE);

  if (CORBA::is_nil (this->topic_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to create topic\n")),
                       1);

  // Create a publisher.
  this->publisher_ =
    this->participant_->create_publisher (PUBLISHER_QOS_DEFAULT,
                                          0,
                                          DDS::STATUS_MASK_NONE);

  if (CORBA::is_nil (this->publisher_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to create publisher\n")),
                       1);

  // Create this application's data writer.
  this->writer_ =
    this->publisher_->create_datawriter (this->topic_.in (),
                                         DATAWRITER_QOS_DEFAULT,
                                         0,
                                         DDS::STATUS_MASK_NONE);

  if (CORBA::is_nil (this->writer_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to create data writer\n")),
                       1);

  Size8DataDataWriter_var typed_writer = Size8DataDataWriter::_narrow (this->writer_.in ());

  size_t count = 0;
  this->is_active_ = true;
  Size8Data data;

  // Start the timer for the application.
  ACE_High_Res_Timer timer;
  timer.start ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - running the sender\n")));

  while (this->is_active_)
  {
    typed_writer->write (data, DDS::HANDLE_NIL);
    ++ count;
  }

  timer.stop ();

  // Calculate the events/second.
  ACE_hrtime_t elapsed;
  timer.elapsed_time (elapsed);

  double tput = ((double)count / (double)elapsed) * (double)ACE_ONE_SECOND_IN_NSECS;

  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("# events sent: %d\n")
              ACE_TEXT ("sender throughput: %f\n"),
              count,
              tput));

  return 0;
}

//
// shutdown
//
void Sender_App::shutdown (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - shutting down the sender\n")));

  this->is_active_ = false;
}
