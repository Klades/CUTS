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

      if ((bool)Variables["is_using_both_log_formats"] == true)
        Insert_UT_Relation (utid, (string)Variables["Relation_Variable_1"],
          (string)Variables["Relation_Variable_2"]);

      foreach (string lfid in (Array)Variables["LFIDs"])
        Insert_UT_LogFormat (utid, lfid);

      // Note Groups are disabled for now
      /* foreach (string VariableID in (Array)Variables["Groups"])
           Insert_UT_Group( utid, VariableID ); */
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

    public static DataTable Evalate_UT_for_single_test (int utid, int test_number)
    {
      try
      {
        PreLoad_UT (utid);
        string sql = "CALL evaluate_unit_test_single(?utid, ?tnum);";

        MySqlCommand command = dba.GetCommand (sql);
        command.Parameters.AddWithValue ("?utid", utid);
        command.Parameters.AddWithValue ("?tnum", test_number);

        DataTable dt = dba.execute_mysql_adapter (command);
        return dt;
      }
      catch (Exception ex)
      {
        throw ex;
      }
      finally
      {
        UnLoad_UT (utid);
      }
    }

    public static DataTable Evaluate_UT_for_all_tests (int utid)
    {
      try
      {
        PreLoad_UT (utid);
        string sql = "CALL evaluate_unit_test_full(?utid);";

        MySqlCommand command = dba.GetCommand (sql);
        command.Parameters.AddWithValue ("?utid", utid);

        DataTable dt = dba.execute_mysql_adapter (command);
        return dt;
      }
      catch (Exception ex) { throw ex; }
      finally { UnLoad_UT (utid); }
    }


    public static DataTable Evalate_UT_as_metric (int utid, int test_number)
    {
      try
      {

        PreLoad_UT (utid);
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
      string sql = "DELETE FROM cuts.unittestdesc WHERE utid=?ut_id;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?ut_id", Unit_Test_ID_);
      dba.ExecuteMySql (comm);
    }

    public static void Remove_Unit_Test (string Package_ID_, string Unit_Test_ID_)
    {
      string sql = "DELETE FROM cuts.packages_unit_tests WHERE " +
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
      string sql = "SELECT * FROM unittestdesc;";
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
      string sql = "SELECT utid,name " +
                   "FROM unittestdesc AS utd,packages_unit_tests AS put " +
                   "WHERE put.id=?p_id AND put.ut_id=utd.utid;";
      MySqlCommand comm = dba.GetCommand (sql);
      comm.Parameters.AddWithValue ("?p_id", Package_ID_);
      DataTable dt = dba.execute_mysql_adapter (comm);
      return dt;
    }

    public static DataRow Get_Unit_Test_Info (string Unit_Test_ID_)
    {
      string sql = "SELECT * " +
                   "FROM unittestdesc " +
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

    private static void PreLoad_UT (int utid)
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

        dsa.FillTable (CurrentLFID, cs_regex, VariableNames);
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
      string sql = "CALL Insert_UT_LogFormat(?utid,?lfid);";
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
        DataTable dt_ = new DataTable (tableName);

        string[] keys = new string[columnInfo.Count];
        columnInfo.Keys.CopyTo (keys, 0);
        foreach (string column_name in keys)
        {
          DataColumn dc = new DataColumn (column_name);

          // Find the appropriate type
          switch (columnInfo[column_name].ToString ())
          {
            case "INT":
              dc.DataType = Type.GetType ("System.Int32");
              break;
            case "STRING":
              dc.DataType = Type.GetType ("System.String");
              break;
          }

          dt_.Columns.Add (dc);
        }

        // test_number should always be a column
        dt_.Columns.Add (new DataColumn ("test_number", System.Type.GetType ("System.Int32")));

        // This is to fix a bug in visual studio where the ds_ tables are
        // maintained inside the temp directory and so the add
        // will throw an exception (across two different builds)
        if (ds_.Tables.Contains (tableName))
          ds_.Tables.Remove (tableName);

        ds_.Tables.Add (dt_);
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
      public void FillTable (int lfid, string cs_regex, Hashtable variables)
      {
        // Get the actual log messages and test_numbers
        string sql = "CALL Get_log_data(?lfid);";
        MySqlCommand comm = dba.GetCommand (sql);
        comm.Parameters.AddWithValue ("?lfid", lfid);
        DataTable dt_ = dba.execute_mysql_adapter (comm);

        /*   Iterate over each Row
         *   Regex the data out
         *   Put the Data into the DataSet
         */

        string TableName = "LF" + lfid.ToString ();


        foreach (DataRow row in dt_.Rows)
        {
          // Get the row to put data into
          DataRow NewRow = GetRow (TableName);

          Regex reg = new Regex (cs_regex, RegexOptions.IgnoreCase);
          Match mat = reg.Match (row["message"].ToString ());

          string[] variable_names = new string[variables.Count];
          variables.Keys.CopyTo (variable_names, 0);

          if (mat.Success == false)
            throw new Exception ("The log message '" + row["message"].ToString () +
              "' was matched by the DataBase engine, but was not matched by " +
              " the C# Regular Expression of '" + cs_regex + "'. ");
          foreach (string varname in variable_names)
          {
            // Get the type associated with the current column
            Type type = this.ds_.Tables[TableName].Columns[varname].DataType;
            switch (type.ToString ())
            {
              case "System.Int32":
                NewRow[varname] = Int32.Parse (mat.Groups[varname].ToString ());
                break;
              case "System.String":
                NewRow[varname] = mat.Groups[varname].ToString ();
                break;
            }
          }


          // There should always be a test_number
          NewRow["test_number"] = row["test_number"];

          InsertRow (TableName, NewRow);
        }
      }

      public void SendToDB ()
      {
        CreateTablesInDB ();

        foreach (DataTable table in ds_.Tables)
          SendTableToDB (table.TableName);
      }

      private DataRow GetRow (string TableName)
      {
        return ds_.Tables[TableName].NewRow ();
      }

      private void InsertRow (string TableName, DataRow NewRow)
      {
        ds_.Tables[TableName].Rows.Add (NewRow);
      }

      private void CreateTablesInDB ()
      {
        foreach (DataTable table in ds_.Tables)
        {
          string sql = "CREATE TABLE `" + table.TableName + "` (";
          foreach (DataColumn column in table.Columns)
            sql += column.ColumnName + " INT,";


          sql = sql.Remove (sql.LastIndexOf (","));
          sql += ");";

          dba.ExecuteMySql (sql);
        }
      }

      private void SendTableToDB (string TableName)
      {
        DataTable table = ds_.Tables[TableName];

        foreach (DataRow row in table.Rows)
        {
          string sql = "INSERT INTO `" + TableName + "` (";

          foreach (DataColumn column in table.Columns)
            sql += column.ColumnName + ",";

          sql = sql.Remove (sql.LastIndexOf (","));
          sql += ") VALUES (";

          foreach (DataColumn column in table.Columns)
            sql += "'" + row[column] + "',";

          sql = sql.Remove (sql.LastIndexOf (","));
          sql += ");";

          dba.ExecuteMySql (sql);
        }
      }


    } // End private class DataSetActions

  } // End Class UnitTestActions

} // End Actions.UnitTestActions