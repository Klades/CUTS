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

using CUTS.Data;
using CUTS.Data.UnitTesting;
using CUTS.Web.UI.UnitTesting;

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

    private MySqlConnection conn_ =
      new MySqlConnection (ConfigurationManager.AppSettings["MySQL"]);

    private UnitTestEvaluator evaluator_;

    /**
     * Unit test actions.
     *
     * @todo Move a lot of this code into the CUTS.Data assembly.
     */
    private UnitTestActions uta_;

    public Performance ()
    {
      // Open the connection to the database.
      this.conn_.Open ();

      // Create a new unit test action object.
      this.uta_ = new UnitTestActions (this.conn_);

      // Create a new evaluator object.
      this.evaluator_ = new UnitTestEvaluator (this.conn_,
                                               new MySqlDataAdapterFactory (),
                                               Server.MapPath ("~/db"));

      // Create a new database object for this page.
      this.database_ = new Database (this.conn_,
                                     new MySqlDataAdapterFactory ());
    }

    /**
     * Callback method for when the page is loading.
     *
     * @param[in]       sender        Sender of the event.
     * @param[in]       e             Event arguments.
     */
    private void Page_Load (object sender, System.EventArgs e)
    {
      this.master_ = (CUTS.Master)Master;

      try
      {
        // Get the test number from the query string.
        String value = Request.QueryString["t"];

        if (value != null)
          this.test_number_ = System.Int32.Parse (value);

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
      DataTable table = this.uta_.get_all_test_suites ();

      ddl_Test_Suites.DataSource = table;
      ddl_Test_Suites.DataBind ();
    }

    private void load_log_messages_view ()
    {
      string test_number = Request.QueryString["t"];
      if (test_number == null)
        return;

      DataTable dt = this.uta_.get_test_messages (test_number);
      this.current_test_messages_.DataSource = dt;
      this.current_test_messages_.DataBind ();
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

    /**
     *
     */
    protected void onclick_evaluate_test_suite (object sender, EventArgs e)
    {
      try
      {
        this.unit_test_panel_.Controls.Clear ();
        this.load_unit_test_panel ();
      }
      catch (Exception ex)
      {
        this.master_.show_exception (ex);
      }
    }

    /**
     *
     */
    private void load_unit_test_panel ()
    {
      try
      {
        DataTable dt = this.uta_.get_packages (ddl_Test_Suites.SelectedValue);

        foreach (DataRow row in dt.Rows)
          this.add_package (row["id"].ToString ());
      }
      catch (Exception ex)
      {
        this.master_.show_exception (ex);
      }
    }

    /**
     *
     */
    private void add_package (string p_id)
    {
      // Get information about the package from the database.
      DataRow package_info = this.uta_.get_package_info (p_id);
      string package_name = (string)package_info["name"];

      TestPackage package = new TestPackage (this.test_number_, package_name);
      this.unit_test_panel_.Controls.Add (package);

      // Fill the DataTable with Name and id
      DataTable dt = this.uta_.get_unit_tests (p_id);

      string eval;
      string[] groups;

      foreach (DataRow row in dt.Rows)
      {
        // Evaluate the unit test.
        int utid = (int)row["id"];

        DataTable data = this.evaluator_.evaluate (this.test_number_,
                                                   utid,
                                                   true,
                                                   out groups,
                                                   out eval);

        if (groups.Length == 0)
        {
          // Create a new result set for the evaluation.
          UnitTestResult result = new UnitTestResult ();
          result.ID = utid;
          result.Name = (string)row["name"];
          result.Result = data.Rows[0]["result"];

          // Insert the result into the package.
          package.Add (result);
        }
        else
        {
          UnitTestGroupResult group_result = new UnitTestGroupResult ();
          group_result.ID = utid;
          group_result.Name = (string)row["name"];

          foreach (DataRow group_data in data.Rows)
          {
            UnitTestResult partial = new UnitTestResult ();

            // Get the actual names in this group.
            ArrayList name_list = new ArrayList ();

            foreach (string grp_name in groups)
              name_list.Add (group_data[grp_name]);

            // Construct the actual name of the group.
            partial.Name = String.Join (".", (string [])name_list.ToArray (typeof (string)));
            partial.Result = group_data["result"];

            // Create a new group to the result set.
            group_result.Add (partial);
          }

          // Insert the group result into the package.
          package.Add (group_result);
        }
      }

      // Bind the data in the package.
      package.DataBind ();
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
          this.load_unit_test_view ();
          break;

        case 3:
          this.load_log_messages_view ();
          break;
      }
    }
    #endregion

    /**
     * Button handler for the current log formats view that will export the
     * datagrid on that view in the chosen format.
     */
    protected void onclick_export (object sender, EventArgs e)
    {
      string export_type = this.export_type_.SelectedValue;

      switch (export_type)
      {
        case "excel":
          this.export_current_test_messages ("excel");
          break;
        case "word":
          this.export_current_test_messages ("word");
          break;
      }
    }
    /**
     * Helper function to export the current test's
     *   log messages into excel format.
     */
    private void export_current_test_messages (string type)
    {
      // Empty the buffer
      Response.ClearContent ();

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
      Response.AddHeader ("content-disposition", "attachment; filename=" + filename);

      // Set the content type
      if (type == "excel")
        Response.ContentType = "application/ms-excel";
      else if (type == "word")
        Response.ContentType = "application/msword";

      // Ensure this is never cached
      Response.Cache.SetCacheability (HttpCacheability.NoCache);

      // Build appropriate writers
      System.IO.StringWriter stringWrite = new System.IO.StringWriter ();
      HtmlTextWriter htmlWrite = new HtmlTextWriter (stringWrite);

      // Render DataGrid
      this.current_test_messages_.RenderControl (htmlWrite);

      // Send to user
      Response.Write (stringWrite.ToString ());
      Response.End ();
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
    protected int test_number_;

    /// The current collection time for the performance metrics.
    protected DateTime collection_time_;
    #endregion
  }
}
