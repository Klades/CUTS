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
using System.Text.RegularExpressions;
using System.Drawing;

public partial class UT_Create : System.Web.UI.Page
{
    private string connString = ConfigurationManager.AppSettings["MySQL"];

    protected void Page_Load(object sender, EventArgs e)
    {
        // We always have to reload the 
        // variable aggregrations
        reload_panel_variables();
                
        if (IsPostBack)
            return;

        load_ddl_Log_Formats();
        
        // Hide the second log format
        lbl_Log_Formats_2.Visible = false;
        ddl_Log_Formats_2.Visible = false;
        panel_Log_Format_variables_2.Visible = false;
        btn_more_lfs.Text = "[+] I need more Log Formats";

        // hide the relations
        relation_head.Visible = false;
        relation1.Visible = false;
        relation2.Visible = false;
        relation_text.Visible = false;
    }

    private void reload_panel_variables()
    {
        if (ViewState["variables1"] != null)
        {
            // Create the regex
            string variables1 = (string)ViewState["variables1"];
            Regex reg = new Regex(@"\|(?<name>.+?),(?<id>.+?);");
            Match m = reg.Match(variables1);
            
            // extract the variables
            while (m.Success)
            {
                string varname = m.Groups["name"].ToString();
                string id = m.Groups["id"].ToString();
                panel_Log_Format_variables_1.Controls.Add(new Log_Format_Variable(varname, id));
                m = m.NextMatch();
            }
        }
        if (ViewState["variables2"] != null)
        {
            // Create the regex
            string variables2 = (string)ViewState["variables2"];
            Regex reg = new Regex(@"\|(?<name>.+?),(?<id>.+?);");
            Match m = reg.Match(variables2);

            // extract the variables
            while (m.Success)
            {
                string varname = m.Groups["name"].ToString();
                string id = m.Groups["id"].ToString();
                panel_Log_Format_variables_2.Controls.Add(new Log_Format_Variable(varname, id));
                m = m.NextMatch();
            }
        }
        if (panel_Log_Format_variables_2.Visible == true)
        {
            load_relations();
        }
    }

    protected void OnClick_more_log_formats(object sender, EventArgs e)
    {
        if (panel_Log_Format_variables_2.Visible == false)
        {// If invisible, make it visible
            
            // Show second selection
            lbl_Log_Formats_2.Visible = true;
            ddl_Log_Formats_2.Visible = true;
            panel_Log_Format_variables_2.Visible = true;
            btn_more_lfs.Text = "[-] I only need one Log Format";

            // Show relations
            relation_head.Visible = true;
            relation_text.Visible = true;
            relation1.Visible = true;
            relation2.Visible = true;
        }
        else
        {// If its visible, hide it
            
            // Hide Second selection
            lbl_Log_Formats_2.Visible = false;
            ddl_Log_Formats_2.Visible = false;
            panel_Log_Format_variables_2.Visible = false;
            btn_more_lfs.Text = "[+]  I need more Log Formats";

            // hide relationship
            relation_head.Visible = false;
            relation1.Visible = false;
            relation2.Visible = false;
            relation_text.Visible = false;
        }
    }

    protected void OnClick_btn_Submit(object sender, EventArgs e)
    {
        ArrayList lfids = new ArrayList();

        // Check that lfid is valid
        if (ddl_Log_Formats_1.SelectedIndex < 0)
            { show_error_message("The first Log Format you have selected is not valid"); return; }
        else
            lfids.Add(ddl_Log_Formats_1.SelectedValue);
        

        // Check if second LF is used
        // Then check if second LF is valid
        if (ddl_Log_Formats_2.Visible == true)
            if (ddl_Log_Formats_2.SelectedIndex < 0)
                { show_error_message("The second Log Format you have selected is not valid"); return; }
            else
                lfids.Add(ddl_Log_Formats_2.SelectedValue);
            
        

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

        Hashtable Aggregrations = new Hashtable();

        try
        {
            // Add aggregrations for variables in panel 1
            foreach (Control c in panel_Log_Format_variables_1.Controls)
                if (c is Log_Format_Variable)
                {
                    Log_Format_Variable var = (Log_Format_Variable)c;
                    Aggregrations.Add(var.VariableID, var.Aggregration);
                }

            // Add aggregrations for variables in panel 2
            if (panel_Log_Format_variables_2.Visible == true)
                foreach (Control c in panel_Log_Format_variables_2.Controls)
                    if (c is Log_Format_Variable)
                    {
                        Log_Format_Variable var = (Log_Format_Variable)c;
                        Aggregrations.Add(var.VariableID, var.Aggregration);
                    }
        }
        catch
        { 
            show_error_message("You are attempting to use the same log message twice."); 
            return; 
        }
                

        variables.Add("Aggregrations", Aggregrations);

        string relation_1 = String.Empty, relation_2 = string.Empty;
        if (panel_Log_Format_variables_2.Visible == true)
        {
            // store the relation information in variables
            relation_1 = relation1.SelectedValue;
            relation_2 = relation2.SelectedValue;
        }
        variables.Add("relation1", relation_1);
        variables.Add("relation2", relation_2);

        try
        {
            UnitTestActions ut = new UnitTestActions();
            ut.Insert_UT(variables);
        }
        catch { show_error_message("There was a problem adding the UT"); return; }
        show_error_message("UT added successfully");
    }
    
    private string get_comparison(string comparison)
    {
        // Note these are their MySQL counterparts. 
        // They are used directly in the query

        switch (comparison)
        {
            case "less":
                return @"<";                
            case "greater":
                return @">";                
            case "less_equal":
                return @"<=";                
            case "greater_equal":
                return @">=";                
            case "equal":
                return @"=";                
            case "not_equal":
                return @"<>";                
            default:
                throw new SystemException("The comparison did not match - This possible hack attempt has been recorded.");
        }
    }

    private void load_ddl_Log_Formats()
    {
        string commString = "SELECT lfid,lfmt FROM logformatdesc";
        DataTable data = ExecuteMySqlAdapter(commString);
        
        // Load first DDL of LogFormats
        ddl_Log_Formats_1.DataSource = data;
        ddl_Log_Formats_1.DataTextField = "lfmt";
        ddl_Log_Formats_1.DataValueField = "lfid";
        ddl_Log_Formats_1.DataBind();
        ddl_Log_Formats_1.Items.Insert(0,"Please choose a Log Format . . .");


        // Load second
        ddl_Log_Formats_2.DataSource = data;
        ddl_Log_Formats_2.DataTextField = "lfmt";
        ddl_Log_Formats_2.DataValueField = "lfid";
        ddl_Log_Formats_2.DataBind();
        ddl_Log_Formats_2.Items.Insert(0,"Please choose a Log Format . . .");
    }

    private void load_panel_Log_Format_Variables(int panel)
    {
        Panel p;
        string lfid;
        string storage;
        if (panel == 2)
        {
            p = panel_Log_Format_variables_2;
            storage = "variables2";
            lfid = ddl_Log_Formats_2.SelectedValue;
        }
        else
        {
            p = panel_Log_Format_variables_1;
            storage = "variables1";
            lfid = ddl_Log_Formats_1.SelectedValue;
        }

        ViewState[storage] = null;
        p.Controls.Clear();

        try
        {
            int lfid_temp = Int32.Parse(lfid);
            // need to throw error here!
            if (lfid_temp < 1)
                return;
        }
        catch { return; }

        // Get all variables
        string sql = "CALL Get_LFID_info('" + lfid + "');";
        DataTable data = ExecuteMySqlAdapter(sql);

        // Add each variable to the page
        foreach (DataRow row in data.Rows)
        {
            string varname = row["varname"].ToString();
            string variableID = row["variable_id"].ToString();

            p.Controls.Add(new Log_Format_Variable(varname, variableID));

            // so - |varname,variableID;
            // This makes it easy to retrieve from the ViewState
            ViewState[storage] += "|" + varname + "," + variableID + ";";
        }

        // For the bottom panel, add a space to make the button look better
        if (panel == 2)
            p.Controls.Add(new LiteralControl("<br />"));
    }

    private void load_relations()
    {
        if (ddl_Log_Formats_1.SelectedIndex < 1 || ddl_Log_Formats_2.SelectedIndex < 1)
        {
            show_error_message("Before the relationship lists can be populated, you must select two valid logformats.");
            return;
        }
        
        relation_head.Visible = true;
        relation1.Visible = true;
        relation2.Visible = true;

        string sql = "CALL Get_LFID_info('" + ddl_Log_Formats_1.SelectedValue + "');";
        DataTable dt = ExecuteMySqlAdapter(sql);

        relation1.DataSource = dt;
        relation1.DataTextField = "extended_varname";
        relation1.DataValueField = "variable_id";
        relation1.DataBind();

        sql = "CALL Get_LFID_info('" + ddl_Log_Formats_2.SelectedValue + "');";
        dt = ExecuteMySqlAdapter(sql);

        relation2.DataSource = dt;
        relation2.DataBind();
    }

    protected void OnChange_ddl_Log_Formats_1(object sender, EventArgs e)
    {
        if (ddl_Log_Formats_1.SelectedIndex < 1)
            return;

        lbl_Log_Formats_1.Text = "Prefix Variables with LF" + ddl_Log_Formats_1.SelectedValue;

        load_panel_Log_Format_Variables(1);

        if (ddl_Log_Formats_1.SelectedIndex < 1 | ddl_Log_Formats_2.SelectedIndex < 1)
            return;

        ViewState["relation"] = ddl_Log_Formats_1.SelectedValue.ToString() +
            "," +
            ddl_Log_Formats_2.SelectedValue.ToString();
    }

    protected void OnChange_ddl_Log_Formats_2(object sender, EventArgs e)
    {
        if (ddl_Log_Formats_2.SelectedIndex < 1)
            return;

        lbl_Log_Formats_2.Text = "Prefix Variables with LF" + ddl_Log_Formats_2.SelectedValue;

        load_panel_Log_Format_Variables(2);

        if (ddl_Log_Formats_1.SelectedIndex < 1 | ddl_Log_Formats_2.SelectedIndex < 1)
            return;

        ViewState["relation"] = ddl_Log_Formats_1.SelectedValue.ToString() +
            "," +
            ddl_Log_Formats_2.SelectedValue.ToString();
    }

    private DataTable ExecuteMySqlAdapter(string sql)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        conn.Open();

        try
        {

            MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
            DataSet ds = new DataSet();
            da.Fill(ds);
            return ds.Tables[0];

        }
        catch (MySqlException e)
        {
            // show mysql exception
            throw e;
        }
        finally
        {
            conn.Close();
        }
    }

    private void show_error_message(string message)
    {
        Label label = (Label)this.Master.FindControl("message_");

        label.Text = message;
        label.ForeColor = Color.Red;
    }

}

public class Log_Format_Variable : CompositeControl
{
    private DropDownList d;
    private string var_ID;
    private string varname;

    public Log_Format_Variable(string varname, string var_ID)
    {
        this.var_ID = var_ID;
        this.varname = varname;
    }

    protected override void CreateChildControls()
    {
        Controls.Clear();
        CreateControlHierarchy();
        ClearChildViewState();
    }
    protected virtual void CreateControlHierarchy()
    {
        Label l = new Label();
        l.Text = "Aggregrate Function for " + varname;

        LiteralControl lc1 = new LiteralControl("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");

        d = new DropDownList();
        d.Items.Add(new ListItem("Sum", "SUM"));
        d.Items.Add(new ListItem("Average", "AVG"));
        d.Items.Add(new ListItem("Max", "MAX"));
        d.Items.Add(new ListItem("Min", "MIN"));
        d.Items.Add(new ListItem("Count", "COUNT"));
        d.Items.Add(new ListItem("Count Distinct", "COUNT DISTINCT"));

        LiteralControl lc2 = new LiteralControl("<br>");


        this.Controls.Add(l);
        this.Controls.Add(lc1);
        this.Controls.Add(d);
        this.Controls.Add(lc2);
    }

    public string VariableID
    {
        get { return var_ID; }
    }

    public string Aggregration
    {
        get { return d.SelectedValue.ToString(); }
    }
}