using System;
using System.Collections;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using MySql.Data.MySqlClient;

/// <summary>
/// . Summary description for Actions
/// . This is a base class for performing
///     actions on log formats, unittests,
///     and charts
/// . This mostly handles DB actions
/// </summary>
/// 

namespace Actions
{
    /// <summary>
    /// Perform insertion and deletion
    /// of LogFormats
    /// </summary>
    public class LogFormatActions
    {
        private string connString;

        public LogFormatActions()
        {
            this.connString = ConfigurationSettings.AppSettings["connString"];
        }

        public void Insert_LF(string log_form, string icase_regex, string cs_regex, Array vars)
        {
            MySqlConnection conn = new MySqlConnection(connString);
            string sql = @"CALL Insert_LF('" + log_form + "','" + icase_regex + "','" + cs_regex + "');";

            object obj = ExecuteMySqlScalar(sql);
            int lfid = Int32.Parse(obj.ToString());

            foreach (string var in vars)
                Insert_LF_variable(lfid,var);
        }

        private void Insert_LF_variable(int lfid,string varname)
        {
            // Need to add support for more than INT
            
            string sql = @"CALL Insert_LF_variable('"+ 
                lfid.ToString() + "','" + 
                varname + "','int');";

            ExecuteMySql(sql);
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

    }   
}