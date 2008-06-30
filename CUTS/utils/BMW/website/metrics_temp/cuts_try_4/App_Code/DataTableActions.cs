using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using LogVariables;

namespace Actions
{
    /// <summary>
    /// Perform actions on the main DataTable
    /// that is used for evaluation, aggregrations,
    /// ect
    /// </summary>
    public sealed class DataTableActions
    {
        private static DataTableActions instance = null;
        private static readonly object padlock = new object();

        private DataTable dt_;
        private static int utid_;
        private Array grouped_x_;
        private Array grouped_z_;


        private DataTableActions()
        {
            dt_ = new DataTable();
            grouped_x_ = LogVariables.LogVariables.getInstance(utid_).Grouped_On_X;
            grouped_z_ = LogVariables.LogVariables.getInstance(utid_).Grouped_On_Z;

            // Add a constraint on the x_cols to ensure data integrity
            ArrayList x_cols = new ArrayList();
            foreach (string varname in grouped_x_.Cast<string>())
            {
                dt_.Columns.Add(new DataColumn(varname));
                x_cols.Add(dt_.Columns[varname]);

            }
            DataColumn[] xcols = (DataColumn[])x_cols.ToArray(typeof(DataColumn));
            UniqueConstraint uc_x = new UniqueConstraint(xcols);
            dt_.Constraints.Add(uc_x);

            // if there are any 3-D constraints
            // on the z axis
            if (grouped_z_.Length != 0)
            {
                // Add a constraint on the x_cols to ensure data integrity
                ArrayList z_cols = new ArrayList();
                foreach (string varname in grouped_z_.Cast<string>())
                {
                    dt_.Columns.Add(new DataColumn(varname));
                    z_cols.Add(dt_.Columns[varname]);

                }
                DataColumn[] zcols = (DataColumn[])z_cols.ToArray(typeof(DataColumn));
                UniqueConstraint uc_z = new UniqueConstraint(zcols);
                dt_.Constraints.Add(uc_z);
            }

            // Make sure the datatable has all of the columns required
            foreach (string varname in LogVariables.LogVariables.getInstance(utid_).Variables.Keys.Cast<string>())
            {
                if (dt_.Columns.IndexOf(varname) < 0)
                    dt_.Columns.Add(new DataColumn(varname));
            }

            // Add a primary key to make things simple on us
            DataColumn pk = new DataColumn("id");
            pk.DataType = System.Type.GetType("System.Int32");
            pk.AutoIncrement = true;
            pk.AutoIncrementSeed = 1;
            dt_.Columns.Add(pk);

            DataColumn[] keys = new DataColumn[1];
            keys[0] = pk;

            dt_.PrimaryKey = keys;
        }

        public static DataTableActions getInstance(int utid)
        {
            lock (padlock)
            {
                if (instance == null || utid_ != utid)
                {
                    utid_ = utid;
                    instance = new DataTableActions();
                }
                return instance;
            }
        }

        public DataTable Table
        {
            get
            {
                return dt_;
            }
        }

        public void insert(Hashtable single_row)
        {
            string select = "";
            // Ensure that the grouped columns are present
            // and build the select statement at the same
            // time
            foreach (string varname in grouped_x_)
                if (single_row.ContainsKey(varname) == false)
                    return;
                else
                    select += varname + "='" + single_row[varname] + "' AND ";
            
            
            foreach (string varname in grouped_z_)
                if (single_row.ContainsKey(varname) == false)
                    return;
                else
                    select += varname + "='" + single_row[varname] + "' AND ";
            
            
            // find the group ID
            string group_select = select.Remove(select.LastIndexOf(" AND "));
            int group_id = Insert_if_not_exists_group(group_select, single_row);

            // remove the group variables
            foreach (string name in grouped_x_)
                single_row.Remove(name);
            foreach (string name in grouped_z_)
                single_row.Remove(name);

            // iterate over the data
            foreach (string varname in single_row.Keys)
                if (Insert_if_not_exists_data(single_row,group_id,varname) == false)
                    aggregrate(single_row, group_id, varname);            
            
        }

        private bool Insert_if_not_exists_data(Hashtable row, int id, string varname)
        {
            // check to see if element already exists
            if (dt_.Rows.Find(id)[varname].ToString() != "")
                return false;
                       
            dt_.Rows.Find(id)[varname] = row[varname];
            return true;
        }

        private void aggregrate(Hashtable row, int id, string varname)
        {
            // only aggregration is sum for now
            dt_.Rows.Find(id)[varname] = Int32.Parse(dt_.Rows.Find(id)[varname].ToString()) 
                + Int32.Parse(row[varname].ToString());   
        }

        private int Insert_if_not_exists_group(string select, Hashtable single_row)
        {
            if (dt_.Select(select).Length == 0)
            {
                DataRow new_row = dt_.NewRow();
                
                // insert the group
                foreach (string name in grouped_x_)
                    new_row[name] = single_row[name];
                foreach (string name in grouped_z_)
                    new_row[name] = single_row[name];

                dt_.Rows.Add(new_row);
            }

            return Int32.Parse(dt_.Select(select)[0]["id"].ToString());
        }
    }
}