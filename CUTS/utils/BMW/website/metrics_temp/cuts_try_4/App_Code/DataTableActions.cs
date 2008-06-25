using System;
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

        private DataTable dt;
        private static int utid_;

        private DataTableActions()
        {
            dt = new DataTable();
            Array x = LogVariables.LogVariables.getInstance(utid_).Grouped_On_X;
            Array z = LogVariables.LogVariables.getInstance(utid_).Grouped_On_Z;

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

        public void insert(string data, string extended_varname)
        {
            // do something with some data here :)
        }

    }
}