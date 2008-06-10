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
using High_Level_Parser;
using CreateCharts;

public partial class ChartDynamic : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void CD_submit_onclick(object s, EventArgs e)
    {
        Parser p = new Parser();
        DataTable data = p.parse(CD_getvars.Text);
        string path = Server.MapPath("~/xml/auto_generated.xml");
        Chart c = new Chart(data,path);
        c.generate();
    }
}
