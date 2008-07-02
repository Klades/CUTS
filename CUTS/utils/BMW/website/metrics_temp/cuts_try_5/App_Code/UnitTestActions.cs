using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Linq;
using System.Text.RegularExpressions;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using MySql.Data.MySqlClient;
using LogVariables;

namespace Actions
{
    /// <summary>
    /// Perform insertion and evaluation of 
    /// UnitTests
    /// </summary>
    public class UnitTestActions
    {
        public void Insert_UT(Hashtable Variables)
        {
            string sql = @"CALL Insert_UT('" +
                Variables["Name"] + "','" + 
                Variables["Description"] + "','" + 
                Variables["FailComparison"] + "','" + 
                Variables["WarnComparison"] + "','" + 
                Variables["Evaluation"] + "','" + 
                Variables["FailValue"] + "','" + 
                Variables["WarnValue"] + "');";

            object obj = ExecuteMySqlScalar(sql);
            int utid = Int32.Parse(obj.ToString());

            
            
            foreach (string lfid in (Array)Variables["LFIDs"])
                Insert_UT_LogFormat(utid, lfid);

            foreach (string VariableID in (Array)Variables["Groups"])
                Insert_UT_Group(utid, VariableID);

            foreach (DictionaryEntry entry in (Hashtable)Variables["Aggregrations"])
                Insert_UT_Aggregration(utid, entry.Key.ToString(), entry.Value.ToString());
        }

        public void Eval_UT(int utid)
        {
            Eval_UT(utid, "UT");
        }

        public void Eval_UT(int utid, string mode)
        {
            /*
             * 
             * 1) create temp dataset
             * 2) put all messages in temp dataset
             * 3) push temp back to real DB 
             * 4) create select statement
             * 
             * */

            DataSetActions dsa = DataSetActions.getInstance(utid);

            Array LFIDs = GetLFIDs(utid);
            foreach (int CurrentLFID in LFIDs.Cast<int>())
            {
                // get the regex and the variable info
                string cs_regex;
                Array VariableNames;
                GetLFIDInfo(out cs_regex, out VariableNames, CurrentLFID);

                /* create a table for this log format 
                 *   Note this needs to take a hash for variables */
                string TableName = "LF" + CurrentLFID.ToString(); 
                dsa.AddTable(TableName, VariableNames);
                
                dsa.FillTable(CurrentLFID, cs_regex, VariableNames);

            }

            dsa.SendToDB();

            if (mode == "metric")
                CreateSelectMetric(utid);
            else
                CreateSelectUT(utid);
        }

        private void CreateSelectMetric(int utid)
        {
            string sql = @"SELECT evaluation FROM unittestdesc WHERE utid='" + utid.ToString() + "';";
            object obj = ExecuteMySqlScalar(sql);
            string evaluation = obj.ToString();

            Regex reg = new Regex(@"(?<variable>lf(?<lfid>\d+)\.(?<varname>\w+))", RegexOptions.IgnoreCase);
            Match mat = reg.Match(evaluation);

            while (mat.Success)
            {
                string LFID = mat.Groups["lfid"].ToString();
                string VarName = mat.Groups["varname"].ToString();
                string OldVariable = mat.Groups["variable"].ToString();

                sql = @"CALL GetVariableAggregration('" +
                    LFID + "','" +
                    VarName + "');";

                Array function = ExecuteMySqlReader(sql, "Function");
                string Function = function.GetValue(0).ToString();

                Array extendedVarName = ExecuteMySqlReader(sql, "ExtendedName");
                string ExtendedVarName = extendedVarName.GetValue(0).ToString();

                string NewVariable = CreateFunctionAggregration(Function, ExtendedVarName);
                evaluation = Regex.Replace(evaluation, OldVariable, NewVariable);                

                mat = mat.NextMatch();
            }


            sql = @"SELECT `TestID`,(" + evaluation + ") as result FROM ";
            
            Array LFIDs = GetLFIDs(utid);
            foreach (string CurrentLFID in LFIDs.Cast<string>())
            {
                sql += "LF" + CurrentLFID + ",";
            }
            sql = sql.Remove(sql.LastIndexOf(","));

            sql += " Group by TestID;";

        }

        private void CreateSelectUT(int utid)
        {
        }

        private string CreateFunctionAggregration(string Function, string ExtendedVarName)
        {
            if (Function == "SUM")
                return "SUM(" + ExtendedVarName + ")";

            // default to sum
            return "SUM(" + ExtendedVarName + ")";
        }

        private void Insert_UT_Aggregration(int utid, string VariableID, string AggregrationFunction)
        {
            string sql = @"CALL Insert_UT_Aggregration('" +
                utid.ToString() + "','" +
                VariableID + "','" +
                AggregrationFunction + "');";
            ExecuteMySql(sql);
        }
        private void Insert_UT_Group(int UTID, string VariableID)
        {
            string sql = @"CALL Insert_UT_Group('" +
                UTID.ToString() + "','" +
                VariableID + "');";
            ExecuteMySql(sql);
        }
        private void Insert_UT_LogFormat(int utid, string lfid)
        {
            string sql = @"CALL Insert_UT_LogFormat('" +
                    utid.ToString() + "','" +
                    lfid + "');";
            ExecuteMySql(sql);
        }

        // helper function for eval_ut to simplify getting lfids given utid
        private Array GetLFIDs(int utid)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationSettings.AppSettings["connString"]);
            conn.Open();
            MySqlCommand comm = new MySqlCommand("SELECT lfid FROM unittesttable WHERE utid=" + utid.ToString(), conn);
            MySqlDataReader r = comm.ExecuteReader();
            ArrayList al = new ArrayList();

            while (r.Read())
            {
                al.Add(r[0]);
            }
            r.Close();
            conn.Close();
            
            return al.ToArray();
        }

        // helper function for eval_ut to get info needed to 
        //    1) extract the data from the log messages
        //    2) generate the internal datatable
        private void GetLFIDInfo(out string cs_regex, out Array vars, int lfid)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationSettings.AppSettings["connString"]);
            conn.Open();

            string sql = @"CALL Get_LFID_info('" + lfid.ToString() + "');";
            MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
            DataSet ds = new DataSet();
            da.Fill(ds, "lfid_info");
            conn.Close();

            cs_regex = @ds.Tables[0].Rows[0]["csharp_regex"].ToString();

            ArrayList v = new ArrayList();
            foreach (DataRow row in ds.Tables[0].Rows)
            {
                v.Add(row["varname"]);

                //Remember to remove returning this from the procedure
                //extend_v.Add(row["extended_varname"]);
            }

            vars = v.ToArray();
        }

        private void ExecuteMySql(string sql)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationSettings.AppSettings["connString"]);
            MySqlCommand comm = new MySqlCommand(sql, conn);
            conn.Open();
            comm.ExecuteNonQuery();
            conn.Close();

        }

        private object ExecuteMySqlScalar(string sql)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationSettings.AppSettings["connString"]);
            MySqlCommand comm = new MySqlCommand(sql, conn);
            conn.Open();
            object obj = comm.ExecuteScalar();
            conn.Close();
            return obj;
        }

        private Array ExecuteMySqlReader(string sql, string ColumnName)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationSettings.AppSettings["connString"]);
            MySqlCommand comm = new MySqlCommand(sql, conn);
            conn.Open();
            MySqlDataReader r = comm.ExecuteReader();
            
            ArrayList al = new ArrayList();
            while (r.Read())
                al.Add(r[ColumnName].ToString());
            
            conn.Close();
            return al.ToArray();
        }
        
        private DataTable ExecuteMySqlAdapter(string sql)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationSettings.AppSettings["connString"]);
            conn.Open();
            
            MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
            DataSet ds = new DataSet();
            da.Fill(ds);
            
            conn.Close();
            return ds.Tables[0];
        } 
    }
}