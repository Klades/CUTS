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
using MySql.Data.MySqlClient;

public partial class UT_Create : System.Web.UI.Page
{
    private string connString = ConfigurationManager.AppSettings["MySQL"];
    protected ASP.AddLogFormat addlf;
    override protected void OnInit(EventArgs e)
    {
        //
        // CODEGEN: This call is required by the ASP.NET Web Form Designer.
        //
        addlf = (ASP.AddLogFormat)LoadControl("~/controls/AddLogFormat.ascx");
        PlaceHolder1.EnableViewState = true;
        PlaceHolder1.Controls.Add(addlf);

        this.Load += new System.EventHandler(this.Page_Load);
        base.OnInit(e);
    }

    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        ArrayList lfids = new ArrayList();
        //lfids.Add(DropDownList1.SelectedValue);
        //string sql= "lfid = " + DropDownList1.SelectedValue.ToString();
        string sql = "";

        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        MySqlCommand comm = new MySqlCommand("Select variable_id FROM logformatvariabletable WHERE " + sql, conn);
        conn.Open();
        MySqlDataReader r = comm.ExecuteReader();

        ArrayList al = new ArrayList();

        while (r.Read())
        {
            al.Add(r.GetString(0));
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
        //groups[0] = "test_number";
        variables.Add("Groups", groups);

        // Note that this only supports SUMs for now
        Hashtable Aggregrations = new Hashtable();
        foreach (string VariableID in al)
            Aggregrations.Add(VariableID, "SUM");
        variables.Add("Aggregrations", Aggregrations);


        UnitTestActions ut = new UnitTestActions();
        ut.Insert_UT(variables);
    }

}
