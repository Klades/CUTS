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

public partial class Unit_Testing : System.Web.UI.Page
{
    private double DEFAULT_WIDTH = 300;
    private CUTS.BMW_Master m;

    protected void Page_Load(object sender, EventArgs e)
    {
        // used to ease creating messages
        m = (CUTS.BMW_Master)Master;

        if (IsPostBack)
            return;
        
        /*
        // Fix the focus so the correct button is always in focus
        
         * Update: this does not work as hoped - when you click in the 
         * text box you cannot type as the focus has gone to the button :(
         
        string ID = this.btn_Create_Test_Suite_Package.UniqueID;
        this.txt_Create_Test_Suite_Package.Attributes.Add("onclick","document.getElementById('" + ID + "').focus()");

        ID = this.btn_Create_Test_Suite.UniqueID;
        this.txt_Create_Test_Suite.Attributes.Add("onclick","document.getElementById('" + ID + "').focus()");
        */

        try
        {
            // load up the help
            show_help.Style.Add("left", "-95px");
            show_help.Style.Add("top", "-10px");
            show_help.Style.Add("float", "right");
            show_help.Style.Add("position", "relative");

            load_test_suite_data();
            this.lb_Test_Suites.SelectedIndex = 0;

            // Guess load of data
            load_test_suite_package_data();
            this.lb_Test_Suite_Packages.SelectedIndex = 0;

            load_unit_test_data();

            ensure_Test_Suite_Package_Width();
            ensure_Unit_Test_Width();
        }
        catch (LoadTestSuiteException ex)
        {
            //m.AddNewMessage(ex.Message, MessageSeverity.Error);
            return;
        }
        catch
        {
            //this.txt_Create_Test_Suite_Error.Text = "Please Create at least one test suite to get started.";
            //this.txt_Create_Test_Suite_Package_Error.Text = "Please add at least one package to the unit test to get started.";
        }

    }

    private void load_test_suite_data()
    {
        // Get all the test from the database.
        string sql = "SELECT * FROM test_suites;";
        
        DataTable dt = ExecuteMySqlAdapter(sql);
        if (dt.Rows.Count == 0)
            throw new LoadTestSuiteException("You do not have a Test Suite Created! Please create one.");

        // Bind Data
        this.lb_Test_Suites.DataSource = dt;
        this.lb_Test_Suites.DataBind();

        ensure_Test_Suite_Width();
    }

    private void ensure_Test_Suite_Width()
    {
        // Ensure width is at least min
        if (txt_Create_Test_Suite.Width.Value < DEFAULT_WIDTH)
            txt_Create_Test_Suite.Width = new Unit(DEFAULT_WIDTH);

        if (lb_Test_Suites.Width.Value < DEFAULT_WIDTH)
            lb_Test_Suites.Width = new Unit(DEFAULT_WIDTH);
    }

    private void load_test_suite_data(string test_suite_to_select)
    {
        load_test_suite_data();

        // Find Item we would like selected
        ListItem desired = lb_Test_Suites.Items.FindByText(test_suite_to_select);
        int index_desired = lb_Test_Suites.Items.IndexOf(desired);

        // Select it
        lb_Test_Suites.SelectedIndex = index_desired;
    }

    private void load_test_suite_package_data()
    {
        // Check integrity of lb_Test_Suites.Selected Index
        if (lb_Test_Suites.SelectedIndex < 0)
        {
            this.txt_Create_Test_Suite_Package_Error.Text = "You do not appear to have a Test Suite Selected. <br />" +
                "Please select one and try again.";
            return;
        }

        // Get the package info for this test
        string sql = "SELECT packages.id as id,name " +
            "FROM packages,test_suite_packages as tsa " +
            "where tsa.id =" + lb_Test_Suites.SelectedValue + " AND tsa.p_id = packages.id;";
        DataTable dt = ExecuteMySqlAdapter(sql);


        // Bind the data
        this.lb_Test_Suite_Packages.DataSource = dt;
        this.lb_Test_Suite_Packages.DataBind();

        // Ensure the width
        ensure_Test_Suite_Package_Width();
        

        // Update the DropDownList to show all packages
        sql = "SELECT * FROM packages";
        dt = ExecuteMySqlAdapter(sql);
        this.ddl_Add_Existing_Test_Suite_Package.DataSource = dt;
        this.ddl_Add_Existing_Test_Suite_Package.DataBind();

        // Insert the Select Statement
        this.ddl_Add_Existing_Test_Suite_Package.Items.Insert(0, "Choose an Existing Package to Add it . . . ");
    }

    private void ensure_Test_Suite_Package_Width()
    {
        if (lb_Test_Suite_Packages.Width.Value < DEFAULT_WIDTH)
            lb_Test_Suite_Packages.Width = new Unit(DEFAULT_WIDTH);

        if (txt_Create_Test_Suite_Package.Width.Value < DEFAULT_WIDTH)
            txt_Create_Test_Suite_Package.Width = new Unit(DEFAULT_WIDTH);

        if (ddl_Add_Existing_Test_Suite_Package.Width.Value < DEFAULT_WIDTH)
            ddl_Add_Existing_Test_Suite_Package.Width = new Unit(DEFAULT_WIDTH);
    }

    private void load_test_suite_package_data(string test_suite_package_to_select)
    {
        load_test_suite_package_data();

        // Find Item we would like selected
        ListItem desired = lb_Test_Suite_Packages.Items.FindByText(test_suite_package_to_select);
        int index_desired = lb_Test_Suite_Packages.Items.IndexOf(desired);

        // Select it
        lb_Test_Suite_Packages.SelectedIndex = index_desired;
    }

    private void load_unit_test_data()
    {
        // Load the ddl_Add_Package_Unit_Test
        string sql = "SELECT * FROM unittestdesc;";
        DataTable dt = ExecuteMySqlAdapter(sql);
        ddl_Add_Package_Unit_Test.DataSource = dt;
        ddl_Add_Package_Unit_Test.DataBind();

        // Check that there is at least one UT
        if (ddl_Add_Package_Unit_Test.Items.Count > 0)
            this.ddl_Add_Package_Unit_Test.Items.Insert(0, "Please select an existing Unit Test to Add it . . . ");
        else
            txt_Add_Package_Unit_Test_Error.Text = "You do not appear to have created any Unit Tests. <br />" +
                "Please create at least one Unit Test to begin.";

        // Check the integrity of the selected package
        if (lb_Test_Suite_Packages.SelectedIndex < 0)
        {
            txt_Add_Package_Unit_Test_Error.Text = "You do not appear to have a Package Selected. <br />" +
                "Please select a package and try again. <br />";
            return;
        }
        
        // Load the Unit Test ListBox
        sql = "SELECT utid,name " +
            "FROM unittestdesc as utd,packages_unit_tests as put " + 
            "WHERE put.id = " + this.lb_Test_Suite_Packages.SelectedValue + " and put.ut_id = utd.utid;";
        dt = ExecuteMySqlAdapter(sql);
        lb_Unit_Tests.DataSource = dt;
        lb_Unit_Tests.DataBind();

        // Ensure the minimum width
        ensure_Unit_Test_Width();
    }

    private void ensure_Unit_Test_Width()
    {
        if (lb_Unit_Tests.Width.Value < DEFAULT_WIDTH)
            lb_Unit_Tests.Width = new Unit(DEFAULT_WIDTH);

        if (ddl_Add_Package_Unit_Test.Width.Value < DEFAULT_WIDTH)
            ddl_Add_Package_Unit_Test.Width = new Unit(DEFAULT_WIDTH);
    }

    private void load_log_format_data()
    {
        // Load the ddl_Add_Package_Unit_Test

        string sql = "SELECT lfd.lfid,lfmt " + 
            "FROM logformatdesc as lfd,unittesttable as utt " + 
            "where utt.lfid = lfd.lfid and utt.utid = " + lb_Unit_Tests.SelectedValue + ";";
        DataTable dt = ExecuteMySqlAdapter(sql);

        this.dg_Unit_Test_Detail_Log_Formats.DataSource = dt;
        this.dg_Unit_Test_Detail_Log_Formats.DataBind();
    }


    protected void OnClick_btn_Create_Test_Suite(object sender, EventArgs e)
    {
        try
        {
            // Ensure the length of the name 
            //   (This also eliminates blank names or one space names - like ' ')
            if (this.txt_Create_Test_Suite.Text.Length < 3)
            {
                txt_Create_Test_Suite_Error.Text = "Please be sure the name is more than three characters.";
                return;
            }

            string sql = @"CALL insert_test_suite('" + txt_Create_Test_Suite.Text + "');";
            ExecuteMySql(sql);
            txt_Create_Test_Suite_Error.Text = "";


            // Reload the data, and select the package just created
            //   ---Could turn this into out parameters and append to the 
            //   ---end of lb_Test_Suites - rather than rehitting the database
            load_test_suite_data(txt_Create_Test_Suite.Text);
        
        }
        catch
        {
            txt_Create_Test_Suite_Error.Text = "There was a problem adding the Test Suite. <br />" +
                "This probably means there was already a Test Suite with that name. ";
        }       
    }

    protected void OnClick_btn_Create_Test_Suite_Package(object sender, EventArgs e)
    {
        try
        {
            // Ensure the length of the name
            //   (This also eliminates blank names or one space names - like ' ')
            if (this.txt_Create_Test_Suite_Package.Text.Length < 3)
            {
                txt_Create_Test_Suite_Package_Error.Text = "Please be sure the package name is more than three characters.";
                return;
            }

            // Ensure we know which Test Suite they would like to add the package to
            if (this.lb_Test_Suites.SelectedIndex < 0)
            {
                // If there is only one, we know which one they want
                if (this.lb_Test_Suites.Items.Count == 1)
                    this.lb_Test_Suites.SelectedIndex = 0;
                else
                {
                    txt_Create_Test_Suite_Package_Error.Text = "I am not sure which Test Suite you " +
                            "would like to add this package to. <br />" +
                            "Please click on a test suite name and try again.";
                    return;
                }
            }

            // Insert the package
            string sql = @"CALL insert_test_suite_package('" + lb_Test_Suites.SelectedValue + "','" +
                txt_Create_Test_Suite_Package.Text + "');";
            ExecuteMySql(sql);
            txt_Create_Test_Suite_Package_Error.Text = "";

            // Reload the data, and select the package just created
            load_test_suite_package_data(txt_Create_Test_Suite_Package.Text);
        }
        catch
        {
            txt_Create_Test_Suite_Package_Error.Text = "There was a problem adding the Test Suite Package. <br />" +
                "This probably means there was already a package with that name. <br />";
        }
    }

    protected void OnClick_show_help(object sender, EventArgs e)
    {
        Panel p = (Panel)this.Master.FindControl("help_");
        if (show_help.Text == "Show Help")
        {
            p.Controls.Add(my_help_);
            p.Visible = true;
            my_help_.Visible = true;
            show_help.Text = "Hide Help";
        }
        else
        {
            p.Controls.Remove(my_help_);
            p.Visible = false;
            my_help_.Visible = false;
            show_help.Text = "Show Help";
        }
    }

    protected void OnChange_lb_Test_Suite_Packages(object sender, EventArgs e)
    {
        load_unit_test_data();
    }

    protected void OnChange_ddl_Add_Existing_Test_Suite_Package(object sender, EventArgs e)
    {
        try
        {
            // Ensure the integrity of the Selected Test Suite
            if (lb_Test_Suites.SelectedIndex < 0)
            {
                // If there is only one, we know which one they want
                if (lb_Test_Suites.Items.Count == 1)
                    lb_Test_Suites.SelectedIndex = 0;
                else
                {
                    txt_Create_Test_Suite_Package_Error.Text = "I am not sure which Test Suite you would like to add this pacakge to. <br />" +
                        "Please select a Test Suite and Try again";
                    return;
                }
            }

            // Insert the package
            string sql = @"CALL insert_test_suite_package_existing('" +
                this.lb_Test_Suites.SelectedValue + "','" +
                this.ddl_Add_Existing_Test_Suite_Package.SelectedValue + "');";
            ExecuteMySql(sql);
            this.txt_Create_Test_Suite_Package_Error.Text = "";

            // Reload the Package data, and select the package just added
            load_test_suite_package_data(ddl_Add_Existing_Test_Suite_Package.SelectedValue);
        }
        catch
        {
            this.txt_Create_Test_Suite_Package_Error.Text = "There was a problem adding the Package. <br />" +
                "Please check to ensure the Test Suite does not <br />" +
                "already contain a Package named " +
                this.ddl_Add_Existing_Test_Suite_Package.SelectedItem.Text + "<br />";
        }
    }

    protected void OnChange_ddl_Add_Package_Unit_Test(object sender, EventArgs e)
    {
        try
        {
            // Ensure the integrity of the Selected Package
            if (lb_Test_Suite_Packages.SelectedIndex < 0)
            {
                // If there is only one, we know which one they want
                if (lb_Test_Suite_Packages.Items.Count == 1)
                    lb_Test_Suite_Packages.SelectedIndex = 0;
                else
                {
                    txt_Add_Package_Unit_Test_Error.Text = "I am not sure which Package you would like to add this unit test to. <br />" +
                        "Please select a Package and Try again";
                    return;
                }
            }

            string sql = @"CALL insert_package_unit_test('" +
                this.lb_Test_Suite_Packages.SelectedValue + "','" +
                this.ddl_Add_Package_Unit_Test.SelectedValue + "');";
            ExecuteMySql(sql);
            this.txt_Add_Package_Unit_Test_Error.Text = "";

            // Reload the Unit test Drop Down List
            load_unit_test_data();
        }
        catch
        {
            this.txt_Add_Package_Unit_Test_Error.Text = "There was a problem adding the Unit Test. <br />" +
                "Please check to ensure the Package does not " +
                "already contain a Unit Test named <br />" +
                this.ddl_Add_Package_Unit_Test.SelectedItem.Text + "<br />";
        }
    }

    protected void OnChange_lb_Test_Suites(object sender, EventArgs e)
    {
        this.txt_Create_Test_Suite_Error.Text = "";
        load_test_suite_package_data();
    }

    protected void OnChange_lb_Unit_Tests(object sender, EventArgs e)
    {
        td_Unit_Test_Details_Is_Visible = true;

        string sql = @"SELECT * FROM unittestdesc WHERE utid = " + lb_Unit_Tests.SelectedValue + " LIMIT 1;";
        DataRow row = ExecuteMySqlRow(sql);

        txt_Unit_Test_Details_Name.Text = row["name"].ToString();
        txt_Unit_Test_Details_Description.Text = row["description"].ToString();
        txt_Unit_Test_Details_Evaluation.Text = row["evaluation"].ToString();
        txt_Unit_Test_Details_Warn_Comparison.Text = row["warn_comparison"].ToString() + " " + row["warn"].ToString();
        txt_Unit_Test_Details_Fail_Comparison.Text = row["fail_comparison"].ToString() + " " + row["fail"].ToString();
        lbl_Unit_Test_Details_ID.Text = row["utid"].ToString();

        load_log_format_data();
    }

    private bool td_Unit_Test_Details_Is_Visible
    {
        get
        {
            return this.td_Unit_Test_Details.Visible;
        }
        set
        {
            this.td_Unit_Test_Details.Visible = value;
        }
    }
    
    private DataTable ExecuteMySqlAdapter(string sql)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        conn.Open();

        MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
        DataSet ds = new DataSet();
        try
        {
            da.Fill(ds);
        }
        catch
        {
            throw new ArgumentException("The sql executed was : " + sql);
        }

        conn.Close();
        return ds.Tables[0];
    }

    private void ExecuteMySql(string sql)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        MySqlCommand comm = new MySqlCommand(sql, conn);
        conn.Open();
        try
        {

            comm.ExecuteNonQuery();
        }
        catch
        {
            throw new ArgumentException("The sql executed was : " + sql);
        }
        conn.Close();
    }

    private DataRow ExecuteMySqlRow(string sql)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        conn.Open();

        MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
        DataSet ds = new DataSet();
        try
        {
            da.Fill(ds);
        }
        catch
        {
            throw new ArgumentException("The sql executed was: " + sql);
        }
        conn.Close();

        return ds.Tables[0].Rows[0];
    }

}

public class LoadTestSuiteException : Exception
{ // All we need is a default Exception constructor

    public LoadTestSuiteException(string message)
        :base(message) {}
}