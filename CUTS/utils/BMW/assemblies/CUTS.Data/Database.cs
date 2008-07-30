// -*- C# -*-

//=============================================================================
/**
 * @file      Database.cs
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.Data;
using System.Text;

namespace CUTS.Data
{
  /**
   * @class Database
   *
   * Implementation of common procedures for interacting with the CUTS
   * database.
   */
  public class Database
  {
    /**
     * Connection used by this database object.
     */
    private IDbConnection conn_;

    /**
     * Factory for creating data adapter objects.
     */
    private IDbDataAdapterFactory adapter_factory_;

    /**
     * Initializing constructor.
     *
     * @param[in]       conn        Open connection to a database
     * @param[in]       adapter     Factory for creating data adapters
     */
    public Database (IDbConnection conn,
                     IDbDataAdapterFactory adapter_factory)
    {
      this.conn_ = conn;
      this.adapter_factory_ = adapter_factory;
    }

    /**
     * Get the connection associated with this database object.
     */
    public IDbConnection Connection
    {
      get { return this.conn_; }
    }

    /**
     * Get the id of a path by name.
     *
     * @param[in]     pathname      Name of the path.
     * @return        The id of the path.
     */
    public System.Int32 path_id_by_name (string name)
    {
      // Create a new command object.
      IDbCommand command = this.conn_.CreateCommand ();

      // Initialize the command object.
      command.CommandText = "SELECT path_id FROM critical_path WHERE path_name = ?p";

      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?p";
      p1.DbType = DbType.String;
      p1.Value = name;

      command.Parameters.Add (p1);

      // Execute the command.
      command.Prepare ();
      object result = command.ExecuteScalar ();

      if (result == null)
        throw new ApplicationException ("The specified path [" + name + "] does not exist");

      return (System.Int32)result;
    }

    /**
     * Get the critical paths as a dataset. The dataset is returned
     * in a table named 'critical_paths'.
     *
     * @param[in]     dataset     Reference to target dataset.
     */
    public void get_critical_paths (ref DataSet dataset)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT path_id, path_name FROM execution_paths ORDER BY path_name";

      // Create an adapter w/ the following select command. Then, fill the
      // dataset using the new adapter.
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (dataset);
    }

    /**
     * Get the collection times for a specific test.
     *
     * @param[in]       test        The id of the test.
     * @param[out]      dataset     Reference to target dataset.
     */
    public void get_collection_times (Int32 test,
                                      ref DataSet dataset)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_distinct_performance_collection_times (?t)";

      // Create the parameters for the statement..
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1);

      // Create an adapter w/ the following select command. Then, fill the
      // dataset using the new adapter.
      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (dataset);
    }

    /**
     * Get the execution times for a particular collection time of a test.
     *
     * @param[in]         test_number         Test number of interet
     * @param[in]         collection_time     Collection time of interest
     * @param[in]         ds                  Target dataset.
     */
    public void get_execution_times (Int32 test_number,
                                     DateTime collection_time,
                                     ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_performance_by_collection_time(?test, ?time)";

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?test";
      p1.DbType = DbType.Int32;
      p1.Value = test_number;

      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?time";
      p2.DbType = DbType.DateTime;
      p2.Value = collection_time;

      // Add the parameters to the statement.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     * Get the execution time for the given path.
     *
     * @param[in]     test          Test number with data.
     * @param[in]     pathname      Name of the path.
     */
    public ExecutionTime path_execution_time (int test, string pathname)
    {
      // Get the id of the path. We really need to make this a STORED
      // PROCEDURE in the database to reduce communication.

      System.Int32 path_id = this.path_id_by_name (pathname);
      ExecutionTime et = new ExecutionTime ();
      ArrayList critical_path = new ArrayList ();

      // Get all the elements in the critical path.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL select_path (?p)";

      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?p";
      p1.DbType = DbType.Int32;
      p1.Value = path_id;

      command.Parameters.Add (path_id);

      // Execute the command.
      command.Prepare ();
      IDataReader reader = command.ExecuteReader ();

      // Extract all the elements in the collection then close
      // the reader.
      while (reader.Read ())
      {
        CUTS.Data.PathElement element =
          new CUTS.Data.PathElement (reader.GetInt32 (1), reader.GetString (2), reader.GetString (3));

        critical_path.Add (element);
      }

      reader.Close ();

      // Get the path information from the database.
      command.CommandText = "CALL select_path_execution_times (?t, ?p)";

      // Create the parameters for the statement.
      IDbDataParameter p = command.CreateParameter ();
      p.ParameterName = "?t";
      p.DbType = DbType.Int32;
      p.Value = test;

      // Insert the parameters into the statement.
      command.Parameters.Add (p);
      command.Parameters.Add (p1);

      command.Prepare ();
      reader = command.ExecuteReader ();

      // Bypass all the empty metrics in the collection and store
      // the first DateTime value as the <collection_time>.
      while (reader.Read () && reader.GetValue (0) == DBNull.Value) ;
      long best_time = 0, average_time = 0, worst_time = 0;
      bool done = false;
      DateTime collection_time;

      do
      {
        bool create_point = false;

        // Get the collection_date, component, src and dst port and create
        // a path element out of it.
        collection_time = reader.GetDateTime (0);

        CUTS.Data.PathElement element =
          new CUTS.Data.PathElement (reader.GetInt32 (1), reader.GetString (3), reader.GetString (4));

        // Locate the following metrics in the collection.
        try
        {
          bool valid = true;
          int index = critical_path.IndexOf (element);

          if (index != 0)
          {
            // Check if the sender of this metric is indeed the previous
            // instance in the critical path for this element.
            CUTS.Data.PathElement prev_element =
              (CUTS.Data.PathElement)critical_path [index - 1];

            if (prev_element.component_ != reader.GetInt32 (2))
            {
              valid = false;
            }
          }

          // If this is a valid metric then we need to add it's information
          // to the current execution times for this collection time.
          if (valid)
          {
            best_time += reader.GetInt32 (7);
            average_time += reader.GetInt32 (8);
            worst_time += reader.GetInt32 (9);
          }
        }
        catch (Exception)
        {

        }

        // Determine if this is the last record in the listing. If it
        // is not then we need to see if the next record is part of this
        // collection period. If this is the last record then we have
        // to create a new point regardless.
        if (reader.Read ())
        {
          if (collection_time != reader.GetDateTime (0))
          {
            create_point = true;
          }
        }
        else
        {
          create_point = true;
          done = true;
        }

        // Create a new collection point in the <et> object.
        if (create_point)
        {
          if (et.samples != 0)
          {
            if (best_time < et.absmin)
            {
              et.absmin = best_time;
            }
            if (worst_time > et.absmax)
            {
              et.absmax = worst_time;
            }
          }
          else
          {
            et.absmin = best_time;
            et.absmax = worst_time;
          }

          et.avgmin += best_time;
          et.avgavg += average_time;
          et.avgmax += worst_time;
          ++et.samples;

          // Reset the time values.
          if (!done)
          {
            best_time = average_time = worst_time = 0;
          }
        }
      } while (!done);

      // Close the reader.
      reader.Close ();

      // Populate the <et> data structure with the appropriate
      // information for the client based on the parsed results.
      if (et.samples != 0)
      {
        et.recentmin = best_time;
        et.recentmax = worst_time;
        et.recentavg = average_time;

        et.avgmin /= et.samples;
        et.avgavg /= et.samples;
        et.avgmax /= et.samples;

        et.lastsample = collection_time;
      }

      return et;
    }

    /**
     * Get all the test from the database. This returns the test in
     * the \a test table of the \ds argument.
     *
     * @param[out]        ds      The target database.
     */
    public void get_all_test (ref DataSet ds)
    {
      // Create the command for the query.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT * FROM tests ORDER BY test_number";

      // Create a new adapter to ease the creation of the dataset.
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     * Get all the known hosts from the database. This returns the
     * records in the \hosts table.
     *
     * @param[out]    ds        The target dataset.
     */
    public void get_all_hosts (ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT * FROM ipaddr_host_map ORDER BY hostname";

      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     * Get information about the testing environment from the
     * database. This returns the information in the table
     * \a testenv.
     */
    public void get_testenv (ref DataSet ds)
    {
      StringBuilder builder = new StringBuilder ();
      builder.Append ("SELECT * FROM ipaddr_host_map ORDER BY hostname");

      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     *
     */
    public void update_testenv (System.Int32 hostid, System.Int32 portnum)
    {
      StringBuilder builder = new StringBuilder ();
      builder.Append ("UPDATE ipaddr_host_map SET portnum = ?portnum ");
      builder.Append ("WHERE hostid = ?hostid");

      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?portnum";
      p1.DbType = DbType.Int32;
      p1.Value = portnum;

      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?hostid";
      p2.DbType = DbType.Int32;
      p2.Value = hostid;

      // Insert the parameters into the command.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      command.Prepare ();
      command.ExecuteNonQuery ();
    }

    /**
     * Register the given host. The hostname can either be a human
     * readable name, or an IP address.
     *
     * @param[in]       host        Target host to register.
     */
    public void register_host (String hostname)
    {
      // Build the command.
      StringBuilder builder = new StringBuilder ();
      builder.Append ("INSERT INTO ipaddr_host_map (hostname) ");
      builder.Append ("VALUES (?hostname)");

      // Create the command object.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the query.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?hostname";
      p1.DbType = DbType.String;
      p1.Value = hostname;

      // Insert the parameters into the database.
      command.Parameters.Add (p1);

      // Excute the command.
      command.Prepare ();
      command.ExecuteNonQuery ();
    }

    /**
     * Get all the component instances from the database. It stores
     * the data in the table 'instances'.
     *
     * @param[out]        ds        Target dataset for query.
     */
    public void get_component_instances (ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_component_instances_all ()";

      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     * Get all the component instances from the database. It stores
     * the data in the table 'instances'.
     *
     * @param[out]        ds        Target dataset for query.
     * @param[in]         typeid    Typeid of the instances.
     */
    public void get_component_instances (System.Int32 typeid,
                                         ref DataSet ds)
    {
      StringBuilder builder = new StringBuilder ();
      builder.Append ("SELECT * FROM component_instances WHERE typeid = ?t ");
      builder.Append ("ORDER BY component_name");

      // Create the SQL statement, or command.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = typeid;

      // Insert the parameter into the statement.
      command.Parameters.Add (p1);

      // Prepare and execute the statement.
      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     * Get all the component instances from the database. It stores
     * the data in the table 'instances'.
     *
     * @param[out]        ds        Target dataset for query.
     */
    public void get_component_types (ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_component_types_all ()";

      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     * Delete test from the database.
     *
     * @param[in]     tests      Collection of test numbers.
     */
    public void delete_tests (System.Int32 [] tests)
    {
      // Verify that we have at least one test.
      if (tests.Length == 0)
        return;

      // Build the comma seperated list of test.
      StringBuilder builder = new StringBuilder (tests [0].ToString ());

      for (int i = 1; i < tests.Length; i++)
      {
        builder.Append (", ");
        builder.Append (tests [i].ToString ());
      }

      // Create the command that will delete all the tests.
      String cmdstr =
        String.Format ("DELETE FROM tests WHERE test_number IN ({0})",
                       builder.ToString ());

      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = cmdstr;

      // Execute the command.
      command.ExecuteNonQuery ();
    }

    /**
     * Get the senders for a component.
     *
     * @param[in]       component       Id of component
     * @param[in]       test            Test id for the component
     * @param[in]       time            Timestamp of interest
     */
    public IDataReader get_senders (System.Int32 component,
                                    System.Int32 test,
                                    DateTime time)
    {
      // Create the query to select the senders.
      System.Text.StringBuilder builder = new System.Text.StringBuilder ();
      builder.Append ("SELECT DISTINCT sender, component_name FROM execution_time ");
      builder.Append ("LEFT JOIN component_instances ON (sender = component_id) ");
      builder.Append ("WHERE (test_number = ?test_number AND component = ?component ");
      builder.Append ("AND collection_time = ?collection_time)");

      // Create and initialize the parameters.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?test_number";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?component";
      p2.DbType = DbType.Int32;
      p2.Value = component;

      IDbDataParameter p3 = command.CreateParameter ();
      p3.ParameterName = "?collection_time";
      p3.DbType = DbType.DateTime;
      p3.Value = time;

      // Set the parameters for the SQL statement.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);
      command.Parameters.Add (p3);

      // Execute the command and return the reader.
      command.Prepare ();
      return command.ExecuteReader ();
    }

    public System.DateTime get_latest_collection_time (System.Int32 test)
    {
      // Create a new command.
      IDbCommand command = this.conn_.CreateCommand ();

      // Initalize the command.
      command.CommandText = "SELECT cuts.get_max_collection_time(?t)";

      // Create the parameters.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Insert the parameters.
      command.Parameters.Add (p1);

      // Execute the command.
      command.Prepare ();
      object value = command.ExecuteScalar ();
      return value != System.DBNull.Value ? (System.DateTime)value : System.DateTime.Now;
    }

    public void get_component_instances (System.Int32 test,
                                         System.DateTime timestamp,
                                         ref DataSet ds)
    {
      StringBuilder builder = new StringBuilder ();
      builder.Append ("SELECT UNIQUE component, component_name FROM execution_time AS et ");
      builder.Append ("LEFT JOIN component_instances AS ci ");
      builder.Append ("ON (ci.component_id = et.component) ");
      builder.Append ("WHERE test_number = ?t AND collection_time = ?ct ORDER BY component_name");

      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Create the parameters for the statement.
      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?ct";
      p2.DbType = DbType.DateTime;
      p2.Value = timestamp;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      // Prepare and execute the statement.
      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    public void get_baseline_data (ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_performance_baseline_all()";

      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    public void select_distinct_components_in_execution_time (Int32 test,
                                                             DateTime colltime,
                                                             ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_distinct_components_in_execution_time(?t, ?ct)";

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Create the parameters for the statement.
      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?ct";
      p2.DbType = DbType.DateTime;
      p2.Value = colltime;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      // Prepare and execute the command.
      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     * Select the cumulative execution time for the specified test.
     *
     * @param[in]         test          Test of interest.
     * @param[in]         ds            Target storage datast.
     */
    public void select_execution_time_cumulative (Int32 test, ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_performance_cumulative(?test)";

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?test";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1); ;

      // Prepare and execute the statement.
      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    /**
     * Get the name of a component given its id.
     *
     * @param[in]         id            Id of the component
     * @return            Name of the component
     */
    public string get_component_name (Int32 id)
    {
      // Prepare the command.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT cuts.get_component_name(?id)";

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?id";
      p1.DbType = DbType.Int32;
      p1.Value = id;

      // Insert the missing parameters.
      command.Parameters.Add (p1);

      command.Prepare ();
      return (string)command.ExecuteScalar ();
    }

    /**
     * Get the name of a port given its id.
     *
     * @param[in]         id            Id of the port
     * @return            Name of the port.
     */
    public string get_component_portname (Int32 id)
    {
      // Prepare the command.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT cuts.component_portname(?id)";

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?id";
      p1.DbType = DbType.Int32;
      p1.Value = id;

      // Insert the missing parameters.
      command.Parameters.Add (p1); ;

      command.Prepare ();
      return (string)command.ExecuteScalar ();
    }

    /**
     *
     **/
    public void get_component_execution_times (Int32 test,
                                              Int32 component,
                                              Int32 sender,
                                              string metric_type,
                                              Int32 src,
                                              Int32 dst,
                                              ref DataSet ds)
    {
      // Create the command to get the desired execution times
      StringBuilder builder = new StringBuilder ();
      builder.Append ("SELECT collection_time, best_time, (total_time / metric_count) AS average_time, worst_time ");
      builder.Append ("FROM execution_time WHERE (test_number = ?t AND component = ?c ");
      builder.Append ("AND sender =?s AND metric_type = ?m AND src = ?src");

      if (dst != -1)
        builder.Append (" AND dst=?dst");
      else
        builder.Append (" AND dst IS NULL");

      builder.Append (") ORDER BY collection_time");

      // Create the SQL command.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?c";
      p2.DbType = DbType.Int32;
      p2.Value = component;

      IDbDataParameter p3 = command.CreateParameter ();
      p3.ParameterName = "?s";
      p3.DbType = DbType.Int32;
      p3.Value = sender;

      IDbDataParameter p4 = command.CreateParameter ();
      p4.ParameterName = "?m";
      p4.DbType = DbType.String;
      p4.Value = metric_type;

      IDbDataParameter p5 = command.CreateParameter ();
      p5.ParameterName = "?src";
      p5.DbType = DbType.Int32;
      p5.Value = src;

      // Insert the missing parameters.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);
      command.Parameters.Add (p3);
      command.Parameters.Add (p4);
      command.Parameters.Add (p5);

      if (dst != -1)
      {
        IDataParameter p6 = command.CreateParameter ();
        p6.ParameterName = "?dst";
        p6.DbType = DbType.Int32;
        p6.Value = dst;

        command.Parameters.Add (p6);
      }

      // Prepare and execute the SQL command.
      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    public long get_worst_execution_time (Int32 test, Int32 component)
    {
      // Create the command and initialize the parameters.
      StringBuilder builder = new System.Text.StringBuilder ();
      builder.Append ("SELECT MAX(worst_time) FROM execution_time ");
      builder.Append ("WHERE (test_number = ?t AND component = ?c)");

      // Prepare the command for execution.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?c";
      p2.DbType = DbType.Int32;
      p2.Value = component;

      // Insert the missing parameters.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      // Execute the parameters.
      command.Prepare ();
      return (System.Int32)command.ExecuteScalar ();
    }

    public void get_baseline_data (Int32 test, ref DataSet ds)
    {
      // Prepare the command for execution.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_baseline_metric_for_test(?t)";

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Insert the missing parameters.
      command.Parameters.Add (p1);

      // Prepare the execute the command.
      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    public void get_baseline_data (Int32 test,
                                   DateTime timestamp,
                                   ref DataSet ds)
    {
      // Prepare the command for execution.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_baseline_metric_for_test_by_time(?t,?ct)";

      // Create the parameters for the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?ct";
      p2.DbType = DbType.DateTime;
      p2.Value = timestamp;

      // Insert the missing parameters.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    public void insert_execution_path (string name, int deadline)
    {
      // Create the SQL string for creating the critical path.
      System.Text.StringBuilder insert_sql = new System.Text.StringBuilder ();
      insert_sql.Append ("INSERT INTO execution_paths (path_name, deadline) ");
      insert_sql.Append ("VALUES (?path, ?deadline)");

      // Create the SQL command.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = insert_sql.ToString ();

      // Create the parameters from the statement.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?path";
      p1.DbType = DbType.String;
      p1.Value = name;

      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?deadline";
      p2.DbType = DbType.Int32;
      p2.Value = deadline;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      // Execute the command to create the critical path.
      command.Prepare ();
      command.ExecuteNonQuery ();
    }

    public void select_execution_paths (ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT * FROM execution_paths ORDER BY path_name";

      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    public void select_component_portnames_i (int inst, string porttype, ref DataSet ds)
    {
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_component_portnames_i (?inst, ?type)";

      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?inst";
      p1.DbType = DbType.Int32;
      p1.Value = inst;

      IDbDataParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?type";
      p2.DbType = DbType.String;
      p2.Value = porttype;

      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      // Create an adapter and fill the dataset.
      command.Prepare ();
      IDbDataAdapter adapter = this.adapter_factory_.CreateDbDataAdapter (command);
      adapter.Fill (ds);
    }

    public void delete_execution_paths (int [] paths)
    {
      // Create a new SQL statement/command.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "DELETE FROM execution_paths WHERE path_id = ?path";

      // Create the parameter for the statment.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?path";
      p1.DbType = DbType.Int32;

      command.Parameters.Add (p1);

      foreach (int id in paths)
      {
        p1.Value = id;

        // Prepare and execute the statement.
        command.Prepare ();
        command.ExecuteNonQuery ();
      }
    }

    public void delete_execution_paths (string [] names)
    {
      // Create a new SQL statement/command.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "DELETE FROM execution_paths WHERE path_name = ?name";

      // Create the parameter for the statment.
      IDbDataParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?name";
      p1.DbType = DbType.String;

      command.Parameters.Add (p1);

      foreach (string name in names)
      {
        p1.Value = name;

        // Prepare and execute the statement.
        command.Prepare ();
        command.ExecuteNonQuery ();
      }
    }
}
}
