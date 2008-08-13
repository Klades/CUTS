using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Text.RegularExpressions;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using MySql.Data.MySqlClient;
using Actions.LogFormatActions;

namespace Actions.UnitTestActions
{
  /**
   * @class UnitTestActions
   *
   * Perform insertion and evaluation of Unit Tests
   */
  public static class UnitTestActions
  {
    /**
    * @var  DataBaseActions dba
    * Contains a reference to the standard Database Actions library
    */
    private static DataBaseActions.DataBaseActions dba =
      new DataBaseActions.DataBaseActions (ConfigurationManager.AppSettings["MySQL"]);
    private static DataSetActions dsa;

    public static void Insert_New_Unit_Test (Hashtable Variables)
    {
      string sql = "CALL Insert_UT(?name,?desc,?fail_comp,?warn_comp,?eval,?fail,?warn,?aggreg_func);";
      MySqlCommand comm = dba.GetCommand (sql);

      comm.Parameters.AddWithValue ("?name", Variables["Name"]);
      comm.Parameters.AddWithValue ("?desc", Variables["Description"]);
      comm.Parameters.AddWithValue ("?fail_comp", Variables["FailComparison"]);
      comm.Parameters.AddWithValue ("?warn_comp", Variables["WarnComparison"]);
      comm.Parameters.AddWithValue ("?eval", Variables["Evaluation"]);
      comm.Parameters.AddWithValue ("?fail", Variables["FailValue"]);
      comm.Parameters.AddWithValue ("?warn", Variables["WarnValue"]);
      comm.Parameters.AddWithValue ("?aggreg_func", Variables["Aggregration_Func"]);

      int utid = dba.ExecuteMySqlScalar (comm);

      string[] formats = (string [])Variables["Formats"];

      foreach (string lfid in formats)
        Insert_UT_LogFormat (utid, lfid);

      if (formats.Length > 1)
      {
        Pair[] relations = (Pair [])Variables["Relations"];

        foreach (Pair relation in relations)
          Insert_UT_Relation (utid, relation.First.ToString (), relation.Second.ToString ());
      }
    }

    public static void Insert_Existing_Unit_Test (string Package_ID_, string Unit_Test_ID_)
    {
      string sql = "CALL insert_package_unit_test(?p_id,?ut_id);";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?p_id", Package_ID_);
      comm.Parameters.AddWithValue ("?ut_id", Unit_Test_ID_);
      dba.ExecuteMySql (comm);
    }

    public static void Insert_Test_Suite (string Test_Suite_Name_)
    {
      string sql = "CALL insert_test_suite(?name);";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?name", Test_Suite_Name_);
      dba.ExecuteMySql (comm);
    }

    public static void create_test_package (string name)
    {
      string sql = "CALL create_test_package (?name);";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?name", name);
      dba.ExecuteMySql (comm);
    }

    public static void Insert_New_Package (string Test_Suite_ID_, string Package_Name_)
    {
      string sql = "CALL insert_test_suite_package(?tsid,?p_name);";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?tsid", Test_Suite_ID_);
      comm.Parameters.AddWithValue ("?p_name", Package_Name_);
      dba.ExecuteMySql (comm);
    }

    public static void Insert_Existing_Package (string Test_Suite_ID_, string Package_ID_)
    {
      string sql = "CALL insert_test_suite_package_existing(?tsid,?p_id);";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?tsid", Test_Suite_ID_);
      comm.Parameters.AddWithValue ("?p_id", Package_ID_);
      dba.ExecuteMySql (comm);
    }

    public static DataTable evaluate_unit_test (int test_number,
                                                int utid,
                                                bool aggregrate,
                                                ref string evaluation)
    {
      CUTS.Variable_Table vtable = new CUTS.Variable_Table ("vtable");

      // Yeah, this REALLY needs to go. It is clearly an incorrect use of the
      // singleton software design pattern!!
      if (dsa == null)
        dsa = new DataSetActions (dba, utid);

      try
      {
        // Get the variable table for this unit test. This table is then sent
        // back to the database for processing, i.e., to execute the user-defined
        // expression to evaluate the unit test.

        create_variable_table (test_number, utid, ref vtable);

        dsa.create_table_in_database (vtable.data);
        dsa.populate_table_in_database (vtable.data);

        //  // Preload the database with the valid table. Each log format for the given
        //  // test will have its own table.
        //  PreLoad_UT (test_number, utid);

        MySqlCommand command = dba.GetCommand ("");
        command.Parameters.AddWithValue ("?utid", utid);

        DataSet ds = new DataSet ();
        MySqlDataAdapter adapter = new MySqlDataAdapter (command);

        // SQL statements for extracting data to construct the final SQL
        // that calculates the result for the unit test.
        string sql_eval =
          "SELECT evaluation AS eval, REPLACE(evaluation, '.', '_') AS eval_escaped, aggregration_function AS aggr " +
          "FROM cuts.unit_tests WHERE utid = ?utid";

        // Run each of the SQL statements, and store the results in
        // a seperate table for later.
        command.CommandText = sql_eval;
        adapter.Fill (ds, "evaluation");

        //  command.CommandText = sql_formats;
        //  adapter.Fill (ds, "tables");

        //  command.CommandText = sql_relations;
        //  adapter.Fill (ds, "relations");

        // Get the evaluation and aggregation functions.
        string eval_stmt = (string)ds.Tables["evaluation"].Rows[0]["eval"];
        string eval_escaped_stmt = (string)ds.Tables["evaluation"].Rows[0]["eval_escaped"];
        string aggr_stmt = (string)ds.Tables["evaluation"].Rows[0]["aggr"];

        // Finally, construct the entire SQL statement for the evaluation.

        string sql_result;

        if (aggregrate)
        {
          sql_result =
            "SELECT " + aggr_stmt + "(" + eval_escaped_stmt + ") AS result FROM " +
            vtable.data.TableName;

          evaluation = aggr_stmt + "(" + eval_stmt + ")";
        }
        else
        {
          sql_result =
            "SELECT " + eval_escaped_stmt + " AS result FROM " +
            vtable.data.TableName;

          evaluation = eval_stmt;
        }

        // Execute the statement, which will calculate the result.
        command = dba.GetCommand (sql_result);
        return dba.execute_mysql_adapter (command);
      }
      catch (Exception ex)
      {
        throw ex;
      }
      finally
      {
        // Make sure we remove the data from the database.
        dsa.RemoveTable (vtable.data.TableName);
      }
    }

    public static DataTable Evalate_UT_for_single_test (int utid, int test_number)
    {
      try
      {
      //  // Preload the database with the valid table. Each log format for the given
      //  // test will have its own table.
      //  PreLoad_UT (test_number, utid);

        MySqlCommand command = dba.GetCommand ("");
        command.Parameters.AddWithValue ("?utid", utid);

        DataSet ds = new DataSet ();
        MySqlDataAdapter adapter = new MySqlDataAdapter (command);

        // SQL statements for extracting data to construct the final SQL
        // that calculates the result for the unit test.
        string sql_eval =
          "SELECT evaluation AS eval, aggregration_function AS aggr " +
          "FROM cuts.unit_tests WHERE utid = ?utid";

        // Run each of the SQL statements, and store the results in
        // a seperate table for later.
        command.CommandText = sql_eval;
        adapter.Fill (ds, "evaluation");

      //  command.CommandText = sql_formats;
      //  adapter.Fill (ds, "tables");

      //  command.CommandText = sql_relations;
      //  adapter.Fill (ds, "relations");

        // Get the evaluation and aggregation functions.
        string eval_stmt = (string)ds.Tables["evaluation"].Rows[0]["eval"];
        string aggr_stmt = (string)ds.Tables["evaluation"].Rows[0]["aggr"];

      //  // Construct the FROM clause using the table names for storing the
      //  // data for each log message.
      //  ArrayList table_names = new ArrayList ();

      //  foreach (DataRow row in ds.Tables["tables"].Rows)
      //    table_names.Add (row["lftable"]);

      //  string from_clause =
      //    "FROM " + String.Join (", ", (string [])table_names.ToArray (typeof (string)));

      //  // Construct the WHERE clause, which is based on the relations between
      //  // each of the log formats.
      //  string where_clause = "";

      //  if (table_names.Count > 1)
      //  {
      //    ArrayList relations = new ArrayList ();

      //    foreach (DataRow row in ds.Tables["relations"].Rows)
      //      relations.Add (row["relation"]);

      //    where_clause =
      //      "WHERE " + String.Join (" AND ", (string [])relations.ToArray (typeof (string)));
      //  }

      //  // Finally, construct the entire SQL statement for the evaluation.
      //  string sql_result =
      //    "SELECT " + utid + ", " + aggr_stmt + "(" + eval_stmt + ") AS result " +
      //    from_clause + " " + where_clause;

      //  command = dba.GetCommand (sql_result);
      //  return dba.execute_mysql_adapter (command);
      }
      catch (Exception ex)
      {
        throw ex;
      }
      finally
      {
        // Make sure we remove the data from the database.
      }

      return null;
    }

    //public static DataTable Evaluate_UT_for_all_tests (int utid)
    //{
    //  try
    //  {
    //    PreLoad_UT (utid);
    //    string sql = "CALL evaluate_unit_test_full(?utid);";

    //    MySqlCommand command = dba.GetCommand (sql);
    //    command.Parameters.AddWithValue ("?utid", utid);

    //    DataTable dt = dba.execute_mysql_adapter (command);
    //    return dt;
    //  }
    //  catch (Exception ex) { throw ex; }
    //  finally { UnLoad_UT (utid); }
    //}

    public static DataTable Evalate_UT_as_metric (int utid, int test_number)
    {
      try
      {

        PreLoad_UT (test_number, utid);
        string sql = "CALL evaluate_unit_test_as_metric(?utid,?test_number);";

        MySqlCommand command = dba.GetCommand (sql);
        command.Parameters.AddWithValue ("?utid", utid);
        command.Parameters.AddWithValue ("?test_number", test_number);

        DataTable dt = dba.execute_mysql_adapter (command);
        return dt;
      }
      catch (Exception ex) { throw ex; }
      finally { UnLoad_UT (utid); }
    }

    public static DataTable Get_All_Test_Suites ()
    {
      string sql = "SELECT * FROM test_suites;";
      DataTable dt = dba.execute_mysql_adapter (sql);
      return dt;
    }
    public static void Delete_Test_Suite (string Test_Suite_ID_)
    {
      string sql = "DELETE FROM cuts.test_suites WHERE id=?t_id;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?t_id", Test_Suite_ID_);
      dba.ExecuteMySql (comm);
    }
    public static void Delete_Package (string Package_ID_)
    {
      string sql = "DELETE FROM cuts.packages WHERE id=?p_id;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?p_id", Package_ID_);
      dba.ExecuteMySql (comm);
    }
    public static void Remove_Package (string Test_Suite_ID, string Package_ID_)
    {
      string sql = "DELETE FROM cuts.test_suite_packages WHERE " +
                    "id=?ts_id AND p_id=?p_id_in;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?ts_id", Test_Suite_ID);
      comm.Parameters.AddWithValue ("?p_id_in", Package_ID_);
      dba.ExecuteMySql (comm);
    }

    public static void Delete_Unit_Test (string Unit_Test_ID_)
    {
      string sql = "DELETE FROM cuts.unit_tests WHERE utid=?ut_id;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?ut_id", Unit_Test_ID_);
      dba.ExecuteMySql (comm);
    }

    public static void Remove_Unit_Test (string Package_ID_, string Unit_Test_ID_)
    {
      string sql = "DELETE FROM cuts.package_unit_tests WHERE " +
                    "id=?p_id AND ut_id=?ut_id_in;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?p_id", Package_ID_);
      comm.Parameters.AddWithValue ("?ut_id_in", Unit_Test_ID_);
      dba.ExecuteMySql (comm);
    }

    public static DataTable Get_All_Packages ()
    {
      string sql = "SELECT * FROM packages";
      DataTable dt = dba.execute_mysql_adapter (sql);
      return dt;
    }

    public static DataTable Get_All_Unit_Tests ()
    {
      string sql = "SELECT * FROM unit_tests;";
      DataTable dt = dba.execute_mysql_adapter (sql);
      return dt;
    }

    public static DataTable Get_Packages (string Test_Suite_ID_)
    {
      string sql = "SELECT packages.id as id,name " +
                   "FROM packages,test_suite_packages AS tsp " +
                   "WHERE tsp.id =?ts_id AND tsp.p_id = packages.id;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?ts_id", Test_Suite_ID_);
      DataTable dt = dba.execute_mysql_adapter (comm);
      return dt;
    }

    public static DataTable Get_Unit_Tests (string Package_ID_)
    {
      string sql = "SELECT utid, name " +
                   "FROM unit_tests AS utd,package_unit_tests AS put " +
                   "WHERE put.id=?p_id AND put.ut_id=utd.utid;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?p_id", Package_ID_);
      DataTable dt = dba.execute_mysql_adapter (comm);
      return dt;
    }

    public static DataRow Get_Unit_Test_Info (string Unit_Test_ID_)
    {
      string sql = "SELECT * " +
                   "FROM unit_tests " +
                   "WHERE utid=?utid_in LIMIT 1;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?utid_in", Unit_Test_ID_);
      DataRow dr = dba.ExecuteMySqlRow (comm);
      return dr;
    }

    private static void UnLoad_UT (int utid)
    {
      if (dsa == null)
        dsa = new DataSetActions (dba, utid);

      Array LFIDs = LogFormatActions.LogFormatActions.GetLFIDs (utid);
      foreach (int CurrentLFID in LFIDs)
        dsa.RemoveTable ("LF" + CurrentLFID.ToString ());
    }

    private static void create_variable_table (int test, int utid, ref CUTS.Variable_Table vtable)
    {
      DataSet ds = new DataSet ();

      MySqlCommand command = dba.GetCommand ("");
      MySqlDataAdapter adapter = new MySqlDataAdapter (command);
      command.Parameters.AddWithValue ("?utid", utid);

      // Get the variabes for this unit test.
      command.CommandText = "CALL cuts.select_unit_test_variables (?utid)";
      command.Prepare ();

      adapter.Fill (ds, "variables");

      // Get the relations for this unit test.
      command.CommandText = "CALL cuts.select_unit_test_relations_as_set (?utid)";
      command.Prepare ();

      adapter.Fill (ds, "relations");

      // Get all the log formats for this unit test.
      command.CommandText = "CALL cuts.select_unit_test_log_formats (?utid)";
      command.Prepare ();

      adapter.Fill (ds, "logformats");

      // Create the relations for this unit test
      CUTS.Relations relations = new CUTS.Relations ();

      foreach (DataRow row in ds.Tables["relations"].Rows)
        relations.insert ((string)row["lhs"], (string)row["rhs"]);

      // Create the variables for this unit test. This involves getting
      // the variables from the database, and creating data table based
      // on the variable types and their names.
      Hashtable vars = new Hashtable ();

      foreach (DataRow row in ds.Tables["variables"].Rows)
        vars.Add (row["fq_name"], row["vartype"]);

      vtable.reset (vars);

      // Prepare the command that will be used to select the log messages
      // based on the log formats of the current unit test.
      MySqlCommand logdata_command =
        dba.GetCommand ("CALL cuts.select_log_data_by_test (?test, ?lfid)");

      // Initialize the parameters for the statement.
      logdata_command.Parameters.AddWithValue ("?test", test);

      MySqlParameter lfid_parameter = logdata_command.CreateParameter ();
      lfid_parameter.ParameterName = "?lfid";
      lfid_parameter.DbType = DbType.Int32;

      // Insert the parameter into the command.
      logdata_command.Parameters.Add (lfid_parameter);

      // Update the select command for the adapter.
      adapter.SelectCommand = logdata_command;

      // Iterate over each of the log formats and select the log messages
      // for the current test that match the format. The log message are
      // returned in order of [hostname, msgtime].

      foreach (DataRow logformat in ds.Tables["logformats"].Rows)
      {
        // Set the parameter value.
        int lfid = (int)logformat["lfid"];
        lfid_parameter.Value = lfid;

        // Clear the 'logdata' table.
        if (ds.Tables.Contains ("logdata"))
          ds.Tables["logdata"].Clear ();

        // Prepare the command then fill a data table. This will select
        // all the log data for the current log format.
        logdata_command.Prepare ();
        adapter.Fill (ds, "logdata");

        // Set the log format id filter for later.
        string lfid_filter = "lfid = " + lfid;

        // Get the variables for this log format.
        DataRow [] log_variables = ds.Tables["variables"].Select (lfid_filter);

        // Locate the variable that is the relation variable for this log
        // message. There may be more than one, but we only need to locate
        // one. It will be used for indexing into the data table.
        string relation_varname = String.Empty;
        string relation_fq_name = String.Empty;

        foreach (DataRow variable in log_variables)
        {
          string fq_name = (string)variable["fq_name"];

          if (relations.is_relation_variable (fq_name))
          {
            relation_varname = (string)variable["varname"];
            relation_fq_name = fq_name;
            break;
          }
        }

        // Create a regular expression to locate the variables in the
        // each of the log messages.
        string regex = (string)logformat["csharp_regex"];
        Regex variable_regex = new Regex (regex);

        foreach (DataRow logdata in ds.Tables["logdata"].Rows)
        {
          // Apply the C# regular expression to the log message.
          string message = (string)logdata["message"];
          Match variable_match = variable_regex.Match (message);

          object value;
          int index = -1;

          // First, get the index of the relation variable. This will be used to
          // index into the variable table for this log message.
          if (relation_varname != String.Empty &&
              relation_fq_name != String.Empty)
          {
            value = variable_match.Groups[relation_varname].Captures[0].Value;
            index = relations.update (relation_fq_name, value);
          }

          foreach (DataRow variable in log_variables)
          {
            // Get the name of the variable.
            string varname = (string)variable["varname"];
            string fq_name = (string)variable["fq_name"];

            // Get the value of the variable from the match.
            value = variable_match.Groups[varname].Captures[0].Value;

            // Either we update an existing location in the variable table,
            // or we just append the data if there are no relations.
            if (index != -1)
              vtable.update_value (index, fq_name, value);
            else
              vtable.add_value (fq_name, value);
          }
        }
      }

      // Now that
    }

    private static void PreLoad_UT (int test, int utid)
    {
      /*
       *
       * 1) create temp dataset
       * 2) put all messages in temp dataset
       * 3) push temp back to real DB
       * 4) create select statement
       *
       */
      if (dsa == null)
        dsa = new DataSetActions (dba, utid);

      Array LFIDs = LogFormatActions.LogFormatActions.GetLFIDs (utid);

      foreach (int CurrentLFID_u in LFIDs)
      {
        int CurrentLFID = Int32.Parse (CurrentLFID_u.ToString ());

        // get the regex and the variable info
        string cs_regex;
        Hashtable VariableNames;
        LogFormatActions.LogFormatActions.GetLFIDInfo (out cs_regex, out VariableNames, CurrentLFID);

        /* create a table for this log format
         *   Note this needs to take a hash for variables */
        string TableName = "LF" + CurrentLFID.ToString ();
        dsa.AddTable (TableName, VariableNames);

        dsa.FillTable (test, CurrentLFID, cs_regex, VariableNames);
      }

      dsa.SendToDB ();
    }

    // Note - Grouping is disabled for now
    /*
    private static void Insert_UT_Group ( int UTID, string VariableID )
    {
      string sql = "CALL Insert_UT_Group(?utid,?variableID);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?utid", UTID );
      comm.Parameters.AddWithValue( "?variableID", VariableID );
      dba.ExecuteMySql( comm );
    }
    */

    private static void Insert_UT_LogFormat (int utid, string lfid)
    {
      string sql = "CALL Insert_UT_LogFormat (?utid, ?lfid);";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?utid", utid);
      comm.Parameters.AddWithValue ("?lfid", lfid);
      dba.ExecuteMySql (comm);
    }

    private static void Insert_UT_Relation (int utid, string rel1, string rel2)
    {
      string sql = "CALL Insert_UT_Relation(?utid, ?var1,?var2)";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?utid", utid);
      comm.Parameters.AddWithValue ("?var1", rel1);
      comm.Parameters.AddWithValue ("?var2", rel2);
      dba.ExecuteMySql (comm);
    }

    private class DataSetActions
    {
      private DataSet ds_;
      private Actions.DataBaseActions.DataBaseActions dba;
      private int utid_;

      public DataSetActions (Actions.DataBaseActions.DataBaseActions dba, int Unit_Test_ID_)
      {
        this.ds_ = new DataSet ();
        this.dba = dba;
        this.utid_ = Unit_Test_ID_;
      }

      /**
       * Adds a table that represents one LogFormat to the DataSet.
       *   General use of the dataset is AddTable, FillTables, Send_To_DB.
       *
       * @param[in]  tableName   The name of the table to be created. This
       *                           should be similar to 'LF5', following the
       *                           format of concat(LF,lfid).
       * @param[in]  columnInfo  This should be the information needed to
       *                           build the columns, aka a hastable with
       *                           keys that are the column/variable names,
       *                           and objects that are the column/variable
       *                           types.
       */
      public void AddTable (string tableName, Hashtable columnInfo)
      {
        DataTable table = new DataTable (tableName);

        // Create an indexer for the data value. This will be used to uniquely
        // identify all the variables in a single evaluation across many log
        // messages.
        table.Columns.Add (new DataColumn ("rowid", typeof (System.Int32)));

        // The test number should always be a column.
        table.Columns.Add (new DataColumn ("test_number", typeof (System.Int32)));

        string[] keys = new string[columnInfo.Count];
        columnInfo.Keys.CopyTo (keys, 0);

        foreach (string column_name in keys)
        {
          DataColumn dc = new DataColumn (column_name);

          // Find the appropriate type
          switch (columnInfo[column_name].ToString ())
          {
            case "INT":
              dc.DataType = typeof (System.Int32);
              break;

            case "STRING":
              dc.DataType = typeof (System.String);
              break;
          }

          table.Columns.Add (dc);
        }

        // This is to fix a bug in visual studio where the ds_ tables are
        // maintained inside the temp directory and so the add
        // will throw an exception (across two different builds)
        if (ds_.Tables.Contains (tableName))
          ds_.Tables.Remove (tableName);

        ds_.Tables.Add (table);
      }

      public void RemoveTable (string tableName)
      {
        string sql = "DROP TABLE IF EXISTS " + tableName + ";";
        dba.ExecuteMySql (sql);
      }

      /**
       * Fills one table in the DataSet by grabbing all of the matching
       * rows from the real DataBase, extracting the data, and storing
       * it in the DataSet.
       *
       * @param[in]   lfid      The Log Format ID. This is used to create
       *                          the table name of concat(LF,lfid).
       * @param[in]   cs_regex  The C Sharp regular expression used to
       *                          extract the variables from the messages
       *                          found that match the Log Format.
       * @param[in]   variables A hashtable that contains the variable
       *                          names as keys, and types as values.
       */
      public void FillTable (int test, int lfid, string cs_regex, Hashtable variables)
      {
        // Get the actual log messages and test_numbers
        string sql = "CALL get_log_data_by_test (?test, ?lfid);";
        MySqlCommand comm = dba.GetCommand (sql);
        comm.Parameters.AddWithValue ("?test", test);
        comm.Parameters.AddWithValue ("?lfid", lfid);

        DataTable table = dba.execute_mysql_adapter (comm);

        /*   Iterate over each Row
         *   Regex the data out
         *   Put the Data into the DataSet
         */

        string TableName = "LF" + lfid.ToString ();

        foreach (DataRow row in table.Rows)
        {
          // Get the row to put data into
          DataRow new_row = GetRow (TableName);

          Regex reg = new Regex (cs_regex, RegexOptions.IgnoreCase);
          Match mat = reg.Match (row["message"].ToString ());

          string[] variable_names = new string[variables.Count];
          variables.Keys.CopyTo (variable_names, 0);

          if (mat.Success == false)
          {
            throw new Exception ("The log message '" + row["message"].ToString () +
              "' was matched by the DataBase engine, but was not matched by " +
              " the C# Regular Expression of '" + cs_regex + "'. ");
          }

          // Set the test number and the rowid for the new row.
          new_row["rowid"] = ds_.Tables[TableName].Rows.Count;
          new_row["test_number"] = row["test_number"];

          foreach (string varname in variable_names)
          {
            // Get the type associated with the current column
            Type type = this.ds_.Tables[TableName].Columns[varname].DataType;

            switch (type.ToString ())
            {
              case "System.Int32":
                new_row[varname] = Int32.Parse (mat.Groups[varname].ToString ());
                break;

              case "System.String":
                new_row[varname] = mat.Groups[varname].ToString ();
                break;
            }
          }

          // Insert the row into the database.
          InsertRow (TableName, new_row);
        }
      }

      public void SendToDB ()
      {
        CreateTablesInDB ();

        foreach (DataTable table in ds_.Tables)
          this.populate_table_in_database (table);
      }

      private DataRow GetRow (string TableName)
      {
        return ds_.Tables[TableName].NewRow ();
      }

      private void InsertRow (string TableName, DataRow new_row)
      {
        ds_.Tables[TableName].Rows.Add (new_row);
      }

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

            default:
              throw new Exception ("Unknown column type: " + column.DataType.ToString ());
          }

          // Insert the column declaration into the database.
          column_list.Add (column_decl);
        }

        string table_columns =
          String.Join (", ", (string[])column_list.ToArray (typeof (string)));

        string sql =
          "CREATE TABLE " + table.TableName + " (" + table_columns + ");";

        dba.ExecuteMySql (sql);
      }

      private void CreateTablesInDB ()
      {
        foreach (DataTable table in ds_.Tables)
          this.create_table_in_database (table);
      }

      /**
       *
       */
      public void populate_table_in_database (DataTable table)
      {
        ArrayList list = new ArrayList ();

        // First, construct the columns for the insert statement.
        foreach (DataColumn column in table.Columns)
          list.Add (column.ColumnName.Replace ('.', '_'));

        string sql_columns =
          String.Join (", ", (string [])list.ToArray (typeof (string)));

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
              case "System.Int32":
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
            "(" + String.Join (", ", (string [])list.ToArray (typeof (string))) + ")";

          // Insert the statement into the value list.
          values.Add (sql_values);
        }

        // Convert the values into their SQL portion of the statement.
        string sql_values_stmt =
          String.Join (", ", (string [])values.ToArray (typeof (string)));

        // Finally, create the insert statement for the data.
        string sql_insert =
          "INSERT INTO " + table.TableName + " (" + sql_columns + ") " +
          "VALUES " + sql_values_stmt;

        dba.ExecuteMySql (sql_insert);
      }


    } // End private class DataSetActions

  } // End Class UnitTestActions

} // End Actions.UnitTestActions