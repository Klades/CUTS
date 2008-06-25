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
            MySqlCommand comm = new MySqlCommand(sql,conn);
            conn.Open();
            
            int lfid = Int32.Parse(comm.ExecuteScalar().ToString());

            foreach (string var in vars)
            {
                Insert_LF_variable(lfid,var,conn);
            }

            conn.Close();
           
        }

        private void Insert_LF_variable(int lfid,string varname, MySqlConnection conn)
        {
            string sql = @"CALL Insert_LF_variable('"+ lfid.ToString() + "','" + varname + "','int','0');";
            MySqlCommand comm = new MySqlCommand(sql, conn);
            comm.ExecuteNonQuery();
        }
    }

    public class UnitTestActions
    {
        private string connString;

        public UnitTestActions()
        {
            this.connString = ConfigurationSettings.AppSettings["connString"];
        }

        public void Insert_UT(string name, string description, string fail_comp, string warn_comp, string fail, string warn,
            string eval, Array log_formats)
        {
            MySqlConnection conn = new MySqlConnection(connString);
            string sql = @"CALL Insert_UT('" + name + "','" + description + "','" + fail_comp + "','" + warn_comp + 
                "','" + eval + "','" + fail + "','" + warn + "');";
            MySqlCommand comm = new MySqlCommand(sql,conn);

            conn.Open();
            int utid = Int32.Parse(comm.ExecuteScalar().ToString());
            foreach (string lfid in log_formats)
            {
                Insert_UT_logformat(lfid, utid,conn);
            }

            conn.Close();
        }

        // helper func for Insert_UT
        private void Insert_UT_logformat(string lfid, int utid, MySqlConnection conn)
        {
            string sql = @"CALL Insert_UT_logformat('" + utid + "','" + lfid + "');";
            MySqlCommand comm = new MySqlCommand(sql, conn);
            comm.ExecuteNonQuery();
        }

        public void Eval_UT(int utid)
        {
            /*
             * 1) get all lfids for this unit test
             * 2) iterate over each lfid
             *      1) get csregex, extended_varnames, varnames, varytypers, grouped
             *      2) create table columns from extended_varnames (syntax LF1.varname)
             *      3) get all data that matches csregex
             *      4) iterate over data
             *              1) match regex to data
             *              2) foreach item in varnames array
             *                      1) match.groups[varname]
             *                      2) insert into table (extended varname, grouped, ect)
             *                
             * */
            MySqlConnection conn = new MySqlConnection(connString);
            conn.Open();
            
            Array lfids = get_lfids(utid, conn);
            foreach (string id in lfids)
            {
                string cs_regex;
                Array vars, extended_vars;
                get_lfid_info(out cs_regex,out vars,out extended_vars, id, conn);
                DataTableActions.Instance.Add_columns(extended_vars);

                DataTable dt;
                get_log_data(out dt, id, cs_regex, vars, conn);


            }
        }

        private void get_log_data(out DataTable dt, string lfid, string cs_regex, Array varnames, MySqlConnection conn)
        {
            
            
            // Get the actual messages
            string sql = @"CALL Get_log_data('" + lfid + "');";
            MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
            DataSet ds = new DataSet();
            da.Fill(ds, "logs");

            // Add a table definition to hold the data after regexing
            ds.Tables.Add(new DataTable("log_data"));
            foreach (string name in varnames)
            {
                ds.Tables["log_data"].Columns.Add(new DataColumn(name));
            }



        }

        // helper function for eval_ut to simplify getting lfids given utid
        private Array get_lfids(int utid,MySqlConnection conn)
        {
            MySqlCommand comm = new MySqlCommand("SELECT lfid FROM unittesttable WHERE utid=" + utid.ToString(), conn);
            MySqlDataReader r = comm.ExecuteReader();
            ArrayList al = new ArrayList();

            while (r.Read())
            {
                al.Add(r[0]);
            }

            return al.ToArray();
        }

        // helper function for eval_ut to get info needed to 
        //    1) extract the data from the log messages
        //    2) generate the internal datatable
        private void get_lfid_info(out string cs_regex,out Array vars, out Array extended_vars, string lfid, MySqlConnection conn)
        {
            string sql = @"CALL Get_LFID_info('" + lfid + "');";
            MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
            DataSet ds = new DataSet();
            da.Fill(ds,"lfid_info");

            cs_regex = ds.Tables[0].Rows[0]["csharp_regex"].ToString();

            ArrayList v = new ArrayList(), 
                      extend_v = new ArrayList();
            foreach (DataRow row in ds.Tables[0].Rows)
            {
                v.Add(row["varname"]);
                extend_v.Add(row["extended_varname"]);
            }

            vars = v.ToArray();
            extended_vars = extend_v.ToArray();
        }
    }

    public sealed class DataTableActions
    {
        private static readonly DataTableActions instance=new DataTableActions();
        private DataTable dt;
        // Explicit static constructor to tell C# compiler
        // not to mark type as beforefieldinit
        // Do not remove or will no longer be thread-safe
        static DataTableActions()
        {}
        private DataTableActions()
        {}

        public static DataTableActions Instance
        {
            get
            {
                return instance;
            }
        }

        // needs to have exceptions and column
        // types added
        public void Add_columns(Array colnames)
        {
            foreach(string name in colnames)
            {
                // Check for duplicate column/variable names
                if (dt.Columns.IndexOf(name) != -1)
                    // Need to throw exception here! Means there are two duplicate names
                    return;
                dt.Columns.Add(new DataColumn(name));
            }
        }

     }
}