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

        conn.Close();
    }
    protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
    {
        Label1.Text = "Varnames prefixed by LF" + DropDownList1.SelectedValue;
    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        ArrayList lfids = new ArrayList();
        lfids.Add(DropDownList1.SelectedValue);
        string sql= "lfid = " + DropDownList1.SelectedValue.ToString();

        MySqlConnection conn = new MySqlConnection(ConfigurationSettings.AppSettings["connString"]);
        MySqlCommand comm = new MySqlCommand("Select variable_id FROM logformatvariabletable WHERE " + sql, conn);
        conn.Open();
        MySqlDataReader r = comm.ExecuteReader();
        
        ArrayList al = new ArrayList();

        while (r.Read())
        {
            al.Add(r[0].ToString());
        }
        r.Close();
        conn.Close();


        Hashtable variables = new Hashtable();
        variables.Add("Name", UT_name.Text);
        variables.Add("Description", UT_desc.Text);
        variables.Add("FailComparison", UT_fail_comp.Text);
        variables.Add("WarnComparison", UT_warn_comp.Text);
        variables.Add("FailValue", UT_fail.Text);
        variables.Add("WarnValue", UT_warn.Text);
        variables.Add("Evaluation", UT_eval.Text);
        variables.Add("LFIDs", lfids.ToArray());
        
        string[] groups = new string[1];
        //groups[0] = "TestID";
        variables.Add("Groups", groups);

        // Note that this only supports SUMs for now
        Hashtable Aggregrations = new Hashtable();
        foreach(string VariableID in al)
            Aggregrations.Add(VariableID,"SUM");
        variables.Add("Aggregrations",Aggregrations);


        UnitTestActions ut = new UnitTestActions();
        ut.Insert_UT(variables);
    }
}

public class GetLogFormat
{
    public GetLogFormat() { }


    public void CreateNew()
    {
        
    }
}