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

        // horrible hack - works for now. Need to update this control
        DropDownList dl = (DropDownList)PlaceHolder1.Controls[0].Controls[0].Controls[1];

        // Note - this only works as long as we only have one LFID per UT
        lfids.Add(dl.SelectedValue);
        string sql = "lfid = " + dl.SelectedValue.ToString();

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
        variables.Add("FailComparison", get_comparison(UT_fail_comp.Text));
        variables.Add("WarnComparison", get_comparison(UT_warn_comp.Text));
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
    private string get_comparison(string comparison)
    {
        // Note these are their MySQL counterparts. 
        // They are used directly in the query

        switch (comparison)
        {
            case "less":
                return @"<";
                break;
            case "greater":
                return @">";
                break;
            case "less_equal":
                return @"<=";
                break;
            case "greater_equal":
                return @">=";
                break;
            case "equal":
                return @"=";
                break;
            case "not_equal":
                return @"<>";
                break;
            default:
                throw new SystemException("The comparison did not match - This possible hack attempt has been recorded.");
                break;
        }
    }

}
