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
using Actions;

public partial class UT_Create : System.Web.UI.Page
{
    private string connString = ConfigurationSettings.AppSettings["connString"];

    protected void Page_Load(object sender, EventArgs e)
    {
        if (IsPostBack)
            return;

        string commString = "SELECT lfid,lfmt FROM logformatdesc";
        MySqlConnection conn = new MySqlConnection(connString);
        conn.Open();
        
        MySqlCommand comm = new MySqlCommand(commString, conn);
        MySqlDataReader r = comm.ExecuteReader();
        DropDownList1.DataSource = r;
        DropDownList1.DataTextField = "lfmt";
        DropDownList1.DataValueField = "lfid";
        DropDownList1.DataBind();
        Label1.Text = "Variables prefixed by LF" + DropDownList1.Items[0].Value;
        r.Close();

        MySqlCommand comm2 = new MySqlCommand(commString, conn);
        MySqlDataReader r2 = comm.ExecuteReader();
        DropDownList2.DataSource = r2;
        DropDownList2.DataTextField = "lfmt";
        DropDownList2.DataValueField = "lfid";
        DropDownList2.DataBind();
        DropDownList2.Items.Insert(0, new ListItem("Feel free to select another", "0"));
        r2.Close();


        conn.Close();

        
    }
    protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
    {
        Label1.Text = "Varnames prefixed by LF" + DropDownList1.SelectedValue;
    }
    
    protected void DropDownList2_SelectedIndexChanged(object sender, EventArgs e)
    {
        Label2.Text = "Varnames prefixed by LF" + DropDownList2.SelectedValue;
        if (DropDownList2.SelectedValue == "0")
            Label2.Text = "";
    }


    protected void Button1_Click(object sender, EventArgs e)
    {
        ArrayList lfids = new ArrayList();
        lfids.Add(DropDownList1.SelectedValue);

        if (DropDownList2.SelectedIndex != 0)
            lfids.Add(DropDownList2.SelectedValue);

        UnitTestActions ut = new UnitTestActions();
        ut.Insert_UT(UT_name.Text, UT_desc.Text, UT_fail_comp.Text, UT_warn_comp.Text, UT_fail.Text, UT_warn.Text, UT_eval.Text, lfids.ToArray());
    }
}
