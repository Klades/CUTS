using System;
using System.Data;
using System.Collections;
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
/// Summary description for Class1
/// </summary>
namespace LogVariables
{
    public sealed class LogVariables
    {
        private static LogVariables instance = null;
        private static readonly object padlock = new object();

        private static Hashtable ht_;
        private static Array grouped_x_;
        private static Array grouped_z_;
        private static int utid_ = 1;

        private LogVariables()
        {
            // gets the variable into
            MySqlConnection conn = new MySqlConnection(ConfigurationSettings.AppSettings["connString"]);
            MySqlDataAdapter da = new MySqlDataAdapter("CALL Get_UTID_vars('" + utid_.ToString() + "')", conn);
            DataSet ds = new DataSet();
            conn.Open();
            da.Fill(ds, "variables");
            conn.Close();

            ht_ = new Hashtable();

            foreach (DataRow row in ds.Tables["variables"].Rows)
            {
                // Optionally, we could also save the
                // aggregration stuff in variable
                string name = row["varname"].ToString(),
                    extended_name = row["extended_varname"].ToString();
                bool grouped_on_x = Boolean.Parse(row["grouped_on_x"].ToString()),
                    grouped_on_z = Boolean.Parse(row["grouped_on_z"].ToString());
                
                SingleVariable t = new SingleVariable(name, extended_name, "int", grouped_on_x, grouped_on_z);
                ht_.Add(extended_name,t);
            }

            // If there are no groups, create a groupd on TestID
            if (Grouped_On_X.Length == 0 && Grouped_On_Z.Length == 0)
                ht_.Add("TestID",new SingleVariable("TestID","TestID","int",true,false));

            
            // setup grouped on x array
            ArrayList al = new ArrayList();
            foreach (DictionaryEntry entry in ht_)
            {
                SingleVariable var = (SingleVariable)entry.Value;
                if (var.Grouped_On_X)
                    al.Add(var.Extended_Varname);
            }
            grouped_x_ = al.ToArray();


            al.Clear();


            // Setup grouped_on_z array
            foreach (DictionaryEntry entry in ht_)
            {
                SingleVariable var = (SingleVariable)entry.Value;
                if (var.Grouped_On_Z)
                    al.Add(var.Extended_Varname);
            }
            grouped_z_ = al.ToArray();
            al = null;
        }

        public static LogVariables getInstance(int utid)
        {
            lock (padlock)
            {
                if (instance == null || utid_ != utid)
                {
                    utid_ = utid;
                    instance = new LogVariables();
                }
                return instance;
            }
        }

        public Hashtable Variables
        {
            get
            {
                return ht_;
            }
        }

        public Array Grouped_On_X
        {
            get
            {
                return grouped_x_;
            }
        }

        public Array Grouped_On_Z
        {
            get
            {
                return grouped_z_;
            }
        }

        private class SingleVariable
        {
            bool grouped_on_x_;
            bool grouped_on_z_;
            string varname_;
            string extended_varname_;
            string type_;

            public SingleVariable(string varname, string extended_varname, string type, bool grouped_on_x, bool grouped_on_z)
            {
                // cannot be both!
                if (grouped_on_x & grouped_on_z)
                    return;

                this.varname_ = varname;
                this.extended_varname_ = varname;
                this.type_ = type;
                this.grouped_on_x_ = grouped_on_x;
                this.grouped_on_z_ = grouped_on_z;
            }

            public bool Grouped
            {
                get
                {
                    return (grouped_on_z_ || grouped_on_x_);
                }
            }

            public bool Grouped_On_X
            {
                get
                {
                    return grouped_on_x_;
                }
            }

            public bool Grouped_On_Z
            {
                get
                {
                    return grouped_on_z_;
                }
            }

            public string Varname
            {
                get
                {
                    return varname_;
                }
            }

            public string Extended_Varname
            {
                get
                {
                    return extended_varname_;
                }
            }

        }
    }
}