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
            MySqlCommand comm = new MySqlCommand(sql, conn);

            conn.Open();
            int utid = Int32.Parse(comm.ExecuteScalar().ToString());
            foreach (string lfid in log_formats)
            {
                Insert_UT_logformat(lfid, utid, conn);
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
            foreach (int current_lfid in lfids.Cast<int>())
            {
                string cs_regex;
                Array vars;
                get_lfid_info(out cs_regex, out vars, current_lfid, conn);



                get_log_data(current_lfid, cs_regex, vars, conn, utid);
            }

        }

        private void get_log_data(int lfid, string cs_regex, Array varnames, MySqlConnection conn, int utid)
        {
            // Get the actual messages
            string sql = @"CALL Get_log_data('" + lfid.ToString() + "');";
            MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
            DataSet ds = new DataSet();
            da.Fill(ds, "logs");

            // Regex the data out
            foreach (DataRow row in ds.Tables["logs"].Rows)
            {
                Regex reg = new Regex(cs_regex, RegexOptions.IgnoreCase);
                Match mat = reg.Match(row["message"].ToString());

                foreach (string xname in LogVariables.LogVariables.getInstance(utid).Grouped_On_X)
                {
                    foreach (string zname in LogVariables.LogVariables.getInstance(utid).Grouped_On_Z)
                    {
                        // This will not currently work

                        foreach (string name in varnames)
                        {
                            DataTableActions.getInstance(utid).insert(mat.Groups[name].ToString(), "LF" + lfid.ToString() + "." + name);
                        }
                    }
                }

                                
                

            }
        }

        // helper function for eval_ut to simplify getting lfids given utid
        private Array get_lfids(int utid, MySqlConnection conn)
        {
            MySqlCommand comm = new MySqlCommand("SELECT lfid FROM unittesttable WHERE utid=" + utid.ToString(), conn);
            MySqlDataReader r = comm.ExecuteReader();
            ArrayList al = new ArrayList();

            while (r.Read())
            {
                al.Add(r[0]);
            }
            r.Close();

            return al.ToArray();
        }

        // helper function for eval_ut to get info needed to 
        //    1) extract the data from the log messages
        //    2) generate the internal datatable
        private void get_lfid_info(out string cs_regex, out Array vars, int lfid, MySqlConnection conn)
        {
            string sql = @"CALL Get_LFID_info('" + lfid.ToString() + "');";
            MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
            DataSet ds = new DataSet();
            da.Fill(ds, "lfid_info");

            cs_regex = ds.Tables[0].Rows[0]["csharp_regex"].ToString();

            ArrayList v = new ArrayList();
            foreach (DataRow row in ds.Tables[0].Rows)
            {
                v.Add(row["varname"]);

                //Remember to remove returning this from the procedure
                //extend_v.Add(row["extended_varname"]);
            }

            vars = v.ToArray();
        }
    }
}