using System;
using System.Collections;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
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
  /**
   * Hamilton:
   *
   * Same comment as in UnitTestActions.aspx.cs WRT to the singleton.
   * Right now there is a STRONG coupling bewteen the database and the
   * processing. Instead, you should let the page calling these methods
   * be the Bridge between this database and this code.
   */
  public class LogFormatActions
    {
        private string connString;

        public LogFormatActions()
        {
            this.connString = ConfigurationManager.AppSettings["MySQL"];
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
            MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
            MySqlCommand comm = new MySqlCommand(sql, conn);
            conn.Open();
            comm.ExecuteNonQuery();
            conn.Close();
        }

        private object ExecuteMySqlScalar(string sql)
        {
            MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
            MySqlCommand comm = new MySqlCommand(sql, conn);
            conn.Open();
            object obj = comm.ExecuteScalar();
            conn.Close();
            return obj;
        }

    }
}