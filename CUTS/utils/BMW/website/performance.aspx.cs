// -*- C# -*-

//=============================================================================
/**
 * @file      performance.aspx.cs
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

using System;
using System.Collections;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using System.Text;

using Actions.UnitTestActions;
using MySql.Data.MySqlClient;

namespace CUTS
{
  //===========================================================================
  /**
   * @class Components
   *
   * Code-behind implemetation for the Component_Instances.aspx
   * page.
   */
  //===========================================================================

  public partial class Performance : System.Web.UI.Page
  {
    /**
     * Concrete master page for this page.
     */
    private CUTS.Master master_;

    public int TestNumber
    {
      get { return this.test_number_; }
    }

    /**
     * Get the current collection time for the page. This is the
     * same time submitted in the query string.
     */
    public DateTime CollectionTime
    {
      get { return this.collection_time_; }
    }

    /**
     * Callback method for when the page is loading.
     *
     * @param[in]       sender        Sender of the event.
     * @param[in]       e             Event arguments.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      MySqlConnection conn = new MySqlConnection (ConfigurationManager.AppSettings ["MySQL"]);

      try
      {
        // Open the connection to the database.
        conn.Open ();

        // Create a new database object for this page.
        this.database_ =
          new CUTS.Data.Database (conn, new CUTS.Data.MySqlDataAdapterFactory ());

        // Get the test number from the query string.
        String value = Request.QueryString ["t"];

        if (value != null)
          this.test_number_ = System.Int32.Parse (value);

        this.master_ = (CUTS.Master)Master;

        if (!this.Page.IsPostBack)
        {
          // Load the collection times into the control
          this.load_collection_times ();

          // Since this isn't a postback, we are going to show the
          // latest collection time for this test.
          this.collection_time_ =
            this.database_.get_latest_collection_time (this.test_number_);

          DataSet ds = new DataSet ();
          this.database_.get_critical_paths (ref ds);
          this.execution_path_.DataSource = ds;
          this.execution_path_.DataMember = "Table";
          this.execution_path_.DataBind ();

          this.collection_times_.SelectedValue = this.collection_time_.ToString ();
          this.load_execution_times ();
        }
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
      }
    }

    /**
     * Get a listing of all the collection times for the
     * current test.
     */
    private void load_collection_times ()
    {
      // Get the collection times from the database
      DataSet ds = new DataSet ();
      this.database_.get_collection_times (this.test_number_, ref ds);

      // Bind the results to the control.
      this.collection_times_.DataSource = ds;
      this.collection_times_.DataMember = "Table";
      this.collection_times_.DataBind ();
    }

    private void load_execution_times ()
    {
      if (this.database_ == null)
        return;

      DataSet ds = new DataSet ();

      // Get all the execution times from the database.
      this.database_.get_execution_times (this.test_number_,
                                          this.collection_time_,
                                          ref ds);

      // Get the baseline metrics from the database.
      //this.database_.get_baseline_data(this.test_number_,
      //                               this.collection_time_,
      //                               ref ds, "baseline");

      // Bind the metrics to the system performance control.
      this.sysperf_.DataSource = ds;
      this.sysperf_.DataMember = "Table";

      //this.sysperf_.DataMemberBaseline = "baseline";
      //this.sysperf_.DataBind();
    }

    private void load_cumulative_times ()
    {
      DataSet ds = new DataSet ();

      // Get the cumulative performance metrics for this test.
      this.database_.select_execution_time_cumulative (this.test_number_,
                                                    ref ds);

      // Bind the cumulative metrics to the control.
      this.cumulative_sysperf_.DataSource = ds;
      this.cumulative_sysperf_.DataMember = "Table";
      this.cumulative_sysperf_.DataBind ();
    }
    private void load_unit_test_view ()
    {
      DataTable table = UnitTestActions.get_all_test_suites();

      ddl_Test_Suites.DataSource = table;
      ddl_Test_Suites.DataBind ();

      ddl_Test_Suites.Items.Insert (0, new ListItem ("Choose a Test Suite to see results . . .    ", "-1"));
    }
    
    private void load_log_messages_view ()
    {
      string test_number = Request.QueryString["t"];
      if (test_number == null)
        return;

      DataTable dt = UnitTestActions.get_test_messages( test_number );
      this.current_test_messages_.DataSource = dt;
      this.current_test_messages_.DataBind();
    }

    protected void on_collection_time_changed (Object sender, EventArgs e)
    {
      this.collection_time_ =
        DateTime.Parse (this.collection_times_.SelectedValue);

      try
      {
        this.load_execution_times ();
      }
      catch (Exception ex)
      {
        this.master_.show_error_message (ex.Message);
      }
    }

    protected void OnChange_ddl_Test_Suites (object sender, EventArgs e)
    {
      if (ddl_Test_Suites.SelectedIndex != 0)
      {
        // Clear out Panel
        this.panel_Packages_Unit_Tests.Controls.Clear ();

        // Load new Panel Data
        this.load_panel_Packages_Unit_Tests ();
      }
      else
      {
        this.master_.show_error_message ("Please select a valid test suite");
      }
    }

    private void load_panel_Packages_Unit_Tests ()
    {
      DataTable dt = UnitTestActions.get_packages( ddl_Test_Suites.SelectedValue );
 
      // An explicit cast to string will not work here
      //   because the adapter types the column to int
      foreach (DataRow row in dt.Rows)
        Add_Package( row["id"].ToString() );
    }

    private void Add_Package (string p_id)
    {
      DataRow package_info = UnitTestActions.get_package_info( p_id );
      string Package_Name = (string)package_info["name"];

      // Add Package Title
      Label Title = new Label ();
      panel_Packages_Unit_Tests.Controls.Add (Title);
      Title.Text = Package_Name;
      Title.CssClass = "performance-ut_view-package_name";

      // Add hr
      panel_Packages_Unit_Tests.Controls.Add (new LiteralControl ("<hr />"));


      // Fill the DataTable with Name and id
      DataTable dt = UnitTestActions.get_unit_tests( p_id );

      // Add Evaluation, Result
      //dt.Columns.Add ("Evaluation");
      dt.Columns.Add ("Result");
      dt.Columns.Add ("Chart");

      // Ensure package has at least one Unit Test
      if (dt.Rows.Count < 1)
        return;

      string evaluation = String.Empty;

      foreach (DataRow row in dt.Rows)
      {

        DataTable temp =
          UnitTestActions.evaluate_unit_test (this.test_number_,
                                              (int)row["id"],
                                              true,
                                              ref evaluation);

        // Evaluate
        //DataTable temp =
        //  UnitTestActions.Evalate_UT_for_single_test  (Int32.Parse (row ["id"].ToString ()), this.test_number_);

        if (temp.Rows.Count == 0)
        {
          master_.show_info_message ("Oops - Looks like there is no data for '" + row ["Name"].ToString () +
              "' in '" + Package_Name + "'");
          //row ["Evaluation"] = "No Data";
          row ["Result"] = "No Data";
          row ["Chart"] = @"<a href='unittestchart.aspx?utid=" + row ["id"].ToString () +
              "'>Chart</a>";
        }
        else
        {
          DataRow temp_Row = temp.Rows [0];

          // Add Results of Evaluation to Main Table
          //row ["Evaluation"] = temp_Row ["evaluation"];
          row ["Result"] = temp_Row ["result"];

          row["Chart"] =
            "<a href='unittestchart.aspx?utid=" + row["id"].ToString () +
            "&t=" + this.test_number_ + "'>view dataset</a>";
        }
      }


      // Add the DataGrid
      DataGrid dg = new DataGrid ();
      panel_Packages_Unit_Tests.Controls.Add (dg);
      dg.AlternatingItemStyle.CssClass = "alternate-row";
      dg.Width = new Unit (100, UnitType.Percentage);
      dg.CssClass = "performance-ut-grid";

      // Bind the DataGrid
      dg.DataSource = dt;
      dg.DataBind ();

      // Add  few spaces
      panel_Packages_Unit_Tests.Controls.Add (new LiteralControl ("<br /><br />"));
    }

    #region Event Handlers
    protected void handle_on_command (Object sender, CommandEventArgs e)
    {
      if (e.CommandName == "viewpath")
      {
        String url = String.Format ("~/Critical_Path_Timeline.aspx?t={0}&p={1}",
                                    this.test_number_,
                                    this.execution_path_.SelectedValue);

        this.Response.Redirect (url);
      }
    }

    protected void handle_onmenuitemclick (Object sender, MenuEventArgs e)
    {
      this.multiview_.ActiveViewIndex = int.Parse (e.Item.Value);
    }

    protected void handle_onactiveviewchanged (Object sender, EventArgs e)
    {
      switch (this.multiview_.ActiveViewIndex)
      {
        case 0:
          if (this.Page.IsPostBack)
          {
            if (this.collection_times_.SelectedIndex != -1)
              this.collection_time_ = DateTime.Parse (this.collection_times_.SelectedValue);
          }
          this.load_execution_times ();

          break;

        case 1:
          this.load_cumulative_times ();
          break;

        case 2:
          this.load_unit_test_view();  
          break;

        case 3:
          this.load_log_messages_view();
          break;
      }
    }
    #endregion

    /**
     * Button handler for the current log formats view that 
     *   will export the datagrid on that view in the chosen format. 
     */
    protected void onclick_export ( object sender, EventArgs e )
    {
      string export_type = this.export_type_.SelectedValue;

      switch (export_type)
      {
        case "excel":
          this.export_current_test_messages( "excel" );
          break;
        case "word":
          this.export_current_test_messages( "word" );
          break;
      }
    }
    /**
     * Helper function to export the current test's
     *   log messages into excel format.
     */
    private void export_current_test_messages ( string type)
    {
      // Empty the buffer
      Response.ClearContent();

      // Generate filename
      string filename = "Test_";
      string test_number = Request.QueryString["t"];
      if (test_number != null)
        filename += test_number;
      filename += "_Log_Messages";

      // Set filetype
      if (type == "excel")
        filename += ".xls";
      else if (type == "word")
        filename += ".doc";

      // Set the content header
      Response.AddHeader( "content-disposition", "attachment; filename=" + filename );

      // Set the content type
      if (type == "excel")
        Response.ContentType = "application/ms-excel";
      else if (type == "word")
        Response.ContentType = "application/msword";

      // Ensure this is never cached
      Response.Cache.SetCacheability( HttpCacheability.NoCache );

      // Build appropriate writers
      System.IO.StringWriter stringWrite = new System.IO.StringWriter();
      HtmlTextWriter htmlWrite = new HtmlTextWriter( stringWrite );

      // Render DataGrid
      this.current_test_messages_.RenderControl( htmlWrite );

      // Send to user
      Response.Write( stringWrite.ToString() );
      Response.End();
    }

    #region Web Form Designer generated code
    override protected void OnInit (EventArgs e)
    {
      // Initialize the component.
      InitializeComponent ();

      // Pass control to the base class.
      base.OnInit (e);
    }

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent ()
    {
      this.Load += new System.EventHandler (this.Page_Load);
    }
    #endregion

    #region Member Variable
    /// Utility class for interacting with the CUTS database.
    private CUTS.Data.Database database_;

    /// The current test number for the performance metrics.
    private int test_number_;

    /// The current collection time for the performance metrics.
    private DateTime collection_time_;
    #endregion
  }
}
