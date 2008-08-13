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
using MySql.Data.MySqlClient;

public partial class AddLogFormat : System.Web.UI.UserControl
{
    #region Web Form Designer generated code
    override protected void OnInit(EventArgs e)
    {
        AddNew(Panel1);

        //
        // CODEGEN: This call is required by the ASP.NET Web Form Designer.
        //
        InitializeComponent();
        base.OnInit(e);
    }

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        this.Load += new System.EventHandler(this.Page_Load);
    }
    #endregion

    
    protected void Page_Load(object sender, EventArgs e)
    {
        AddLabel();
        CreateAggregrations();
    }
    
    private void AddNew(Panel p)
    {
        DropDownList d = new DropDownList();
        p.Controls.Add(d);

        d.ID = "D_list";
        d.Height = Unit.Pixel(24);
        d.Width = Unit.Pixel(431);
        d.AutoPostBack = true;
        FillDropDownList(d);
    }

    private void AddLabel()
    {
        Label l = new Label();
        Control c = Panel1.FindControl("D_label");
        if (c == null)
        {
            Panel1.Controls.Add(l);
            l.ID = "D_label";

            DropDownList d = (DropDownList)Panel1.FindControl("D_list");
            l.Text = "Variables Prefixed by LF" + d.SelectedValue;

            Panel1.Controls.Add(new LiteralControl("<br>"));
        }
    }
    
    private void CreateAggregrations()
    {
        DropDownList d = (DropDownList)Panel1.FindControl("D_list");
        int id = Int32.Parse(d.SelectedValue);
        string sql = @"CALL Get_LFID_info('" + d.SelectedValue + "');";
        foreach (string var_id in ExecuteMySqlReader(sql, "extended_varname"))
        {
            DropDownList ddl = new DropDownList();
            Control c = Panel1.FindControl(var_id);
            if (c == null)
            {
                Panel1.Controls.Add(new LiteralControl("Agg. for " + var_id + ":  "));
                Panel1.Controls.Add(ddl);
                
                ddl.ID = var_id;
                ddl.AutoPostBack = false;
                ddl.EnableViewState = true;
                ddl.Items.Add(new ListItem("Sum", "SUM"));
                ddl.Items.Add(new ListItem("Average", "AVG"));
                ddl.Items.Add(new ListItem("Max", "MAX"));
                ddl.Items.Add(new ListItem("Min", "MIN"));
                ddl.Items.Add(new ListItem("Count", "COUNT"));
                ddl.Items.Add(new ListItem("Count Distinct", "COUNT DISTINCT"));
                                
                Panel1.Controls.Add(new LiteralControl("<br>"));
            }
        }
    }
    
    private void FillDropDownList(DropDownList d)
    {
        string commString = "SELECT lfid,lfmt FROM log_formats";
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        conn.Open();

        MySqlCommand comm = new MySqlCommand(commString, conn);
        MySqlDataReader r = comm.ExecuteReader();
        d.DataSource = r;
        d.DataTextField = "lfmt";
        d.DataValueField = "lfid";
        d.DataBind();
        r.Close();

        conn.Close();
    }

    private Array ExecuteMySqlReader(string sql, string ColumnName)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        MySqlCommand comm = new MySqlCommand(sql, conn);
        conn.Open();
        MySqlDataReader r = comm.ExecuteReader();

        ArrayList al = new ArrayList();
        while (r.Read())
            al.Add(r.GetString(ColumnName));

        conn.Close();
        return al.ToArray();
    }

}