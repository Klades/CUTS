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
      new DataBaseActions.DataBaseActions( ConfigurationManager.AppSettings["MySQL"] );
    private static DataSetActions dsa;

    public static void Insert_New_Unit_Test ( Hashtable Variables )
    {
      string sql = "CALL Insert_UT(?name,?desc,?fail_comp,?warn_comp,?eval,?fail,?warn,?aggreg_func);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?name", Variables["Name"] );
      comm.Parameters.AddWithValue( "?desc", Variables["Description"] );
      comm.Parameters.AddWithValue( "?fail_comp", Variables["FailComparison"] );
      comm.Parameters.AddWithValue( "?warn_comp", Variables["WarnComparison"] );
      comm.Parameters.AddWithValue( "?eval", Variables["Evaluation"] );
      comm.Parameters.AddWithValue( "?fail", Variables["FailValue"] );
      comm.Parameters.AddWithValue( "?warn", Variables["WarnValue"] );
      comm.Parameters.AddWithValue( "?aggreg_func", Variables["Aggregration_Func"] );

      int utid = dba.ExecuteMySqlScalar( comm );

      if ((bool)Variables["UsingBothLogFormats"] == true)
        Insert_UT_Relation( utid, (string)Variables["Relation_Variable_1"],
          (string)Variables["Relation_Variable_1"] );

      foreach (string lfid in (Array)Variables["LFIDs"])
        Insert_UT_LogFormat( utid, lfid );

      // Note Groups are disabled for now
      /* foreach (string VariableID in (Array)Variables["Groups"])
           Insert_UT_Group( utid, VariableID ); */
    }

    public static void Insert_Existing_Unit_Test ( string Package_ID_, string Unit_Test_ID_ )
    {
      string sql = "CALL insert_package_unit_test(?p_id,?ut_id);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?p_id", Package_ID_ );
      comm.Parameters.AddWithValue( "?ut_id", Unit_Test_ID_ );
      dba.ExecuteMySql( comm );
    }

    public static void Insert_Test_Suite ( string Test_Suite_Name_ )
    {
      string sql = "CALL insert_test_suite(?name);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?name", Test_Suite_Name_ );
      dba.ExecuteMySql( comm );
    }

    public static void Insert_New_Package ( string Test_Suite_ID_, string Package_Name_ )
    {
      string sql = "CALL insert_test_suite_package(?tsid,?p_name);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?tsid", Test_Suite_ID_ );
      comm.Parameters.AddWithValue( "?p_name", Package_Name_ );
      dba.ExecuteMySql( comm );
    }

    public static void Insert_Existing_Package ( string Test_Suite_ID_, string Package_ID_ )
    {
      string sql = "CALL insert_test_suite_package_existing(?tsid,?p_id);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?tsid", Test_Suite_ID_ );
      comm.Parameters.AddWithValue( "?p_id", Package_ID_ );
      dba.ExecuteMySql( comm );
    }

    public static DataTable Evalate_UT_for_single_test ( int utid, int test_number )
    {
      try
      {
        PreLoad_UT( utid );
        string sql = "CALL evaluate_unit_test_single(?utid, ?tnum);";

        MySqlCommand command = dba.GetCommand( sql );
        command.Parameters.AddWithValue( "?utid", utid );
        command.Parameters.AddWithValue( "?tnum", test_number );

        DataTable dt = dba.ExecuteMySqlAdapter( command );
        return dt;
      }
      catch (Exception ex) { throw ex; }
      finally { UnLoad_UT( utid ); }
    }

    public static DataTable Evaluate_UT_for_all_tests ( int utid )
    {
      try
      {
        PreLoad_UT( utid );
        string sql = "CALL evaluate_unit_test_full(?utid);";

        MySqlCommand command = dba.GetCommand( sql );
        command.Parameters.AddWithValue( "?utid", utid );

        DataTable dt = dba.ExecuteMySqlAdapter( command );
        return dt;
      }
      catch (Exception ex) { throw ex; }
      finally { UnLoad_UT( utid ); }
    }


    public static DataTable Evalate_UT_as_metric ( int utid, int test_number )
    {
      try
      {

        PreLoad_UT( utid );
        string sql = "CALL evaluate_unit_test_as_metric(?utid,?test_number);";

        MySqlCommand command = dba.GetCommand( sql );
        command.Parameters.AddWithValue( "?utid", utid );
        command.Parameters.AddWithValue( "?test_number", test_number );

        DataTable dt = dba.ExecuteMySqlAdapter( command );
        return dt;
      }
      catch (Exception ex) { throw ex; }
      finally { UnLoad_UT( utid ); }
    }

    public static DataTable Get_All_Test_Suites ()
    {
      string sql = "SELECT * FROM test_suites;";
      DataTable dt = dba.ExecuteMySqlAdapter( sql );
      return dt;
    }
    
    public static DataTable Get_All_Packages ()
    {
      string sql = "SELECT * FROM packages";
      DataTable dt = dba.ExecuteMySqlAdapter( sql );
      return dt;
    }

    public static DataTable Get_All_Unit_Tests ()
    {
      string sql = "SELECT * FROM unittestdesc;";
      DataTable dt = dba.ExecuteMySqlAdapter( sql );
      return dt;
    }

    public static DataTable Get_Packages (string Test_Suite_ID_)
    {
      string sql = "SELECT packages.id as id,name " + 
                   "FROM packages,test_suite_packages AS tsp " +
                   "WHERE tsp.id =?ts_id AND tsp.p_id = packages.id;";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?ts_id", Test_Suite_ID_ );
      DataTable dt = dba.ExecuteMySqlAdapter( comm );
      return dt;
    }
    
    public static DataTable Get_Unit_Tests ( string Package_ID_ )
    {
      string sql = "SELECT utid,name " +
                   "FROM unittestdesc AS utd,packages_unit_tests AS put " +
                   "WHERE put.id=?p_id AND put.ut_id=utd.utid;";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?p_id", Package_ID_);
      DataTable dt = dba.ExecuteMySqlAdapter( comm );
      return dt;
    }

    public static DataRow Get_Unit_Test_Info ( string Unit_Test_ID_ )
    {
      string sql = "SELECT * " +
                   "FROM unittestdesc " + 
                   "WHERE utid=?utid_in LIMIT 1;";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?utid_in", Unit_Test_ID_ );
      DataRow dr = dba.ExecuteMySqlRow( comm );
      return dr;    
    }

    private static void UnLoad_UT ( int utid )
    {
      if (dsa == null)
        dsa = new DataSetActions( dba, utid );

      Array LFIDs = LogFormatActions.LogFormatActions.GetLFIDs( utid );
      foreach (int CurrentLFID in LFIDs)
        dsa.RemoveTable( "LF" + CurrentLFID.ToString() );
    }

    private static void PreLoad_UT ( int utid )
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
        dsa = new DataSetActions( dba, utid );
      

      Array LFIDs = LogFormatActions.LogFormatActions.GetLFIDs( utid );

      foreach (int CurrentLFID_u in LFIDs)
      {
        int CurrentLFID = Int32.Parse( CurrentLFID_u.ToString() );
        
        // get the regex and the variable info
        string cs_regex;
        Array VariableNames;
        LogFormatActions.LogFormatActions.GetLFIDInfo( out cs_regex, out VariableNames, CurrentLFID );

        /* create a table for this log format
         *   Note this needs to take a hash for variables */
        string TableName = "LF" + CurrentLFID.ToString();
        dsa.AddTable( TableName, VariableNames );

        dsa.FillTable( CurrentLFID, cs_regex, VariableNames );
      }

      dsa.SendToDB();
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

    private static void Insert_UT_LogFormat ( int utid, string lfid )
    {
      string sql = "CALL Insert_UT_LogFormat(?utid,?lfid);";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?utid", utid );
      comm.Parameters.AddWithValue( "?lfid", lfid );
      dba.ExecuteMySql( comm );
    }

    private static void Insert_UT_Relation ( int utid, string rel1, string rel2 )
    {
      string sql = "CALL Insert_UT_Relation(?utid, ?var1,?var2)";
      MySqlCommand comm = dba.GetCommand( sql );
      comm.Parameters.AddWithValue( "?utid", utid );
      comm.Parameters.AddWithValue( "?var1", rel1 );
      comm.Parameters.AddWithValue( "?var2", rel2 );
      dba.ExecuteMySql( comm );
    }

    private class DataSetActions
    {
      private DataSet ds_;
      private Actions.DataBaseActions.DataBaseActions dba;
      private int utid_;

      public DataSetActions (Actions.DataBaseActions.DataBaseActions dba, int Unit_Test_ID_)
      {
        this.ds_ = new DataSet();
        this.dba = dba;
        this.utid_ = Unit_Test_ID_;
      }

      /// <summary>
      /// Adds a table that represents one
      /// LogFormat to the DataSet
      ///
      /// General use is AddTable, FillTables, Send_To_DB()
      ///
      /// Note: this needs to take in a Hash for
      /// columnInfo, so that we can have types
      /// other than int32
      /// </summary>
      public void AddTable ( string tableName, Array columnInfo )
      {
        DataTable dt_ = new DataTable( tableName );
        foreach (string columnName in columnInfo)
        {
          dt_.Columns.Add( new DataColumn( columnName, System.Type.GetType( "System.Int32" ) ) );
        }

        // test_number should always be a column
        dt_.Columns.Add( new DataColumn( "test_number", System.Type.GetType( "System.Int32" ) ) );

        // This is to fix a bug in visual studio where the ds_ tables are
        // maintained inside the temp directory and so the add
        // will throw an exception (across two different builds)
        if (ds_.Tables.Contains( tableName ))
          ds_.Tables.Remove( tableName );

        ds_.Tables.Add( dt_ );
      }

      public void RemoveTable ( string tableName )
      {
        string sql = "DROP TABLE IF EXISTS " + tableName + ";";
        dba.ExecuteMySql( sql );
      }

      public void FillTable ( int lfid, string cs_regex, Array varnames )
      {
        // Get the actual log messages and test_numbers
        string sql = "CALL Get_log_data(?lfid);";
        MySqlCommand comm = dba.GetCommand( sql );
        comm.Parameters.AddWithValue( "?lfid", lfid );
        DataTable dt_ = dba.ExecuteMySqlAdapter( comm );

        /*   Iterate over each Row
         *   Regex the data out
         *   Put the Data into the DataSet
         */

        // Note: need to add in support for different types

        string TableName = "LF" + lfid.ToString();


        foreach (DataRow row in dt_.Rows)
        {
          // Get the row to put data into
          DataRow NewRow = GetRow( TableName );

          Regex reg = new Regex( cs_regex, RegexOptions.IgnoreCase );
          Match mat = reg.Match( row["message"].ToString() );

          foreach (string name in varnames)
          {
            string value = mat.Groups[name].ToString();
            int Value = Int32.Parse( value );
            NewRow[name] = Value;
          }

          // There should always be a test_number
          NewRow["test_number"] = row["test_number"];

          InsertRow( TableName, NewRow );
        }
      }

      public void SendToDB ()
      {
        CreateTablesInDB();

        foreach (DataTable table in ds_.Tables)
          SendTableToDB( table.TableName );
      }

      private DataRow GetRow ( string TableName )
      {
        return ds_.Tables[TableName].NewRow();
      }

      private void InsertRow ( string TableName, DataRow NewRow )
      {
        ds_.Tables[TableName].Rows.Add( NewRow );
      }

      private void CreateTablesInDB ()
      {
        foreach (DataTable table in ds_.Tables)
        {
          string sql = "CREATE TABLE `" + table.TableName + "` (";
          foreach (DataColumn column in table.Columns)
            sql += column.ColumnName + " INT,";


          sql = sql.Remove( sql.LastIndexOf( "," ) );
          sql += ");";

          dba.ExecuteMySql( sql );
        }
      }

      private void SendTableToDB ( string TableName )
      {
        DataTable table = ds_.Tables[TableName];

        foreach (DataRow row in table.Rows)
        {
          string sql = "INSERT INTO `" + TableName + "` (";

          foreach (DataColumn column in table.Columns)
            sql += column.ColumnName + ",";

          sql = sql.Remove( sql.LastIndexOf( "," ) );
          sql += ") VALUES (";

          foreach (DataColumn column in table.Columns)
            sql += "'" + row[column] + "',";

          sql = sql.Remove( sql.LastIndexOf( "," ) );
          sql += ");";

          dba.ExecuteMySql( sql );
        }
      }


    } // End private class DataSetActions

  } // End Class UnitTestActions

} // End Actions.UnitTestActions