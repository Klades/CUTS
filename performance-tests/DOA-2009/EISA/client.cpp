// $Id$

#include "ace/Get_Opt.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/High_Res_Timer.h"
#include "ace/streams.h"
#include "ace/OS_NS_unistd.h"
#include "eisa/EINode_i.h"
#include "eisa/Software_Probe.h"
#include "eisa/Software_Probe_Factory_T.h"
#include "eisa/Software_Probe_Data_Packet.h"
#include <sstream>

class Simple_Probe : public EISA_Software_Probe
{
public:
  Simple_Probe (EISA::EINode_ptr parent)
    : EISA_Software_Probe (parent, "E860E6F7-0A10-4F94-846D-8E99F4B250B1", "heartbeat", " ")
  {
    EISA_Software_Probe_Data_Packet * packet = 0;

    ACE_NEW_THROW_EX (packet,
                      EISA_Software_Probe_Data_Packet (this->uuid_),
                      CORBA::NO_MEMORY ());

    this->packet_.reset (packet);
  }

  virtual ~Simple_Probe (void)
  {

  };

  void init (const char *)
  {

  }

  void fini (void)
  {

  }

  void handle_command (const char * command)
  {

  }

  void send_value (size_t value)
  {
    this->packet_->reset (++ this->seqnum_, 0);
    this->packet_->write_long (value);
    this->einode_->send_data (this->packet_->stream ());
  }

private:
  ACE_Auto_Ptr <EISA_Software_Probe_Data_Packet> packet_;

  size_t seqnum_;
};

class Client
{
public:
  Client (void)
    : max_events_ (1000)
  {
  }

  ~Client (void)
  {

  }

  int run_main (int argc, char * argv [])
  {
    try
    {
      this->orb_ = ::CORBA::ORB_init (argc, argv);
      this->parse_args (argc, argv);

      EISA_EINode_i einode (true);
      einode.activate (this->config_file_, this->orb_.in ());

      ACE_OS::sleep (2);

      size_t event_count (0);
      Simple_Probe simple_probe (&einode);

      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - running the test for %d event(s)\n",
                  this->max_events_));

      ACE_High_Res_Timer timer;
      timer.start ();

      while (event_count < this->max_events_)
      {
        simple_probe.send_value (++ event_count);
      }

      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - test is complete\n",
                  this->max_events_));

      timer.stop ();
      einode.deactivate ();

      ACE_Time_Value elapsed_time;
      timer.elapsed_time (elapsed_time);

      std::cout
        << "sent " << event_count << " in " <<
        elapsed_time.sec () << "." << elapsed_time.usec ()
        << " second(s)" << std::endl
        << std::endl;

      return 0;
    }
    catch (const ::CORBA::Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  "%T - %M - %s\n",
                  ex._info ().c_str ()));
    }

    return -1;
  }

  int parse_args (int argc, char * argv [])
  {
    const char * optargs = "n:c:";
    ACE_Get_Opt get_opt (argc, argv, optargs);

    int opt;

    while (EOF != (opt = get_opt ()))
    {
      switch (opt)
      {
      case 'n':
        {
          std::istringstream istr (get_opt.opt_arg ());
          istr >> this->max_events_;
        }
        break;

      case 'c':
        this->config_file_ = get_opt.opt_arg ();
        break;
      }
    }

    return 0;
  }

  void destroy (void)
  {
    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->destroy ();
  }

private:
  ::CORBA::ORB_var orb_;

  size_t max_events_;

  ACE_CString config_file_;
};

#define CLIENT \
  ACE_Singleton <Client, ACE_Null_Mutex>::instance ()

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  int retval;

  u_long default_mask =
    LM_EMERGENCY | LM_ALERT | LM_CRITICAL | LM_ERROR | LM_WARNING | LM_NOTICE | LM_DEBUG;

  ACE_LOG_MSG->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

  try
  {
    retval = CLIENT->run_main (argc, argv);
  }
  catch (...)
  {
    retval = 1;
  }

  CLIENT->destroy ();
  return retval;
}
