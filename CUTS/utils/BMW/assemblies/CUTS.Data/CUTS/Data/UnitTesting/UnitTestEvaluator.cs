// -*- C# -**

using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Text.RegularExpressions;

using CUTS.Data;
using CUTS.Graph;

namespace CUTS.Data.UnitTesting
{
  /**
   * @class UnitTestEvaluator
   *
   * Data abstraction for evaluating a unit test.
   */
  public class UnitTestEvaluator
  {
    /**
     * Initializing constructor.
     */
    public UnitTestEvaluator (DbProviderFactory factory)
      : this (factory, String.Empty)
    {

    }

    public UnitTestEvaluator (DbProviderFactory factory, string temppath)
    {
      this.factory_ = factory;
      this.location_ = temppath;

      this.conn_ = this.factory_.CreateConnection ();
    }

    /**
     * Destructor.
     */
    ~UnitTestEvaluator ()
    {
      this.Close ();
    }

    public string TempPath
    {
      get
      {
        return this.location_;
      }

      set
      {
        this.location_ = value;
      }
    }

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
     * Open the connection to the database for the evaluator.
     *
     * @param[in]       connstr       Connection string.
     */
    public void Open ()
    {
      // Close the current database connection.
      this.Close ();

      // Open a new connection to the database.
      this.conn_.Open ();
    }

    /**
     * Close the evaluator.
     */
    public void Close ()
    {
      if (this.conn_.State == ConnectionState.Open)
        this.conn_.Close ();
    }

    /**
     * Get the data trend for the unit test.
     */
    public UnitTestDataTrend GetDataTrend (int test, int utid)
    {
      // First, get the SQL string for selecting the data trend.
      List<string> groups;
      string sqlstr = this.create_evaluation_query (utid, true, out groups);

      // Create a new variable table for this unit test.
      UnitTestVariableTable vtable = new UnitTestVariableTable (this.location_);

      // Open the variable table.
      vtable.Open (test, utid);
      DbTransaction transaction = vtable.BeginTransaction ();

      try
      {
        // Evalute the unit test.
        DataTable results = new DataTable ();
        vtable.Evaluate (sqlstr, ref results);

        // Commit the transaction.
        transaction.Commit ();

        UnitTestDataTrend trend = new UnitTestDataTrend ();

        if (groups.Count == 0)
        {
          // Write the data set for the single group.
          foreach (DataRow row in results.Rows)
            trend.Data.Add (row["result"]);
        }
        else
        {
          string current_group = String.Empty;
          DataTrend group_data = new DataTrend ();

          foreach (DataRow grprow in results.Rows)
          {
            // First, construct the name of the group for this row in
            // the data table.
            List <string> name_list = new List <string> ();

            foreach (string name in groups)
              name_list.Add ((string)grprow[name]);

            string grp_name = String.Join (".", name_list.ToArray ());

            if (grp_name != current_group)
            {
              if (current_group != String.Empty)
              {
                // Insert the group data into the collection.
                trend.GroupData.Add (current_group, group_data);

                // End the current group's data by creating.
                group_data = new DataTrend ();
              }

              // Save the new group name.
              current_group = grp_name;
            }

            // Insert the value into the group's result.
            group_data.Add (grprow["result"]);
          }

          if (group_data.Count > 0)
            trend.GroupData.Add (current_group, group_data);
        }

        return trend;
      }
      catch (Exception)
      {
        transaction.Rollback ();
        throw;
      }
      finally
      {
        vtable.Close ();
      }
   }

    /**
     * Re-evaluate a unit test.
     */
    public UnitTestResult Reevaluate (int test, int utid, bool aggr)
    {
      // Create a new variable table for this unit test.
      UnitTestVariableTable vtable = new UnitTestVariableTable (this.location_);

      try
      {
        // Open the variable table.
        vtable.Open (test, utid);
        DbTransaction transaction = vtable.BeginTransaction ();

        try
        {
          // Get the variable table for this unit test. This table is then sent
          // back to the database for processing, i.e., to execute the user-defined
          // expression to evaluate the unit test.
          this.create_variable_table (ref vtable);

          // Commit the transaction.
          transaction.Commit ();
        }
        catch (Exception)
        {
          transaction.Rollback ();
          throw;
        }

        return this.evaluate_i (vtable, aggr);
      }
      finally
      {
        vtable.Close ();
      }
    }

    /**
     * Evaluate the unit test of a specific test. When evaluating the unit
     * test, the user has the option of either aggregating the results, or
     * getting back the raw data for the result.
     *
     * @param[in]       test       Test number of interest
     * @param[in]       utid       Unit test of interest
     * @param[in]       aggr       Apply aggregation function
     * @param[out]      eval       Evaluation function
     */
    public UnitTestResult Evaluate (int test, int utid, bool aggr)
    {
      // Create a new variable table for this unit test.
      UnitTestVariableTable vtable =
        new UnitTestVariableTable (this.location_);

      try
      {
        // Open the variable table.
        vtable.Open (test, utid);
        DataTable table = vtable.Data;

        // Begin a new transaction.
        return this.evaluate_i (vtable, aggr);
      }
      finally
      {
        vtable.Close ();
      }
    }

    /**
     * Helper method to create the variable table for a unit test. This
     * will create the columns for the variable table, as well as fill in
     * all the rows - while maintaining causility in the data.
     *
     * @param[in]       test          Test of interest
     * @param[in]       utid          Unit test to evaluate
     * @param[out]      vtable        Target variable table
     */
    private void create_variable_table (ref UnitTestVariableTable vtable)
    {
      if (this.conn_ == null || this.conn_.State != ConnectionState.Open)
        throw new Exception ("Connection to database is not open");

      // Initialize the database objects.
      DataSet ds = new DataSet ();
      DbCommand command = this.conn_.CreateCommand ();
      DbDataAdapter adapter = this.factory_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      // Create a parameter for the command.
      DbParameter p1 = command.CreateParameter ();

      // Initialize the parameter.
      p1.ParameterName = "?utid";
      p1.DbType = DbType.Int32;
      p1.Value = vtable.UnitTestNumber;

      command.Parameters.Add (p1);

      // Get the variabes for this unit test.
      command.CommandText = "CALL cuts.select_unit_test_variables (?utid)";
      adapter.Fill (ds, "variables");

      // Get the relations for this unit test.
      command.CommandText = "CALL cuts.select_unit_test_relations_as_set (?utid)";
      adapter.Fill (ds, "relations");

      // Get the cuasality derived from the relations.
      command.CommandText = "CALL cuts.select_unit_test_causal_relations (?utid)";
      adapter.Fill (ds, "causality");

      // Get all the log formats for this unit test.
      command.CommandText = "CALL cuts.select_unit_test_log_formats (?utid)";
      adapter.Fill (ds, "logformats");

      // First, create a graph using the log formats and their
      // relations. The log formats will be the nodes, and the
      // relations will be the edges.
      CUTS.Graph.DirectedGraph log_graph = new CUTS.Graph.DirectedGraph ();

      foreach (DataRow row in ds.Tables["logformats"].Rows)
      {
        // Create a node for the log format.
        int lfid = (int)row["lfid"];
        string name = String.Format ("LF{0}", lfid);
        CUTS.Graph.Node node = new CUTS.Graph.Node (name);

        // Set the properties of the node.
        node.property ("lfid", lfid);
        node.property ("regex.csharp", row["csharp_regex"]);
        node.property ("regex.mysql", row["icase_regex"]);

        // Insert the node into the graph.
        log_graph.insert_node (node);
      }

      ArrayList relation_set = new ArrayList ();

      foreach (DataRow row in ds.Tables["causality"].Rows)
      {
        // Get the name of the source/target nodes.
        string source = "LF" + row["cause"];
        string target = "LF" + row["effect"];

        // Create an edge between the two nodes.
        log_graph.create_edge (source, target);

        // Get the source node of the causality.
        CUTS.Graph.Node source_node = log_graph.node (source);

        Relation relation;
        string filter = String.Format ("relid = {0}", row["relid"]);
        DataRow[] relations = ds.Tables["relations"].Select (filter, "rel_index ASC");

        if (relations.Length != 0)
        {
          // Create a new relation for this log format.
          relation = new Relation ();

          foreach (DataRow equality in relations)
          {
            string lhs_eq = (string)equality["lhs"];
            string rhs_eq = (string)equality["rhs"];

            // Insert the next equality into the relation.
            relation.add (lhs_eq, rhs_eq);
          }

          // Store the relation with the source node.
          ArrayList r;

          if (source_node.properties.ContainsKey ("relation"))
          {
            r = (ArrayList)source_node.property ("relation");
          }
          else
          {
            r = new ArrayList ();
            source_node.property ("relation", r);
          }

          // Add the relation to this node's relation set.
          r.Add (relation);

          // Save the relation.
          if (!relation_set.Contains (relation))
            relation_set.Add (relation);
        }
      }

      // Do a topological sort of the log formats. This will give us the
      // order in which we must process the formats to extract the correct
      // log messages, and ensure causality.
      CUTS.Graph.Node[] sorted_node_list =
        CUTS.Graph.Algorithm.topological_sort (log_graph);

      // Create the variables for this unit test. This involves getting
      // the variables from the database, and creating data table based
      // on the variable types and their names.
      Hashtable vars = new Hashtable ();

      foreach (DataRow row in ds.Tables["variables"].Rows)
        vars.Add (row["fq_name"], row["vartype"]);

      vtable.Create (vars, true);
      vtable.CreateIndices ((Relation[])relation_set.ToArray (typeof (Relation)));

      // Prepare the command that will be used to select the log messages
      // based on the log formats of the current unit test.
      DbCommand logdata_command = (DbCommand)this.conn_.CreateCommand ();
      adapter.SelectCommand = logdata_command;

      logdata_command.CommandText =
        "CALL cuts.select_log_data_asc_by_test_number (?test, ?lfid)";

      DbParameter test_param = logdata_command.CreateParameter ();
      test_param.ParameterName = "?test";
      test_param.DbType = DbType.Int32;
      test_param.Value = vtable.TestNumber;
      logdata_command.Parameters.Add (test_param);

      DbParameter lfid_param = logdata_command.CreateParameter ();
      lfid_param.ParameterName = "?lfid";
      lfid_param.DbType = DbType.Int32;
      logdata_command.Parameters.Add (lfid_param);

      // Iterate over each of the log formats and select the log messages
      // for the current test that match the format. The log message are
      // returned in order of [hostname, msgtime].
      DataTable logdata = new DataTable ();
      Hashtable variables = new Hashtable ();

      foreach (CUTS.Graph.Node node in sorted_node_list)
      {
        // Set the parameter value for the log format.
        int lfid = (int)node.property ("lfid");
        lfid_param.Value = lfid;

        // Select the variables for this log format.
        string lfid_filter = String.Format ("lfid = {0}", lfid);

        DataRow[] log_variables = ds.Tables["variables"].Select (lfid_filter);
        Hashtable log_vars = new Hashtable ();
        ArrayList rel_list = new ArrayList ();

        foreach (DataRow info in log_variables)
        {
          log_vars.Add (info["varname"], info["fq_name"]);
          rel_list.Add (info["fq_name"]);
        }

        // Create a regular expression to locate the variables in the
        // each of the log messages.
        String csharp_regex = (String)node.property ("regex.csharp");
        Regex regex = new Regex (csharp_regex);

        // Get the log data for this log format.
        if (logdata.Rows.Count != 0)
          logdata.Clear ();

        adapter.Fill (logdata);

        // Get the relation for this log format.
        ArrayList relations = (ArrayList)node.property ("relation");

        // Create a data entry object for this log format.
        LogFormatDataEntry entry;

        if (relations == null)
        {
          entry = new LogFormatDataEntry (vtable,
                                          (String[])rel_list.ToArray (typeof (String)));

          this.process_log_messages (entry, regex, log_vars, logdata);
        }
        else
        {
          foreach (Relation relation in relations)
          {
            entry = new LogFormatDataEntry (vtable,
                                            (String[])rel_list.ToArray (typeof (String)),
                                            relation);

            this.process_log_messages (entry, regex, log_vars, logdata);
          }
        }

        //// Clear the variable hash table.
        //if (variables.Count > 0)
        //  variables.Clear ();


        //foreach (Relation relation in relations)
        //{
        //  while (reader.Read ())
        //  {
        //    // Apply the C# regular expression to the log message.
        //    String varname, fq_name;
        //    String message = (String)reader["message"];
        //    Match variable_match = variable_regex.Match (message);

        //    // Get all the variables from this log message.
        //    foreach (DictionaryEntry v in log_vars)
        //    {
        //      // Get the name of the variable.
        //      varname = (String)v.Key;
        //      fq_name = (String)v.Value;

        //      // Get the value of the variable from the match.
        //      variables[fq_name] =
        //        variable_match.Groups[varname].Captures[0].Value;
        //    }

        //    // Process the set of variables.
        //    entry.Process (variables);
        //  }

        //  // Close the reader for the next set of data.
        //  reader.Close ();
        //}
      }
    }

    private void process_log_messages (LogFormatDataEntry entry,
                                       Regex regex,
                                       Hashtable variables,
                                       DataTable logdata)
    {
      String varname, fq_name, message;
      Match match;
      Hashtable parameter = new Hashtable ();

      foreach (DataRow row in logdata.Rows)
      {
        if (parameter.Count != 0)
          parameter.Clear ();

        // Apply the C# regular expression to the log message.
        message = (String)row["message"];
        match = regex.Match (message);

        // Get all the variables from this log message.
        foreach (DictionaryEntry var in variables)
        {
          // Get the name of the variable.
          varname = (String)var.Key;
          fq_name = (String)var.Value;

          // Get the value of the variable from the match.
          parameter[fq_name] = match.Groups[varname].Captures[0].Value;
        }

        // Process the set of variables.
        entry.Process (parameter);
      }
    }

    private UnitTestResult evaluate_i (UnitTestVariableTable vtable, bool aggr)
    {
      List<string> groups;
      string sqlstr = this.create_evaluation_query (vtable.UnitTestNumber,
                                                    !aggr,
                                                    out groups);

      // Evaluate the unit test.
      DataTable table = new DataTable ("result");
      vtable.Evaluate (sqlstr, ref table);

      UnitTestResult result = new UnitTestResult ();

      if (groups.Count == 0)
      {
        // There is only a single result in the set.
        result.Value = table.Rows[0]["result"];
      }
      else
      {
        // Each row in the result set is its own group. We just need to
        // construct the name of the groups based on the provided columns
        // used for grouping.

        foreach (DataRow grp_row in table.Rows)
        {
          // First, construct name of group for this row in data table.
          ArrayList name_list = new ArrayList ();

          foreach (string column in groups)
            name_list.Add (grp_row[column]);

          string name = String.Join (".", (string[])name_list.ToArray (typeof (string)));

          // Save group result to main result set.
          result.GroupResults.Add (name, grp_row["result"]);
        }
      }

      return result;
    }

    private string create_evaluation_query (int utid,
                                            bool trend,
                                            out List<string> groups)
    {
      // SQL statements for extracting data to construct the final SQL
      // that calculates the result for the unit test.
      string sql_eval =
        "SELECT evaluation AS eval, REPLACE(evaluation, '.', '_') AS eval_escaped, aggregration_function AS aggr " +
        "FROM cuts.unit_tests WHERE utid = ?utid";

      DbCommand command = this.conn_.CreateCommand ();
      command.CommandText = sql_eval;

      DbParameter p1 = command.CreateParameter ();

      p1.ParameterName = "?utid";
      p1.DbType = DbType.Int32;
      p1.Value = utid;
      command.Parameters.Add (p1);

      // Execute the SQL statement.
      DataSet ds = new DataSet ();
      DbDataAdapter adapter = this.factory_.CreateDataAdapter ();
      adapter.SelectCommand = command;

      command.CommandText = sql_eval;
      adapter.Fill (ds, "evaluation");

      // Get the evaluation and aggregation functions.
      string eval_stmt = (string)ds.Tables["evaluation"].Rows[0]["eval"];
      string eval_escaped_stmt = (string)ds.Tables["evaluation"].Rows[0]["eval_escaped"];
      string aggr_stmt = (string)ds.Tables["evaluation"].Rows[0]["aggr"];

      // Get the groupings for the unit test. At this point, we need
      // to create a comma separate list of the group variables. This will
      // be used to construct the GROUP BY statement.
      string sql_grouping = "CALL cuts.select_unit_test_grouping (?utid)";
      command.CommandText = sql_grouping;
      adapter.Fill (ds, "groupings");

      string name;
      groups = new List<string> ();

      foreach (DataRow row in ds.Tables["groupings"].Rows)
      {
        name = (string)row["fq_name"];
        groups.Add (name.Replace (".", "_"));
      }

      string grouping = String.Join (",", groups.ToArray ());
      string sqlstr;

      if (trend)
      {
        sqlstr = "SELECT ";

        if (grouping != String.Empty)
          sqlstr += grouping + ",";

        sqlstr += eval_escaped_stmt + " AS result FROM vtable";
      }
      else
      {
        sqlstr = "SELECT ";

        if (grouping != String.Empty)
          sqlstr += grouping + ",";

        sqlstr += aggr_stmt + "(" + eval_escaped_stmt + ") AS result FROM vtable";
      }

      if (grouping != String.Empty)
      {
        if (trend)
          sqlstr += " ORDER BY " + grouping;
        else
          sqlstr += " GROUP BY " + grouping;
      }

      return sqlstr;
    }

    /**
     * Database connection for the evaluator.
     */
    private DbProviderFactory factory_;

    private DbConnection conn_;

    private string location_;
  }
}
