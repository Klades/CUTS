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
using Actions;

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
     * Get the current test number for the page. This is the same
     * test number submitted in the query string.
     *
     * @return      Current test number.
     */
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
    private void Page_Load(object sender, System.EventArgs e)
    {
      // Get the test number from the query string.
      String value = Request.QueryString["t"];

      if (value != null)
        this.test_number_ = System.Int32.Parse(value);

      if (!this.Page.IsPostBack)
      {
        // Load the collection times into the control
        this.load_collection_times();

        // Load Unit Test View
        load_unit_test_view();

        try
        {
          // Since this isn't a postback, we are going to show the
          // latest collection time for this test.
          this.collection_time_ =
            this.cutsdb_.get_latest_collection_time(this.test_number_);

          DataSet ds = new DataSet();
          this.cutsdb_.get_critical_paths(ref ds);
          this.execution_path_.DataSource = ds;
          this.execution_path_.DataMember = "execution_paths";
          this.execution_path_.DataBind();

          this.collection_times_.SelectedValue = this.collection_time_.ToString();
          this.load_execution_times();
        }
        catch (Exception ex)
        {
          this.show_error_message(ex.StackTrace);
        }
      }
    }

    /**
     * Get a listing of all the collection times for the
     * current test.
     */
    private void load_collection_times()
    {
      // Get the collection times from the database
      DataSet ds = new DataSet();
      this.cutsdb_.get_collection_times (this.test_number_, ref ds);

      // Bind the results to the control.
      this.collection_times_.DataSource = ds;
      this.collection_times_.DataMember = "collection_time";
      this.collection_times_.DataBind();
    }

    private void load_execution_times()
    {
      DataSet ds = new DataSet();

      // Get all the execution times from the database.
      this.cutsdb_.get_execution_times(this.test_number_,
                                       this.collection_time_,
                                       ref ds, "execution_time");

      // Get the baseline metrics from the database.
      //this.cutsdb_.get_baseline_data(this.test_number_,
      //                               this.collection_time_,
      //                               ref ds, "baseline");

      // Bind the metrics to the system performance control.
      this.sysperf_.DataSource = ds;
      this.sysperf_.DataMember = "execution_time";

      //this.sysperf_.DataMemberBaseline = "baseline";
      //this.sysperf_.DataBind();
    }

    private void load_cumulative_times()
    {
      DataSet ds = new DataSet();

      // Get the cumulative performance metrics for this test.
      this.cutsdb_.select_execution_time_cumulative(this.test_number_,
                                                    ref ds,
                                                    "cumulative");

      // Bind the cumulative metrics to the control.
      this.cumulative_sysperf_.DataSource = ds;
      this.cumulative_sysperf_.DataMember = "cumulative";
      this.cumulative_sysperf_.DataBind();
    }
    private void load_unit_test_view()
    {
        string sql = "SELECT * FROM test_suites";
        DataTable dt_ = ExecuteMySqlAdapter(sql);

        ddl_Test_Suites.DataSource = dt_;
        ddl_Test_Suites.DataBind();

        ddl_Test_Suites.Items.Insert(0, new ListItem("Choose a Test Suite to see results . . .    ", "-1"));
    }

    protected void on_collection_time_changed(Object sender, EventArgs e)
    {
      this.collection_time_ =
        DateTime.Parse(this.collection_times_.SelectedValue);

      try
      {
        this.load_execution_times();
      }
      catch (Exception ex)
      {
        this.show_error_message(ex.Message);
      }
    }

    protected void OnChange_ddl_Test_Suites(object sender, EventArgs e)
    {
        if (ddl_Test_Suites.SelectedIndex < 1)
        {
            show_error_message("Please choose another Test Suite. That one is not valid. ");
        }
        
        // Clear out Panel
        panel_Packages_Unit_Tests.Controls.Clear();

        
        // Load new Panel Data
        load_panel_Packages_Unit_Tests();
    }
      private void load_panel_Packages_Unit_Tests()
      {
          string sql = "SELECT p_id FROM test_suite_packages WHERE id=" + ddl_Test_Suites.SelectedValue + ";";
          Array p_ids = ExecuteMySqlReader(sql, "p_id");
          foreach (object CurrentPID in p_ids)
              Add_Package(CurrentPID.ToString());
                }
      private void Add_Package(string p_id)
      {
          string sql = "SELECT name FROM packages WHERE id=" + p_id;
          string Package_Name = ExecuteMySqlScalar(sql).ToString();

          // Add Package Title
          Label Title = new Label();
          panel_Packages_Unit_Tests.Controls.Add(Title);
          Title.Text = Package_Name;

          // Add hr
          panel_Packages_Unit_Tests.Controls.Add(new LiteralControl("<hr />"));

          // Fill the DataTable with Name and id
          sql = "SELECT utid AS id,name AS Name FROM unittestdesc " +
              "WHERE utid IN (SELECT ut_id FROM packages_unit_tests WHERE id=" + p_id + ");";
          DataTable dt = ExecuteMySqlAdapter(sql);
          
          // Add Evaluation, Result
          dt.Columns.Add("Evaluation");
          dt.Columns.Add("Result");
          UnitTestActions uta = new UnitTestActions();
          
          // For each Unit Test
          foreach (DataRow row in dt.Rows)
          {
              // Evaluate
              DataTable temp = uta.Eval_UT(Int32.Parse(row["id"].ToString()));
              DataRow temp_Row = temp.Rows[0];
              
              // Add Results of Evaluation to Main Table
              row["Evaluation"] = temp_Row["evaluation"];
              row["Result"] = temp_Row["result"];
          }
          

          // Add the DataGrid
          DataGrid dg = new DataGrid();
          panel_Packages_Unit_Tests.Controls.Add(dg);


          // Bind the DataGrid
          dg.DataSource = dt;
          dg.DataBind();
      }

    #region Event Handlers
    protected void handle_on_command(Object sender, CommandEventArgs e)
    {
      if (e.CommandName == "viewpath")
      {
        String url = String.Format ("~/Critical_Path_Timeline.aspx?t={0}&p={1}",
                                    this.test_number_,
                                    this.execution_path_.SelectedValue);

        this.Response.Redirect(url);
      }
    }

    protected void handle_onmenuitemclick(Object sender, MenuEventArgs e)
    {
      this.multiview_.ActiveViewIndex = int.Parse (e.Item.Value);
    }

    protected void handle_onactiveviewchanged(Object sender, EventArgs e)
    {
      switch (this.multiview_.ActiveViewIndex)
      {
        case 0:
          if (this.Page.IsPostBack)
            this.collection_time_ = DateTime.Parse(this.collection_times_.SelectedValue);

          this.load_execution_times();
          break;

        case 1:
          this.load_cumulative_times();
          break;

        case 2:
          // INSERT CODE HERE TO UPDATE THE UNIT TEST VIEW. IT WOULD BE BEST TO
          // CREATE A PRIVATE FUNCTION THAT IS INVOKED TO UPDATE YOUR VIEW
          // ACCORDINGLY. DONT FOLLOW THE METHOD ABOVE SINCE ITS NOT THE BEST. ;-)
          break;
      }
    }
    #endregion
    /**
     * Show an error message. This formats the message
     * and displays it to the user.
     *
     * @param[in]     message       Message to show.
     */
    private void show_error_message(string message)
    {
      Label label = (Label) this.Master.FindControl("message_");

      label.Text = message;
      label.ForeColor = Color.Red;
    }
      private DataTable ExecuteMySqlAdapter(string sql)
      {
          MySql.Data.MySqlClient.MySqlConnection conn = new MySql.Data.MySqlClient.MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
          conn.Open();

          MySql.Data.MySqlClient.MySqlDataAdapter da = new MySql.Data.MySqlClient.MySqlDataAdapter(sql, conn);
          DataSet ds = new DataSet();
          da.Fill(ds);

          conn.Close();
          return ds.Tables[0];
      }
      private Array ExecuteMySqlReader(string sql, string ColumnName)
      {
          MySql.Data.MySqlClient.MySqlConnection conn = new MySql.Data.MySqlClient.MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
          MySql.Data.MySqlClient.MySqlCommand comm = new MySql.Data.MySqlClient.MySqlCommand(sql, conn);
          conn.Open();
          MySql.Data.MySqlClient.MySqlDataReader r = comm.ExecuteReader();

          ArrayList al = new ArrayList();
          while (r.Read())
              al.Add(r.GetString(ColumnName).ToString());

          conn.Close();
          return al.ToArray();
      }

      private object ExecuteMySqlScalar(string sql)
      {
          MySql.Data.MySqlClient.MySqlConnection conn = new MySql.Data.MySqlClient.MySqlConnection(ConfigurationManager.AppSettings["MySQL"]);
          MySql.Data.MySqlClient.MySqlCommand comm = new MySql.Data.MySqlClient.MySqlCommand(sql, conn);
          conn.Open();
          object obj = comm.ExecuteScalar();
          conn.Close();
          return obj;
      }
        

#region Web Form Designer generated code
    override protected void OnInit(EventArgs e)
    {
      // Initialize the component.
      InitializeComponent();

      // Pass control to the base class.
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

    #region Member Variables
    /// Utility class for interacting with the CUTS database.
    private CUTS.Data.Database cutsdb_ =
      new CUTS.Data.Database(ConfigurationManager.AppSettings["MySQL"]);

    /// The current test number for the performance metrics.
    private int test_number_;

    /// The current collection time for the performance metrics.
    private DateTime collection_time_;
    #endregion
  }
}
