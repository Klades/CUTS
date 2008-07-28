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
   * are mainly insertion and selection.
   * 
   */
  public static class LogFormatActions
  {
    /**
     * @var  DataBaseActions dba
     * Contains a reference to the standard Database Actions library
     */
    private static DataBaseActions.DataBaseActions dba =
      new DataBaseActions.DataBaseActions( ConfigurationManager.AppSettings["MySQL"] );

    /**
     * Method to insert a Log Format. Uses sql procedure Insert_LF
     * 
     * @param[in]       log_format       The LF to be inserted. 
     * @param[in]       icase_regex      The MySql case-insensitive regular
     *                                     expression used to find matching
     *                                     LF's in the msglog table.
     * @param[in]       cs_regex         The C Sharp regular expression used
     *                                     to extract the variable in C#.
     * @param[in]       vars             An array containing the names of 
     *                                     the variables that were found in 
     *                                     the LF. Note: This needs to be 
     *                                     updated so that you can pass in 
     *                                     name/type pairs, which will 
     *                                     be integral for types other than
     *                                     integer. 
     */
    public static void Insert_LF ( string log_format, string icase_regex, string cs_regex, Array vars )
    {

      string sql = "CALL Insert_LF(?lf, ?icase_regex, ?cs_regex);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?lf", log_format );
      comm.Parameters.AddWithValue( "?icase_regex", icase_regex );
      comm.Parameters.AddWithValue( "?cs_regex", cs_regex );

      int lfid = dba.ExecuteMySqlScalar( sql );

      foreach (string var in vars)
        Insert_LF_variable( lfid, var );
    }

    /**
     * Adds a single variable for a Log Format. SubFunction of Insert_LF.
     * Note that this uses MySql procedure Inser_LF_Variable. NOTE - THIS
     * NEEDS TO BE UPDATED TO ADD IN VARIABLE TYPE FOR TYPES OTHER THAN 
     * INTEGER.
     * 
     * @param[in]  lfid       The ID of the Log Format the variable belongs to.
     * @param[in]  varname    The name of the variable.
     */
    private static void Insert_LF_variable ( int lfid, string varname )
    {
      // Need to add support for more than INT

      string sql = "CALL Insert_LF_variable(?lfid,?varname,?vartype);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?lfid", lfid );
      comm.Parameters.AddWithValue( "?varname", varname );
      comm.Parameters.AddWithValue( "?vartype", "int" );
      dba.ExecuteMySql( sql );
    }

    /**
     * Returns all data from logformatdesc table. For now, this does not
     * use a stored procedure in MySql. This should be changed to a 
     * stored proc sometime soon. 
     */
    public static DataTable Get_All_Log_Formats ()
    {
      string sql = "SELECT * FROM logformatdesc";
      return dba.ExecuteMySqlAdapter( sql );
    }

    /**
     * Returns all the Log Format Ids that are used in any given Unit Test.
     * For now, this is not using a MySql stored procedure. This should be
     * changed soon. 
     * 
     * @param[in]  utid    The ID of the Unit Test referenced. 
     */
    public static Array GetLFIDs ( int utid )
    {
      string sql = "SELECT lfid FROM unittesttable WHERE utid=?utid_in;";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?utid_in", utid );

      MySqlDataReader r = comm.ExecuteReader();
      ArrayList al = new ArrayList();

      while (r.Read())
      {
        al.Add( Int32.Parse( r[0].ToString() ) );
      }
      r.Close();

      return al.ToArray();
    }
    
    /**
     * Given a Unit Test ID, return all the Log Format info (IDs and 
     * the Log Formats) for that Unit Test.
     * 
     * @param[in] Unit_Test_ID_   The ID of the referenced Unit Test
     */
    public static DataTable Get_Log_Formats ( string Unit_Test_ID_ )
    {
      string sql = "SELECT lfd.lfid,lfmt " +
                   "FROM logformatdesc AS lfd,unittesttable AS utt " +
                   "WHERE utt.lfid=lfd.lfid and utt.utid=?utid_in;"; 
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?utid_in", Unit_Test_ID_);
      DataTable dt = dba.ExecuteMySqlAdapter( comm );
      return dt;
    }


    /**
     * Given a Log Format ID, this returns info about that 
     * Log Format, including the cs_regex and a list of variable names.
     * Note that this needs to be updated to return variable types and names.
     * Note that this uses MySql Stored Procedure Get_LFID_Info, and the 
     * procedure needs to be updated not to return extended_varname and to 
     * return vartype.
     *
     * @param[out] cs_regex     The string you would like the C Sharp regular
     *                            expression to be stored into. 
     * @param[out] vars         The array you would like the variable names to 
     *                            be stored into. 
     * @param[in]  lfid         The ID of the Log Format referenced.
     */
    public static void GetLFIDInfo ( out string cs_regex, out Array vars, int lfid )
    {
      string sql = @"CALL Get_LFID_info( ?lfid );";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?lfid", lfid );

      DataTable dt = dba.ExecuteMySqlAdapter( comm );

      cs_regex = dt.Rows[0]["csharp_regex"].ToString();

      ArrayList v = new ArrayList();
      foreach (DataRow row in dt.Rows)
      {
        v.Add( row["varname"] );

        //Remember to remove returning this from the procedure
        //extend_v.Add(row["extended_varname"]);
      }
      vars = v.ToArray();
    }

  }
}