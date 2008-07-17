using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Actions;
using System.IO;
using System.Xml;
using System.Text;
using MySql.Data.MySqlClient;

public partial class UT_Chart : System.Web.UI.Page
{

    protected void Page_Load(object sender, EventArgs e)
    {
        if (IsPostBack)
            return;

        string id_string = Request.QueryString.Get("utid");
        int id = Int32.Parse(id_string);

        UnitTestActions ut = new UnitTestActions();
        DataTable dt_ = ut.Eval_UT(id,"metric");
        
        Chart(dt_);


        string ChartObject = @"<object classid='clsid:D27CDB6E-AE6D-11cf-96B8-444553540000' codebase='http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0'" +
            @" width='900' height='500' id='charts'>"+
            @"<param name='movie' value='charts/charts.swf?library_path=charts/charts_library&xml_source=xml/auto_generated.xml' />" +
            @"<param name='quality' value='high' />"+
            @"<param name='bgcolor' value='#666666' />" +
            @"<param name='allowScriptAccess' value='sameDomain' />" +
            @"<embed src='charts/charts.swf?library_path=charts/charts_library&xml_source=xml/auto_generated.xml' " +
            @"quality='high' bgcolor='#666666' width='900' height='500' name='charts' allowscriptaccess='sameDomain' " +
            @"swliveconnect='true' type='application/x-shockwave-flash' pluginspage='http://www.macromedia.com/go/getflashplayer'>" +
            @"</embed></object>";

        LiteralControl chart = new LiteralControl(ChartObject);
        placeholder.Controls.Add(chart);
        
    }

    private void Chart(DataTable dt)
    {
        string xmlPath = Server.MapPath("~/xml/auto_generated.xml");
        FileInfo XMLExists = new FileInfo(xmlPath);
        if (XMLExists.Exists)
        {
            File.Delete(xmlPath);
        }

        XmlTextWriter writer = new XmlTextWriter(xmlPath, Encoding.UTF8);

        writer.WriteStartDocument();
        writer.WriteStartElement("chart"); // <chart>
        writer.WriteStartElement("chart_data"); // <chart_data>
        writer.WriteStartElement("row");   // <row>
        writer.WriteRaw("<null/>");        // <null/>
        foreach (DataRow row in dt.Rows)
        {
            writer.WriteElementString("string", row["test_number"].ToString());
        }
        writer.WriteEndElement();           // </row>

        writer.WriteStartElement("row");   // <row>

        writer.WriteElementString("string", "result");

        foreach (DataRow row in dt.Rows)
        {
            writer.WriteElementString("number", row["result"].ToString());
        }
        writer.WriteEndElement();


        writer.WriteEndElement();  // </chart_data>
        writer.WriteEndElement();  // </chart>
        writer.WriteEndDocument();
        writer.Flush();
        writer.Close();
    }

    private DataTable ExecuteMySqlAdapter(string sql)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        conn.Open();

        MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
        DataSet ds = new DataSet();
        da.Fill(ds);

        conn.Close();
        return ds.Tables[0];
    }

}
