using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using LogVariables;
using MySql.Data.MySqlClient;
using System.Text.RegularExpressions;

namespace Actions
{
    /// <summary>
    /// Perform actions on the main DataSet
    /// that is used for evaluation, aggregrations,
    /// ect
    /// </summary>
    public sealed class DataSetActions
    {
        private static DataSetActions instance = null;
        private static readonly object padlock = new object();

        private DataSet ds_;
        private static int utid_;
        private Array grouped_x_;
        private Array grouped_z_;


        private DataSetActions()
        {
            ds_ = new DataSet();
        }

        public static DataSetActions getInstance(int utid)
        {
            lock (padlock)
            {
                if (instance == null || utid_ != utid)
                {
                    utid_ = utid;
                    instance = new DataSetActions();
                }
                return instance;
            }
        }

        public DataSet Set
        {
            get
            {
                return ds_;
            }
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
        public void AddTable(string tableName, Array columnInfo)
        {
            DataTable dt_ = new DataTable(tableName);
            foreach (string columnName in columnInfo)
            {
                dt_.Columns.Add(new DataColumn(columnName, System.Type.GetType("System.Int32")));
            }

            // test_number should always be a column
            dt_.Columns.Add(new DataColumn("test_number", System.Type.GetType("System.Int32")));

            // This is to fix a bug in visual studio where the ds_ tables are
            // maintained inside the temp directory and so the add
            // will throw an exception (across two different builds)
            if (ds_.Tables.Contains(tableName))
                ds_.Tables.Remove(tableName);
            
            ds_.Tables.Add(dt_);
        }

        public void FillTable(int lfid, string cs_regex, Array varnames)
        {            
            // Get the actual log messages and test_numbers
            string sql = @"CALL Get_log_data('" + 
                lfid.ToString() + "');";
            DataTable dt_ = ExecuteMySqlAdapter(sql);

            /*   Iterate over each Row
             *   Regex the data out
             *   Put the Data into the DataSet 
             */
            
            // Note: need to add in support for different types

            string TableName = "LF" + lfid.ToString();
            

            foreach (DataRow row in dt_.Rows)
            {
                // Get the row to put data into
                DataRow NewRow = GetRow(TableName);

                Regex reg = new Regex(cs_regex, RegexOptions.IgnoreCase);
                Match mat = reg.Match(row["message"].ToString());

                foreach (string name in varnames)
                {
                    string value = mat.Groups[name].ToString();
                    int Value = Int32.Parse(value);
                    NewRow[name] = Value;
                }

                // There should always be a test_number
                NewRow["test_number"] = row["test_number"];
                
                InsertRow(TableName, NewRow);
            }
        }

        public void SendToDB()
        {
            CreateTablesInDB();

            foreach (DataTable table in ds_.Tables)
                SendTableToDB(table.TableName);
        }

        private DataRow GetRow(string TableName)
        {
            return ds_.Tables[TableName].NewRow();
        }

        private void InsertRow(string TableName, DataRow NewRow)
        {
            ds_.Tables[TableName].Rows.Add(NewRow);
        }

        private void CreateTablesInDB()
        {
            foreach (DataTable table in ds_.Tables)
            {
                string sql = "CREATE TABLE `" + table.TableName + "` (";
                foreach (DataColumn column in table.Columns)
                    sql += column.ColumnName + " INT,";
                
                
                sql = sql.Remove(sql.LastIndexOf(","));
                sql += ");";

                ExecuteMySql(sql);
            }
        }

        private void SendTableToDB(string TableName)
        {
            DataTable table = ds_.Tables[TableName];

            foreach (DataRow row in table.Rows)
            {
                string sql = "INSERT INTO `" + TableName + "` (";

                foreach (DataColumn column in table.Columns)
                    sql += column.ColumnName + ",";

                sql = sql.Remove(sql.LastIndexOf(","));
                sql += ") VALUES (";

                foreach (DataColumn column in table.Columns)
                    sql += "'" + row[column] + "',";

                sql = sql.Remove(sql.LastIndexOf(","));
                sql += ");";

                ExecuteMySql(sql);
            }
        }

        private void ExecuteMySql(string sql)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
            MySqlCommand comm = new MySqlCommand(sql, conn);
            conn.Open();
            comm.ExecuteNonQuery();
            conn.Close();
        
        }
        
        private DataTable ExecuteMySqlAdapter(string sql)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
            conn.Open();

            MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
            DataSet ds = new DataSet();
            da.Fill(ds);

            conn.Close();
            return ds.Tables[0];
        } 
    }
}