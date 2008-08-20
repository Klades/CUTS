/**
 * @file        LogFormatActions.cs
 *
 * Defines the Actions.LogFormatActions code.
 *
 * @author      Hamilton Turner
 */
using System;
using System.Data;
using System.Collections;
using System.Configuration;
using MySql.Data.MySqlClient;


namespace Actions.LogFormatActions
{
  /**
   * @class LogformatActions
   *
   * Handles typical DataBase actions related to log formats, which
   *   are mainly insertion and selection. This class needs updates!!!
   * 
   * Updates needed: The private static dba variable should be updated/
   *   changed. The database connection should not be a static variable!
   *   See the CUTS.Data code to see how to change this so it uses an
   *   interface. The class needs to be moved out from Actions namespace
   *   and somewhere into the appropriate CUTS namespace. THe class needs
   *   to have the static quantifier removed. 
   */
  public static class LogFormatActions
  {
    /**
     * @var  DataBaseActions dba
     * Contains a reference to the standard Database Actions library
     */
    private static DataBaseActions.DataBaseActions dba =
      new DataBaseActions.DataBaseActions (ConfigurationManager.AppSettings["MySQL"]);

    /**
     * Method to insert a Log Format. Uses sql procedure insert_log_format
     *
     * @param[in]       log_format       The LF to be inserted.
     * @param[in]       icase_regex      The MySql case-insensitive regular
     *                                     expression used to find matching
     *                                     LF's in the msglog table.
     * @param[in]       cs_regex         The C Sharp regular expression used
     *                                     to extract the variable in C#.
     * @param[in]       vars             An hashtable containing the variable
     *                                     names as keys, and types as values.
     */
    public static void insert_log_format (string log_format, string icase_regex, string cs_regex, Hashtable vars)
    {

      string sql = "CALL insert_log_format(?lf, ?icase_regex, ?cs_regex);";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?lf", log_format);
      comm.Parameters.AddWithValue ("?icase_regex", icase_regex);
      comm.Parameters.AddWithValue ("?cs_regex", cs_regex);

      int lfid = dba.execute_mysql_scalar (comm);

      // Itera
      string[] keys = new string[vars.Count];
      vars.Keys.CopyTo (keys, 0);
      foreach (string key in keys)
        insert_log_format_variable (lfid, key, vars[key].ToString ());
    }

    /**
     * Adds a single variable for a Log Format. SubFunction of Insert_LF.
     *   Note that this uses MySql procedure insert_log_format_variable.
     *
     * @param[in]  lfid       The ID of the Log Format the variable belongs to.
     * @param[in]  varname    The name of the variable.
     */
    private static void insert_log_format_variable (int lfid, string varname, string vartype)
    {
      string sql = "CALL insert_log_format_variable(?lfid,?varname,?vartype);";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?lfid", lfid);
      comm.Parameters.AddWithValue ("?varname", varname);
      comm.Parameters.AddWithValue ("?vartype", vartype);
      dba.execute_mysql (comm);
    }

    /**
     * Returns all data from log_formats table. For now, this does not
     *   use a stored procedure in MySql. This should be changed to a
     *   stored proc sometime soon.
     */
    public static DataTable get_all_log_formats ()
    {
      string sql = "SELECT * FROM log_formats";
      return dba.execute_mysql_adapter (sql);
    }

    /**
     * Returns all the Log Format Ids that are used in any given Unit Test.
     *   For now, this is not using a MySql stored procedure. This should be
     *   changed soon.
     *
     * @param[in]  utid    The ID of the Unit Test referenced.
     */
    public static Array get_log_format_ids (int utid)
    {
      string sql = "SELECT lfid FROM unit_test_log_formats WHERE utid=?utid_in;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?utid_in", utid);

      MySqlDataReader r = comm.ExecuteReader ();
      ArrayList al = new ArrayList ();

      while (r.Read ())
      {
        al.Add (Int32.Parse (r[0].ToString ()));
      }
      r.Close ();

      return al.ToArray ();
    }

    /**
     * Given a Unit Test ID, return all the Log Format info (IDs and
     *   the Log Formats) for that Unit Test.
     *
     * @param[in] unit_test_id   The ID of the referenced Unit Test
     */
    public static DataTable get_log_formats (string unit_test_id)
    {
      string sql = "SELECT lfd.lfid,lfmt " +
                   "FROM log_formats AS lfd,unit_test_log_formats AS utt " +
                   "WHERE utt.lfid=lfd.lfid and utt.utid=?utid_in;";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?utid_in", unit_test_id);
      DataTable dt = dba.execute_mysql_adapter (comm);
      return dt;
    }


    /**
     * Given a Log Format ID, this returns info about that
     *   Log Format, including the cs_regex and a list of variable names.
     *   Note that this needs to be updated to return variable types and names.
     *   Note that this uses MySql Stored Procedure select_log_format_information.
     *
     * @param[out] cs_regex     The string you would like the C Sharp regular
     *                            expression to be stored into.
     * @param[out] vars         A hashtable that will contain the variable
     *                            names as keys, and types as values.
     * @param[in]  lfid         The ID of the Log Format referenced.
     */
    public static void get_log_format_info (out string cs_regex, out Hashtable vars, int lfid)
    {
      string sql = @"CALL select_log_format_information( ?lfid );";
      MySqlCommand comm = dba.get_command (sql);
      comm.Parameters.AddWithValue ("?lfid", lfid);

      DataTable dt = dba.execute_mysql_adapter (comm);

      cs_regex = dt.Rows[0]["csharp_regex"].ToString ();

      // Fills in the variables
      vars = new Hashtable ();

      foreach (DataRow row in dt.Rows)
        vars.Add (row["varname"], row["vartype"]);
    }

    /**
     * Given an array of log format ids, this function
     *   will iterate through those and delete the log 
     *   formats identified. 
     * 
     * @param[in]  format_ids  The int[] of log format ids.
     */
    public static void delete_log_formats (int[] format_ids)
    {
      string sql = "DELETE FROM cuts.log_formats WHERE lfid = ?id";
      MySqlCommand command = dba.get_command (sql);

      // Create the parameter for the command.
      MySqlParameter p1 = command.CreateParameter ();
      p1.ParameterName = "?id";
      p1.DbType = DbType.Int32;

      // Insert the parameter into the command.
      command.Parameters.Add (p1);

      foreach (int id in format_ids)
      {
        // Set the parameter's value.
        p1.Value = id;

        // Prepare and execute the command.
        command.Prepare ();
        command.ExecuteNonQuery ();
      }
    }
  }
}