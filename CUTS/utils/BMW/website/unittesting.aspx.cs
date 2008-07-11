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
    protected void Page_Load(object sender, EventArgs e)
    {
        
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
            load_test_suite_data();
            this.lb_Test_Suites.SelectedIndex = 0;

            load_test_suite_package_data();
            this.lb_Test_Suite_Packages.SelectedIndex = 0;

            load_unit_test_data();
        }
        catch
        {
            this.txt_Create_Test_Suite_Error.Style.Add("color", "red");
            this.txt_Create_Test_Suite_Error.Text = "Please Create at least one test suite to get started.";

            this.txt_Create_Test_Suite_Package_Error.Style.Add("color", "red");
            this.txt_Create_Test_Suite_Package_Error.Text = "Please add at least one package to the unit test to get started.";
        }

    }

    private void load_test_suite_data()
    {
        // Get all the test from the database.
        string sql = "SELECT * FROM test_suites;";
        DataTable dt = ExecuteMySqlAdapter(sql);

        // Expose the <DefaultView> of the result.
        this.lb_Test_Suites.DataSource = dt;
        this.lb_Test_Suites.DataBind();
    }

    private void load_test_suite_package_data()
    {
        // Update the lb_Test_Suite_Packages

        // Get all the test from the database.
        string sql = "SELECT packages.id,name " +
            "FROM packages,test_suite_packages as tsa " +
            "where tsa.id =" + lb_Test_Suites.SelectedValue + " AND tsa.p_id = packages.id;";
        
        DataTable dt = ExecuteMySqlAdapter(sql);

        // Expose the <DefaultView> of the result.
        this.lb_Test_Suite_Packages.DataSource = dt;
        this.lb_Test_Suite_Packages.DataBind();

        if (lb_Test_Suite_Packages.Width.Value < Unit.Pixel(180).Value)
            lb_Test_Suite_Packages.Width = Unit.Pixel(180);

        // Update the ddl_Add_Existing_Test_Suite_Package

        sql = "SELECT * FROM packages";
        dt = ExecuteMySqlAdapter(sql);

        this.ddl_Add_Existing_Test_Suite_Package.DataSource = dt;
        this.ddl_Add_Existing_Test_Suite_Package.DataBind();

        this.ddl_Add_Existing_Test_Suite_Package.Items.Insert(0, "Choose an Existing Package to Add it . . . ");
    }

    private void load_unit_test_data()
    {
        // Load the ddl_Add_Package_Unit_Test

        string sql = "SELECT * FROM unittestdesc;";
        DataTable dt = ExecuteMySqlAdapter(sql);

        this.ddl_Add_Package_Unit_Test.DataSource = dt;
        this.ddl_Add_Package_Unit_Test.DataBind();

        this.ddl_Add_Package_Unit_Test.Items.Insert(0, "Please select an existing Unit Test to Add it . . . ");

        // Load the lb_Unit_Test
        sql = "SELECT utid,name " +
            "FROM unittestdesc as utd,packages_unit_tests as put " + 
            "WHERE put.id = " + this.lb_Test_Suite_Packages.SelectedValue + " and put.ut_id = utd.utid;";
        dt = ExecuteMySqlAdapter(sql);

        // Expose the <DefaultView> of the result.
        this.lb_Unit_Tests.DataSource = dt;
        this.lb_Unit_Tests.DataBind();

        if (lb_Unit_Tests.Width.Value < Unit.Pixel(180).Value)
            lb_Unit_Tests.Width = Unit.Pixel(180);
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
            if (this.txt_Create_Test_Suite.Text.Length < 3)
                throw new FormatException("Please be sure the name is more than three characters.");
            string sql = @"CALL insert_test_suite('" + txt_Create_Test_Suite.Text + "');";
            ExecuteMySql(sql);
            txt_Create_Test_Suite_Error.Text = "";
        }
        catch (FormatException ex)
        {
            txt_Create_Test_Suite_Error.Style.Add("color", "red");
            txt_Create_Test_Suite_Error.Text = ex.Message;
        }
        catch
        {
            txt_Create_Test_Suite_Error.Style.Add("color", "red");
            txt_Create_Test_Suite_Error.Text = "There was a problem adding the Test Suite. <br /> This probably means there was already a Test Suite with that name. ";
        }

        // Could turn this into out parameters and append to the 
        // end of lb_Test_Suites - rather than rehitting the database
        load_test_suite_data();

        
    }

    protected void OnClick_btn_Create_Test_Suite_Package(object sender, EventArgs e)
    {
        try
        {
            if (this.txt_Create_Test_Suite_Package.Text.Length < 3)
                throw new ArgumentException("Please be sure the package name is more than three characters.");
            
            if (this.lb_Test_Suites.SelectedIndex < 0)
            {
                // If there is only one, we know which one they want
                if (this.lb_Test_Suites.Items.Count == 1)
                    this.lb_Test_Suites.SelectedIndex = 0;
                else
                    throw new ArgumentException("I am not sure which Test Suite you " + 
                        "would like to add this package to. <br />" + 
                        "Please click on a test suite name.");
            }


            string sql = @"CALL insert_test_suite_package('" + lb_Test_Suites.SelectedValue + "','" + 
                txt_Create_Test_Suite_Package.Text + "');";
            ExecuteMySql(sql);
            txt_Create_Test_Suite_Package_Error.Text = "";
        }
        catch (ArgumentException ae)
        {
            txt_Create_Test_Suite_Package_Error.Style.Add("color", "red");
            txt_Create_Test_Suite_Package_Error.Text = ae.Message;
        }
        catch
        {
            txt_Create_Test_Suite_Package_Error.Style.Add("color", "red");
            txt_Create_Test_Suite_Package_Error.Text = "There was a problem adding the Test Suite Package. <br />" + 
                "This probably means there was already a package with that name. <br />";
        }

        load_test_suite_package_data();
    }

    protected void OnChange_lb_Test_Suite_Packages(object sender, EventArgs e)
    {
        load_unit_test_data();
    }

    protected void OnChange_ddl_Add_Existing_Test_Suite_Package(object sender, EventArgs e)
    {
        try
        {
            string sql = @"CALL insert_test_suite_package_existing('" +
                this.lb_Test_Suites.SelectedValue + "','" +
                this.ddl_Add_Existing_Test_Suite_Package.SelectedValue + "');";
            ExecuteMySql(sql);
            this.txt_Create_Test_Suite_Package_Error.Text = "";
        }
        catch
        {
            this.txt_Create_Test_Suite_Package_Error.Style.Add("color", "red");
            this.txt_Create_Test_Suite_Package_Error.Text = "There was a problem adding the Package. <br />" +
                "Please check to ensure the Test Suite does not " + 
                "already contain a Package named " +
                this.ddl_Add_Existing_Test_Suite_Package.SelectedItem.Text + "<br />";
        }

        load_test_suite_package_data();
    }

    protected void OnChange_ddl_Add_Package_Unit_Test(object sender, EventArgs e)
    {
        try
        {
            string sql = @"CALL insert_package_unit_test('" +
                this.lb_Test_Suite_Packages.SelectedValue + "','" +
                this.ddl_Add_Package_Unit_Test.SelectedValue + "');";
            ExecuteMySql(sql);
            this.txt_Add_Package_Unit_Test_Error.Text = "";
        }
        catch
        {
            this.txt_Add_Package_Unit_Test_Error.Style.Add("color", "red");
            this.txt_Add_Package_Unit_Test_Error.Text = "There was a problem adding the Unit Test. <br />" +
                "Please check to ensure the Package does not " +
                "already contain a Unit Test named " +
                this.ddl_Add_Package_Unit_Test.SelectedItem.Text + "<br />";
        }

        load_unit_test_data();
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
        txt_Unit_Test_Details_Description.Text = row["desc"].ToString();
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
        da.Fill(ds);

        conn.Close();
        return ds.Tables[0];
    }

    private void ExecuteMySql(string sql)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        MySqlCommand comm = new MySqlCommand(sql, conn);
        conn.Open();
        comm.ExecuteNonQuery();
        conn.Close();

    }

    private DataRow ExecuteMySqlRow(string sql)
    {
        MySqlConnection conn = new MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
        conn.Open();

        MySqlDataAdapter da = new MySqlDataAdapter(sql, conn);
        DataSet ds = new DataSet();
        da.Fill(ds);

        conn.Close();

        return ds.Tables[0].Rows[0];
    }

}