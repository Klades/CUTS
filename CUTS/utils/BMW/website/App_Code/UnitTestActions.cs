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
  public class UnitTestActions
  {
    /**
    * @var  DataBaseActions this.dba_
    * Contains a reference to the standard Database Actions library
    */
    private DataBaseActions.DataBaseActions dba_ =
      new DataBaseActions.DataBaseActions (ConfigurationManager.AppSettings["MySQL"]);

    /**
     * Used to insert a brand new unit test. Uses SQL procedure
     *   insert_unit_test.
     *
     * @param[in]   variables   A Hashtable of all of the variables
     *                            needed to create a unit test.
     */
    public void insert_new_unit_test (Hashtable properties)
    {
      MySqlTransaction transaction = this.dba_.Connection.BeginTransaction ();

      try
      {
        // Prepare SQL
        string sql = "CALL insert_unit_test(?name,?desc,?fail_comp,?warn_comp," +
          "?eval,?fail,?warn,?aggreg_func);";
        MySqlCommand comm = this.dba_.get_command (sql);

        // Add parameters
        comm.Parameters.AddWithValue ("?name", properties["Name"]);
        comm.Parameters.AddWithValue ("?desc", properties["Description"]);
        comm.Parameters.AddWithValue ("?fail_comp", properties["FailComparison"]);
        comm.Parameters.AddWithValue ("?warn_comp", properties["WarnComparison"]);
        comm.Parameters.AddWithValue ("?eval", properties["Evaluation"]);
        comm.Parameters.AddWithValue ("?fail", properties["FailValue"]);
        comm.Parameters.AddWithValue ("?warn", properties["WarnValue"]);
        comm.Parameters.AddWithValue ("?aggreg_func", properties["Aggregration_Func"]);

        int utid = this.dba_.execute_mysql_scalar (comm);

        // Insert all log formats
        int[] formats = (int[])properties["Formats"];

        foreach (int lfid in formats)
          this.insert_unit_test_log_format (utid, lfid);

        // Insert all relations
        if (formats.Length > 1)
        {
          CUTS.Data.Relation [] relations = (CUTS.Data.Relation[])properties["Relations"];

          for (int i = 0; i < relations.Length; ++ i)
            this.insert_unit_test_relation (utid, i, relations[i].LeftValues, relations[i].RightValues);
        }

        // Commit this transaction to the database.
        transaction.Commit ();
      }
      catch (Exception)
      {
        // Rollback the changes during this transaction.
        transaction.Rollback ();
        throw;
      }
    }

    /**
     * Used to insert an existing unit test into an existing test
     *   package.
     *
     * @param[in]     package_id    The id of the existing test package.
     * @param[in]     unit_test_id  The id of the existing unit test.
     */
    public void insert_existing_unit_test (string package_id, string unit_test_id)
    {
      string sql = "CALL insert_package_unit_test(?p_id,?ut_id);";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?p_id", package_id);
      comm.Parameters.AddWithValue ("?ut_id", unit_test_id);

      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to create a new test suite (which naturally inserts
     *   it into the database).
     *
     * @param[in] test_suite_name   The name of the test suite to
     *                                be created.
     */
    public void insert_test_suite (string test_suite_name)
    {
      string sql = "CALL insert_test_suite(?name);";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?name", test_suite_name);

      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to create a new test package (which naturally inserts
     *   it into the database).
     *
     * @param[in]   test_package_name    The name of the test package to be created.
     */
    public void create_test_package (string test_package_name)
    {
      string sql = "CALL create_test_package (?name);";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?name", test_package_name);

      this.dba_.execute_mysql (comm);
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
    public void insert_new_package (string test_suite_id, string package_name)
    {
      string sql = "CALL insert_test_suite_package(?tsid,?p_name);";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?tsid", test_suite_id);
      comm.Parameters.AddWithValue ("?p_name", package_name);

      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to insert an existing test package into an existing
     *   test suite.
     *
     * @param[in]  test_suite_id    The id of the existing test suite.
     * @param[in]  package_id       The id of the existing test package.
     */
    public void insert_existing_package (string test_suite_id, string package_id)
    {
      string sql = "CALL insert_test_suite_package_existing(?tsid,?p_id);";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?tsid", test_suite_id);
      comm.Parameters.AddWithValue ("?p_id", package_id);

      this.dba_.execute_mysql (comm);
    }

    /**
     * Return all of the test suites currently in the
     *   database. Uses no stored procedure.
     */
    public DataTable get_all_test_suites ()
    {
      string sql = "SELECT * FROM test_suites;";
      DataTable dt = this.dba_.execute_mysql_adapter (sql);
      return dt;
    }


    /**
     * Used to delete a test suite from the database, which will
     *   also remove any information about packages that were in
     *   the test suite (but will not delete those packages!).
     *
     * @param[in]  test_suite_id    The id of the test suite to delete.
     */
    public void delete_test_suite (string test_suite_id)
    {
      string sql = "DELETE FROM cuts.test_suites WHERE id=?t_id;";
      MySqlCommand comm = this.dba_.get_command (sql);
      comm.Parameters.AddWithValue ("?t_id", test_suite_id);
      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to delete a test package from the database, which will
     *   also remove and information about unit tests that were
     *   contained in the test pacakge (but will not remove those
     *   unit tests!).
     *
     * @param[in]  package_id     The id of the test pacakge to remove.
     */
    public void delete_test_package (string package_id)
    {
      string sql = "DELETE FROM cuts.packages WHERE id=?p_id;";
      MySqlCommand comm = this.dba_.get_command (sql);
      comm.Parameters.AddWithValue ("?p_id", package_id);
      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to get the name of all the test suites that contain
     * the provided package. This is useful for error reporting,
     * aka when someone tries to remove a test pacakge that is still
     * contained in test suites this can be used to print a list of
     * the affected test suites.
     *
     * @param[in]  package_id  The id of the package that is still
     *                           contained in some test suites.
     */
    public DataTable containing_test_suites (string package_id)
    {
      string sql = "SELECT name FROM test_suites WHERE id IN " +
        "(SELECT DISTINCT id FROM test_suite_packages WHERE p_id=?p_id);";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?p_id", package_id);
      DataTable dt = this.dba_.execute_mysql_adapter (comm);

      return dt;
    }

    /**
     * Used to remove an already inserted test pacakge from a test
     * suite that it is inserted into. This may throw an error if the
     * package is not actually inserted into the test suite (this behavior
     * should be checked for, and corrected if found. This should NOT
     * throw an error in that case, it should just quietly return.
     *
     * @param[in] test_suite_id     The id of the test suite to remove the
     *                                test package from.
     * @param[in] package_id        The id of the test package to be removed.
     */
    public void remove_package (string test_suite_id, string package_id)
    {
      string sql = "DELETE FROM cuts.test_suite_packages WHERE " +
                    "id=?ts_id AND p_id=?p_id_in;";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?ts_id", test_suite_id);
      comm.Parameters.AddWithValue ("?p_id_in", package_id);

      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to delete a unit test from the database.
     *
     * @param[in]  unit_test_id   The id of the unit test to
     *                              be removed.
     */
    public void delete_unit_test (string unit_test_id)
    {
      string sql = "DELETE FROM cuts.unit_tests WHERE utid=?ut_id;";
      MySqlCommand comm = this.dba_.get_command (sql);
      comm.Parameters.AddWithValue ("?ut_id", unit_test_id);
      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to remove a unit test from a test package that it
     *   is inserted into.
     *
     * @param[in]  package_id     The id of the test package that
     *                              contains the unit test.
     * @param[in]  unit_test_id   The id of the unit test to be removed.
     */
    public void remove_unit_test (string package_id, string unit_test_id)
    {
      string sql = "DELETE FROM cuts.package_unit_tests WHERE " +
                    "id=?p_id AND ut_id=?ut_id_in;";
      MySqlCommand comm = this.dba_.get_command (sql);
      comm.Parameters.AddWithValue ("?p_id", package_id);
      comm.Parameters.AddWithValue ("?ut_id_in", unit_test_id);
      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to get a list of the names and ids of all the
     *   test packages currently in the database.
     */
    public DataTable get_all_packages ()
    {
      string sql = "SELECT * FROM packages";
      DataTable dt = this.dba_.execute_mysql_adapter (sql);
      return dt;
    }

    /**
     * Used to get a list of the names and ids
     *   of all unit tests currently in the system.
     */
    public DataTable get_all_unit_tests ()
    {
      string sql = "SELECT * FROM unit_tests;";
      DataTable dt = this.dba_.execute_mysql_adapter (sql);
      return dt;
    }

    /**
     * Used to get a list of the names and ids of
     *   all the test packages contained in the
     *   given test suite.
     *
     * @param[in] test_suite_id   The id of the test suite.
     */
    public DataTable get_packages (string test_suite_id)
    {
      string sql = "SELECT packages.id as id,name " +
                   "FROM packages,test_suite_packages AS tsp " +
                   "WHERE tsp.id =?ts_id AND tsp.p_id = packages.id;";
      MySqlCommand comm = this.dba_.get_command (sql);
      comm.Parameters.AddWithValue ("?ts_id", test_suite_id);
      DataTable dt = this.dba_.execute_mysql_adapter (comm);
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
    public DataTable get_test_messages (string test_number)
    {
      string sql = "SELECT hostid, msgtime AS message_time,severity," +
        "message FROM msglog WHERE test_number=?tid;";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?tid", test_number);

      DataTable dt = this.dba_.execute_mysql_adapter (comm);
      return dt;
    }


    /**
     * Used to get the names and ids of all the unit
     *   tests contained in a test package.
     *
     * @param[in]  package_id   The id of the containing test package.
     */
    public DataTable get_unit_tests (string package_id)
    {
      string sql = "SELECT utid AS id, name " +
                   "FROM unit_tests AS utd,package_unit_tests AS put " +
                   "WHERE put.id=?p_id AND put.ut_id=utd.utid;";
      MySqlCommand comm = this.dba_.get_command (sql);
      comm.Parameters.AddWithValue ("?p_id", package_id);
      DataTable dt = this.dba_.execute_mysql_adapter (comm);
      return dt;
    }

    /**
     * Used to get all one to one info for a unit test (Ex: name, desc, etc).
     *
     * @param[in]  unit_test_id   The id of the unit test.
     */
    public DataRow get_unit_test_info (string unit_test_id)
    {
      string sql = "SELECT * " +
                   "FROM unit_tests " +
                   "WHERE utid=?utid_in LIMIT 1;";
      MySqlCommand comm = this.dba_.get_command (sql);
      comm.Parameters.AddWithValue ("?utid_in", unit_test_id);
      DataRow dr = this.dba_.execute_mysql_row (comm);
      return dr;
    }

    /**
     * Used to get all one to one info for a test package (Ex: name, desc, etc.).
     *
     * @param[in]   package_id    The id of the test pacakge.
     */
    public DataRow get_package_info (string package_id)
    {
      string sql = "SELECT id,name FROM packages WHERE id=?pid LIMIT 1;";
      MySqlCommand comm = this.dba_.get_command (sql);
      comm.Parameters.AddWithValue ("?pid", package_id);
      DataRow dr = this.dba_.execute_mysql_row (comm);
      return dr;
    }

    /**
     * Used to insert an existing log format into an existing unit test.
     *
     * @param[in]   utid    The id of the unit test.
     * @param[in]   lfid    The id of the log format.
     */
    private void insert_unit_test_log_format (int utid, int lfid)
    {
      string sql = "CALL insert_unit_test_log_format (?utid, ?lfid);";
      MySqlCommand comm = this.dba_.get_command (sql);

      comm.Parameters.AddWithValue ("?utid", utid);
      comm.Parameters.AddWithValue ("?lfid", lfid);

      this.dba_.execute_mysql (comm);
    }

    /**
     * Used to insert a relationship into a unit test. This is always an equality
     * relation, aka var1 == var2. For each log format n > 1, there must be a relation
     * equating any prior n to the current n (normally, n-1 and n are related, so
     * format 2 would reference format 1, 3 would ref. 2, and etc).
     *
     * @param[in]  utid     The id of the unit test the relation will be in.
     * @param[in]  rel1     The id of the first variable.
     * @param[in]  rel2     The id of the second variable.
     */
    private void insert_unit_test_relation (int utid, int relid, object [] cause, object [] effect)
    {
      // Initialize the command statement.
      string sql = "CALL insert_unit_test_relation (?utid, ?relid, ?index, ?cause, ?effect)";
      MySqlCommand comm = this.dba_.get_command (sql);

      // Prepare the parameters for the statement.
      MySqlParameter p_utid = comm.CreateParameter ();
      p_utid.DbType = DbType.Int32;
      p_utid.ParameterName = "?utid";
      p_utid.Value = utid;
      comm.Parameters.Add (p_utid);

      MySqlParameter p_relid = comm.CreateParameter ();
      p_relid.DbType = DbType.Int32;
      p_relid.ParameterName = "?relid";
      p_relid.Value = relid;
      comm.Parameters.Add (p_relid);

      MySqlParameter p_index = comm.CreateParameter ();
      p_index.DbType = DbType.Int32;
      p_index.ParameterName = "?index";
      comm.Parameters.Add (p_index);

      MySqlParameter p_cause = comm.CreateParameter ();
      p_cause.DbType = DbType.Int32;
      p_cause.ParameterName = "?cause";
      comm.Parameters.Add (p_cause);

      MySqlParameter p_effect = comm.CreateParameter ();
      p_effect.DbType = DbType.Int32;
      p_effect.ParameterName = "?effect";
      comm.Parameters.Add (p_effect);

      // Get the length of the relations.
      int length = cause.Length;

      for (int i = 0; i < length; ++i)
      {
        // Update the value for the parameters.
        p_index.Value = i;
        p_cause.Value = cause[i];
        p_effect.Value = effect[i];

        // Execute the statement.
        this.dba_.execute_mysql (comm);
      }
    }
  }
}