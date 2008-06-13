using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using System.Text.RegularExpressions;
using MySql.Data.MySqlClient;
using High_Level_Parser;
using CreateCharts;


public partial class SavedChartsWrapper : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        string id = Request.QueryString["id"];
        
        // pass in id of 0 if you just want to use the
        // generated xml
        // Use this when another page generates - like
        // when charting dynamically
        if (id != "0")
        {
            string connString = "SERVER=localhost;DATABASE=qed;UID=hamy;PASSWORD=banana";
            string commString = "Select * From charts WHERE ID=" + id;
            MySqlConnection conn = new MySqlConnection(connString);
            MySqlCommand comm = new MySqlCommand(commString, conn);
            conn.Open();

            MySqlDataReader r = comm.ExecuteReader();
            Parser hl = new Parser();
            r.Read();
            string[] str = Regex.Split(r["UTs"].ToString(), ",");
            string commString2 = "Select HLRegex,Eval From unit_tests WHERE UTid=" + str.First();
            foreach (string single in str)
            {
                commString2 += " OR UTid=" + single;
            }
            r.Close();

            MySqlCommand comm2 = new MySqlCommand(commString2, conn);
            MySqlDataReader r2 = comm2.ExecuteReader();

            string parse = "";
            while (r2.Read())
            {
                parse += r2["HLRegex"].ToString() + ";";
            }
            Regex.Replace(parse, ";;", ";");

            DataTable dt = hl.parse(parse);

            string path = Server.MapPath("~/xml/auto_generated.xml");
            Chart ch = new Chart(dt, path);
            ch.generate();
        }
               

    }
}
