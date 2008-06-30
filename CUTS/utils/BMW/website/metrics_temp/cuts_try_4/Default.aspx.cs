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
using Actions;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        Actions.UnitTestActions ut = new UnitTestActions();
        ut.Eval_UT(1);

        string path = Server.MapPath("~/xml/auto_generated.xml");
        ChartActions ch = new ChartActions(1, "TestID", path);
        ch.Chart();
    }
}