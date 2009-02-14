// -*- C# -*-

//=============================================================================
/**
 * @file        Database.cs
 *
 * $Id$
 *
 * @author      James H. Hill <j dot hill at vanderbilt dot edu>
 */
//=============================================================================

using System;
using System.Collections;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.Common;
using System.Reflection;
using System.Security.Cryptography;
using System.Runtime.Remoting;
using System.Text;
using CUTS.Data.UnitTesting;

namespace CUTS.BMW
{
  /**
   * @class Database
   *
   * Helper class for managing/maintaining the BMW's database.
   */
  public class Database
  {
    /**
     * Default constructor
     */
    public Database (string provider)
    {
      // Get the provider name.
      string[] items = provider.Split (",".ToCharArray ());

      // Dynamically instantiate provider factory for database.
      Assembly assembly = Assembly.LoadWithPartialName (items[1]);
      object obj = assembly.CreateInstance (items[0]);

      if (obj != null)
      {
        this.provider_ = (DbProviderFactory)obj;
        this.conn_ = this.provider_.CreateConnection ();
      }
    }

    /**
     * Default constructor
     */
    public Database (DbProviderFactory factory)
    {
      this.provider_ = factory;
      this.conn_ = this.provider_.CreateConnection ();
    }

    /**
     * Destructor
     */
    ~Database ()
    {
      if (this.conn_.State == ConnectionState.Open)
        this.conn_.Close ();
    }

    public DbProviderFactory Provider
    {
      get
      {
        return this.provider_;
      }
    }

    /**
     * Open a connection to the databse.
     *
     * @param[in]         filename          Location of the database.
     */
    public void Open ()
    {
      this.conn_.Open ();
    }

    /**
     * Get the state of the connection.
     */
    public ConnectionState State
    {
      get
      {
        return this.conn_.State;
      }
    }

    /**
     * Get/set the connection string for the connection.
     */
    public string ConnectionString
    {
      get
      {
        return this.conn_.ConnectionString;
      }

      set
      {
        this.conn_.ConnectionString = value;
      }
    }

    /**
     * Close the connection to the database.
     */
    public void Close ()
    {
      this.conn_.Close ();
    }

    /**
     * Autheticate username/password with the database.
     */
    public bool AuthenticateUser (string email, string password)
    {
      // Create a new SQL command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT password FROM users WHERE email=@email";

      // Initialize the parameters.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "@email";
      p1.DbType = DbType.String;
      p1.Value = email;

      command.Parameters.Add (p1);

      // Execute the command.
      object obj = command.ExecuteScalar ();

      if (obj == null)
        return false;

      byte [] passwd = (byte [])obj;

      // Compute the hash for the username/password.
      UTF8Encoding encoding = new UTF8Encoding ();
      SHA1CryptoServiceProvider crypt = new SHA1CryptoServiceProvider ();
      Byte[] hash = crypt.ComputeHash (encoding.GetBytes (email + password));

      // First, check the lengths of the arrays.
      if (passwd.Length != hash.Length)
        return false;

      // Next, compare each value in the array.
      for (int i = 0; i < passwd.Length; i++)
      {
        if (passwd[i] != hash[i])
          return false;
      }

      return true;
    }

    /**
     * Create a new user profile in the database.
     *
     * @param[in]         username          Username for new user
     * @param[in]         password          Password for the new user
     */
    public void CreateNewUser (NewUserProfile profile)
    {
      // Compute the hash for the username/password.
      UTF8Encoding encoding = new UTF8Encoding ();
      SHA1CryptoServiceProvider crypt = new SHA1CryptoServiceProvider ();
      Byte[] hash = crypt.ComputeHash (encoding.GetBytes (profile.EmailAddress + profile.Password));

      // Create the SQL command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText =
        "INSERT INTO users (email, password) VALUES (@email, @password)";

      // Prepare the SQL parameters.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "@email";
      p1.DbType = DbType.String;
      p1.Value = profile.EmailAddress;
      command.Parameters.Add (p1);

      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "@password";
      p2.DbType = DbType.Binary;
      p2.Value = hash;
      command.Parameters.Add (p2);

      // Execute the SQL query.
      command.ExecuteNonQuery ();
    }

    public void CreateNewUnitTest (UnitTestDefinition definition)
    {
      DbTransaction transaction = this.conn_.BeginTransaction ();

      try
      {
        // Prepare the SQL statement for inserting a new unit test.
        DbCommand command = this.conn_.CreateCommand ();
        command.CommandText = "CALL cuts.insert_unit_test (@name, @desc, @eval, @aggr)";

        DbParameter p1 = command.CreateParameter ();
        p1.ParameterName = "@name";
        p1.Value = definition.Name;
        command.Parameters.Add (p1);

        DbParameter p2 = command.CreateParameter ();
        p2.ParameterName = "@desc";
        p2.Value = definition.Description;
        command.Parameters.Add (p2);

        DbParameter p3 = command.CreateParameter ();
        p3.ParameterName = "@eval";
        p3.Value = definition.EvalFunction;
        command.Parameters.Add (p3);

        DbParameter p4 = command.CreateParameter ();
        p4.ParameterName = "@aggr";
        p4.Value = definition.AggrFunction;
        command.Parameters.Add (p4);

        // Execute the SQL statement.
        command.ExecuteNonQuery ();

        // We need to insert each of the log formats next. We can reuse
        // some of the parameters from the previous query.
        command.CommandText = "CALL cuts.insert_unit_test_log_format (@name, @lfid)";
        p2.ParameterName = "@lfid";

        foreach (LogFormat format in definition.LogFormats)
        {
          p2.Value = format.ID;
          command.ExecuteNonQuery ();
        }

        // Finally, insert the relations for the unit test.
        command.CommandText =
          "CALL cuts.insert_unit_test_relation (@name, @relid, @varindex, " +
          "@lfid_cause, @varname_cause, @lfid_effect, @varname_effect)";

        p2.ParameterName = "@relid";
        p3.ParameterName = "@varindex";
        p4.ParameterName = "@lfid_cause";

        DbParameter p5 = command.CreateParameter ();
        p5.ParameterName = "@varname_cause";
        command.Parameters.Add (p5);

        DbParameter p6 = command.CreateParameter ();
        p6.ParameterName = "@lfid_effect";
        command.Parameters.Add (p6);

        DbParameter p7 = command.CreateParameter ();
        p7.ParameterName = "@varname_effect";
        command.Parameters.Add (p7);

        int relation_id = 0;

        foreach (LogFormatRelation relation in definition.Relations)
        {
          // Set the value of the next relation index.
          p2.Value = relation_id++;

          int var_index = 0;
          foreach (VariableRelation variables in relation)
          {
            // Set the value of the next variable's index.
            p3.Value = var_index++;

            // Update the remainder of the parameters.
            p4.Value = variables.Left.ID;
            p5.Value = variables.Left.Name;
            p6.Value = variables.Right.ID;
            p7.Value = variables.Right.Name;

            // Execute the SQL statement.
            command.ExecuteNonQuery ();
          }
        }

        if (definition.Grouping.Count > 0)
        {
          // Finally, insert the grouping information into database.
          command.CommandText = "CALL cuts.insert_unit_test_grouping (@name, @index, @lfid, @varname)";

          // Update the parameter names.
          p2.ParameterName = "@index";
          p3.ParameterName = "@lfid";
          p4.ParameterName = "@varname";

          int index = 0;

          foreach (LogFormatVariable variable in definition.Grouping)
          {
            // Update the values of the variables.
            p2.Value = index++;
            p3.Value = variable.ID;
            p4.Value = variable.Name;

            // Execute the SQL command.
            command.ExecuteNonQuery ();
          }
        }

        // Commit the transaction.
        transaction.Commit ();
      }
      catch (Exception)
      {
        // Rollback the transaction and rethrow exception.
        transaction.Rollback ();
        throw;
      }
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
      DbCommand command = this.conn_.CreateCommand ();

      // Initialize the command object.
      command.CommandText = "SELECT path_id FROM critical_path WHERE path_name = ?p";

      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?p";
      p1.DbType = DbType.String;
      p1.Value = name;

      command.Parameters.Add (p1);

      // Execute the command.
      object result = command.ExecuteScalar ();

      if (result == null)
        throw new Exception ("Path name " + name + " does not exist");

      return (System.Int32)result;
    }

    /**
     * Get the critical paths as a dataset. The dataset is returned
     * in a table named 'critical_paths'.
     *
     * @param[in]     dataset     Reference to target dataset.
     */
    public void get_critical_paths (ref DataSet dataset, string tablename)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT path_id, path_name FROM execution_paths ORDER BY path_name";

      // Create an adapter w/ the following select command. Then, fill the
      // dataset using the new adapter.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (dataset, tablename);
    }

    /**
     * Get the collection times for a specific test.
     *
     * @param[in]       test        The id of the test.
     * @param[out]      dataset     Reference to target dataset.
     */
    public void get_collection_times (Int32 test, ref DataSet dataset)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_distinct_performance_collection_times (?t)";

      // Create the parameters for the statement..
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1);

      // Create an adapter w/ the following select command. Then, fill the
      // dataset using the new adapter.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_performance_by_collection_time(?test, ?time)";

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?test";
      p1.DbType = DbType.Int32;
      p1.Value = test_number;

      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?time";
      p2.DbType = DbType.DateTime;
      p2.Value = collection_time;

      // Add the parameters to the statement.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    /**
     * Get the execution time for the given path.
     *
     * @param[in]     test          Test number with data.
     * @param[in]     pathname      Name of the path.
     */
    public CUTS.Data.ExecutionTime path_execution_time (int test, string pathname)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Get the id of the path. We really need to make this a STORED
      // PROCEDURE in the database to reduce communication.

      System.Int32 path_id = this.path_id_by_name (pathname);
      CUTS.Data.ExecutionTime et = new CUTS.Data.ExecutionTime ();
      ArrayList critical_path = new ArrayList ();

      // Get all the elements in the critical path.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL select_path (?p)";

      DbParameter p1 = command.CreateParameter ();
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
      DbParameter p = command.CreateParameter ();
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
              (CUTS.Data.PathElement)critical_path[index - 1];

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
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT * FROM tests ORDER BY test_number";

      // Create a new adapter to ease the creation of the dataset.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;
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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT * FROM ipaddr_host_map ORDER BY hostname";

      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    /**
     * Get information about the testing environment from the
     * database. This returns the information in the table
     * \a testenv.
     */
    public void get_testenv (ref DataSet ds)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      StringBuilder builder = new StringBuilder ();
      builder.Append ("SELECT * FROM ipaddr_host_map ORDER BY hostname");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    /**
     *
     */
    public void update_testenv (System.Int32 hostid, System.Int32 portnum)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      StringBuilder builder = new StringBuilder ();
      builder.Append ("UPDATE ipaddr_host_map SET portnum = ?portnum ");
      builder.Append ("WHERE hostid = ?hostid");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?portnum";
      p1.DbType = DbType.Int32;
      p1.Value = portnum;

      DbParameter p2 = command.CreateParameter ();
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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Build the command.
      StringBuilder builder = new StringBuilder ();
      builder.Append ("INSERT INTO ipaddr_host_map (hostname) ");
      builder.Append ("VALUES (?hostname)");

      // Create the command object.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the query.
      DbParameter p1 = command.CreateParameter ();
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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_component_instances_all ()";

      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    /**
     * Get all the component instances from the database. It stores
     * the data in the table 'instances'.
     *
     * @param[out]        ds        Target dataset for query.
     * @param[in]         typeid    Typeid of the instances.
     */
    public void get_component_instances (System.Int32 typeid, ref DataSet ds)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      StringBuilder builder = new StringBuilder ();
      builder.Append ("SELECT * FROM component_instances WHERE typeid = ?t ");
      builder.Append ("ORDER BY component_name");

      // Create the SQL statement, or command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = typeid;

      // Insert the parameter into the statement.
      command.Parameters.Add (p1);

      // Prepare and execute the statement.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_component_types_all ()";

      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    /**
     * Delete test from the database.
     *
     * @param[in]     tests      Collection of test numbers.
     */
    public void delete_tests (System.Int32[] tests)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Verify that we have at least one test.
      if (tests.Length == 0)
        return;

      // Build the comma seperated list of test.
      ArrayList list = new ArrayList ();

      foreach (System.Int32 test in tests)
        list.Add (test.ToString ());

      // Create the command that will delete all the tests.
      String sqlstr =
        String.Format ("DELETE FROM tests WHERE test_number IN ({0})",
                       String.Join (",", (string[])list.ToArray (typeof (string))));

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = sqlstr;

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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Create the query to select the senders.
      System.Text.StringBuilder builder = new System.Text.StringBuilder ();
      builder.Append ("SELECT DISTINCT sender, component_name FROM execution_time ");
      builder.Append ("LEFT JOIN component_instances ON (sender = component_id) ");
      builder.Append ("WHERE (test_number = ?test_number AND component = ?component ");
      builder.Append ("AND collection_time = ?collection_time)");

      // Create and initialize the parameters.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?test_number";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?component";
      p2.DbType = DbType.Int32;
      p2.Value = component;

      DbParameter p3 = command.CreateParameter ();
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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Create a new command.
      DbCommand command = this.conn_.CreateCommand ();

      // Initalize the command.
      command.CommandText = "SELECT cuts.get_max_collection_time(?t)";

      // Create the parameters.
      DbParameter p1 = command.CreateParameter ();
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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      StringBuilder builder = new StringBuilder ();
      builder.Append ("SELECT UNIQUE component, component_name FROM execution_time AS et ");
      builder.Append ("LEFT JOIN component_instances AS ci ");
      builder.Append ("ON (ci.component_id = et.component) ");
      builder.Append ("WHERE test_number = ?t AND collection_time = ?ct ORDER BY component_name");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Create the parameters for the statement.
      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?ct";
      p2.DbType = DbType.DateTime;
      p2.Value = timestamp;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      // Prepare and execute the statement.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    public void get_baseline_data (ref DataSet ds)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_performance_baseline_all()";

      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;
      adapter.Fill (ds);
    }

    public void select_distinct_components_in_execution_time (Int32 test,
                                                             DateTime colltime,
                                                             ref DataSet ds)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_distinct_components_in_execution_time(?t, ?ct)";

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Create the parameters for the statement.
      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?ct";
      p2.DbType = DbType.DateTime;
      p2.Value = colltime;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      // Prepare and execute the command.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_performance_cumulative(?test)";

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?test";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Insert the parameters into the statement.
      command.Parameters.Add (p1); ;

      // Prepare and execute the statement.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Prepare the command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT cuts.get_component_name(?id)";

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Prepare the command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT cuts.component_portname(?id)";

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

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
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?c";
      p2.DbType = DbType.Int32;
      p2.Value = component;

      DbParameter p3 = command.CreateParameter ();
      p3.ParameterName = "?s";
      p3.DbType = DbType.Int32;
      p3.Value = sender;

      DbParameter p4 = command.CreateParameter ();
      p4.ParameterName = "?m";
      p4.DbType = DbType.String;
      p4.Value = metric_type;

      DbParameter p5 = command.CreateParameter ();
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
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    public long get_worst_execution_time (Int32 test, Int32 component)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Create the command and initialize the parameters.
      StringBuilder builder = new System.Text.StringBuilder ();
      builder.Append ("SELECT MAX(worst_time) FROM execution_time ");
      builder.Append ("WHERE (test_number = ?t AND component = ?c)");

      // Prepare the command for execution.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = builder.ToString ();

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      DbParameter p2 = command.CreateParameter ();
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
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Prepare the command for execution.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_baseline_metric_for_test(?t)";

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      // Insert the missing parameters.
      command.Parameters.Add (p1);

      // Prepare the execute the command.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    public void get_baseline_data (Int32 test,
                                   DateTime timestamp,
                                   ref DataSet ds)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Prepare the command for execution.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_baseline_metric_for_test_by_time(?t,?ct)";

      // Create the parameters for the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?t";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?ct";
      p2.DbType = DbType.DateTime;
      p2.Value = timestamp;

      // Insert the missing parameters.
      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    public void insert_execution_path (string name, int deadline)
    {
      // Create the SQL string for creating the critical path.
      System.Text.StringBuilder insert_sql = new System.Text.StringBuilder ();
      insert_sql.Append ("INSERT INTO execution_paths (path_name, deadline) ");
      insert_sql.Append ("VALUES (?path, ?deadline)");

      // Create the SQL command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = insert_sql.ToString ();

      // Create the parameters from the statement.
      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?path";
      p1.DbType = DbType.String;
      p1.Value = name;

      DbParameter p2 = command.CreateParameter ();
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
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT * FROM execution_paths ORDER BY path_name";

      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    public DbDataReader SelectTestSuiteManifestReader (Int32 id)
    {
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_test_suite_manifest_i (?id)";

      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?id";
      p1.DbType = DbType.Int32;
      p1.Value = id;
      command.Parameters.Add (p1);

      return command.ExecuteReader ();
    }

    public DbDataReader SelectTestSuiteManifestReader (string name)
    {
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_test_suite_manifest (?name)";

      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?name";
      p1.DbType = DbType.String;
      p1.Value = name;
      command.Parameters.Add (p1);

      return command.ExecuteReader ();
    }

    public DataTable SelectUnitTests (Int32 suite)
    {
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_unit_tests_in_test_suite_i (?id)";

      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?id";
      p1.DbType = DbType.Int32;
      p1.Value = suite;

      command.Parameters.Add (p1);

      DataSet ds = new DataSet ();
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
      return ds.Tables["Table"];
    }

    public DataTable SelectUnitTests (string suite)
    {
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_unit_tests_in_test_suite (?name)";

      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?name";
      p1.DbType = DbType.String;
      p1.Value = suite;

      command.Parameters.Add (p1);

      DataSet ds = new DataSet ();
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
      return ds.Tables["Table"];
    }

    public DataTable SelectUnitTestSuites ()
    {
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT * FROM cuts.test_suites ORDER BY name";

      DataSet ds = new DataSet ();
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
      return ds.Tables["Table"];
    }

    public DbDataReader SelectLogFormatReader ()
    {
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT lfid, lfmt FROM cuts.log_formats ORDER BY lfmt";

      return command.ExecuteReader ();
    }

    public void select_component_portnames_i (int inst, string porttype, ref DataSet ds)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "CALL cuts.select_component_portnames_i (?inst, ?type)";

      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?inst";
      p1.DbType = DbType.Int32;
      p1.Value = inst;

      DbParameter p2 = command.CreateParameter ();
      p2.ParameterName = "?type";
      p2.DbType = DbType.String;
      p2.Value = porttype;

      command.Parameters.Add (p1);
      command.Parameters.Add (p2);

      // Create an adapter and fill the dataset.
      DbDataAdapter adapter = this.provider_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      adapter.Fill (ds);
    }

    public void delete_execution_paths (int[] paths)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Create a new SQL statement/command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "DELETE FROM execution_paths WHERE path_id = ?path";

      // Create the parameter for the statment.
      DbParameter p1 = command.CreateParameter ();
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

    public int get_test_number (string uuid)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Create a new SQL statement/command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT test_number FROM tests WHERE test_uuid = ?uuid";

      DbParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?uuid";
      p1.DbType = DbType.String;
      p1.Value = uuid;

      command.Parameters.Add (p1);

      object retval = command.ExecuteScalar ();
      return retval != null ? (int)retval : -1;
    }

    public int get_unit_test_id (string name)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Create a new SQL statement/command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "SELECT utid FROM unit_tests WHERE name = ?name";

      DbParameter p1 = command.CreateParameter ();

      p1.ParameterName = "?name";
      p1.DbType = DbType.String;
      p1.Value = name;
      command.Parameters.Add (p1);

      object retval = command.ExecuteScalar ();
      return retval != null ? (int)retval : -1;
    }

    public void delete_execution_paths (string[] names)
    {
      if (this.conn_ == null)
        throw new Exception ("Connection to database is not open");

      // Create a new SQL statement/command.
      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = "DELETE FROM execution_paths WHERE path_name = ?name";

      // Create the parameter for the statment.
      DbParameter p1 = command.CreateParameter ();
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

    /**
     * Connection to the database.
     */
    private DbProviderFactory provider_;

    /**
     * Connection to the database.
     */
    private DbConnection conn_;
  }
}
