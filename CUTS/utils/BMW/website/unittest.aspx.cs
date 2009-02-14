// -*- C# -*-

//=============================================================================
/**
 * @file            unittest.aspx.cs
 *
 * $Id$
 *
 * @author          Hamilton Turner
 */
//=============================================================================

using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.Common;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using MySql.Data.MySqlClient;
using Actions.UnitTestActions;
using Actions.LogFormatActions;
using CUTS.Web.UI;
using CUTS.Web.UI.UnitTest;
using CUTS.Data.UnitTesting;

namespace CUTS.Web.Page
{
  public partial class UnitTesting : System.Web.UI.Page
  {
    public UnitTesting ()
    {
      // Instantiate a connection to the database.
      ConnectionStringSettings settings =
        ConfigurationManager.ConnectionStrings["BMWConnectionString"];

      this.database_ = new CUTS.BMW.Database (settings.ProviderName);
      this.database_.ConnectionString = settings.ConnectionString;
    }

    protected void Page_Load (object sender, EventArgs e)
    {
      this.master_ = (CUTS.Master)Master;
    }

   /**
    * Helper method to load all the test suites from the database
    * into the existing test suites listbox.
    */
    private void load_existing_test_suites ()
    {
      try
      {
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        this.load_existing_test_suites_i ();
      }
      catch (Exception e)
      {
        this.master_.Console.Add (e);
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    private void load_existing_test_suites_i ()
    {
      // Query for the existing test suites.
      DataTable suites = new DataTable ();
      this.database_.SelectUnitTestSuites (ref suites);

      // Bind the data table to the control.
      this.existing_test_suites_.DataSource = suites;
      this.existing_test_suites_.DataTextField = "name";
      this.existing_test_suites_.DataValueField = "id";
      this.existing_test_suites_.DataBind ();
    }

    /**
     * Loads all of the packages currently in the
     *   database into the existing packages dropdownlist.
     */
    private void load_existing_packages (int suite)
    {
      // Query the database for the packages.
      DataTable packages = new DataTable ();
      this.database_.SelectTestPackages (suite, ref packages);

      // Bind the data to the control.
      this.existing_test_packages_.DataSource = packages;
      this.existing_test_packages_.DataValueField = "tspid";
      this.existing_test_packages_.DataTextField = "name";
      this.existing_test_packages_.DataBind ();
    }

    /**
     * Loads all of the unit tests currently in
     *   the database into the existing unit tests dropdownlist.
     */
    private void load_existing_unit_tests (int package)
    {
      // First, get the existing unit test in this package.
      DataTable tests = new DataTable ();
      this.database_.SelectUnitTests (package, ref tests);

      this.existing_unit_tests_.DataSource = tests;
      this.existing_unit_tests_.DataTextField = "name";
      this.existing_unit_tests_.DataValueField = "tpiid";
      this.existing_unit_tests_.DataBind ();

      // Now, get the unused test in the package.
      DataTable unused = new DataTable ();
      this.database_.SelectUnusedUnitTests (package, ref unused);
      this.unused_unit_tests_.DataSource = unused;
      this.unused_unit_tests_.DataValueField = "utid";
      this.unused_unit_tests_.DataTextField = "name";
      this.unused_unit_tests_.DataBind ();
    }

    /**
     * Helper method to load the test suites from the database.
     */
    private void load_test_suites ()
    {
      if (this.master_ == null)
        this.master_ = (CUTS.Master)this.Page.Master;

      try
      {
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        DataTable suites = new DataTable ();
        this.database_.SelectUnitTestSuites (ref suites);

        ListItem item;

        foreach (DataRow row in suites.Rows)
        {
          item = new ListItem (row["name"].ToString (), row["id"].ToString ());
          this.existing_test_suites_.Items.Add (item);
        }
      }
      catch (Exception e)
      {
        this.master_.Console.Add (e);
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    private void load_log_formats ()
    {
      if (this.master_ == null)
        this.master_ = (CUTS.Master)this.Page.Master;

      try
      {
        // Open the connection to the database.
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        // Select the log formats from the table.
        DbDataReader reader = this.database_.SelectLogFormatReader ();

        try
        {
          if (reader.HasRows)
          {
            // Get the ordinals of the columns in the table.
            int lfid = reader.GetOrdinal ("lfid");
            int lfmt = reader.GetOrdinal ("lfmt");
            LogFormat lf;

            while (reader.Read ())
            {
              // Create a new log format.
              lf = new LogFormat (reader.GetInt32 (lfid),
                                  reader.GetString (lfmt));

              // Insert the log format into the manager.
              this.lf_manager_.Add (lf);
            }
          }
        }
        finally
        {
          // Make sure the reader is closed.
          if (!reader.IsClosed)
            reader.Close ();
        }
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
      finally
      {
        // Make sure the database collection if closed.
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    /**
     * Button handler function that attempts to create a new test suite,
     *   reload the listbox containing the suites if it
     *   is created, and select the TS just created.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_create_test_suite (object sender, EventArgs e)
    {
      string name = this.test_suite_name_.Text;

      try
      {
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        // Create the new test suite.
        this.database_.CreateTestSuite (name);
        this.master_.Console.Add (MessageSeverity.Info,
                                  "Successfully created test suite: " + name);

        // Clear the name of the test suite.
        this.test_suite_name_.Text = String.Empty;

        // Update the list of existing test suites.
        this.load_existing_test_suites_i ();
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
        this.master_.Console.Add (MessageSeverity.Error,
                                  "Failed to create test suite " + name);
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    /**
     * Button handler function that attempts to create a new test
     *   package, reload the existing package list, and select the
     *   package just created. An error is shown if the creation
     *   fails. There are minor bugs in this function that could
     *   occur if a test package is created, but fails to insert.
     *   The user interface might not be fully updated. The fix
     *   is to revamp this function.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_create_test_package (object sender, EventArgs e)
    {
      if (this.master_ == null)
        this.master_ = (CUTS.Master)this.Page.Master;


      try
      {
        string name = this.test_package_name_.Text;

        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        // Create the test package
        Int32 id = Int32.Parse (this.existing_test_suites_.SelectedValue);
        this.database_.CreateTestPackage (id, name);

        // Show info message
        string msg = "Successfully created test package: " + name;
        this.master_.Console.Add (MessageSeverity.Info, msg);

        this.test_package_name_.Text = String.Empty;

        // Load the existing test packages.
        this.load_existing_packages (id);
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
        this.master_.Console.Add (MessageSeverity.Error, "Failed to create test package");
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    /**
     * Button handler function that deletes the selected test suites,
     *   printing out error or success messages as it goes, and reloading
     *   the interface correctly at the end.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_delete_test_suite (object sender, EventArgs e)
    {
      try
      {
        // Delete the test suite from the database.
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        this.delete_test_suite_i ();
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
        this.master_.Console.Add (MessageSeverity.Error, "Failed to delete selected test suite");
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    /**
     * Button handler function that deletes the selected test suites,
     *   printing out error or success messages as it goes, and reloading
     *   the interface correctly at the end.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void delete_test_suite_i ()
    {
      // Delete the test suite from the database.
      Int32 id = Int32.Parse (this.existing_test_suites_.SelectedValue);
      this.database_.DeleteTestSuite (id);

      // Show a message to the user.
      string msg = "Successfully deleted test suite: " +
                   this.existing_test_suites_.SelectedItem.Text;

      this.master_.Console.Add (MessageSeverity.Info, msg);

      // Reload the existing test suites.
      this.load_existing_test_suites_i ();
    }

    /**
     * Button handler function that removes a test package from
     * a test suite, reloads the current package list, and
     * prints an info message.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_remove_test_package (object sender, EventArgs e)
    {
      try
      {
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        int tspid = int.Parse (this.existing_test_packages_.SelectedValue);
        this.database_.DeleteTestSuitePackage (tspid);

        // Reload the existing test packages.
        int suite = int.Parse (this.existing_test_suites_.SelectedValue);
        this.load_existing_packages (suite);
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    /**
     * Button handler function that inserts a unit test into the selected
     * test package, giving confirmation or error messages.
     *
     * @param[in]     sender    The button that sent the click event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onclick_insert_unit_test (object sender, EventArgs e)
    {
      if (this.master_ == null)
        this.master_ = (CUTS.Master)this.Master;

      try
      {
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        int package = int.Parse (this.existing_test_packages_.SelectedValue);
        int utid = int.Parse (this.unused_unit_tests_.SelectedValue);

        this.database_.InsertUnitTest (package, utid);
        this.load_existing_unit_tests (package);
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    protected void onclick_remove_unit_test (object sender, EventArgs e)
    {
      if (this.master_ == null)
        this.master_ = (CUTS.Master)this.Master;

      try
      {
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        int test = int.Parse (this.existing_unit_tests_.SelectedValue);
        this.database_.RemoveUnitTest (test);

        int package = int.Parse (this.existing_test_packages_.SelectedValue);
        this.load_existing_unit_tests (package);
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    /**
     * OnChange handler for the existing test suites list. Checks the
     * selection validity, enables/disables buttons as needed, and
     * then loads the current package list if the test suite selection
     * is valid.
     *
     * @param[in]     sender    The onject that sent the onchange event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onchange_existing_test_suites (object sender, EventArgs e)
    {
      if (this.master_ == null)
        this.master_ = (CUTS.Master)this.Master;

      try
      {
        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        // Query for the existing packages from the database.
        int id = int.Parse (this.existing_test_suites_.SelectedValue);
        this.load_existing_packages (id);
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (ex);
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    /**
     * On Change Handler for the existing test packages. Function
     *   checks to see if the selected test package exists in the current
     *   test packages list, disables/enables appropriate buttons,
     *   and possibly selects the test package in the current test packages
     *   list.
     *
     * @param[in]     sender    The onject that sent the onchange event.
     * @param[in]     e         The EventArgs that were sent with the event.
     */
    protected void onchange_existing_test_packages (object sender, EventArgs e)
    {
      int package = int.Parse (this.existing_test_packages_.SelectedValue);
      this.load_existing_unit_tests (package);
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
          this.load_test_suites ();
          break;

        case 1:
          this.load_log_formats ();
          break;
      }
    }

    /**
     * Event handler for clicking the Create button for a unit test. This will
     * create an entry in the database for the specified information.
     */
    protected void onclick_create_unit_test (object sender, EventArgs e)
    {
      try
      {
        // Create a new unit test definition.
        UnitTestDefinition test = new UnitTestDefinition ();

        test.Name = this.unit_test_name_.Text;
        test.Description = this.unit_test_description_.Text;
        test.LogFormats.AddRange (this.lf_manager_.SelectedItems);
        test.Relations.AddRange (this.lf_manager_.SelectedRelations);
        test.Grouping.AddRange (this.grouping_.Variables);
        test.EvalFunction = this.unit_test_eval_.Text;
        test.AggrFunction = this.aggr_function_.Text;

        if (this.database_.State == ConnectionState.Closed)
          this.database_.Open ();

        // Create the unit test in the database.
        this.database_.CreateNewUnitTest (test);

        this.master_.Console.Add (MessageSeverity.Info, "Successfully created unit test");
        this.reset_unit_test_form ();
      }
      catch (Exception ex)
      {
        this.master_.Console.Add (MessageSeverity.Error, ex.Message);
        this.master_.Console.Add (MessageSeverity.Error, "Failed to create new unit test");
      }
      finally
      {
        if (this.database_.State == ConnectionState.Open)
          this.database_.Close ();
      }
    }

    /**
     * Reset the unit test creation form.
     */
    private void reset_unit_test_form ()
    {
      this.unit_test_name_.Text = String.Empty;
      this.unit_test_description_.Text = String.Empty;
      this.unit_test_eval_.Text = String.Empty;

      this.lf_manager_.Clear ();
      this.grouping_.Clear ();
    }

    private string get_mysql_comparison (string comparison)
    {
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
          master_.Console.Add (MessageSeverity.Error, "The warn or fail comparison had a problem." +
            "Please refresh the page and try again.");
          return String.Empty;
      }
    }

    override protected void OnInit (EventArgs e)
    {
      // Initialize the component.
      this.InitializeComponent ();

      // Pass control to the base class.
      base.OnInit (e);
    }

    private void InitializeComponent ()
    {
      // Set the page load callback.
      this.Load += new System.EventHandler (this.Page_Load);
    }

    private CUTS.BMW.Database database_;

    private CUTS.Master master_;
  }
}