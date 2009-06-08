// $Id$

#include "ace/Get_Opt.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/High_Res_Timer.h"
#include "ace/streams.h"
#include "AnyTestC.h"
#include <sstream>

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

      ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("AnyTest");
      ::PerformanceTests::AnyTest_var anytest = ::PerformanceTests::AnyTest::_narrow (obj.in ());

      ::CORBA::Any any;
      size_t event_count (0);

      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - running the test for %d event(s)\n",
                  this->max_events_));

      ACE_High_Res_Timer timer;
      timer.start ();

      for (; event_count < this->max_events_; event_count)
      {
        any <<= event_count ++;
        anytest->send_any (any);
      }

      ACE_DEBUG ((LM_DEBUG,
                  "%T - %M - test is complete\n",
                  this->max_events_));

      timer.stop ();

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
    const char * optargs = "n:";
    ACE_Get_Opt get_opt (argc, argv, optargs);

    char opt;

    while (EOF != (opt = get_opt ()))
    {
      switch (opt)
      {
      case 'n':
        std::istringstream istr (get_opt.opt_arg ());
        istr >> this->max_events_;
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
};

#define CLIENT \
  ACE_Singleton <Client, ACE_Null_Mutex>::instance ()

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  int retval;

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
