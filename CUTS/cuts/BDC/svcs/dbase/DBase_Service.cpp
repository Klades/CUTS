// $Id$

#include "DBase_Service.h"

#if !defined (__CUTS_INLINE__)
#include "DBase_Service.inl"
#endif

#include "cuts/Auto_Functor_T.h"
#include "cuts/Component_Info.h"
#include "cuts/System_Metric.h"
#include "cuts/Component_Info.h"
#include "cuts/Component_Metric.h"
#include "cuts/Component_Type.h"
#include "cuts/Host_Table_Entry.h"
#include "cuts/Port_Metric.h"
#include "cuts/Time.h"
#include "cuts/Testing_Service.h"
#include "cuts/BDC/BDC_Service_Manager.h"
#include "cuts/utils/db/ODBC/ODBC_Connection.h"
#include "cuts/utils/db/ODBC/ODBC_Types.h"
#include "cuts/utils/db/DB_Query.h"
#include "cuts/utils/db/DB_Record.h"
#include "cuts/utils/db/DB_Parameter.h"

#include "ace/Guard_T.h"
#include "ace/Auto_Ptr.h"
#include "ace/Log_Msg.h"
#include "ace/Date_Time.h"
#include "ace/Time_Value.h"
#include "ace/OS_NS_time.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_sys_time.h"
#include "ace/Get_Opt.h"

#define MAX_VARCHAR_LENGTH 256

CUTS_BDC_SERVICE_IMPL (CUTS_Database_Service);

#define VERBOSE_MESSAGE(msg) \
  if (this->verbose_) \
  { \
    ACE_ERROR (msg); \
  }

#define VERBOSE_MESSAGE_RETURN(msg) \
  if (this->verbose_) \
  { \
    ACE_ERROR_RETURN (msg); \
  }

//
// CUTS_Database_Service
//
CUTS_Database_Service::CUTS_Database_Service (void)
: verbose_ (false),
  server_ (CUTS_DEFAULT_HOSTNAME),
  username_ (CUTS_USERNAME),
  password_ (CUTS_PASSWORD),
  port_ (CUTS_DEFAULT_PORT),
  test_number_ (-1),
  enable_deployment_ (false)
{
  CUTS_DB_Connection * conn = 0;
  ACE_NEW (conn, ODBC_Connection ());
  this->conn_.reset (conn);
}

//
// ~CUTS_Database_Service
//
CUTS_Database_Service::~CUTS_Database_Service (void)
{

}

//
// init
//
int CUTS_Database_Service::init (int argc, ACE_TCHAR * argv [])
{
  if (this->parse_args (argc, argv) != 0)
    return -1;

  try
  {
    // Create a connection
    this->conn_->connect (this->username_.c_str (),
                          this->password_.c_str (),
                          this->server_.c_str (),
                          this->port_);

    if (this->conn_->is_connected ())
    {
      VERBOSE_MESSAGE ((LM_INFO,
                        "*** info [archive]: successfully connected to "
                        "database on %s\n",
                        this->server_.c_str ()));

      this->registry_.attach (this->conn_.get ());
      return true;
    }
    else
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error [archive]: failed to connect to database "
                  "[server=%s;username=%s;password=%s;port=%d]\n",
                  this->server_.c_str (),
                  this->username_.c_str (),
                  this->password_.c_str (),
                  this->port_));
      return false;
    }
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: caught unknown exception\n"));
  }
}

//
// fini
//
int CUTS_Database_Service::fini (void)
{
  try
  {
    // Stop the current test.
    this->stop_current_test ();

    // Remove the connection from the registry.
    this->registry_.detach ();

    // Stop the current test.
    this->stop_current_test ();

    // Disconnect from the database.
    this->conn_->disconnect ();
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [achvive]: %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: caught unknown exception\n"));
  }

  return 0;
}

//
// parse_args
//
int CUTS_Database_Service::parse_args (int argc, ACE_TCHAR * argv [])
{
  const char * opts = ACE_TEXT ("s:p:");
  ACE_Get_Opt get_opt (argc, argv, opts, 0);

  get_opt.long_option ("server", 's', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("port", 'p', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("verbose", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("enable-deployment", ACE_Get_Opt::NO_ARG);

  int option;

  while ((option = get_opt ()) != EOF)
  {
    switch (option)
    {
    case 0:
      if (ACE_OS::strcmp (get_opt.long_option (), "server") == 0)
      {
        this->server_ = get_opt.opt_arg ();
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "port") == 0)
      {
        this->port_ = ACE_OS::atoi (get_opt.opt_arg ());
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "verbose") == 0)
      {
        this->verbose_ = true;
      }
      else if (ACE_OS::strcmp (get_opt.long_option (), "enable-deployment") == 0)
      {
        this->enable_deployment_ = true;
      }
      break;

    case 's':
      this->server_ = get_opt.opt_arg ();
      break;

    case 'p':
      this->port_ = ACE_OS::atoi (get_opt.opt_arg ());
      break;

    case '?':
      // unknown option; do nothing
      break;

    case ':':
      ACE_ERROR_RETURN ((LM_ERROR,
                         "*** error [archive]: %c is missing an argument\n",
                         get_opt.opt_opt ()),
                         1);
      break;

    default:
      /* do nothing */;
    }
  }

  return 0;
}

//
// create_new_test
//
bool CUTS_Database_Service::create_new_test (void)
{
  ACE_WRITE_GUARD_RETURN (ACE_RW_Thread_Mutex,
                          guard,
                          this->lock_,
                          false);

  if (this->test_number_ != -1 && !this->stop_current_test_i ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       "*** error [archive]: cannot stop current test\n"),
                       false);
  }

  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    // Prepare the statement for exection.
    const char * str_stmt =
      "INSERT INTO tests (start_time, status) VALUES (NOW(), 'active')";

    // Execute the statement and get the last inserted id.
    query->execute_no_record (str_stmt);
    this->test_number_ = query->last_insert_id ();
    return true;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: %s\n"
                "*** error [archive]: failed to create new test\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: unknown exception caught; "
                "failed to create new test\n"));
  }

  return false;
}

//
// stop_current_test
//
bool CUTS_Database_Service::stop_current_test (void)
{
  ACE_WRITE_GUARD_RETURN (ACE_RW_Thread_Mutex,
                          guard,
                          this->lock_,
                          false);

  return this->stop_current_test_i ();
}

//
// stop_current_test_i
//
bool CUTS_Database_Service::stop_current_test_i (void)
{
  if (this->test_number_ == 0)
    return true;

  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    const char * str_stmt =
      "UPDATE tests SET stop_time = NOW(), status = 'inactive' "
      "WHERE (test_number = ?)";

    // Create the binding for initializing a test.
    query->prepare (str_stmt);
    query->parameter (0)->bind (&this->test_number_);

    // Execute the statement and reset the test number.
    query->execute_no_record ();
    this->test_number_ = -1;
    return true;
  }
  catch (const CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: %s\n"
                "*** error [archive]: failed to stop current test\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: caught unknown exception\n"
                "*** error [archive]: failed to stop current test\n"));
  }

  return false;
}

//
// handle_metrics
//
int CUTS_Database_Service::
handle_metrics (const CUTS_System_Metric & metrics)
{
  ACE_READ_GUARD_RETURN (ACE_RW_Thread_Mutex, guard, this->lock_, 0);

  long best_time,
       worst_time,
       total_time,
       perf_count,
       outport_index;

  char inport[MAX_VARCHAR_LENGTH],
       outport[MAX_VARCHAR_LENGTH],
       metric_type[MAX_VARCHAR_LENGTH],
       component[MAX_VARCHAR_LENGTH],
       sender[MAX_VARCHAR_LENGTH];

  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      perf_query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    CUTS_Auto_Functor_T <CUTS_DB_Query>
      perf_endpoint_query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    // Convert the <timestamp> to a known type.
    ACE_Time_Value timestamp = metrics.get_timestamp ();
    ACE_Date_Time ct (timestamp);

    ODBC_Date_Time datetime (ct);

    // Prepare the statement and bind all the parameters.
    const char * perf_stmt =
      "CALL cuts.insert_component_instance_performance (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    const char * perf_endpoint_stmt =
      "CALL cuts.insert_component_instance_performance_endpoint (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    // Get the component registry for this service.
    const CUTS_Component_Registry & registry =
      this->svc_mgr ()->testing_service ()->registry ();

    perf_query->prepare (perf_stmt);
    perf_query->parameter (0)->bind (&this->test_number_);
    perf_query->parameter (1)->bind (&datetime);
    perf_query->parameter (2)->bind (component, 0);
    perf_query->parameter (3)->bind (sender, 0);
    perf_query->parameter (4)->bind (inport, 0);
    perf_query->parameter (5)->bind (metric_type, 0);
    perf_query->parameter (6)->bind (&perf_count);
    perf_query->parameter (7)->bind (&best_time);
    perf_query->parameter (8)->bind (&total_time);
    perf_query->parameter (9)->bind (&worst_time);

    perf_endpoint_query->prepare (perf_endpoint_stmt);
    perf_endpoint_query->parameter (0)->bind (&this->test_number_);
    perf_endpoint_query->parameter (1)->bind (&datetime);
    perf_endpoint_query->parameter (2)->bind (component, 0);
    perf_endpoint_query->parameter (3)->bind (sender, 0);
    perf_endpoint_query->parameter (4)->bind (inport, 0);
    perf_endpoint_query->parameter (5)->bind (&outport_index);
    perf_endpoint_query->parameter (6)->bind (outport, 0);
    perf_endpoint_query->parameter (7)->bind (&perf_count);
    perf_endpoint_query->parameter (8)->bind (&best_time);
    perf_endpoint_query->parameter (9)->bind (&total_time);
    perf_endpoint_query->parameter (10)->bind (&worst_time);

    CUTS_Component_Metric_Map::
      CONST_ITERATOR cm_iter (metrics.component_metrics ());

    ACE_CString portname;
    const CUTS_Component_Info * myinfo = 0, * sender_info = 0;

    for (cm_iter; !cm_iter.done (); cm_iter ++)
    {
      // Determine if this component has any metrics that correspond
      // with the lastest timestamp for the system metrics. If it does
      // not then why bother going any further.
      if (timestamp != cm_iter->item ()->timestamp ())
        continue;

      if (registry.get_component_info (cm_iter->key (), &myinfo) == -1)
        continue;

      // Copy the name of the component into the buffer.
      ACE_OS::strncpy (component, myinfo->inst_.c_str (), MAX_VARCHAR_LENGTH);

      // Iterate over all the ports in the <component_metric>.
      CUTS_Port_Metric_Map::
        CONST_ITERATOR pm_iter (cm_iter->item ()->port_metrics ());

      for (pm_iter; !pm_iter.done (); pm_iter ++)
      {
        if (timestamp != pm_iter->item ()->timestamp ())
          continue;

        // Since we aren't working with any sender's at this time,
        // we can NULL this parameter.
        perf_query->parameter (3)->null ();
        perf_endpoint_query->parameter (3)->null ();

        // Copy the name of the source port, which is a event sink,
        // into its corresponding buffer.
        myinfo->type_->sinks_.find (pm_iter->key (), portname);
        ACE_OS::strncpy (inport, portname.c_str (), MAX_VARCHAR_LENGTH);

        CUTS_Port_Summary & summary = pm_iter->item ()->summary ();

        // We are going to archive the overall queuing time for the
        // current port.
        ACE_OS::strcpy (metric_type, "queue");
        best_time  = summary.queuing_time ().min_value ().msec ();
        worst_time = summary.queuing_time ().max_value ().msec ();
        total_time = summary.queuing_time ().summation ().msec ();
        perf_count = summary.queuing_time ().count ();

        perf_query->execute_no_record ();

        // We are going to archive the overall processing time for the
        // current port.
        ACE_OS::strcpy (metric_type, "process");
        best_time = summary.service_time ().min_value ().msec ();
        worst_time = summary.service_time ().max_value ().msec ();
        total_time = summary.service_time ().summation ().msec ();
        perf_count = summary.service_time ().count ();

        perf_query->execute_no_record ();

        CUTS_Endpoint_Data_Logs::
          CONST_ITERATOR ep_iter (summary.endpoints ().logs ());

        for (; !ep_iter.done (); ep_iter ++)
        {
          // Determine if this port has any metrics that corresponds
          // with the lastest timestamp for the system metrics. If it
          // does not then why bother going any further.
          //if (timestamp != ep_iter->item ()->item ()->timestamp ())
          //  continue;

          // Copy the name of the destination port, which is a event
          // source, into its corresponding buffer.
          myinfo->type_->sources_.find (ep_iter->key (), portname);
          ACE_OS::strcpy (outport, portname.c_str ());

          ACE_DEBUG ((LM_DEBUG,
                      "%T - %M - inserting metrics for output port '%s'\n",
                      outport));

          // Store the metrics in their parameters.
          CUTS_Endpoint_Data_Log::const_iterator eplog_iter (*ep_iter->item ());

          outport_index = 0;

          for ( ; !eplog_iter.done (); eplog_iter.advance ())
          {
            // Set the values of the parameter.
            best_time = eplog_iter->min_value ().time_of_completion ().msec ();
            worst_time = eplog_iter->max_value ().time_of_completion ().msec ();
            total_time = eplog_iter->summation ().time_of_completion ().msec ();
            perf_count = eplog_iter->count ();

            // Execute the query for the endpoint.
            perf_endpoint_query->execute_no_record ();

            // Increment the output index.
            ++ outport_index;
          }
        }
      }
    }

    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info [archive]: successfully archived metrics\n"));
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: %s\n"
                "*** error [archive]: aborting archiving operation\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: caught unknown exception\n"
                "*** error [archive]: aborting archiving operation\n"));
  }

  return 0;
}

//
// handle_component
//
int CUTS_Database_Service::
handle_component (const CUTS_Component_Info & info)
{
  if (info.host_info_ != 0)
  {
    try
    {
      // Regardless of the state, we still need to make sure the
      // host is registered with the database.
      this->registry_.register_host (*info.host_info_);

      VERBOSE_MESSAGE ((LM_INFO,
                        "*** info [archive]: successfully registered "
                        "%s [%s]\n",
                        info.host_info_->hostname_.c_str (),
                        info.host_info_->ipaddr_.c_str ()));
    }
    catch (const CUTS_DB_Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error (archive): %s\n"
                  "*** error (archive): failed to register host %s [%s]\n",
                  ex.message ().c_str (),
                  info.host_info_->hostname_.c_str (),
                  info.host_info_->ipaddr_.c_str ()));
    }
    catch (...)
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error (archive): unknown exception occurred\n"
                  "*** error (archive): failed to register host %s [%s]\n",
                  info.host_info_->hostname_.c_str (),
                  info.host_info_->ipaddr_.c_str ()));
    }
  }

  if (info.state_ == CUTS_Component_Info::STATE_ACTIVATE)
  {
    try
    {
      this->registry_.register_component_instance (info);

      VERBOSE_MESSAGE ((LM_INFO,
                        "*** info [archive]: successfully registered "
                        "component %s\n",
                        info.inst_.c_str ()));

      // Set component's uptime in deployment table if allowed.
      if (this->enable_deployment_)
        this->set_component_uptime (info);

      return 0;
    }
    catch (const CUTS_DB_Exception & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error [archive]: %s\n"
                  "*** error [archive]: failed to register component %s\n",
                  ex.message ().c_str (),
                  info.inst_.c_str ()));
    }
    catch (...)
    {
      ACE_ERROR ((LM_ERROR,
                  "*** error [archive]: unknown exception occured\n"
                  "*** error [archive]: failed to register component %s\n",
                  info.inst_.c_str ()));
    }
  }
  else if (info.state_ == CUTS_Component_Info::STATE_PASSIVATE)
  {
    // Set component's downtime in deployment table if allowed.
    if (this->enable_deployment_)
      this->set_component_downtime (info);

    return 0;
  }

  return -1;
}

//
// handle_activate
//
int CUTS_Database_Service::handle_activate (void)
{
  // Create a new test in the database.
  if (!this->create_new_test ())
    return -1;

  return this->set_test_uuid () ? 0 : -1;
}

//
// set_test_uuid_i
//
bool CUTS_Database_Service::set_test_uuid (void)
{
  try
  {
    // Associate that test with the UUID of the service manager.
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    // Prepare a SQL query for execution.
    const char * query_stmt =
      "UPDATE tests SET test_uuid = ? WHERE test_number = ?";

    char * uuid = const_cast <char *> (this->svc_mgr ()->get_uuid ().c_str ());

    query->prepare (query_stmt);
    query->parameter (0)->bind (uuid, 0);
    query->parameter (1)->bind (&this->test_number_);

    // Execute the query.
    query->execute_no_record ();

    return true;
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [achive]: caught unknown exception\n"));
  }

  return false;
}

//
// set_component_uptime
//
void CUTS_Database_Service::
set_component_uptime (const CUTS_Component_Info & info)
{
  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    const char * stmt =
      "CALL cuts.insert_component_instance_uptime_by_hostname (?,?,?)";

    char hostname[256];
    char instance[256];

    // Prepare the statement and it's parameters.
    query->prepare (stmt);
    query->parameter (0)->bind (&this->test_number_);
    query->parameter (1)->bind (instance, 0);
    query->parameter (2)->bind (hostname, 0);

    // Copy the strings into the parameter buffers.
    ACE_OS::strncpy (hostname,
                     info.host_info_->hostname_.c_str (),
                     sizeof (hostname));

    ACE_OS::strncpy (instance,
                     info.inst_.c_str (),
                     sizeof (instance));

    // Execute the query.
    query->execute_no_record ();

    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info [archive]: successfully set uptime "
                      "for <%s> on <%s>\n",
                      instance,
                      hostname))
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error [archive]: caught unknown exception\n"));
  }
}

//
// set_component_downtime
//
void CUTS_Database_Service::
set_component_downtime (const CUTS_Component_Info & info)
{
  try
  {
    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    const char * stmt =
      "CALL cuts.insert_component_instance_downtime_by_hostname (?,?,?)";

    char hostname[256];
    char instance[256];

    // Prepare the statement and it's parameters.
    query->prepare (stmt);
    query->parameter (0)->bind (&this->test_number_);
    query->parameter (1)->bind (instance, 0);
    query->parameter (2)->bind (hostname, 0);

    // Copy the strings into the parameter buffers.
    ACE_OS::strncpy (hostname,
                     info.host_info_->hostname_.c_str (),
                     sizeof (hostname));

    ACE_OS::strncpy (instance,
                     info.inst_.c_str (),
                     sizeof (instance));

    // Execute the query.
    query->execute_no_record ();

    VERBOSE_MESSAGE ((LM_INFO,
                      "*** info (archive): successfully set downtime "
                      "for <%s> on <%s>\n",
                      instance,
                      hostname))
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (archive): %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (archive): caught unknown exception in "
                "set_component_downtime ()\n"));
  }
}
