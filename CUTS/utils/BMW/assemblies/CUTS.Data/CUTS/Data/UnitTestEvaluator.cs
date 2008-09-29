// -*- C# -**

using System;
using System.Collections;
using System.Data;
using System.Data.Common;
using System.Text.RegularExpressions;

namespace CUTS.Data
{
  /**
   * @class UnitTestEvaluator
   *
   * Data abstraction for evaluating a unit test.
   */
  public class UnitTestEvaluator
  {
    /**
     * Database connection for the evaluator.
     */
    private IDbConnection conn_;

    /**
     * Factory for generating data adapters.
     */
    private CUTS.Data.IDbDataAdapterFactory adapter_factory_;

    /**
     * Initializing constructor.
     */
    public UnitTestEvaluator (IDbConnection conn, IDbDataAdapterFactory factory)
    {
      this.conn_ = conn;
      this.adapter_factory_ = factory;
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
    public DataTable evaluate (int test,
                               int utid,
                               bool aggr,
                               out string [] group_name,
                               out string eval)
    {
      // Create a new variable table for this unit test.
      CUTS.Data.VariableTable vtable = new CUTS.Data.VariableTable ("vtable");

      try
      {
        // Get the variable table for this unit test. This table is then sent
        // back to the database for processing, i.e., to execute the user-defined
        // expression to evaluate the unit test.
        this.create_variable_table (test, utid, ref vtable);

        // Create the table in the database.
        this.create_table_in_database (vtable.data);

        // Fill the table in the database.
        this.populate_table_in_database (vtable.data);

        // SQL statements for extracting data to construct the final SQL
        // that calculates the result for the unit test.
        string sql_eval =
          "SELECT evaluation AS eval, REPLACE(evaluation, '.', '_') AS eval_escaped, aggregration_function AS aggr " +
          "FROM cuts.unit_tests WHERE utid = ?utid";

        IDbCommand command = this.conn_.CreateCommand ();
        command.CommandText = sql_eval;

        IDbDataParameter p1 = command.CreateParameter ();

        p1.ParameterName = "?utid";
        p1.DbType = DbType.Int32;
        p1.Value = utid;
        command.Parameters.Add (p1);

        // Execute the SQL statement.
        DataSet ds = new DataSet ();
        DbDataAdapter adapter =
          (DbDataAdapter)this.adapter_factory_.CreateDbDataAdapter (command);

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

        ArrayList group_list = new ArrayList ();

        foreach (DataRow row in ds.Tables["groupings"].Rows)
        {
          string name = (string)row["fq_name"];
          group_list.Add (name.Replace (".", "_"));
        }

        group_name = (string[])group_list.ToArray (typeof (string));
        string grouping = String.Join (",", group_name);

        // Finally, construct the entire SQL statement for the evaluation.
        string sql_result;

        if (aggr)
        {
          sql_result = "SELECT ";

          if (grouping != String.Empty)
            sql_result += grouping + ",";

          sql_result +=
            aggr_stmt + "(" + eval_escaped_stmt + ") AS result FROM " +
            vtable.data.TableName;

          eval = aggr_stmt + "(" + eval_stmt + ")";
        }
        else
        {
          sql_result = "SELECT ";

          if (grouping != String.Empty)
            sql_result += grouping + ",";

          sql_result +=
            eval_escaped_stmt + " AS result FROM " +
            vtable.data.TableName;

          eval = eval_stmt;
        }

        if (aggr && grouping != String.Empty)
            sql_result += " GROUP BY " + grouping;

        // Execute the statement, which will calculate the result.
        command.CommandText = sql_result;
        adapter.Fill (ds, "result");

        return ds.Tables["result"];
      }
      finally
      {
        this.remove_table (vtable.data.TableName);
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
    private void create_variable_table (int test,
                                        int utid,
                                        ref CUTS.Data.VariableTable vtable)
    {
      // Initialize the database objects.
      DataSet ds = new DataSet ();
      IDbCommand command = this.conn_.CreateCommand ();
      DbDataAdapter adapter =
        (DbDataAdapter) this.adapter_factory_.CreateDbDataAdapter (command);

      // Create a parameter for the command.
      IDbDataParameter p1 = command.CreateParameter ();

      // Initialize the parameter.
      p1.ParameterName = "?utid";
      p1.DbType = DbType.Int32;
      p1.Value = utid;

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

      foreach (DataRow row in ds.Tables["causality"].Rows)
      {
        // Get the name of the source/target nodes.
        string source = "LF" + row["cause"];
        string target = "LF" + row["effect"];

        // Create an edge between the two nodes.
        log_graph.create_edge (source, target);

        // Get the source node of the causality.
        CUTS.Graph.Node source_node = log_graph.node (source);

        string filter = String.Format ("relid = {0}", row["relid"]);
        DataRow[] relations = ds.Tables["relations"].Select (filter, "rel_index ASC");

        if (relations.Length != 0)
        {
          // Create a new relation for this log format.
          CUTS.Data.Relation relation = new CUTS.Data.Relation ();

          foreach (DataRow equality in relations)
          {
            // int index = (int)equality["rel_index"] - 1;
            string lhs_eq = (string)equality["lhs"];
            string rhs_eq = (string)equality["rhs"];

            // Insert the next equality into the relation.
            relation.add (lhs_eq, rhs_eq);
          }

          // Store the relation with the source node.
          source_node.property ("relation", relation);
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

      vtable.reset (vars);

      // Prepare the command that will be used to select the log messages
      // based on the log formats of the current unit test.
      IDbCommand logdata_command = this.conn_.CreateCommand ();

      command.CommandText =
        "CALL cuts.select_log_data_asc_by_test_number (?test, ?lfid)";

      p1.ParameterName = "?test";
      p1.DbType = DbType.Int32;
      p1.Value = test;

      IDbDataParameter p2 = command.CreateParameter ();

      p2.ParameterName = "?lfid";
      p2.DbType = DbType.Int32;
      command.Parameters.Add (p2);

      // Iterate over each of the log formats and select the log messages
      // for the current test that match the format. The log message are
      // returned in order of [hostname, msgtime].

      foreach (CUTS.Graph.Node node in sorted_node_list)
      {
        // Set the parameter value.
        int lfid = (int)node.property ("lfid");
        p2.Value = lfid;

        // Clear the 'logdata' table.
        if (ds.Tables.Contains ("logdata"))
          ds.Tables["logdata"].Clear ();

        // Prepare the command then fill a data table. This will select
        // all the log data for the current log format.
        adapter.Fill (ds, "logdata");

        // Select the variables for this log format.
        string lfid_filter = String.Format ("lfid = {0}", lfid);
        DataRow[] log_variables = ds.Tables["variables"].Select (lfid_filter);

        // Get the relation for this log format, i.e., the variables
        // that we must ensure are equal between this format and  another
        // format.
        CUTS.Data.Relation relation =
          (CUTS.Data.Relation)node.property ("relation");

        // Create a regular expression to locate the variables in the
        // each of the log messages.
        string regex = (string)node.property ("regex.csharp");
        Regex variable_regex = new Regex (regex);

        Hashtable variables = new Hashtable ();

        foreach (DataRow logdata in ds.Tables["logdata"].Rows)
        {
          // Apply the C# regular expression to the log message.
          string message = (string)logdata["message"];
          Match variable_match = variable_regex.Match (message);

          // Get all the variables from this log message.
          foreach (DataRow variable in log_variables)
          {
            // Get the name of the variable.
            string varname = (string)variable["varname"];
            string fq_name = (string)variable["fq_name"];

            // Get the value of the variable from the match.
            object var_value = variable_match.Groups[varname].Captures[0].Value;
            variables[fq_name] = var_value;
          }

          if (relation != null)
          {
            // Update table based on relation between two log messages.
            vtable.add_values (variables, relation, true);
          }
          else
          {
            // Just insert the data into the table.
            vtable.add_values (variables);
          }
        }
      }
    }

    /**
     * Used to safely remove a table from the database.
     *
     * @param[in] table_name   The name of the table to be removed.
     */
    public void remove_table (string table_name)
    {
      IDbCommand command = this.conn_.CreateCommand ();

      command.CommandText = "DROP TABLE IF EXISTS " + table_name + ";";
      command.ExecuteNonQuery ();
    }

    /**
     * Used to create a single table in the database. THis is
     *   probably a legacy function that can be safely removed.
     *
     * @param[in]  table   The table to be created in the database.
     */
    public void create_table_in_database (DataTable table)
    {
      ArrayList column_list = new ArrayList ();
      string column_decl;

      foreach (DataColumn column in table.Columns)
      {
        column_decl = column.ColumnName.Replace ('.', '_') + " ";

        switch (column.DataType.ToString ())
        {
          case "System.String":
            column_decl += "VARCHAR (256)";
            break;

          case "System.Int32":
            column_decl += "INT";
            break;

          case "System.Int64":
            column_decl += "BIGINT";
            break;

          default:
            throw new Exception ("Unknown column type: " + column.DataType.ToString ());
        }

        // Insert the column declaration into the database.
        column_list.Add (column_decl);
      }

      // Build the query for creating the table.
      string table_columns =
        String.Join (", ", (string[])column_list.ToArray (typeof (string)));

      string sql =
        "CREATE TABLE " + table.TableName + " (" + table_columns + ");";

      // Creat the table in the database.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = sql;
      command.ExecuteNonQuery ();
    }

    /**
     * Used to send all of the data in the data table to the database
     * using an insert statement.
     *
     * @param[in]       table             Source data table
     */
    public void populate_table_in_database (DataTable table)
    {
      if (table.Rows.Count == 0)
        return;

      ArrayList list = new ArrayList ();

      // First, construct the columns for the insert statement.
      foreach (DataColumn column in table.Columns)
        list.Add (column.ColumnName.Replace ('.', '_'));

      string sql_columns =
        String.Join (", ", (string[])list.ToArray (typeof (string)));

      // Listing for storing the values.
      ArrayList values = new ArrayList ();

      // Next, construct the values to insert into the table.
      foreach (DataRow row in table.Rows)
      {
        // Clear the listing for this iteration.
        if (list.Count > 0)
          list.Clear ();

        // Gather all the values for this row. They will be used to
        // construct the VALUES portion of the INSERT INTO SQL statement.
        foreach (object obj in row.ItemArray)
        {
          string encoding;

          switch (obj.GetType ().ToString ())
          {
            case "System.Int16":
            case "System.Int32":
            case "System.Int64":
              encoding = obj.ToString ();
              break;

            case "System.String":
              encoding = "'" + obj.ToString () + "'";
              break;

            default:
              throw new Exception ("data type is not supported : " + obj.GetType ().ToString ());
          }

          // Insert the value into the listing.
          list.Add (encoding);
        }

        // Create the SQL statement for setting the values.
        string sql_values =
          "(" + String.Join (", ", (string[])list.ToArray (typeof (string))) + ")";

        // Insert the statement into the value list.
        values.Add (sql_values);
      }

      // Convert the values into their SQL portion of the statement.
      string sql_values_stmt =
        String.Join (", ", (string[])values.ToArray (typeof (string)));

      // Finally, create the insert statement for the data.
      string sql_insert =
        "INSERT INTO " + table.TableName + " (" + sql_columns + ") " +
        "VALUES " + sql_values_stmt;

      // Send the data to the database.
      IDbCommand command = this.conn_.CreateCommand ();
      command.CommandText = sql_insert;
      command.ExecuteNonQuery ();
    }
  }
}
