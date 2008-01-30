// $Id$

#include "DB_Registry.h"

#if !defined (__CUTS_INLINE__)
#include "DB_Registry.inl"
#endif

#include "cuts/Auto_Functor_T.h"
#include "cuts/utils/DB_Connection.h"
#include "cuts/utils/DB_Exception.h"
#include "cuts/utils/DB_Query.h"
#include "cuts/utils/DB_Record.h"
#include "cuts/utils/DB_Parameter.h"
#include "ace/Log_Msg.h"
#include <sstream>

#define MAX_VARCHAR_LENGTH 256

//
// CUTS_DB_Registry
//
CUTS_DB_Registry::CUTS_DB_Registry (void)
{

}

//
// ~CUTS_DB_Registry
//
CUTS_DB_Registry::~CUTS_DB_Registry (void)
{

}

//
// register_host
//
void CUTS_DB_Registry::
register_host (const CUTS_Host_Table_Entry & host)
{
  CUTS_Auto_Functor_T <CUTS_DB_Query>
    query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

  const char * str_stmt = "CALL cuts.insert_ipaddr_hostname (?,?)";

  // Prepare the statement for execution.
  query->prepare (str_stmt);
  query->parameter (0)->bind (const_cast <char *> (host.ipaddr_.c_str ()), 0);
  query->parameter (1)->bind (const_cast <char *> (host.hostname_.c_str ()), 0);

  // Execute the statement.
  query->execute_no_record ();
}

//
// get_hostid_by_ipaddr
//
bool CUTS_DB_Registry::
get_hostid_by_ipaddr (const char * ipaddr, long * hostid)
{
  CUTS_Auto_Functor_T <CUTS_DB_Query>
    query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

  try
  {
    // Prepare the statement to select the component_id of the component
    // with the specified name.
    const char * str_stmt =
      "SELECT hostid FROM ipaddr_host_map WHERE ipaddr = ?";

    query->prepare (str_stmt);
    query->parameter (0)->bind (const_cast <char *> (ipaddr), 0);

    // Get the results from executing the query. If the query returns
    // nothing then this will throw an exception.
    CUTS_DB_Record * record = query->execute ();

    if (record->count () == 0)
      return false;

    // We need to store the host id if the caller requests.
    if (hostid != 0)
    {
      record->fetch ();
      record->get_data (1, *hostid);
    }

    return true;
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_hostid_by_ipaddr): %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_hostid_by_ipaddr): caught unknown exception\n"));
  }
  return false;
}

//
// get_hostid_by_hostname
//
bool CUTS_DB_Registry::
get_hostid_by_hostname (const char * hostname, long * hostid)
{
  CUTS_Auto_Functor_T <CUTS_DB_Query>
    query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

  try
  {
    // Prepare the statement to select the component_id of the component
    // with the specified name.
    const char * str_stmt =
      "SELECT hostid FROM ipaddr_host_map WHERE hostname = ?";

    query->prepare (str_stmt);
    query->parameter (0)->bind (const_cast <char *> (hostname), 0);

    // Get the results from executing the query. If the query returns
    // nothing then this will throw an exception.
    CUTS_DB_Record * record = query->execute ();

    if (record->count () == 0)
      return false;

    // We need to store the host id if the caller requests.
    if (hostid != 0)
    {
      record->fetch ();
      record->get_data (1, *hostid);
    }

    return true;
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_hostid_by_hostname): %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_hostid_by_hostname): caught unknown exception\n"));
  }
  return false;
}

//
// get_instance_id
//
bool CUTS_DB_Registry::
get_instance_id (const char * inst, long * instid)
{
  CUTS_Auto_Functor_T <CUTS_DB_Query>
    query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

  try
  {
    // Prepare the statement to select the component_id of the component
    // with the specified name.
    const char * query_stmt =
      "SELECT component_id FROM component_instances WHERE component_name = ?";

    query->prepare (query_stmt);
    query->parameter (0)->bind (const_cast <char *> (inst), 0);

    // Execute the statement and get the returned id.
    CUTS_DB_Record * record = query->execute ();
    size_t count = record->count ();

    if (count > 0 && instid != 0)
    {
      record->fetch ();
      record->get_data (1, *instid);
    }

    return count > 0;
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_instance_id): %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_instance_id): caught unknown exception\n"));
  }

  return false;
}

//
// get_component_typeid
//
bool CUTS_DB_Registry::
get_component_typeid (const char * type, long & type_id)
{
  CUTS_Auto_Functor_T <CUTS_DB_Query>
    query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

  try
  {
    // Prepare a SQL query for execution.
    const char * query_stmt = "SELECT cuts.get_component_typename_id (?)";

    query->prepare (query_stmt);
    query->parameter (0)->bind (const_cast <char *> (type), 0);

    // Execute the query.
    CUTS_DB_Record * record = query->execute ();

    if (record->count () > 0)
    {
      record->fetch ();
      record->get_data (1, type_id);
      return true;
    }
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_component_typeid): %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_component_typeid): caught unknown exception\n"));
  }

  return false;
}

//
// get_port_id
//
bool CUTS_DB_Registry::
get_port_id (const char * porttype, const char * portname, long & portid)
{
  CUTS_Auto_Functor_T <CUTS_DB_Query>
    query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

  try
  {
    // Prepare a SQL query for execution.
    const char * query_stmt = "SELECT cuts.get_port_id (?, ?)";

    query->prepare (query_stmt);
    query->parameter (0)->bind (const_cast <char *> (porttype), 0);
    query->parameter (1)->bind (const_cast <char *> (portname), 0);

    // Execute the query.
    CUTS_DB_Record * record = query->execute ();

    if (record->count () > 0)
    {
      record->fetch ();
      record->get_data (1, portid);
      return true;
    }
  }
  catch (CUTS_DB_Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_component_typeid): %s\n",
                ex.message ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                "*** error (get_component_typeid): caught unknown exception\n"));
  }

  return false;
}

//
// register_instance
//
void CUTS_DB_Registry::
register_component_instance (const CUTS_Component_Info & info)
{
  // Register the type information with the database.
  if (info.type_ != 0)
  {
    this->register_component_type (*info.type_);

    CUTS_Auto_Functor_T <CUTS_DB_Query>
      query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

    // Prepare a SQL query for execution.
    const char * query_stmt =
      "CALL cuts.insert_component_instance (?, ?)";

    query->prepare (query_stmt);
    query->parameter (0)->bind (const_cast <char *> (info.inst_.c_str ()), 0);
    query->parameter (1)->bind (const_cast <char *> (info.type_->name_.c_str ()), 0);

    // Execute the record. We are not expecting any results.
    query->execute_no_record ();
  }
}

//
// register_instance
//
void CUTS_DB_Registry::
register_component_type (const CUTS_Component_Type & type)
{
  CUTS_Auto_Functor_T <CUTS_DB_Query>
    query (this->conn_->create_query (), &CUTS_DB_Query::destroy);

  // Prepare a SQL query for execution.
  const char * query_stmt =
    "CALL cuts.insert_component_typeinfo (?, ?, ?)";

  query->prepare (query_stmt);
  query->parameter (0)->bind (const_cast <char *> (type.name_.c_str ()), 0);

  this->insert_component_ports (*query, "sink", type.sinks_);
  this->insert_component_ports (*query, "source", type.sources_);
}

//
// insert_component_ports
//
void CUTS_DB_Registry::
insert_component_ports (CUTS_DB_Query & query,
                        const char * porttype,
                        const CUTS_Port_Description_Map & ports)
{
  // Initialize the port type parameter.
  query.parameter (1)->bind (const_cast <char *> (porttype), 0);

  // Insert all the ports into the database.
  for (CUTS_Port_Description_Map::CONST_ITERATOR iter (ports);
       !iter.done ();
       iter ++)
  {
    query.parameter (2)->bind (const_cast <char *> (iter->item ().c_str ()), 0);
    query.execute_no_record ();
  }
}
