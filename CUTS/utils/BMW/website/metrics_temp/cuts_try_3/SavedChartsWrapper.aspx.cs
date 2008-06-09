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
using MySql.Data.MySqlClient;
using Parser;
using cuts;
using CreateCharts;


public partial class SavedChartsWrapper : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

        
        
        string id = Request.QueryString["id"];
        string connString = "SERVER=localhost;DATABASE=qed;UID=hamy;PASSWORD=banana";
        string commString = "Select HLRegex,Eval From unit_tests WHERE UTid=" + id;
        MySqlConnection conn = new MySqlConnection(connString);
        MySqlCommand comm = new MySqlCommand(commString, conn);
        conn.Open();

        MySqlDataReader r = comm.ExecuteReader();
        High_Level_Parser hl = new High_Level_Parser();      
        r.Read();
        DataTable dt = hl.parse(r["HLRegex"].ToString());
        Chart ch = new Chart(dt);
        ch.generate();

        
        
        

    }
}
