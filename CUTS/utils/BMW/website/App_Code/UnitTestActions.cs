/**
 * @file        UnitTestActions.cs
 *
 * Defines the Actions.UnitTestActions code.
 *
 * @author      Hamilton Turner
 */

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
   * Perform insertion and evaluation of Unit Tests. This class needs some
   *   updates!!! It uses a faulty singleton in a few places, needs to be 
   *   refactored so that it is not a static class, and needs to be 
   *   removed into the CUTS namespace at some appropriate level. 
   * 
   * Also, this class should not throw errors on functions of type 
   *   remove this, delete this, remove this from that if 'this'
   *   does not exist, or does not exist in 'that'. This might not happen,
   *   but it needs to be checked to make sure. 
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

    /**
     * Used to insert a brand new unit test. Uses SQL procedure
     *   insert_unit_test.
     * 
     * @param[in]   variables   A Hashtable of all of the variables
     *                            needed to create a unit test.
     */
    public static void insert_new_unit_test (Hashtable variables)
    {
      // Prepare SQL
      string sql = "CALL insert_unit_test(?name,?desc,?fail_comp,?warn_comp," + 
        "?eval,?fail,?warn,?aggreg_func);";
      MySqlCommand comm = dba.get_command (sql);

      // Add parameters
      comm.Parameters.AddWithValue ("?name", variables["Name"]);
      comm.Parameters.AddWithValue ("?desc", variables["Description"]);
      comm.Parameters.AddWithValue ("?fail_comp", variables["FailComparison"]);
      comm.Parameters.AddWithValue ("?warn_comp", variables["WarnComparison"]);
      comm.Parameters.AddWithValue ("?eval", variables["Evaluation"]);
      comm.Parameters.AddWithValue ("?fail", variables["FailValue"]);
      comm.Parameters.AddWithValue ("?warn", variables["WarnValue"]);
      comm.Parameters.AddWithValue ("?aggreg_func", variables["Aggregration_Func"]);

      int utid = dba.execute_mysql_scalar (comm);
      
      // Insert all log formats
      string[] formats = (string [])variables["Formats"];
      foreach (string lfid in formats)
        insert_unit_test_log_format (utid, Int32.Parse(lfid));

      // Insert all relations
      if (formats.Length > 1)
      {
        Pair[] relations = (Pair [])variables["Relations"];
        foreach (Pair relation in relations)
          insert_unit_test_relation (utid, relation.First.ToString (), relation.Second.ToString ());
      }
    }

    /**
     * Used to insert an existing unit test into an existing test
     *   package. 
     * 
     * @param[in]     package_id    The id of the existing test package.
     * @param[in]     unit_test_id  The id of the existing unit test. 
     */
    public static void insert_existing_unit_test (string package_id, string unit_test_id)
    {
      string sql = "CALL insert_package_unit_test(?p_id,?ut_id);";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?p_id", package_id);
      comm.Parameters.AddWithValue ("?ut_id", unit_test_id);
      dba.execute_mysql (comm);
    }

    /**
     * Used to create a new test suite (which naturally inserts 
     *   it into the database).
     * 
     * @param[in] test_suite_name   The name of the test suite to
     *                                be created.
     */
    public static void insert_test_suite (string test_suite_name)
    {
      string sql = "CALL insert_test_suite(?name);";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?name", test_suite_name);
      dba.execute_mysql (comm);
    }

    /**
     * Used to create a new test package (which naturally inserts
     *   it into the database).
     * 
     * @param[in]   test_package_name    The name of the test package to be created.
     */
    public static void create_test_package (string test_package_name)
    {
      string sql = "CALL create_test_package (?name);";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?name", test_package_name);
      dba.execute_mysql (comm);
    }

    /** 
     * Used to create a new test pacakge, and then insert it into 
     *   the given test suite. 
     * 
     * @param[in]  test_suite_id    The id of the test suite that the 
     *                                new test pacakge should be inserted
     *                                into. 
     * @param[in]  pacakge_name     The name to give the new test package. 
     */
    public static void insert_new_package (string test_suite_id, string package_name)
    {
      string sql = "CALL insert_test_suite_package(?tsid,?p_name);";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?tsid", test_suite_id);
      comm.Parameters.AddWithValue ("?p_name", package_name);
      dba.execute_mysql (comm);
    }

    /** 
     * Used to insert an existing test package into an existing
     *   test suite.
     * 
     * @param[in]  test_suite_id    The id of the existing test suite. 
     * @param[in]  package_id       The id of the existing test package.
     */
    public static void insert_existing_package (string test_suite_id, string package_id)
    {
      string sql = "CALL insert_test_suite_package_existing(?tsid,?p_id);";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?tsid", test_suite_id);
      comm.Parameters.AddWithValue ("?p_id", package_id);
      dba.execute_mysql (comm);
    }


    /**
     * Used to evaluate a unit test. This function is now a 'back-end'
     *   function, and probably needs to be updated and cleaned up some!
     * 
     * @param[in]  test_number    The test number that we would like to 
     *                              evaluate the unit test on - this is 
     *                              basically a filter to remove the 
     *                              unit test results that apply to an
     *                              unwanted unit test. 
     * @param[in]  utid           The id of the existing unit test. 
     * @param[in]  aggregrate     A bool that determines whether
     *                              the full results are returned, 
     *                              or if the results are aggregrated 
     *                              down to one number. 
     */
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

        UnitTestActions.create_variable_table (test_number, utid, ref vtable);

        dsa.create_table_in_database (vtable.data);
        dsa.populate_table_in_database (vtable.data);

        //  // Preload the database with the valid table. Each log format for the given
        //  // test will have its own table.
        //  PreLoad_UT (test_number, utid);

        MySqlCommand command = dba.get_command ("");
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
        command = dba.get_command (sql_result);
        return dba.execute_mysql_adapter (command);
      }
      catch (Exception ex)
      {
        throw ex;
      }
      finally
      {
        // Make sure we remove the data from the database.
        dsa.remove_table (vtable.data.TableName);
      }
    }

    /**
     * Used to evaluate a unit test for one test. Note that this
     *   can already be accomplished with the evaluate_unit_test
     *   function, so ideally this should be refactored to just
     *   call that function, or this funciton should be removed. 
     * 
     * @param[in]  utid         The id fo the unit test to evaluate. 
     * @param[in]  test_number  The number of the test to evaluate the 
     *                            unit test against. 
     */
    public static DataTable evalate_unit_test_for_single_test (int utid, int test_number)
    {
      try
      {
      //  // Preload the database with the valid table. Each log format for the given
      //  // test will have its own table.
      //  PreLoad_UT (test_number, utid);

        MySqlCommand command = dba.get_command ("");
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

    
    /**
     * James H. commented this out - I am assuming it was either 
     *   buggy or unused but still has some valuable information. 
     * I would speak with him as to what should be done with it. 
     */
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

    /**
     * Used to evaluate a unit test, filter it down to one test number,
     *   and then return the unaggregrated results so they can be charted. 
     *   Note that this can all be done with the evaluate_unit_test funtion, 
     *   so this should either be refactored to use that one, or should be
     *   deleted entirely. 
     * 
     * @param[in]   utid          The id of the unit test to evaluate. 
     * @param[in]   test_number   The number of the test to evaluate the 
     *                              unit test against. 
     */
    public static DataTable evalate_unit_test_as_metric (int utid, int test_number)
    {
      try
      {

        preload_unit_test (test_number, utid);
        string sql = "CALL evaluate_unit_test_as_metric(?utid,?test_number);";

        MySqlCommand command = dba.get_command (sql);
        command.Parameters.AddWithValue ("?utid", utid);
        command.Parameters.AddWithValue ("?test_number", test_number);

        DataTable dt = dba.execute_mysql_adapter (command);
        return dt;
      }
      catch (Exception ex) { throw ex; }
      finally { unload_unit_test (utid); }
    }

    /**
     * Return all of the test suites currently in the 
     *   database. Uses no stored procedure. 
     */
    public static DataTable get_all_test_suites ()
    {
      string sql = "SELECT * FROM test_suites;";
      DataTable dt = dba.execute_mysql_adapter (sql);
      return dt;
    }


    /** 
     * Used to delete a test suite from the database, which will 
     *   also remove any information about packages that were in 
     *   the test suite (but will not delete those packages!).
     * 
     * @param[in]  test_suite_id    The id of the test suite to delete. 
     */
    public static void delete_test_suite (string test_suite_id)
    {
      string sql = "DELETE FROM cuts.test_suites WHERE id=?t_id;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?t_id", test_suite_id);
      dba.execute_mysql (comm);
    }

    /** 
     * Used to delete a test package from the database, which will 
     *   also remove and information about unit tests that were 
     *   contained in the test pacakge (but will not remove those
     *   unit tests!). 
     * 
     * @param[in]  package_id     The id of the test pacakge to remove.
     */
    public static void delete_test_package (string package_id)
    {
      string sql = "DELETE FROM cuts.packages WHERE id=?p_id;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?p_id", package_id);
      dba.execute_mysql (comm);
    }

    /**
     * Used to get the name of all the test suites that contain 
     *   the provided package. This is useful for error reporting,
     *   aka when someone tries to remove a test pacakge that is still
     *   contained in test suites this can be used to print a list of 
     *   the affected test suites. 
     * 
     * @param[in]  package_id  The id of the package that is still 
     *                           contained in some test suites. 
     */
    public static DataTable containing_test_suites ( string package_id )
    {
      string sql = "SELECT name FROM test_suites WHERE id IN " + 
        "(SELECT DISTINCT id FROM test_suite_packages WHERE p_id=?p_id);";
      MySqlCommand comm = dba.get_command( sql );
      comm.Parameters.AddWithValue( "?p_id", package_id );
      DataTable dt = dba.execute_mysql_adapter( comm );
      return dt;
    }

    /**
     * Used to remove an already inserted test pacakge from a test
     *   suite that it is inserted into. This may throw an error if the 
     *   package is not actually inserted into the test suite (this behavior
     *   should be checked for, and corrected if found. This should NOT
     *   throw an error in that case, it should just quietly return.
     * 
     * @param[in] test_suite_id     The id of the test suite to remove the 
     *                                test package from. 
     * @param[in] package_id        The id of the test package to be removed. 
     */
    public static void remove_package (string test_suite_id, string package_id)
    {
      string sql = "DELETE FROM cuts.test_suite_packages WHERE " +
                    "id=?ts_id AND p_id=?p_id_in;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?ts_id", test_suite_id);
      comm.Parameters.AddWithValue ("?p_id_in", package_id);
      dba.execute_mysql (comm);
    }

    /**
     * Used to delete a unit test from the database.
     * 
     * @param[in]  unit_test_id   The id of the unit test to 
     *                              be removed. 
     */
    public static void delete_unit_test (string unit_test_id)
    {
      string sql = "DELETE FROM cuts.unit_tests WHERE utid=?ut_id;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?ut_id", unit_test_id);
      dba.execute_mysql (comm);
    }

    /**
     * Used to remove a unit test from a test package that it 
     *   is inserted into. 
     * 
     * @param[in]  package_id     The id of the test package that 
     *                              contains the unit test. 
     * @param[in]  unit_test_id   The id of the unit test to be removed.
     */
    public static void remove_unit_test (string package_id, string unit_test_id)
    {
      string sql = "DELETE FROM cuts.package_unit_tests WHERE " +
                    "id=?p_id AND ut_id=?ut_id_in;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?p_id", package_id);
      comm.Parameters.AddWithValue ("?ut_id_in", unit_test_id);
      dba.execute_mysql (comm);
    }

    /**
     * Used to get a list of the names and ids of all the 
     *   test packages currently in the database. 
     */
    public static DataTable get_all_packages ()
    {
      string sql = "SELECT * FROM packages";
      DataTable dt = dba.execute_mysql_adapter (sql);
      return dt;
    }

    /**
     * Used to get a list of the names and ids
     *   of all unit tests currently in the system. 
     */
    public static DataTable get_all_unit_tests ()
    {
      string sql = "SELECT * FROM unit_tests;";
      DataTable dt = dba.execute_mysql_adapter (sql);
      return dt;
    }

    /**
     * Used to get a list of the names and ids of 
     *   all the test packages contained in the 
     *   given test suite. 
     * 
     * @param[in] test_suite_id   The id of the test suite. 
     */
    public static DataTable get_packages (string test_suite_id)
    {
      string sql = "SELECT packages.id as id,name " +
                   "FROM packages,test_suite_packages AS tsp " +
                   "WHERE tsp.id =?ts_id AND tsp.p_id = packages.id;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?ts_id", test_suite_id);
      DataTable dt = dba.execute_mysql_adapter (comm);
      return dt;
    }

    /**
     * Used to get all messages generated by a test. Returns
     *   the host IDs, message times, message severities, and 
     *   actual messages. 
     * 
     * @param[in] test_number   The number of the test you would like 
     *                            to retrieve the log messages for. 
     */
    public static DataTable get_test_messages ( string test_number )
    {
      string sql = "SELECT hostid, msgtime AS message_time,severity," +
        "message FROM msglog WHERE test_number=?tid;";
      MySqlCommand comm = dba.get_command( sql );
      comm.Parameters.AddWithValue( "?tid", test_number );
      DataTable dt = dba.execute_mysql_adapter( comm );
      return dt;
    }


    /**
     * Used to get the names and ids of all the unit 
     *   tests contained in a test package. 
     * 
     * @param[in]  package_id   The id of the containing test package. 
     */
    public static DataTable get_unit_tests (string package_id)
    {
      string sql = "SELECT utid AS id, name " +
                   "FROM unit_tests AS utd,package_unit_tests AS put " +
                   "WHERE put.id=?p_id AND put.ut_id=utd.utid;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?p_id", package_id);
      DataTable dt = dba.execute_mysql_adapter (comm);
      return dt;
    }

    /**
     * Used to get all one to one info for a unit test (Ex: name, desc, etc).  
     * 
     * @param[in]  unit_test_id   The id of the unit test. 
     */
    public static DataRow get_unit_test_info (string unit_test_id)
    {
      string sql = "SELECT * " +
                   "FROM unit_tests " +
                   "WHERE utid=?utid_in LIMIT 1;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?utid_in", unit_test_id);
      DataRow dr = dba.execute_mysql_row (comm);
      return dr;
    }

    /**
     * Used to get all one to one info for a test package (Ex: name, desc, etc.).
     * 
     * @param[in]   package_id    The id of the test pacakge. 
     */
    public static DataRow get_package_info ( string package_id )
    {
      string sql = "SELECT id,name FROM packages WHERE id=?pid LIMIT 1;";
      MySqlCommand comm = dba.get_command( sql );
      comm.Parameters.AddWithValue( "?pid", package_id );
      DataRow dr = dba.execute_mysql_row( comm );
      return dr;
    }

    /**
     * This was used in conjunction with preload_unit_test
     *   to remove all of the tables that would have been 
     *   created with the evaluation of a unit test. This function
     *   is probably outdated with the new back-end, and needs to 
     *   be safely removed. 
     * 
     * @param[in]  utid  The id of the unit test that was evaluated. 
     */
    private static void unload_unit_test (int utid)
    {
      if (dsa == null)
        dsa = new DataSetActions (dba, utid);

      Array LFIDs = LogFormatActions.LogFormatActions.get_log_format_ids (utid);
      foreach (int CurrentLFID in LFIDs)
        dsa.remove_table ("LF" + CurrentLFID.ToString ());
    }

    /**
     * Used to create the variable table to evaluate a unit test with. 
     *   Created by James H, so he might have a better description. 
     * 
     * @param[in]  test    The number of the test to be evaluated against.
     * @param[in]  utid    The id of the unit test to be evaluated. 
     * @param[ref] vtable  The CUTS.Variable_Table to be filled with the 
     *                       variables. 
     */
    private static void create_variable_table (int test, int utid, ref CUTS.Variable_Table vtable)
    {
      DataSet ds = new DataSet ();

      MySqlCommand command = dba.get_command ("");
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
        dba.get_command ("CALL cuts.select_log_data_by_test (?test, ?lfid)");

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

    /**
     * Used to prepare the database for evaluation of a unit test. 
     *   This is a legacy function with the new back-end, and should be 
     *   safely removed. 
     * 
     * @param[in]  test   The test number the unit test will be evaluated 
     *                      against.
     * @param[in]  utid   The id of the unit test to be evaulated. 
     */
    private static void preload_unit_test (int test, int utid)
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

      Array LFIDs = LogFormatActions.LogFormatActions.get_log_format_ids (utid);

      foreach (int CurrentLFID_u in LFIDs)
      {
        int CurrentLFID = Int32.Parse (CurrentLFID_u.ToString ());

        // get the regex and the variable info
        string cs_regex;
        Hashtable VariableNames;
        LogFormatActions.LogFormatActions.get_log_format_info (out cs_regex, out VariableNames, CurrentLFID);

        /* create a table for this log format
         *   Note this needs to take a hash for variables */
        string TableName = "LF" + CurrentLFID.ToString ();
        dsa.add_table (TableName, VariableNames);

        dsa.fill_table (test, CurrentLFID, cs_regex, VariableNames);
      }

      dsa.send_to_database ();
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

    /**
     * Used to insert an existing log format into an existing unit test. 
     * 
     * @param[in]   utid    The id of the unit test. 
     * @param[in]   lfid    The id of the log format. 
     */
    private static void insert_unit_test_log_format (int utid, int lfid)
    {
      string sql = "CALL insert_unit_test_log_format (?utid, ?lfid);";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?utid", utid);
      comm.Parameters.AddWithValue ("?lfid", lfid);
      dba.execute_mysql (comm);
    }

    /** 
     * Used to insert a relationship into a unit test. This is always 
     *   an equality relation, aka var1 == var2. For each log format
     *   n > 1, there must be a relation equating any prior n to the 
     *   current n (normally, n-1 and n are related, so format 2 would
     *   reference format 1, 3 would ref. 2, etc. ).
     * 
     * @param[in]  utid     The id of the unit test the relation will be in. 
     * @param[in]  rel1     The id of the first variable. 
     * @param[in]  rel2     The id of the second variable. 
     */
    private static void insert_unit_test_relation (int utid, string rel1, string rel2)
    {
      string sql = "CALL insert_unit_test_relation(?utid, ?var1,?var2)";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?utid", utid);
      comm.Parameters.AddWithValue ("?var1", rel1);
      comm.Parameters.AddWithValue ("?var2", rel2);
      dba.execute_mysql (comm);
    }


    /**
     * Class that is used in the evaluation of a unit test. This is now a 
     *   'back-end' item, so James will know if this class is still being 
     *   being used, or if it should be safely removed. 
     * 
     * The class has methods for easily manipulating a dataset to work with 
     *   evaluating unit tests. 
     */
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
       * @param[in]  table_name   The name of the table to be created. This
       *                            should be similar to 'LF5', following the
       *                            format of concat(LF,lfid).
       * @param[in]  column_info  This should be the information needed to
       *                            build the columns, aka a hastable with
       *                            keys that are the column/variable names,
       *                            and objects that are the column/variable
       *                            types.
       */
      public void add_table (string table_name, Hashtable column_info)
      {
        DataTable table = new DataTable (table_name);

        // Create an indexer for the data value. This will be used to uniquely
        // identify all the variables in a single evaluation across many log
        // messages.
        table.Columns.Add (new DataColumn ("rowid", typeof (System.Int32)));

        // The test number should always be a column.
        table.Columns.Add (new DataColumn ("test_number", typeof (System.Int32)));

        string[] keys = new string[column_info.Count];
        column_info.Keys.CopyTo (keys, 0);

        foreach (string column_name in keys)
        {
          DataColumn dc = new DataColumn (column_name);

          // Find the appropriate type
          switch (column_info[column_name].ToString ())
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
        if (ds_.Tables.Contains (table_name))
          ds_.Tables.Remove (table_name);

        ds_.Tables.Add (table);
      }

      /**
       * Used to safely remove a table from the database.
       * 
       * @param[in] table_name   The name of the table to be removed. 
       */
      public void remove_table (string table_name)
      {
        string sql = "DROP TABLE IF EXISTS " + table_name + ";";
        dba.execute_mysql (sql);
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
      public void fill_table (int test, int lfid, string cs_regex, Hashtable variables)
      {
        // Get the actual log messages and test_numbers
        string sql = "CALL get_log_data_by_test (?test, ?lfid);";
        MySqlCommand comm = dba.get_command (sql);
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
          DataRow new_row = get_row (TableName);

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
          insert_row (TableName, new_row);
        }
      }

      /** 
       * Used to send the created dataset back to the main database for
       *   faster evaluation. Probably a legacy function that can be 
       *   safely removed. 
       */
      public void send_to_database ()
      {
        create_tables_in_database ();

        foreach (DataTable table in ds_.Tables)
          this.populate_table_in_database (table);
      }

      /**
       * Used to easily call the asp NewRow() function on a table in the 
       *   dataset. 
       * 
       * @param[in]  table_name  The name of the table in the dataset
       *                           to get a new row for. 
       */
      private DataRow get_row (string table_name)
      {
        return ds_.Tables[table_name].NewRow ();
      }

      /** 
       * Used to easily add a row to the specified table in the
       *   dataset. 
       * 
       * @param[in]  table_name   The name of the table in the 
       *                            dataset to insert the row into. 
       * @param[in]  new_row      The DataRow to insert.
       */
      private void insert_row (string table_name, DataRow new_row)
      {
        ds_.Tables[table_name].Rows.Add (new_row);
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

        dba.execute_mysql (sql);
      }

      /**
       * Used to automatically send the entire dataset to the 
       *   database. This function calls create_table_in_database,
       *   so is probably also a removeable legacy func. 
       */
      private void create_tables_in_database ()
      {
        foreach (DataTable table in ds_.Tables)
          this.create_table_in_database (table);
      }

      /**
       * Used to send all of the data in a particular DataTable
       *   in the dataset into its corresponding table in the 
       *   main database. This is probably legacy code and should
       *   be removed. 
       * 
       * @param[in]  table  The DataTable to send to the database. 
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

        dba.execute_mysql (sql_insert);
      }

    } // End private class DataSetActions
  } // End Class UnitTestActions
} // End Actions.UnitTestActions