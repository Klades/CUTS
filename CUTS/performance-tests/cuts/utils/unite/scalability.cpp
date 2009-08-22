// $Id$

#include "ace/Get_Opt.h"
#include "ace/OS_NS_unistd.h"
#include "ace/streams.h"
#include "ace/Atomic_Op.h"
#include "ace/Condition_T.h"
#include "ace/Guard_T.h"
#include "cuts/utils/logging/client/logger/Client_Logger.h"
#include "cuts/utils/logging/server/LoggingServerS.h"
#include "cuts/utils/testing/svcs/server/testingC.h"
#include "cuts/UUID.h"
#include "cuts/Servant_Manager_T.h"
#include "cuts/ORB_Server_Task.h"
#include <sstream>

struct opts_t
{
  opts_t (void)
    : formats_ (1),
      relations_ (1),
      messages_ (20000)
  {

  }

  ACE_CString client_;

  int formats_;

  int relations_;

  int messages_;
};

class MessageCounter :
  public POA_CUTS::LoggingServerListener
{
public:
  MessageCounter (void)
    : recv_count_ (0),
      send_count_ (0),
      is_done_ (done_mutex_)
  {

  }

  virtual ~MessageCounter (void)
  {

  }

  virtual void handle_messages (const char * hostname,
                                const ::CUTS::UUID & test,
                                const ::CUTS::LogMessages & messages)
  {
    long recv_count = this->recv_count_ += messages.length ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - message counter received %d ")
                ACE_TEXT ("message(s) [count=%d]\n"),
                messages.length (),
                recv_count));

    ACE_GUARD (ACE_Thread_Mutex, guard, this->done_mutex_);

    if (recv_count == this->send_count_)
      this->is_done_.broadcast ();
  }

  int wait_for_completion (long send_count)
  {
    ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->done_mutex_, -1);

    if (send_count > this->recv_count_.value ())
    {
      this->send_count_ = send_count;
      this->is_done_.wait ();
    }

    return 0;
  }

private:
  ACE_Atomic_Op <ACE_RW_Thread_Mutex, long> recv_count_;

  long send_count_;

  ACE_Thread_Mutex done_mutex_;

  ACE_Condition <ACE_Thread_Mutex> is_done_;
};

//
// parse_args
//
int parse_args (int argc, char * argv [], opts_t & opts)
{
  const char * optstr = "r:f:";
  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("client", ACE_Get_Opt::ARG_REQUIRED);

  char opt;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("client", get_opt.long_option ()))
      {
        opts.client_ = get_opt.opt_arg ();
      }
      break;

    case 'f':
      {
        std::istringstream istr (get_opt.opt_arg ());
        istr >> opts.formats_;
      }
      break;

    case 'r':
      {
        std::istringstream istr (get_opt.opt_arg ());
        istr >> opts.relations_;
      }
      break;
    }
  }

  return 0;
}

//
// generate_execution_trace
//
int generate_execution_trace (CUTS_Client_Logger & logger,
                              const opts_t & opts,
                              long & send_count)
{
  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - generating executing traces ")
              ACE_TEXT ("[formats=%d; relations=%d; messages=%d]\n"),
              opts.formats_,
              opts.relations_,
              opts.messages_));

  for (int format = 0; format < opts.formats_; ++ format)
  {
    ACE_DEBUG ((LM_DEBUG, "LF%d\n", format));

    for (int i = 0; i < opts.messages_; ++ i)
    {
      std::ostringstream ostr;
      ostr << "LF" << format << ":";

      for (int rel = 0; rel < opts.relations_; ++ rel)
        ostr << " " << i << ";";

      if (0 == logger.log (LM_INFO, ostr.str ().c_str ()))
      {
        ++ send_count;
      }
      else
      {
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to log message [%s]\n"),
                    ostr.str ().c_str ()));

      }
    }
  }

  return 0;
}

//
// write_datagraph_file
//
int write_datagraph_file (const ACE_Utils::UUID & uuid, const opts_t & opts)
{
  // Open the datagraph file for writing.
  std::string filename (uuid.to_string ()->c_str ());
  filename += ".datagraph";

  std::ofstream fout;
  fout.open (filename.c_str ());

  if (!fout.is_open ())
    return -1;

  fout << "<?xml version='1.0' encoding='UTF-8' standalone='no' ?>" << std::endl
       << "<cuts:datagraph xmlns='http://www.dre.vanderbilt.edu/CUTS'" << std::endl
       << "      xmlns:cuts='http://www.dre.vanderbilt.edu/CUTS'" << std::endl
       << "      xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'" << std::endl
       << "      xsi:schemaLocation='http://www.dre.vanderbilt.edu/CUTS cuts-unite.xsd'" << std::endl
       << std::endl
       << "  <name>" << uuid.to_string ()->c_str () << "</name>" << std::endl
       << "  <logformats>" << std::endl;

  for (int format = 0; format < opts.formats_; ++ format)
  {
    std::ostringstream ostr;
    ostr << "LF" << format << ":";

    for (int rel = 0; rel < opts.relations_; ++ rel)
      ostr << " {INT r" << rel << "};";

    fout << "    <logformat id='LF" << format << "'>" << std::endl
         << "      <value>" << ostr.str () << "</value>" << std::endl;

    if (format != opts.formats_ - 1)
    {
      fout << "      <relations>" << std::endl
           << "        <relation effectref='LF'" << format + 1 << "'>'" << std::endl;

      for (int rel = 0; rel < opts.relations_; ++ rel)
        fout << "          <causality cause='r" << rel << "' effect='r" << rel << "' />" << std::endl;

      fout << "        </relation>" << std::endl
           << "      </relations>" << std::endl;
    }

    fout << "    <logformat>" << std::endl;
  }

  fout << "  </logformats>" << std::endl
       << "</cuts:datagraph>" << std::endl;

  fout.close ();

  return 0;
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    ::CORBA::ORB_var orb = ::CORBA::ORB_init (argc, argv);

    opts_t opts;

    if (0 != ::parse_args (argc, argv, opts))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse command-line arugments\n")),
                         1);

    ::CORBA::Object_var obj = orb->resolve_initial_references ("RootPOA");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve RootPOA\n")),
                         -1);

    ::PortableServer::POA_var poa = ::PortableServer::POA::_narrow (obj.in ());

    if (::CORBA::is_nil (poa.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a POA\n")),
                         -1);

    ::PortableServer::POAManager_var mgr = poa->the_POAManager ();
    mgr->activate ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating MessageCounter\n")));

    MessageCounter counter;
    CUTS_Servant_Manager_T <MessageCounter> servant (&counter, false);
    servant.activate (poa.in ());

    obj = servant.get_reference ();
    ::CUTS::LoggingServerListener_var listener = ::CUTS::LoggingServerListener::_narrow (obj.in ());

    obj = orb->resolve_initial_references ("TestServer");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve TestServer\n")),
                         -1);

    ::CUTS::TestManager_var test_manager = ::CUTS::TestManager::_narrow (obj.in ());

    if (::CORBA::is_nil (test_manager.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a CUTS::TestManager\n")),
                         -1);

    obj = orb->resolve_initial_references ("LoggingServer");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve LoggingServer\n")),
                         -1);

    ::CUTS::LoggingServer_var logging_server = ::CUTS::LoggingServer::_narrow (obj.in ());

    if (::CORBA::is_nil (test_manager.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a CUTS::LoggingServer\n")),
                         -1);

    // Connect the logger to the logging client.
    CUTS_Client_Logger logger ("logger");
    if (0 != logger.connect (opts.client_.c_str ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - client logger failed to connect\n")),
                         -1);

    // Associate message from this logger with the current test.
    CUTS::TestDetails_var details = test_manager->details ();

    ACE_Utils::UUID uuid;
    details->uid >>= uuid;
    logger.set_uuid (uuid);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating ORB task\n")));

    CUTS_ORB_Server_Task task (orb.in ());
    task.activate ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - registering message counter listener\n")));

    ::CUTS::UUID_var cookie = logging_server->register_listener (details->uid, listener.in ());

    long send_count = 0;
    if (0 != ::generate_execution_trace (logger, opts, send_count))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to generate execution trace\n")));

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - waiting for receipt of %d message(s)\n"),
                send_count));

    // Shutdown the ORB and wait for task to return.
    counter.wait_for_completion (send_count);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - unregistering message counter listener\n")));

    logging_server->unregister_listener (details->uid, cookie);

    // Disconnect from the logging client.
    if (0 != logger.disconnect ())
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - client logger failed to disconnect\n")));

    if (0 != write_datagraph_file (uuid, opts))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to write datagraph file\n")));


    // Deactivate the servant.
    servant.deactivate ();

    //ACE_DEBUG ((LM_DEBUG,
    //            ACE_TEXT ("%T (%t) - %M - signaling test to shutdown\n")));
    //// test_manager->shutdown ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - shutdown down the ORB\n")));

    orb->shutdown ();
    task.wait ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - destroying ORB and POA\n")));

    poa->destroy (0, 0);
    orb->destroy ();

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception (%N:%l)\n")));
  }

  return 1;
}
